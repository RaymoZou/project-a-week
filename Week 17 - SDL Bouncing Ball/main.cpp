#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_keyboard.h"
#include "SDL_log.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_scancode.h"
#include "SDL_stdinc.h"
#include "SDL_timer.h"
#include "SDL_video.h"
#include <SDL.h>
#include <algorithm>
#include <iostream>
#include <stdio.h>

#define HEIGHT 768
#define WIDTH 1024
#define WALL_WIDTH WIDTH / 20
#define PADDLE_WIDTH 10
#define PADDLE_HEIGHT 100
#define BALL_SIZE 10

int BALL_VELOCITY = 1;

SDL_Rect left_wall{0, 0, WALL_WIDTH, HEIGHT};
SDL_Rect right_wall{WIDTH - WALL_WIDTH, 0, WIDTH / 10, HEIGHT};

// paddle at middle left of screen
SDL_Rect paddle{
    0,
    HEIGHT / 2 - PADDLE_HEIGHT / 2,
    PADDLE_WIDTH,
    PADDLE_HEIGHT,
};

// ball at middle of screen
SDL_Rect ball{
    WIDTH / 2,
    HEIGHT / 2,
    BALL_SIZE,
    BALL_SIZE,
};

struct Vector2 {
  float x, y;
};

void ProcessInput(bool *isRunning) {
  // allocate memory for event
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      *isRunning = false;
      break;
    };
  };

  const Uint8 *state = SDL_GetKeyboardState(NULL);
  if (state[SDL_SCANCODE_ESCAPE]) {
    *isRunning = false;
  };

  if (state[SDL_SCANCODE_W]) {
    paddle.y -= 1;
  };

  if (state[SDL_SCANCODE_S]) {
    paddle.y += 1;
  };
};

// calculate the time since last framE
void Update(Uint64 *time, Vector2 *ballVelocity) {
  Uint64 currTime = SDL_GetTicks64(); // time elapsed in ms
  Uint64 deltaTime = SDL_GetTicks64() - *time;
  *time = currTime;

  // game loop logic as a function of deltaTime

  // 1) ball x position
  ball.x += ballVelocity->x;
  if (ball.x > WIDTH | ball.x < 0) {
    ballVelocity->x *= -1;
  }

  ball.y += ballVelocity->y;
  if (ball.y > HEIGHT | ball.y < 0) {
    ballVelocity->y *= -1;
  };
};

void generateOutput(SDL_Renderer *renderer) {
  // render black background
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // set black
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

  // render paddle
  SDL_RenderFillRect(renderer, &paddle);

  // render ball
  SDL_RenderFillRect(renderer, &ball);

  // present the back buffer
  SDL_RenderPresent(renderer);
};

int main(int argc, char *args[]) {

  SDL_Window *window;
  SDL_Renderer *renderer;
  bool isRunning = true;          // game is running by default
  Vector2 ball_velocity = {3, 1}; // TODO: initiate ball velocity randomly
  Uint64 time = 0;                // ticks since initialization

  // SDL_Init
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("There was an error initiating the SDL library\n");
    return -1;
  }

  window = SDL_CreateWindow("Bouncing Ball Game", 100, 100, WIDTH, HEIGHT, 0);
  if (!window) {
    SDL_Log("Failed to create window\n: %s", SDL_GetError());
  };

  // initialize renderer
  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer) {
    SDL_Log("Failed to create renderer\n: %s", SDL_GetError());
  }

  // create SDL window

  // game loop
  while (isRunning) {
    // process input
    ProcessInput(&isRunning);
    Update(&time, &ball_velocity);
    generateOutput(renderer);
  };

  SDL_DestroyWindow(window);
  SDL_Quit();
  SDL_DestroyRenderer(renderer);

  printf("nice (program exited successfully)\n");
  return 0;
};
