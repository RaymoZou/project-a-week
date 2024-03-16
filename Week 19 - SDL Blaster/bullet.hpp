#pragma once
#include "actor.hpp"

class Bullet : public Actor {
public:
  float x_velocity;
  float y_velocity;
  Bullet(Game *game, float x, float y, float w, float h);
  void Update(float deltaTime);
};
