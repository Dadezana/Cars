# Cars<br>![Cocoapods platforms](https://img.shields.io/badge/platform-linux-yellow)<br>
A terminal racing car game with ascii art

# How to play
The game is simple: avoid other cars
- **W**:     Accelerate
- **S**:     Brake
- **D**:     Turn right
- **A**:     Turn left
- **Space**: Horn
>*Make sure your terminal screen size is at least 225x41. Otherwise the game won't display correctly. You can zoom out or set the window to fullscreen*
# Build
This program in order to be built needs the [SFML](https://www.sfml-dev.org/download.php) API<br>
You can also download it from the command line(suggested):
### Arch linux
```bash
sudo pacman -S sfml
```
### Ubuntu
```bash
sudo apt-get install libsfml-dev
```

Remember to include the flags of the modules you use in the program:
```bash
g++ *.cpp -lsfml-window -lsfml-audio
```
You can find other info about building [here](https://www.sfml-dev.org/tutorials/2.5/start-linux.php)


## Credits
Car graphic and road animation: [MX-05](https://github.com/MX-05)<br>
Acceleration/Braking/SameSpeed sounds: [biholao](https://freesound.org/people/biholao/sounds/370277/)<br/>
Background music: [FoolBoyMedia](https://freesound.org/people/FoolBoyMedia/sounds/237089/)<br/>
Horn sound: [15HPanska_Ruttner_Jan](https://freesound.org/people/15HPanska_Ruttner_Jan/sounds/461679/)<br/>
Crash sound: [squareal](https://freesound.org/people/squareal/sounds/237375/)<br/>