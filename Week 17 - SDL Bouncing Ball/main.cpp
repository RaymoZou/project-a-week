#include "game.cpp"

int main(int argc, char *args[]) {

  Game game = Game();
  if (game.Initialize() != 0) {
    return EXIT_FAILURE;
  };
  game.RunLoop();
  game.EndGame();

  printf("program exited successfully\n");
  return EXIT_SUCCESS;
};
