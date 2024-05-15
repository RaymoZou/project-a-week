#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>

int main() {
  SDL_Log("hello world\n");

  SDL_Window *window =
      SDL_CreateWindow("PAW - Week 27", 100, 100, 1024, 768, SDL_WINDOW_OPENGL);

  if (!glewInit()) {
    SDL_Log("Error: %s\n", SDL_GetError());
  };

  // request and check OpenGL core version
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_CreateContext(window);
  int major, minor;
  /* SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major); */
  /* SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor); */
  /* SDL_Log("opengl version: %d.%d\n", major, minor); */

  float positions[6] = {-0.5f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f};
  SDL_bool shouldClose = SDL_FALSE;

  glViewport(0, 0, 1024, 768);
  glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

  while (!shouldClose) {
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
      shouldClose = SDL_TRUE;
    };
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
  };

  return 0;
};
