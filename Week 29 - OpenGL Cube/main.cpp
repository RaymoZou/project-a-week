#include "GL/glew.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

unsigned int programID, VBO, VAO, vertex_shader, fragment_shader;
SDL_Window *window;
bool close;

// TODO: add index buffer object to reuse vertices
// TODO: add shaders
int main() {
  close = false;
  window = SDL_CreateWindow("Week 29 - OpenGL Cube", 0, 0, 800, 600,
                            SDL_WINDOW_OPENGL);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
  SDL_GL_CreateContext(window);
  glewInit();
  SDL_Log("OpenGL version: %s\n", glGetString(GL_VERSION));

  glClearColor(0.75f, 0.75f, 0.90f, 1.0f); // set buffer clear color

  glGenVertexArrays(1, &VAO);
  SDL_Log("OpenGL Error Code: %d\n", glGetError());
  glBindVertexArray(VAO);
  const float vertices[] = {
      0.5f, -0.5f,
      -0.5f, -0.5f,
      -0.5f, 0.5f,

      0.5f, -0.5f,
      -0.5f, 0.5f,
      0.5f, 0.5f
  };
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
  glEnableVertexAttribArray(0);

  while (!close) {
    // handle window close event
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
      close = true;
    };
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    SDL_GL_SwapWindow(window);
  };

  return 0;
};
