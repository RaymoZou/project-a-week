#include "bullet.hpp"

// x is the x position
// y is the y position
// w is the width of the rect
// h is the width of the rect
Bullet::Bullet(Game *game, float x = 0, float y = 0, float w = 10, float h = 10)
    : Actor(game) {
  rect = {x, y, w, h};
};


void Bullet::Update(float deltaTime) {
    rect.x += x_velocity * deltaTime;
    rect.y += y_velocity * deltaTime;
};
