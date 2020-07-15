#pragma once

#include <glad/glad.h>

#include <map>
#include <string>

namespace engine::graphics {

  class Shader {
  public:
    Shader(std::string vertex_shader_path, std::string fragment_shader_path);
    ~Shader();

    // Mutators
    void use();
    void set_uniform_vec3(const GLchar* uniform, const GLfloat* data);
    void set_uniform_mat4(const GLchar* uniform, const GLfloat* data);

  private:
    GLuint program;
    GLuint vertex_shader;
    GLuint fragment_shader;

    inline static std::map<std::string, GLuint> _cache = std::map<std::string, GLuint>();

    // Accessors
    auto load_shader_file(std::string shader_path, GLenum shaderType) -> GLuint;
  };
}
