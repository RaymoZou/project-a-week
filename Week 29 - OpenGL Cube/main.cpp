#include "GL/glew.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <fstream>
#include <sstream>
#include <string>

unsigned int program, VBO, VAO, EBO, vs, fs;
SDL_Window *window;
bool close;

// TODO: add index buffer object to reuse vertices
char *parseGLSL(std::string file_path) {
  char *result = NULL;
  std::ifstream file(file_path);

  if (!file.is_open()) {
    SDL_Log("could not open file\n");
  } else {
    SDL_Log("file opened successfully\n");
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    std::string temp = buffer.str();

    result = (char *)malloc(sizeof(char) * temp.length() + 1);
    strcpy(result, temp.c_str());
  }
  return result;
};

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
  glBindVertexArray(VAO);
  const float vertices[] = {
      0.5f,  -0.5f, // 0 bottom right
      -0.5f, -0.5f, // 1 bottom left
      -0.5f, 0.5f,  // 2 top left
      0.5f,  0.5f   // 3 top right
  };
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // param 1: starting index of array buffer
  // param 2: size of vertex attribute
  // param 3: GL_FLOAT
  // param 4: should normalize coordinates? (no);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
  glEnableVertexAttribArray(0);

  // shaders
  vs = glCreateShader(GL_VERTEX_SHADER);
  char *vs_src = parseGLSL("vs.glsl");
  glShaderSource(vs, 1, &vs_src, NULL);
  glCompileShader(vs);
  // check compilation of vertex shader
  GLint vs_compile_status;
  glGetShaderiv(vs, GL_COMPILE_STATUS, &vs_compile_status);
  SDL_Log("vertex shader compile status: %d\n", vs_compile_status);

  fs = glCreateShader(GL_FRAGMENT_SHADER);
  char *fs_src = parseGLSL("fs.glsl");
  glShaderSource(fs, 1, &fs_src, NULL);
  glCompileShader(fs);
  // check compilation of fragment shader
  GLint fs_compile_status;
  glGetShaderiv(fs, GL_COMPILE_STATUS, &fs_compile_status);
  SDL_Log("fragment shader compile status: %d\n", fs_compile_status);
  program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  SDL_Log("OpenGL Error Code: %d\n", glGetError());

  // element buffer object
  unsigned int indices[] = {0, 1, 3,

                            1, 2, 3};
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  while (!close) {
    // handle window close event
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
      close = true;
    };
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(VAO);
    glUseProgram(program);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    SDL_GL_SwapWindow(window);
  };

  return 0;
};
