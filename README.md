# Tetris PPO (Proximal Policy Optimization)

*This project is still under construction 🛠️*

## Overview
An implementation of Tetris with graphics written in C++ using SDL3 with several modes, including Single Player, Local Multiplayer, Player vs AI. This project also includes a Python script to train your own Tetris playing AI models using [PPO](https://arxiv.org/abs/1707.06347).

## Requirements
- Python <=3.11
- CMake >=3.22.1

## Setup
### Linux
If you want to just play this game, first run the following two commands to setup the dependencies and to build the project
```
setup.sh
build.sh
```
After that run the `tetris` executable

If you want to train your own Tetris AI then first install the required dependencies using 
```
pip install -r requirements.txt
```
And then run `python3 Train.py`
