import torch
import torch.nn as nn

ACTION_SPACE_SIZE = 7

class PPO(nn.Module):
    def __init__(self):
        super(PPO, self).__init__()

        self.board_encode = nn.Sequential(
            nn.Conv2d(1, 16, 3),
            nn.ReLU(),
            nn.MaxPool2d(2),
            nn.Conv2d(16, 16, 3),
            nn.ReLU(),
            nn.Flatten()
        )

        self.shared_head: nn.Module = nn.Sequential(
            nn.Linear(432, 128),    # 432 -> 128
            nn.ReLU(),
            nn.Linear(128, 64),     # 128 -> 64
            nn.ReLU(),
        )
        
        self.actor: nn.Module = nn.Sequential(
            nn.Linear(64, 64),
            nn.ReLU(),
            nn.Linear(64, ACTION_SPACE_SIZE)
        )

        # Gradients being computed
        self.critic: nn.Module = nn.Sequential(
            nn.Linear(64, 64),
            nn.ReLU(),
            nn.Linear(64, 1)
        )


    def encode_observation(self, board, piece):
        board_encoded = self.board_encode(board.unsqueeze(1))
        flattened_board = torch.flatten(board, start_dim=1)
        encoded_obs = torch.cat((flattened_board, board_encoded, piece), dim=1)

        return self.shared_head(encoded_obs)

    def forward(self, board, piece):
        z = self.encode_observation(board, piece)
        return self.actor(z), self.critic(z)

    def forward_actor(self, board, piece):
        z = self.encode_observation(board, piece)
        return self.actor(z)

    def forward_critic(self, board, piece):
        z = self.encode_observation(board, piece)
        return self.critic(z)

    @staticmethod
    def dist_from_actor_output(actor_output, temperture=1):
        action_distribution = torch.softmax(actor_output / temperture, dim=-1)

        return action_distribution
