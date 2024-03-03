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
#include <ctime>
#include <iostream>
#include <ostream>
#include <stdio.h>

#define HEIGHT 768
#define WIDTH 1024
#define WALL_WIDTH WIDTH / 20
#define PADDLE_WIDTH 10
#define PADDLE_HEIGHT 100
#define BALL_SIZE 10

float X_VELOCITY = 1;
float Y_VELOCITY = 1;

SDL_Rect left_wall{0, 0, WALL_WIDTH, HEIGHT};
SDL_Rect right_wall{WIDTH - WALL_WIDTH, 0, WIDTH / 10, HEIGHT};

// paddle at middle left of screen
SDL_Rect paddle{
    0,
    HEIGHT / 2 - PADDLE_HEIGHT / 2, // middle left of screen
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

void ProcessInput(bool *isRunning, Uint32 deltaTime) {
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
    // if paddle is greater than 0;
    if (paddle.y > 0) {
      paddle.y -= 1 * deltaTime;
    };
  };

  if (state[SDL_SCANCODE_S]) {
    if (paddle.y + PADDLE_HEIGHT < HEIGHT) {
      paddle.y += 1 * deltaTime;
    };
  };
};

// calculate the time since last frame
void Update(Uint32 *time, bool *isRunning) {
  Uint32 currTime = SDL_GetTicks64();          // time elapsed in ms
  Uint32 deltaTime = SDL_GetTicks64() - *time; // time elapsed since last frame
  *time = currTime;

  /* std::cout << deltaTime / 1000.0f << std::endl; */
  /* std::cout << *time << std::endl; */

  // game loop logic as a function of deltaTime
  // TODO: add paddle collision detection

  if ((ball.x < PADDLE_WIDTH) && (paddle.y < ball.y) && (ball.y < paddle.y + PADDLE_HEIGHT) && (X_VELOCITY != 1)) {
    printf("paddle collision detected x\n");
    X_VELOCITY *= -1;
  };

  // left wall
  if (ball.x < 0 && X_VELOCITY != 1) {
    X_VELOCITY *= -1;
  };
  // right wall
  if (ball.x > WIDTH && X_VELOCITY != -1) {
    X_VELOCITY *= -1;
  };
  ball.x += X_VELOCITY * deltaTime;

  // top wall
  if (ball.y < 0 && Y_VELOCITY != 1) {
    Y_VELOCITY *= -1;
  };
  // bottom wall
  if (ball.y > HEIGHT && Y_VELOCITY != -1) {
    Y_VELOCITY *= -1;
  };
  ball.y += Y_VELOCITY * deltaTime;

  // 3) process input
  ProcessInput(isRunning, deltaTime);
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
  bool isRunning = true; // game is running by default
  Uint32 time = 0;       // ticks since initialization

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
  // TODO: add vsync?
  /* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC); */
  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) {
    SDL_Log("Failed to create renderer\n: %s", SDL_GetError());
  }

  // game loop
  while (isRunning) {
    Update(&time, &isRunning);
    /* ProcessInput(&isRunning); */
    generateOutput(renderer);
  };

  SDL_DestroyWindow(window);
  SDL_Quit();
  SDL_DestroyRenderer(renderer);

  printf("program exited successfully\n");
  return 0;
};
