#include <glm/ext/vector_float2.hpp>
#include <glm/fwd.hpp>
#include <glm/matrix.hpp>
#include <glm/vec2.hpp>
#include <iostream>

int main() {
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
