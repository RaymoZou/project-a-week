#pragma once
#include "actor.hpp"

class Bullet : public Actor {
public:
  float x_velocity;
  float y_velocity;
  Bullet(Game *game, SDL_FRect frect, float xvel, float yvel);
  void Update(float deltaTime);
};
