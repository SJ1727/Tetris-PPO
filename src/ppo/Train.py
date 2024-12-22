from Trainer import TetrisPPOTrainer
from Timing import PerformaceTimer
import torch

def main():
    with PerformaceTimer() as timer:
        trainer = TetrisPPOTrainer(num_episodes=50, max_episode_length=100, learning_rate=0.01, training_info_file_name="training", num_workers=None)
        trainer.fit(iterations=10, epochs=20, verbose=True)

    print(f"{timer.elapsed_time}")

if __name__ == "__main__":
    main()
