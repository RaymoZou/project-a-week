#include <SDL.h>

#define HEIGHT 600
#define WIDTH 800

class Game {
public:
  bool isRunning;

  void Initialize();
  void RunGameLoop();

private:
  SDL_Window *window;
  SDL_Renderer *renderer;
};
