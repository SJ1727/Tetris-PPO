from enum import Enum
import torch
from random import randint

class Move(Enum):
    RIGHT = 0
    LEFT = 1
    DOWN = 2
    ROTATE_RIGHT = 3
    ROTATE_LEFT = 4
    DROP = 5
    HOLD = 6
    NO_MOVE = 7

class TetrisEnv:
    BOARD_SIZE = 200
    BOARD_WIDTH = 10
    BOARD_HEIGHT = 20
    PIECE_SIZE = 7
    STATE_SIZE = 207
    
    def __init__(self):
        self.value = 0

    def reset(self):
        pass

    def step(self, move):
        self.value = int(move)

    def get_observation(self):
        board = torch.randint(0, 2, (10, 20)).float()
        piece = torch.randint(0, 2, (7,)).float()
        reward = torch.rand(1).float() + self.value
        done = randint(0, 100) == 42 
        return board, piece, reward, done