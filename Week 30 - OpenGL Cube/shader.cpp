#include "shader.h"
#include <GL/glew.h>
#include <cstring>
#include <cwchar>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

// utility class for creating and compiling shaders

char *parseGLSL(std::string file_path) {
  char *result = NULL;
  std::ifstream file(file_path);

  if (!file.is_open()) {
    std::cout << "could not open file\n" << std::endl;
  } else {
    std::cout << "file opened successfully\n" << std::endl;
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    std::string temp = buffer.str();

    result = (char *)malloc(sizeof(char) * temp.length() + 1);
    strcpy(result, temp.c_str());
  }
  return result;
};

Shader::Shader(std::string file_path, int SHADER_TYPE) {
  id = glCreateShader(SHADER_TYPE);
  char *src = parseGLSL(file_path);
  glShaderSource(id, 1, &src, NULL);
  glCompileShader(id);
  // check compilation status of shader status
  int compile_status;
  char info_log[512];
  glGetShaderiv(id, GL_COMPILE_STATUS, &compile_status);
  if (!compile_status) {
    glGetShaderInfoLog(id, 512, NULL, info_log);
    std::cout << info_log << std::endl;
  } else {
    std::cout << "shader compiled successfully" << std::endl;
  }
};
