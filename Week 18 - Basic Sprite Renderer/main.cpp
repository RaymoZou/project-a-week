#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_image.h"
#include "SDL_keyboard.h"
#include "SDL_log.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_scancode.h"
#include "SDL_stdinc.h"
#include "SDL_surface.h"
#include "SDL_timer.h"
#include "SDL_video.h"
#include <SDL.h>
#include <cstdio>
#include <cstdlib>

#define HEIGHT 400
#define WIDTH 600

// global variables
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *playerTexture;
bool isRunning = true;
Uint64 tickCount = 0; // # of ticks since last frame
Uint64 deltaTime;

struct Vector2 {
  float x, y;
};

// TODO: refactor movement into PlayerController class
class Player {
public:
  const int size = 30;
  const int moveSpeed = 1;
  SDL_Rect playerRect;
  const char *spritePath = "sprite.png"; // path to player sprite

  // set player position to origin
  Player() {
    playerRect = {0, 0, size, size};
    printf("player instantiated\n");
  };

  // functions
  void Update() {
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    if (keyState[SDL_SCANCODE_W]) {
      playerRect.y -= moveSpeed * deltaTime;
    }
    if (keyState[SDL_SCANCODE_A]) {
      playerRect.x -= moveSpeed * deltaTime;
    }
    if (keyState[SDL_SCANCODE_S]) {
      playerRect.y += moveSpeed * deltaTime;
    }
    if (keyState[SDL_SCANCODE_D]) {
      playerRect.x += moveSpeed * deltaTime;
    }

    // TODO: refactor this out of here (does not belong in player input)
    if (keyState[SDL_SCANCODE_ESCAPE])
      isRunning = false;
  };
};

int main(int argc, char *argv[]) {

  // initialize SDL: non-zero on failure
  int sdl_init = SDL_Init(SDL_INIT_VIDEO);

  window =
      SDL_CreateWindow("Basic Sprite Renderer", 100, 100, WIDTH, HEIGHT, 0);

  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  int img_init = IMG_Init(IMG_INIT_PNG);

  // check for initialization failures
  if (!window | sdl_init | !renderer | !img_init) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s\n", SDL_GetError());
    return -1;
  };

  Player *player = new Player();
  SDL_Surface *temp_surface = IMG_Load(player->spritePath);
  playerTexture = SDL_CreateTextureFromSurface(renderer, temp_surface);
  SDL_FreeSurface(temp_surface);

  while (isRunning) {
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
      isRunning = false;
    };

    // calculate deltaTime
    deltaTime = SDL_GetTicks64() - tickCount;
    tickCount = SDL_GetTicks64();

    // update game logic (includes polling player input)
    player->Update();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // render player
    SDL_Rect src = {0, 0, 16, 16};
    SDL_RenderCopy(renderer, playerTexture, &src, &player->playerRect);
    SDL_RenderPresent(renderer);
  };

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();

  return 0;
};
