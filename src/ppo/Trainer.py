import torch
import torch.nn.functional as F
import torch.optim as optim
from TrajectoryCollector import TrajectoryCollector
from Timing import PerformaceTimer
from PPO import PPO
import csv

EPISODE_LOGGING_FREQUENCY = 5

class EpisodeMemory:
    def __init__(self, device: str):
        self.reset()
        self.device = device

    def reset(self):
        self.boards, self.pieces, self.rewards, self.actions, self.action_probs, self.state_values = \
            [], [], [], [], [], []

    def store(
        self,
        boards: torch.Tensor,
        pieces: torch.Tensor,
        rewards: torch.Tensor,
        actions: torch.Tensor,
        action_probs: torch.Tensor, 
        state_values: torch.Tensor
    ) -> None:

        self.boards.append(boards.to(self.device))
        self.pieces.append(pieces.to(self.device))
        self.rewards.append(rewards.to(self.device))
        self.actions.append(actions.to(self.device))
        self.action_probs.append(action_probs.to(self.device))
        self.state_values.append(state_values.to(self.device))

    def get_episode(self, episode: int) -> list[torch.Tensor]:
        return self.boards[episode], self.pieces[episode], self.rewards[episode], \
            self.actions[episode], self.action_probs[episode], self.state_values[episode]

class TetrisPPOTrainer:
    def __init__(
        self,
        num_episodes: int,
        max_episode_length: int,
        *,
        learning_rate: float = 1e-3,
        discount: float = 0.95,
        gae_lambda: float = 0.95,
        epsilon: float = 0.2,
        alpha: float = 0.5,
        beta: float = 1e-3,
        num_workers: int = 1,
        training_info_file_name: str = None,
        device: str = None
    ) -> None:

        self.num_episodes = num_episodes
        self.max_episode_length = max_episode_length
        self.learning_rate = learning_rate
        self.discount = discount 
        self.gae_lambda = gae_lambda
        self.epsilon = epsilon
        self.alpha = alpha
        self.beta = beta
        self.num_workers = num_workers
        self.training_info_file_name = training_info_file_name

        if device is None:
            self.device = "cuda" if torch.cuda.is_available() else "cpu"
        else:
            self.device = device

        self.memory = EpisodeMemory(device=self.device)

        self.policy = PPO().to(self.device)
        self.policy.share_memory()
        self.optimizer = optim.Adam(self.policy.parameters(), lr=learning_rate)

        self.trajectory_collector: TrajectoryCollector = None

        self.episodes_trained: int = 0

        # Setting up the training infomation csv file
        if training_info_file_name is not None:
            self.training_info_file_name = training_info_file_name + ".csv"
            self._initialize_training_csv()


    def fit(self, iterations: int, epochs: int, verbose: bool=True, save_path: str=None) -> None:
        self.trajectory_collector = TrajectoryCollector(self.policy, max_episode_length=self.max_episode_length, num_workers=self.num_workers)

        for iteration in range(iterations):
            optimization_time = 0
            loss_calculation_time = 0

            with PerformaceTimer() as timer:
                self._rollout()
            rollout_time = timer.elapsed_time

            for epoch in range(epochs):
                with PerformaceTimer() as timer:
                    loss = self._compute_loss(iteration, epoch, verbose)
                loss_calculation_time += timer.elapsed_time

                with PerformaceTimer() as timer:
                    self.optimizer.zero_grad()
                    # Computes the gradients with respect to the loss
                    loss.backward()
                    # Updates the models parameters 
                    self.optimizer.step()
                optimization_time += timer.elapsed_time

            # Writes the timings for each section of the training loop
            if verbose:
                iteration_time = rollout_time + loss_calculation_time + optimization_time
                print(f"\n Iteration total time = {iteration_time:.4f}")
                print(f" Rollout time = {rollout_time:.4f} ({rollout_time / iteration_time * 100:.2f}%)")
                print(f" Loss calculation time = {loss_calculation_time:.4f} ({loss_calculation_time / iteration_time * 100:.2f}%)")
                print(f" Optimization time = {optimization_time:.4f} ({optimization_time / iteration_time * 100:.2f}%)\n")

            if save_path:
                self.save(save_path)

        self.trajectory_collector.close()


    def _compute_loss(self, iteration: int, epoch: int, verbose: bool) -> torch.Tensor:
        total_loss = torch.tensor([0], dtype=torch.float32)

        for episode in range(self.num_episodes):
            boards, pieces, rewards, actions, old_action_probs, state_values = self.memory.get_episode(episode)

            # Compute losses and entropy penalty
            critic_loss = self._compute_critic_loss(self.policy.forward_critic(boards, pieces), rewards)
            actor_loss, entropy_penalty = self._compute_actor_loss(boards, pieces, actions, old_action_probs, rewards, state_values)

            # Computes the final loss function
            loss = -actor_loss + self.alpha * critic_loss + self.beta * -entropy_penalty

            # Adding the loss from the current episode to the total loss of the current trajectory
            total_loss += loss
            
            if epoch == 0:
                self.episodes_trained += 1

            # Writing training infomation to csv file  
            if self.training_info_file_name is not None and epoch == 0:
                with open(self.training_info_file_name, mode='a', newline='') as file:
                    writer = csv.writer(file)
                    writer.writerow([
                        self.episodes_trained,
                        iteration + 1,
                        episode + 1,
                        critic_loss.item(),
                        -actor_loss.item(),
                        entropy_penalty.item(),
                        torch.mean(rewards).item()
                    ])

            # Writing training infomation to the console
            if verbose and episode % (self.num_episodes // EPISODE_LOGGING_FREQUENCY) == 0:
                if epoch == 0:
                    print(f"\n Episodes Trained = {self.episodes_trained}")
                    print(f" Iteration = {iteration + 1}")
                    print(f" Episode = {episode + 1}")
                    print(f" Critic Loss = {round(critic_loss.item(), 7)}")
                    print(f" Actor Loss = {-round(actor_loss.item(), 7)}")
                    print(f" Entropy = {round(entropy_penalty.item(), 7)}")
                    print(f" Average Reward = {round(torch.mean(rewards).item(), 7)}")
        
        if verbose:  
            print(f" Completed Epoch {epoch}")

        return total_loss


    def _compute_critic_loss(self, state_values: torch.Tensor, rewards: torch.Tensor) -> torch.Tensor:
        discounted_returns = self._discounted_return(rewards)
        return F.mse_loss(state_values, discounted_returns)


    def _compute_actor_loss(
        self,
        boards: torch.Tensor,
        pieces: torch.Tensor,
        actions: torch.Tensor,
        old_action_dist: torch.Tensor,
        rewards: torch.Tensor,
        state_values: torch.Tensor
    ) -> tuple[torch.Tensor, torch.Tensor]:

        actor_loss, entropy_penalty = 0, 0
        advantages = self._gae(rewards, state_values)
        new_actor_output = self.policy.forward_actor(boards, pieces)

        new_action_dist = self.policy.dist_from_actor_output(new_actor_output)
        new_action_probs = new_action_dist[torch.arange(new_action_dist.size(0)), actions.squeeze()]
        old_action_probs = old_action_dist.squeeze()[torch.arange(old_action_dist.size(0)), actions.squeeze()]

        # Find the ratio of the probabilities between the old and new policy
        ratio = new_action_probs / old_action_probs

        actor_loss = torch.sum(
            torch.min(ratio * advantages.squeeze(), torch.clip(ratio, 1 - self.epsilon, 1 + self.epsilon) * advantages.squeeze())
        )

        entropy_penalty = -torch.sum(new_action_dist * torch.log(new_action_dist))

        actor_loss /= new_actor_output.size(0)
        entropy_penalty /= new_actor_output.size(0)

        return actor_loss, entropy_penalty


    def _discounted_return(self, rewards: torch.Tensor) -> torch.Tensor:
        discounted_returns = torch.zeros((rewards.size(0), 1))

        discounted_returns[-1] = rewards[-1]
        for i in range(rewards.size(0) - 2, -1, -1):
            discounted_returns[i] = rewards[i] + discounted_returns[i + 1] * self.discount

        return discounted_returns


    def _gae(self, rewards: torch.Tensor, state_values: torch.Tensor) -> torch.Tensor:
        temporal_differences = torch.zeros((rewards.size(0), 1))
        gaes = torch.zeros_like(temporal_differences)
        temporal_differences = rewards[:-1] + self.discount * state_values[1:] - state_values[:-1]

        # Computes the general advantage estimate for each time step
        for t in range(len(temporal_differences) - 2, -1, -1):
            gaes[t] = temporal_differences[t] + self.discount * self.gae_lambda * gaes[t + 1]

        return gaes


    def _rollout(self) -> None:
        self.memory.reset()

        trajectories = self.trajectory_collector.collect_trajectories(self.num_episodes)

        for trajectory in trajectories:
            self.memory.store(*trajectory)


    def save(self, file_name: str) -> None:
        training_state = {
            "model_state" : self.policy.state_dict(),
            "optimizer_state" : self.optimizer.state_dict(),
            "episodes_trained" : self.episodes_trained
        }
        torch.save(training_state, file_name + ".pt")


    def save_policy_as_onnx(self, file_name: str) -> None:
        dummy_input = (torch.zeros((1, 10, 20)).float(), torch.zeros((1, 8)).float())
        torch.onnx.export(
            self.policy,
            dummy_input,
            file_name + ".onnx",
            input_names=["board", "piece"],
            output_names=["actor_output", "critic_output"]
        )


    def load(self, save_path: str) -> None:
        training_state = torch.load(save_path)
        self.policy.load_state_dict(training_state["model_state"])
        self.optimizer.load_state_dict(training_state["optimizer_state"])
        self.episodes_trained = training_state["episodes_trained"]


    def _initialize_training_csv(self) -> None:
        with open(self.training_info_file_name, mode='w', newline='') as file:
            writer = csv.writer(file)
            writer.writerow(["Episodes_trained", "Iteration", "Episode", "Critic_loss", "Actor_loss", "Entropy", "Average_Reward"])
