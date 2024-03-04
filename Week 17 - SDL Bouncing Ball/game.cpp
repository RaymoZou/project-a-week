#include "SDL.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_stdinc.h"
#include "SDL_timer.h"
#include "SDL_video.h"
#include <cstdio>

#define SCREEN_HEIGHT 768
#define SCREEN_WIDTH 1024
#define PADDLE_WIDTH 10
#define PADDLE_HEIGHT 100
#define BALL_SIZE 10

struct Vector2 {
  float x, y;
};

struct Ball {
  SDL_Rect rect;
  Vector2 velocity;
};

typedef SDL_Rect Paddle;

// TODO: UI for scorekeeping
class Game {
public:
  // class fields
  bool isRunning;
  SDL_Window *window;
  SDL_Renderer *renderer;
  Uint64 ticksPassed;
  Uint64 deltaTime;
  Ball ball;
  Paddle paddle;

  // class functions
  int Initialize() {
    window = SDL_CreateWindow("Bouncing Ball Game", 100, 100, SCREEN_WIDTH,
                              SCREEN_HEIGHT, 0);
    // TODO: additional add necessary renderer flags
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    int init_result = SDL_Init(SDL_INIT_VIDEO);
    if (!renderer || !window || init_result) {
      SDL_Log("Failed to create initialize\n: %s", SDL_GetError());
      return -1;
    };
    isRunning = true;
    ticksPassed = SDL_GetTicks64();

    // initiate ball
    ball.rect.x = SCREEN_WIDTH / 2;
    ball.rect.y = SCREEN_HEIGHT / 2;
    ball.rect.h = BALL_SIZE;
    ball.rect.w = BALL_SIZE;
    // TODO: randomize velocity
    ball.velocity.x = 1;
    ball.velocity.y = 1;

    // initiate paddle
    paddle.x = 0;
    paddle.y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    paddle.w = PADDLE_WIDTH;
    paddle.h = PADDLE_HEIGHT;
    return 0;
  };

  void RunLoop() {
    while (isRunning) {
      Update();       // update game logic
      ProcessInput(); // get user input
      Render();       // render (swap back and present buffers)
    };
  };

  void EndGame() {
    SDL_DestroyWindow(window);
    SDL_Quit();
    SDL_DestroyRenderer(renderer);
  };

private:
  void Update() {

    Uint64 currTime = SDL_GetTicks64();         // time elapsed in ms
    deltaTime = SDL_GetTicks64() - ticksPassed; // time elapsed since last frame
    ticksPassed = currTime;

    // if ball and paddle intersect AND ball hasn't flipped velocity
    if (SDL_HasIntersection(&ball.rect, &paddle) && (ball.velocity.x != 1)) {
      printf("paddle collision detected\n");
      ball.velocity.x *= -1;
    };

    // left wall
    if (ball.rect.x < 0 && ball.velocity.x != 1) {
      ball.velocity.x *= -1;
    };
    // right wall
    if (ball.rect.x > SCREEN_WIDTH && ball.velocity.x != -1) {
      ball.velocity.x *= -1;
    };
    ball.rect.x += ball.velocity.x * deltaTime;
    // top wall
    if (ball.rect.y < 0 && ball.velocity.y != 1) {
      ball.velocity.y *= -1;
    };
    // bottom wall
    if (ball.rect.y > SCREEN_HEIGHT && ball.velocity.y != -1) {
      ball.velocity.y *= -1;
    };
    ball.rect.y += ball.velocity.y * deltaTime;
  };

  void Render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // set black
    SDL_RenderClear(renderer); // clear current buffer with renderer color
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0); // set white
    SDL_RenderFillRect(renderer, &paddle);
    SDL_RenderFillRect(renderer, &ball.rect);
    SDL_RenderPresent(renderer);
  };

  void ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        isRunning = false;
        break;
      };
    };

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE]) {
      isRunning = false;
    };

    if (state[SDL_SCANCODE_W]) {
      if (paddle.y > 0) {
        paddle.y -= 1 * deltaTime;
      };
    };

    if (state[SDL_SCANCODE_S]) {
      if (paddle.y + PADDLE_HEIGHT < SCREEN_HEIGHT) {
        paddle.y += 1 * deltaTime;
      };
    };
  }
};
