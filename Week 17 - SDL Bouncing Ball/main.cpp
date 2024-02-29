#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_keyboard.h"
#include "SDL_log.h"
#include "SDL_scancode.h"
#include "SDL_stdinc.h"
#include "SDL_video.h"
#include <SDL.h>
#include <algorithm>
#include <iostream>
#include <stdio.h>

#define HEIGHT 768
#define WIDTH 1024

void ProcessInput(bool *isRunning) {
  // allocate memory for event
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      *isRunning = false;
      break;
    }
  };

  // exit on Esc key press
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  if (state[SDL_SCANCODE_ESCAPE]) {
    *isRunning = false;
  };
};

void Update(){};
void generateOutput(){};

int main(int argc, char *args[]) {

  SDL_Window *window;
  bool isRunning = true;

  // initialize
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("There was an error initiating the SDL library\n");
    return -1;
  }

  // create SDL window
  window = SDL_CreateWindow("Bouncing Ball Game", 0, 0, WIDTH, HEIGHT, 0);
  if (!window) {
    SDL_Log("Failed to create window\n: %s", SDL_GetError());
  };

  // game loop
  while (isRunning) {
    // process input
    ProcessInput(&isRunning);
    Update();
    generateOutput();
  };

  SDL_DestroyWindow(window);
  SDL_Quit();

  printf("nice (program exited successfully)\n");
  return 0;
};
