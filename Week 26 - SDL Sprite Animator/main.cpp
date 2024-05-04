#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

const int SCALE = 32; // rendering scale
const int FPS = 15;
int spriteSize = 8; // spliced spritesheet size
int width;
int height;
int numSprites;
char *file_path;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_bool isRunning = SDL_TRUE;
SDL_Rect *sprites = NULL;

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

  SDL_Rect displayBounds;
  SDL_GetDisplayBounds(0, &displayBounds);
  window = SDL_CreateWindow("Animator", displayBounds.w / 2,
                            displayBounds.h / 2, 800, 600, 0);
  renderer = SDL_CreateRenderer(
      window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  SDL_Texture *texture = IMG_LoadTexture(renderer, file_path);
  SDL_QueryTexture(texture, NULL, NULL, &width, &height);
  numSprites = width / spriteSize;
  SDL_SetWindowSize(window, spriteSize * SCALE, spriteSize * SCALE);

  // splice spritesheet
  sprites = (SDL_Rect *)malloc(sizeof(SDL_Rect) * numSprites);
  int x = 0;
  int y = 0;
  for (int i = 0; i < numSprites; i++) {
    sprites[i].h = spriteSize;
    sprites[i].w = spriteSize;
    sprites[i].x = x;
    sprites[i].y = y;
    x += spriteSize;
  };

  int index = 0;
  // run animation loop
  while (isRunning) {
    int start = SDL_GetTicks64();

    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
      isRunning = SDL_FALSE;
      break;
    };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, &sprites[index], NULL);
    SDL_RenderPresent(renderer);

    index++;
    if (index >= numSprites) {
      index = 0;
    };

    int deltaTime = SDL_GetTicks64() - start;
    SDL_Log("%d\n", deltaTime);
    if (deltaTime < 1000 / FPS) { // for 30 fps
      SDL_Delay(1000 / FPS - deltaTime);
    };
  };

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
};
