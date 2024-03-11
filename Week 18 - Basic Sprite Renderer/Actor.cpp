#include <SDL.h>
#include <cstdio>

// for now, assume every actor has the following:
// 1) a 2D Vector position (origin by default)
// 2) a sprite that needs to be rendered every frame
class Actor {
public:
  SDL_FRect rect;
  const float size = 32.0f;

  Actor() {
    rect = {0, 0, size, size};
    // printf("actor constructor\n");
  };

  virtual ~Actor() {
      printf("actor dead\n");
  };

  virtual void Update() = 0;
};
