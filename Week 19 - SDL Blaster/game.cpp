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

#include "actor.hpp"
#include "game.hpp"
#include "player.hpp"

void Game::Initialize() {
  int init_result = SDL_Init(SDL_INIT_VIDEO); // 0 on success
  isRunning = true;
  window = SDL_CreateWindow("Blaster", 100, 100, WIDTH, HEIGHT, 0);
  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  if ((init_result != 0) | !window | !renderer) {
    printf("SDL Error: %s\n", SDL_GetError());
  };

  player = new Player(this);
}

void Game::Update() {
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
    // player->Update(deltaTime);
    for (Actor *actor : actors) {
      actor->Update(deltaTime);
    };

    // render actors
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    // TODO: renderer draw color should be based on the actor
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
    for (Actor *actor : actors) {
      SDL_RenderFillRect(renderer, &actor->rect);
    }
    SDL_RenderPresent(renderer);
  };
};
