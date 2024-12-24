from tetris_engine import TetrisEngine, Move

engine = TetrisEngine()

cmd_to_move = {
    "":  Move.NO_MOVE,
    "r": Move.RIGHT,
    "l": Move.LEFT,
    "s": Move.DOWN,
    "d": Move.DROP,
    "h": Move.HOLD,
    "o": Move.ROTATE_LEFT,
    "p": Move.ROTATE_RIGHT
}

cmd = ""
while cmd != "stop":
    cmd = input()

    move = cmd_to_move.get(cmd)
    if move is not None:
        engine.set_next_move(move)

    engine.update()
    
    print(engine.get_board_as_string())


