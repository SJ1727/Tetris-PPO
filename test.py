from tetris_engine import *

engine = TetrisEngine()

for _ in range(30):
    engine.update()

for _ in range(10):
    print(engine.get_board_as_string())
    engine.update()
    input()
    engine.set_next_move(DROP)
