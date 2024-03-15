#pragma once
#include "actor.hpp"

// player class
class Player : public Actor {
public:
  int moveSpeed = 1;
  Player(Game *game);
  void Update(float deltaTime);
};
