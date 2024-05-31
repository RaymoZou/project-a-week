#include <SDL2/SDL_log.h>
#include <SDL2/SDL_video.h>
#include <glm/ext/vector_float2.hpp>
#include <glm/fwd.hpp>
#include <glm/matrix.hpp>
#include <glm/vec2.hpp>
#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>

int main() {
    SDL_Window *window = SDL_CreateWindow("PAW - Week 30", 0, 0, 300, 300, SDL_WINDOW_OPENGL);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); 
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3); 
    SDL_GL_CreateContext(window);
    glewInit();
    SDL_Log("OpenGL version: %s\n", glGetString(GL_VERSION));

  // pos:
  // -1
  //  2
  glm::vec2 pos(-1, 2);
  // transform:
  //  1 3
  // -2 0
  glm::mat2 transform = glm::mat2(glm::vec2(1, 3), glm::vec2(-2, 0));
  // result:
  // -1(1)  + 2(3) = 5
  //  2(-2) + 0()
  glm::vec2 result = pos * transform;
  std::cout << result.x << " " << result.y << std::endl;
  return 0;
};
