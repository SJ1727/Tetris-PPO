import torch
import torch.nn as nn
import torch.multiprocessing as mp
from Tetris import TetrisEnv
from torch.distributions import Categorical

class TrajectoryCollector:
    def __init__(self, policy: nn.Module, *, max_episode_length: int = 1000, num_workers: int = None) -> None:
        mp.set_start_method('spawn', force=True) 

        self.policy = policy
        self.max_episode_length = max_episode_length
        self.num_workers = num_workers if num_workers is not None else mp.cpu_count()
        self.workers, self.parent_conn = self._init_workers()
    
    def _init_workers(self) -> tuple:
        parent_conn, child_conn = zip(*[mp.Pipe() for _ in range(self.num_workers)])
        workers = []

        for worker_id in range(self.num_workers):
            worker = mp.Process(target=self._worker, args=(worker_id, self.policy, child_conn[worker_id]))
            worker.start()
            workers.append(worker)

        return workers, parent_conn

    def _worker(self, worker_id: int, policy: nn.Module, conn: tuple) -> None:
        env = TetrisEnv()

        while True:
            command, _ = conn.recv()
            if command == "run_episode":
                boards, pieces, rewards, actions, action_probs, state_values = [], [], [], [], [], []
                done = False

                for i in range(self.max_episode_length):
                    if done and i > 1:
                        break

                    # Collect trajectory data from enviroment
                    board, piece, reward, done = env.get_observation() 

                    boards.append(board)
                    pieces.append(piece)
                    rewards.append(reward)

                    current_game_state = (
                        boards[i].unsqueeze(0),
                        pieces[i].unsqueeze(0)
                    )

                    with torch.no_grad():
                        actor_output = policy.forward_actor(*current_game_state)
                        critic_output = policy.forward_critic(*current_game_state)

                    action_dist = Categorical(probs=policy.dist_from_actor_output(actor_output))  
                    action = action_dist.sample()

                    state_values.append(torch.squeeze(critic_output, dim=1))
                    action_probs.append(action_dist.probs)
                    actions.append(action)

                    # Updating the enviroment using the sampled action
                    env.step(action)

                conn.send(
                    (
                        torch.stack(boards),
                        torch.stack(pieces),
                        torch.stack(rewards),
                        torch.stack(actions),
                        torch.stack(action_probs),
                        torch.stack(state_values)
                        )
                    )

            elif command == "close":
                conn.close()
                break

    def collect_trajectories(self, num_episodes: int) -> list[tuple[torch.Tensor]]:
        trajectories = []
        episodes_per_worker = num_episodes // self.num_workers

        for _ in range(episodes_per_worker):
            for conn in self.parent_conn:
                conn.send(("run_episode", None))

            for conn in self.parent_conn:
                trajectories.append(conn.recv())

        # If the number of trajectories is not a multiple of the number of workers there will be some 
        # remaining episodes that need to be ran
        remaining_episodes = num_episodes - self.num_workers * episodes_per_worker
        for conn in self.parent_conn[:remaining_episodes]:
            conn.send(("run_episode", None))

        for conn in self.parent_conn[:remaining_episodes]:
            trajectories.append(conn.recv())

        return trajectories

    def close(self) -> None:
        for conn in self.parent_conn:
            conn.send(("close", None))