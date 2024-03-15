#include "actor.hpp"
#include "game.hpp"

Actor::Actor(Game *game) {
    rect = {0, 0, 100, 100};
    game->actors.push_back(this); // add the actor so it can updated
    printf("actor initialized\n");
};
