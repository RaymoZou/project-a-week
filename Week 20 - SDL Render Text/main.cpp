#include "SDL_render.h"
#include "SDL_video.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <cstdio>

SDL_Window *window;
SDL_Renderer *renderer;

int main(int argc, char **argv) {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindow("Text Renderer", 100, 100, 800, 600, 0);
  SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  TTF_Init();

  // accept 1 argument string and 1 argument string only
  if (argc == 2) {
    printf("second argument: %s\n", argv[1]);
  };

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();

  return 0;
};
