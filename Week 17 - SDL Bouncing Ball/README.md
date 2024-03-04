# Week 17 of Paw - SDL Bouncing Ball

Bouncing ball created using the SDL2 library.

## How to compile:
- You'll need to add the `include` and `lib` directories of the SDL2 library with compile flags.
- Here's an example of a basic `Makefile` which uses the `mingw` compiler (note the `winmm` and `lmingw32` libraries)
```
CC = g++
INCLUDES = -I\Path\To\include
LIBS = -L\Path\To\lib -lmingw32 -lwinmm -lSDL2main -lSDL2

main:
	g++ main.cpp -o main.exe $(INCLUDES) $(LIBS) -g
```

## The game:
- When the ball and paddle collide, a message will be printed out in the console
- Otherwise, the ball just bounces off the walls
