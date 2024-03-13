#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_keyboard.h"
#include "SDL_pixels.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_scancode.h"
#include "SDL_stdinc.h"
#include "SDL_timer.h"
#include <SDL.h>
#include <cstdio>
#include <vector>

#define HEIGHT 600
#define WIDTH 800

// actor class
// for now, make the following assumptions about an actor
// 1) have a sprite that needs to rendered each frame
// 2) have a position
class Actor {
public:
  SDL_Rect rect;
  Actor() {
    rect = {0, 0, 100, 100};
    printf("actor initialized\n");
  };
  virtual void Update(float deltaTime) = 0;
};

class Player : public Actor {
public:
  void Update(float deltaTime) override {
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    if (keyState[SDL_SCANCODE_D]) {
      rect.x += moveSpeed * deltaTime;
    };
    if (keyState[SDL_SCANCODE_A]) {
      rect.x -= moveSpeed * deltaTime;
    };
    if (keyState[SDL_SCANCODE_W]) {
      rect.y -= moveSpeed * deltaTime;
    };
    if (keyState[SDL_SCANCODE_S]) {
      rect.y += moveSpeed * deltaTime;
    };
  };
private:
  int moveSpeed = 1;
};

class Game {
public:
  bool isRunning;
  void Initialize() {
    int init_result = SDL_Init(SDL_INIT_VIDEO); // 0 on success
    isRunning = true;
    window = SDL_CreateWindow("Blaster", 100, 100, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if ((init_result != 0) | !window | !renderer) {
      printf("SDL Error: %s\n", SDL_GetError());
    };
  }

  void Update() {
    while (isRunning) {

      SDL_Event event;
      SDL_PollEvent(&event);
      if (event.type == SDL_QUIT) {
        isRunning = false;
      };

      // calculate deltaTime
      deltaTime = SDL_GetTicks64() - ticks;
      ticks = SDL_GetTicks64();
      // update actors
      player.Update(deltaTime);
      // render actors
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
      SDL_RenderClear(renderer);
      SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
      SDL_RenderFillRect(renderer, &player.rect);
      SDL_RenderPresent(renderer);
    };
  };

private:
  Uint64 deltaTime = 0;
  Uint64 ticks = 0;
  std::vector<Actor *> actors;
  SDL_Window *window;
  SDL_Renderer *renderer;
  Player player;
};
