#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_video.h>
#include <glm/ext/vector_float2.hpp>
#include <glm/fwd.hpp>
#include <glm/matrix.hpp>
#include <glm/vec2.hpp>

unsigned char open = 1;
unsigned int vbo;

int main() {
  SDL_Window *window =
      SDL_CreateWindow("PAW - Week 30", 0, 0, 300, 300, SDL_WINDOW_OPENGL);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_CreateContext(window);
  glewInit();
  SDL_Log("OpenGL version: %s\n", glGetString(GL_VERSION));

  const float indices[] = {0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 6, NULL, GL_STATIC_DRAW);

  glm::vec2 pos(3, 1);
  glm::mat2 transform;
  transform[0][0] = -1.0f;
  transform[0][1] = 0.0f;
  transform[1][0] = 0.0f;
  transform[1][1] = -1.0f;
  glm::vec2 result = transform * pos;
  SDL_Log("x: %f\n", result.x);
  SDL_Log("y: %f\n", result.y);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  while (open) {
    SDL_Event e;
    SDL_PollEvent(&e);
    if (e.type == SDL_QUIT) {
      open = 0;
    };
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
  };
  return 0;
};
