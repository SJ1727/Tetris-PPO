from tetris_engine import TetrisEngine, Move
from enum import Enum
import torch

BOARD_SIZE = 200
BOARD_WIDTH = 10
BOARD_HEIGHT = 20
PIECE_SIZE = 8
STATE_SIZE = BOARD_SIZE + PIECE_SIZE

class TetrisEnv:
    def __init__(self):
        self.engine = TetrisEngine()

    def reset(self):
        self.engine.init()

    def step(self, move):
        self.engine.set_next_move(Move(move))
        self.engine.update()

    def get_observation(self):
        board, piece, reward, done = self.engine.get_game_state()
        
        board = torch.tensor(board, dtype=torch.float32)
        piece = torch.tensor(piece, dtype=torch.float32)
        reward = torch.tensor([reward], dtype=torch.float32)

        board = torch.reshape(board, (BOARD_WIDTH, BOARD_HEIGHT))
        
        return board, piece, reward, done
