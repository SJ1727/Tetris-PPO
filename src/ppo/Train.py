from Trainer import TetrisPPOTrainer
from Timing import PerformaceTimer
import torch

def main():
    with PerformaceTimer() as timer:
        trainer = TetrisPPOTrainer(num_episodes=1, max_episode_length=500, learning_rate=0.001, training_info_file_name="training", num_workers=None)
        trainer.load("training_test_1.pt")

    print(f"Init Time: {timer.elapsed_time}")

    with PerformaceTimer() as timer:
        trainer.fit(iterations=1, epochs=1, verbose=True)

    print(f"Training Time: {timer.elapsed_time}")

if __name__ == "__main__":
    main()
