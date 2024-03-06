#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_image.h"
#include "SDL_log.h"
#include "SDL_render.h"
#include "SDL_stdinc.h"
#include "SDL_surface.h"
#include "SDL_timer.h"
#include "SDL_video.h"
#include <SDL.h>
#include <cstdio>

#define HEIGHT 400
#define WIDTH 600

// global variables
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;
SDL_Surface *surface;
bool isRunning = true;

int main(int argc, char *argv[]) {

  // initialize SDL: non-zero on failure
  int sdl_init = SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow("Basic Sprite Renderer", 100, 100, WIDTH, HEIGHT,
                            0); // NULL on failure

  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  int img_init = IMG_Init(IMG_INIT_PNG);

  // load surface
  surface = IMG_Load("sprite.png");
  SDL_Log("surface width: %d\n", surface->w);
  SDL_Log("surface height: %d\n", surface->h);

  // check for initialization failures
  if (!window | sdl_init | !renderer | !img_init | !surface) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s\n", SDL_GetError());
    return -1;
  };

  // load texture from surface
  texture = SDL_CreateTextureFromSurface(renderer, surface);

  while (isRunning) {
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
      isRunning = false;
    };

    // clear screen
    // 1 pixel from surface = 4 pixels on the screen
    int aspect_ratio = surface->h;
    SDL_Rect src = {0, 0, surface->w, surface->h};
    SDL_Rect dest = {WIDTH / 2, HEIGHT / 2, 64, 64};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, &src, &dest);

    // present the rendered conten
    SDL_RenderPresent(renderer);
  };

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();

  return 0;
};
