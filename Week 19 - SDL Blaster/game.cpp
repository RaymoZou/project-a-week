#include "game.hpp"
#include <cstdio>

// TODO:
void Game::Initialize() {
  int init_result = SDL_Init(SDL_INIT_VIDEO);

  bool isRunning = true;
  SDL_Window *window = SDL_CreateWindow("Blaster", 100, 100, WIDTH, HEIGHT, 0);
  SDL_Renderer *renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

  if ((init_result != 0) | !window | !renderer) {
    printf("SDL Error: %s\n", SDL_GetError());
  };
};

void Game::RunGameLoop() {
  while (isRunning) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        isRunning = false;
        break;
      case SDL_KEYDOWN:
        printf("key down event detected\n");
        break;
      case SDL_KEYUP:
        printf("key up event detected\n");
        break;
      };
    };
  };
};
