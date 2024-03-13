#include "game.hpp"
#include <cstdio>

int main(int argc, char *args[]) {
  Game game;
  game.Initialize();
  game.RunGameLoop();
  return 0;
};
