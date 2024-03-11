# Week 18 of Paw - Basic Sprite Renderer

A basic renderer for sprites created using SDL and the SDL_image libraries.

## How to compile:
- You'll need to add the `include` and `lib` directories of the SDL2 library with compile flags.
- Here's an example of a basic `Makefile` which uses the `mingw` compiler (note the `winmm` and `lmingw32` libraries)

## Usage:
- Press 'T' to spawn new blocks
- Press 'F' to delete blocks

```
CC = g++
INCLUDES = -I\Path\To\include
LIBS = -L\Path\To\lib -lmingw32 -lwinmm -lSDL2main -lSDL2 -lSDL2_image

main:
	g++ main.cpp -o main.exe $(INCLUDES) $(LIBS) -g
```
