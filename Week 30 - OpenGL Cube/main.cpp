#include "shader.h"
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
unsigned int vbo, vao;

int main() {
  SDL_Window *window =
      SDL_CreateWindow("PAW - Week 30", 0, 0, 1024, 768, SDL_WINDOW_OPENGL);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_CreateContext(window);
  glewInit();
  SDL_Log("OpenGL version: %s\n", glGetString(GL_VERSION));

  // vao
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  float vertices[] = {0.0f, 0.0f,  // bottom left
                      1.0f, 0.0f,  // bottom right
                      0.0f, 1.0f}; // top

  // vbo
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  // shaders
  Shader vs("vs.glsl", GL_VERTEX_SHADER);
  Shader fs("fs.glsl", GL_FRAGMENT_SHADER);
  unsigned int program = glCreateProgram();
  glAttachShader(program, vs.id);
  glAttachShader(program, fs.id);
  glLinkProgram(program);

  // uniforms
  int colorLocation = glGetUniformLocation(program, "u_color");
  glUseProgram(program);
  glUniform4f(colorLocation, 0.5f, 0.0f, 1.0f, 1.0f);
  int offsetLocation = glGetUniformLocation(program, "u_offset");
  glUniform4f(offsetLocation, -0.5f, 0.0f, 0.0f, 0.0f);

  /* glm::vec2 pos(-1, 2); */
  /* glm::mat2 transform; */
  /* transform[0][0] = 1.0f; */
  /* transform[0][1] = -2.0f; */
  /* transform[1][0] = 3.0f; */
  /* transform[1][1] = 0.0f; */
  /* glm::vec2 result = transform * pos; */
  /* SDL_Log("x: %f\n", result.x); */
  /* SDL_Log("y: %f\n", result.y); */

  /* glClearColor(0.0f, 0.0f, 0.0f, 1.0f); */
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  while (open) {
    SDL_Event e;
    SDL_PollEvent(&e);
    if (e.type == SDL_QUIT) {
      open = 0;
    };
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(vao);
    glUseProgram(program);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    SDL_GL_SwapWindow(window);
  };
  return 0;
};
