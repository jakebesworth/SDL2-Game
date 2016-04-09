# SDL2 Game - in Development

## About

A simple, lightweight, multi-platform, GNU C, Make, and SDL2 desktop game

## What is done so far?

The foundation, wrapper functions and basic game structure is done

## What needs to be done?

Actual gameplay, music, sprites, more SDL2 wrapper functions
- Resolution changes via a menu -> .config file
- Compile on other systems
- Add 64x64 text remove others, add percentage to object creation via the rectangle

## Installing and Running the game

Build the software
```
make
```

Or download precompiled build

[GNU/Linux](https://github.com/jakebesworth/SDL2-Game/raw/master/dist/SDL2-game-linux.tar.gz)

[Windows](https://github.com/jakebesworth/SDL2-Game/raw/master/dist/SDL2-game-windows.tar.gz)

[OS X](https://github.com/jakebesworth/SDL2-Game/raw/master/dist/SDL2-game-osx.tar.gz)

Run the game
```
./star
```

**Note that Linux needs to package install the SDL2 library such as:**

```
sudo apt-get install libsdl2-dev
```

## Game Controls

Move
```
Up, Down, Left and Right arrows, or wasd keys
```

Shoot
```
Spacebar and or 0-9
```

Pause
```
p key
```

Exit
```
Escape key
```

## Screenshots


![alt tag](https://raw.githubusercontent.com/jakebesworth/SDL2-game/master/assets/examples/game.png)
