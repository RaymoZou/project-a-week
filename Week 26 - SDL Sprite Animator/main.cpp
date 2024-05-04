#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>

const int SCALE = 32;

// ./main.exe image.png
char *file_path;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_bool isRunning = SDL_TRUE;

int main(int argc, char **argv) {
  // TODO: check for init failures
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);

  if (argc == 2) {
    file_path = argv[1];
    SDL_Log("file location: %s", file_path);
  } else {
    SDL_Log("invalid argument input\n");
    return -1;
  };

  window = SDL_CreateWindow("Animator", 0, 0, 800, 600, 0);
  renderer = SDL_CreateRenderer(
      window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  SDL_Texture *texture = IMG_LoadTexture(renderer, file_path);
  int width;
  int height;
  SDL_QueryTexture(texture, NULL, NULL, &width, &height);
  SDL_SetWindowSize(window, width * SCALE, height * SCALE);

  // run animation loop
  while (isRunning) {

    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
      isRunning = SDL_FALSE;
      break;
    };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
  };

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
};
