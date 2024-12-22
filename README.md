# Tetris PPO (Proximal Policy Optimization)

*This project is still under construction 🛠️*

*As such features included in the readme may not be implemented fully yet*

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
And then run `python3 src/ppo/Train.py`

If you wish to visualise your AI models training data then you can run 
```
python3 src/ppo/Visualisation.py --help
```
and then select the options to display the data you want. For example if you want to see the entropy overtime with a rolling average of 50, simply run  
```
python3 src/ppo/Visualisation.py --entropy --rolling-average 50
```

