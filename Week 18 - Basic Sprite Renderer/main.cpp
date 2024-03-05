#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_log.h"
#include "SDL_render.h"
#include "SDL_stdinc.h"
#include "SDL_timer.h"
#include "SDL_video.h"
#include <SDL.h>
#include <cstdio>

#define HEIGHT 400
#define WIDTH 600

SDL_Window *window;
SDL_Renderer *renderer;
SDL_bool isRunning = SDL_TRUE;

int main(int argc, char *argv[]) {

  // non-zero on failure
  int init_result = SDL_Init(SDL_INIT_VIDEO);

  // NULL on failure
  window =
      SDL_CreateWindow("Basic Sprite Renderer", 100, 100, WIDTH, HEIGHT, 0);

  if (!window | init_result) {
    printf("error: %s\n", SDL_GetError());
    return -1;
  };

  while (isRunning) {
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
      isRunning = SDL_FALSE;
    };
  };

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();

  return 0;
};
