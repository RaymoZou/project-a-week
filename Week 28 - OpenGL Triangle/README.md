# Week 28 of Paw - OpenGL Triangle (Part 2)

Simple triangle rendered with OpenGL and SDL2. Didn't quite get to finish last week so here we are. GLEW is used to fetch available functions from the user's graphics driver.
The main feature of this week's project is the `parseGLSL` function which parses `.glsl` shader files into C-style strings which are required to compile shaders.

## Installation (Arch Linux):
1. Install dependencies with `sudo pacman -Syu sdl2 glew`.
2. Compile using `make`.
3. Run with `./main.exe`.
