#include "Actor.cpp"
#include "SDL_image.h"
#include "SDL_rect.h"
#include <SDL.h>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>

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

struct Vector2 {
  float x, y;
};

class Block : public Actor {
public:
  Vector2 moveSpeed;

  Block() {
    float r1 = -1.0f + static_cast<float>(
                           rand() / static_cast<float>((RAND_MAX / 2.0f)));
    float r2 = -1.0f + static_cast<float>(
                           rand() / static_cast<float>((RAND_MAX / 2.0f)));
    moveSpeed = {r1, r2};
    // printf("block instantiated\n");
  };
  ~Block() { printf("block destroyed\n"); };

  void Update() {
    if (rect.y > HEIGHT && (moveSpeed.y > 0)) {
      moveSpeed.y *= -1;
    };
    if (rect.y < 0 && (moveSpeed.y < 0)) {
      moveSpeed.y *= -1;
    };
    if (rect.x > WIDTH && (moveSpeed.x > 0)) {
      moveSpeed.x *= -1;
    };
    if (rect.x < 0 && (moveSpeed.x < 0)) {
      moveSpeed.x *= -1;
    };
    rect.y += moveSpeed.y * deltaTime;
    rect.x += moveSpeed.x * deltaTime;
  };
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

// testing
std::vector<class Actor *> actors;

// load textures
void LoadData() {
  playerTexture = IMG_LoadTexture(renderer, "player.png");
  blockTexture = IMG_LoadTexture(renderer, "block.png");
};

void Render() {

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  for (auto actor : actors) {
    SDL_RenderCopyF(renderer, blockTexture, NULL, &actor->rect);
  };

  SDL_RenderPresent(renderer);
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
  actors.emplace_back(player);
  actors.emplace_back(block);

  // should be 2 (1 for block and 1 for player);
  printf("%d\n", actors.size());

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

    // if (keyState[SDL_SCANCODE_F] & (block != nullptr)) {
    //   auto iter = std::find(actors.begin(), actors.end(), block);
    //   if (iter != actors.end()) {
    //     std::iter_swap(iter, actors.end() - 1);
    //     actors.pop_back();
    //   }
    //   delete block;
    //   block = nullptr;
    // };
    //
    if (keyState[SDL_SCANCODE_F]) {
      // if there are no actors, return
      if (!actors.empty()) {
        Actor *last_actor = actors.back();
        actors.pop_back();
        delete last_actor;
        last_actor = nullptr;
      }
    };

    if (keyState[SDL_SCANCODE_T]) {
      Block *new_block = new Block();
      actors.emplace_back(new_block);
    };

    // update all actors
    for (auto actor : actors) {
      actor->Update();
    };

    Render();
  };

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();

  return 0;
};
