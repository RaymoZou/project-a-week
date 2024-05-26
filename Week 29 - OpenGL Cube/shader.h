// generic OpenGL shader class
//

#include <string>
class Shader {
public:
  unsigned int id;
  Shader(std::string file_path, unsigned int SHADER_TYPE);
};
