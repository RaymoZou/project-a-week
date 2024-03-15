#include "player.hpp"
#include "SDL_events.h"
#include <cstdio>

Player::Player(Game *game) : Actor(game) {
  printf("player constructor called\n");
};

void Player::Update(float deltaTime) {
  // process input
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
