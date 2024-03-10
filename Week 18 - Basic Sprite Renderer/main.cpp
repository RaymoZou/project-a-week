#include "Actor.cpp"
#include "SDL_image.h"
#include "SDL_rect.h"
#include <SDL.h>
#include <cstdio>

#define HEIGHT 1080
#define WIDTH 1920

// global variables
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *playerTexture;
SDL_Texture *blockTexture;
bool isRunning = true;
Uint64 tickCount = 0; // # of ticks since last frame
Uint64 deltaTime;

// load textures
void LoadData() {
  playerTexture = IMG_LoadTexture(renderer, "player.png");
  blockTexture = IMG_LoadTexture(renderer, "block.png");
};

struct Vector2 {
  float x, y;
};

class Block : public Actor {
public:
  const char *spritePath = "block.png";
  const float moveSpeed = 0.1f;

  Block() { printf("block instantiated\n"); };

  ~Block() { printf("block destroyed\n"); };

  void Update() {
    rect.y += moveSpeed * deltaTime;
    if (rect.y > HEIGHT) {
      rect.y = 0;
    };
  };

  void Test() { printf("i'm a block\n"); }
};

class Player : public Actor {
public:
  const float moveSpeed = 0.6f;
  Player() { printf("player instantiated\n"); };

  // functions
  void Update() {
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    if (keyState[SDL_SCANCODE_W]) {
      rect.y -= moveSpeed * deltaTime;
    }
    if (keyState[SDL_SCANCODE_A]) {
      rect.x -= moveSpeed * deltaTime;
    }
    if (keyState[SDL_SCANCODE_S]) {
      rect.y += moveSpeed * deltaTime;
    }
    if (keyState[SDL_SCANCODE_D]) {
      rect.x += moveSpeed * deltaTime;
    }

    if (keyState[SDL_SCANCODE_ESCAPE]) {
      isRunning = false;
    };
  };
};

int main(int argc, char *argv[]) {

  int sdl_init = SDL_Init(SDL_INIT_VIDEO);
  window =
      SDL_CreateWindow("Basic Sprite Renderer", 100, 100, WIDTH, HEIGHT, 0);
  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  int img_init = IMG_Init(IMG_INIT_PNG);
  if (!window | sdl_init | !renderer | !img_init) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s\n", SDL_GetError());
    return -1;
  };

  LoadData();
  Block *block = new Block();
  Player *player = new Player();

  while (isRunning) {

    // calculate deltaTime
    deltaTime = SDL_GetTicks64() - tickCount;
    tickCount = SDL_GetTicks64();

    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
      isRunning = false;
    };

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    if (keyState[SDL_SCANCODE_F]) {
      if (block) {
        delete block;
        block = nullptr;
      }
    };

    // update game logic (includes polling player input)
    // Get all actors and update them
    player->Update();
    if (block)
      block->Update();

    // update screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    if (block) {
      SDL_RenderCopyF(renderer, blockTexture, NULL, &block->rect);
    };
    SDL_RenderCopyF(renderer, playerTexture, NULL, &player->rect);

    SDL_RenderPresent(renderer);
  };

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();

  return 0;
};
