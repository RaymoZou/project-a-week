#include "main.cpp"

class Player : public Actor {
public:
  const float moveSpeed = 0.6f;
  Player() { printf("player instantiated\n"); };

  // functions
  void Update() {
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    if (keyState[SDL_SCANCODE_W]) {
      rect.y -= moveSpeed * deltaTime;
    }
    if (keyState[SDL_SCANCODE_A]) {
      rect.x -= moveSpeed * deltaTime;
    }
    if (keyState[SDL_SCANCODE_S]) {
      rect.y += moveSpeed * deltaTime;
    }
    if (keyState[SDL_SCANCODE_D]) {
      rect.x += moveSpeed * deltaTime;
    }

    if (keyState[SDL_SCANCODE_ESCAPE]) {
      isRunning = false;
    };
  };
};
