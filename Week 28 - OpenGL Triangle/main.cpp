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

  // TODO: check for failure
  SDL_Window *window =
      SDL_CreateWindow("PAW - Week 27", 100, 100, 1024, 768, SDL_WINDOW_OPENGL);

  // request and check OpenGL core version
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_CreateContext(window);
  SDL_Log("%s\n", glGetString(GL_VERSION));

  if (glewInit() != GLEW_OK) {
    SDL_Log("Error initializing GLEW library\n");
  };

  float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
  SDL_bool shouldClose = SDL_FALSE;

  glClearColor(0.2f, 0.2f, 0.0f, 1.0f);

  // vertex shader
  const char *vertex_shader_source =
      "#version 330 core\n"
      "layout (location = 0) in vec3 aPos;\n"
      "void main()\n"
      "{\n"
      "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      "}\0";
  const char *frag_shader_src = "#version 330 core\n"
                                "out vec4 FragColor;\n"
                                "void main()\n"
                                "{\n"
                                "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                "}\0";

  // compile shader
  unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
  glCompileShader(vertex_shader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
    SDL_Log("vertex shader compilation failed\n");
  };

  unsigned int frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag_shader, 1, &frag_shader_src, NULL);
  glCompileShader(frag_shader);
  glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
    SDL_Log("frag shader compilation failed\n");
  };

  // create program
  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertex_shader);
  glAttachShader(shaderProgram, frag_shader);
  glLinkProgram(shaderProgram);

  // vertex array object (VAO)
  unsigned int vao, vbo;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // vertex buffer object (VBO)
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glDeleteShader(vertex_shader);
  glDeleteShader(frag_shader);

  while (!shouldClose) {
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
      shouldClose = SDL_TRUE;
    };
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    SDL_GL_SwapWindow(window);
  };
  /* glClearColor(1.0f, 0.0f, 0.0f, 1.0f); */
  /* glClear(GL_COLOR_BUFFER_BIT); */
  /* glUseProgram(shaderProgram); */
  /* glBindVertexArray(vao); */
  /* glDrawArrays(GL_TRIANGLES, 0, 3); */

  /* SDL_Delay(2500); */

  return 0;
};
