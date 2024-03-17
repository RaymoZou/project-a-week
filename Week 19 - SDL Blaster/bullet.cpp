#include "bullet.hpp"

// x is the x position
// y is the y position
// w is the width of the rect
// h is the width of the rect
// x_vel = x velocity
// y_vel = y velocity
Bullet::Bullet(Game *game, SDL_FRect frect, float xvel, float yvel)
    : Actor(game) {
  rect = frect;
  x_velocity = xvel;
  y_velocity = yvel;
};

void Bullet::Update(float deltaTime) {
  rect.x += x_velocity * deltaTime;
  rect.y += y_velocity * deltaTime;
};
