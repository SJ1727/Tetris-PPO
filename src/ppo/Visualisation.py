import argparse
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

sns.set_theme()

def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Training Data Visualisation")
    parser.add_argument("--data-path", type=str, default="training.csv", help="Path to the training data CSV")
    parser.add_argument("--actor-loss", action=argparse.BooleanOptionalAction, help="Plot Actor Loss")
    parser.add_argument("--critic-loss", action=argparse.BooleanOptionalAction, help="Plot Critic Loss")
    parser.add_argument("--entropy", action=argparse.BooleanOptionalAction, help="Plot Entropy Penalty")
    parser.add_argument("--rolling-average", type=int, default=-1, help="Show rolling average for the specified window")
    return parser.parse_args()

def validate_columns(data: pd.DataFrame, required_columns: list[str]) -> None:
    missing_columns = [col for col in required_columns if col not in data.columns]
    if missing_columns:
        raise ValueError(f"Missing required columns: {', '.join(missing_columns)}")

def plot_data(episodes: pd.Series, data: pd.DataFrame, label: str, rolling_average: int):
    sns.lineplot(x=episodes, y=data, label=label)

    # If rolling average is specified and valid, plot the rolling average
    if rolling_average > 1:
        data_rolling_avg: pd.DataFrame = data.rolling(rolling_average).mean()
        sns.lineplot(x=episodes, y=data_rolling_avg, label=f"{label} (Rolling Avg)")

def main():
    args = parse_args()

    # Load training data
    try:
        training_data = pd.read_csv(args.data_path)
    except Exception as e:
        print(f"Error loading data from {args.data_path}: {e}")
        return

    # Validate necessary columns
    required_columns = ["Episodes_trained", "Actor_loss", "Critic_loss", "Entropy"]
    validate_columns(training_data, required_columns)

    episodes_trained = training_data["Episodes_trained"]

    # Plot data based on user input
    if args.actor_loss:
        plot_data(episodes_trained, training_data["Actor_loss"], "Actor Loss", args.rolling_average)
    
    if args.critic_loss:
        plot_data(episodes_trained, training_data["Critic_loss"], "Critic Loss", args.rolling_average)

    if args.entropy:
        plot_data(episodes_trained, training_data["Entropy"], "Entropy", args.rolling_average)

    plt.xlabel("Episodes Trained")
    plt.title("Training Data Visualization")
    plt.legend(title="Metrics")
    plt.tight_layout()

    plt.show()

if __name__ == "__main__":
    main()
