# Tetris PPO (Proximal Policy Optimization)

*This project is still under construction 🛠️*

*As such features included in the readme may not be implemented fully yet*

<p align="center">
  <img alt="Main Menu" src=https://github.com/user-attachments/assets/8bfdcb18-9881-427c-a5d2-af0d8ec2b53f / width="300">
  <img alt="Player vs AI" src=https://github.com/user-attachments/assets/2f7e548e-a052-4166-8b7d-ec6fec78e5c8 / width="300">
</p>

## Overview
An implementation of Tetris with graphics written in C++ using SDL3 with several modes, including Single Player, Local Multiplayer, Player vs AI. This project also includes a Python script to train your own Tetris playing AI models using [PPO](https://arxiv.org/abs/1707.06347).

## Requirements
- Python <=3.11
- CMake >=3.22.1

## Setup
*Should in theory be cross platfrom but currently have some strange bug with windows*
### Linux
If you want to just play this game, first run the following two commands to setup the dependencies and to build the project
```
setup.sh
build.sh
```
After that run the `tetris` executable

If you want to train your own Tetris AI then I recommend creating a [virtual enviroment](https://docs.python.org/3.11/library/venv.html), activating it, and then running
```
pip install -r requirements.txt
python3 setup.py bdist_wheel
pip install dist/*.whl
```
After the dependecies have been installed you can run `python3 src/ppo/Train.py`, if you want to change the parameters of the model then you can chnage the parameters of the `TetrisPPOTrainer` inside the train script

If you wish to visualise your AI models training data then you can run 
```
python3 src/ppo/Visualisation.py --help
```
and then select the options to display the data you want. For example if you want to see the average reward overtime with a rolling average of 10, simply run  
```
python3 src/ppo/Visualisation.py --reward --rolling-average 10
```
<p align="center">
  <img alt="Reward Visual" src=https://github.com/user-attachments/assets/9ede5a15-c089-4480-a48c-8c7b92d9eb23 / width="400">
</p>


If you wish to see your model play an actual game you can use the `src/ppo/Test.py` file, all you need to do is change the file path which is being loaded by the trainer to the path of your models save file. 
<p align="center">
  <img alt="Terminal Model Test" src=https://github.com/user-attachments/assets/f46da2db-0ece-4a56-af61-3a74462efff6 / width="400">
</p>

