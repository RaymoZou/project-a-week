#pragma once
#include <SDL.h>
#include "game.hpp"
#include <cstdio>

// actor class
// for now, make the following assumptions about an actor
// 1) have a sprite that needs to rendered each frame
// 2) have a position
class Actor {
public:
  SDL_Rect rect;
  Actor(Game *game);
  virtual void Update(float deltaTime) = 0;
};
