#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void) {
  GLFWwindow *window;

  if (!glfwInit()) {
    // TODO: handle failure
    glfwTerminate();
    return -1;
  };

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  window = glfwCreateWindow(640, 480, "OpenGL Triangle", NULL, NULL);
  if (!window) {
    return -1;
    // Window or OpenGL context creation failed
  }
  glfwSetKeyCallback(window,
                     key_callback); // register key for closing the window
  glfwMakeContextCurrent(window);
  glewInit();

  if (GLEW_VERSION_3_3) {
    std::cout << "Yay, OpenGL 3.3 supported!\n" << std::endl;
  }


  while (!glfwWindowShouldClose(window)) {
    glfwSwapBuffers(window);
    glfwPollEvents();
  };

  glfwTerminate();
  glfwDestroyWindow(window);
  return 0;
}
