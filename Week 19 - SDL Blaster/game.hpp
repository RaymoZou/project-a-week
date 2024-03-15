#pragma once
// #include "player.hpp"
#include <SDL.h>
#include <vector>

#define HEIGHT 600
#define WIDTH 800

class Game {
  // TODO: make fields private when it makes sense to do so
public:
  Uint64 deltaTime = 0;
  Uint64 ticks = 0;
  SDL_Window *window;
  SDL_Renderer *renderer;
  std::vector<class Actor *> actors;
  bool isRunning;
  class Player *player;

  void Initialize();
  void Update();
};
