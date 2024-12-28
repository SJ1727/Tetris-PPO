from Trainer import TetrisPPOTrainer
from PPO import PPO
from Tetris import TetrisEnv
import torch
from torch.distributions import Categorical

def play_episode(policy: PPO):
    env = TetrisEnv(verbose=True)

    while True:
        board, piece, reward, done = env.get_observation() 

        current_game_state = (
            board.unsqueeze(0),
            piece.unsqueeze(0)
        )

        with torch.no_grad():
            actor_output = policy.forward_actor(*current_game_state)

        action_dist = Categorical(probs=policy.dist_from_actor_output(actor_output, temperture=100))  
        action = action_dist.sample()

        env.step(action, delay=0.07)

        if done:
            break


def main():
    trainer = TetrisPPOTrainer(num_episodes=1, max_episode_length=1, training_info_file_name=None, num_workers=1)
    trainer.load("training_test_4.pt")
    policy = trainer.policy
    play_episode(policy)

if __name__ == "__main__":
    main()
