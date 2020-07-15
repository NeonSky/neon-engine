#pragma once

#include <glad/glad.h>

#include <map>
#include <string>

namespace engine::graphics {

  class Shader {
  public:
    Shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path);
    ~Shader() = default;

    // Mutators
    void use() const;
    void set_uniform_vec3(const GLchar* uniform, const GLfloat* data) const;
    void set_uniform_mat4(const GLchar* uniform, const GLfloat* data) const;

  private:
    GLuint program;
    GLuint vertex_shader;
    GLuint fragment_shader;

    inline static std::map<std::string, GLuint> _cache = std::map<std::string, GLuint>();

    // Accessors
    static auto load_shader_file(const std::string& shader_path, GLenum shader_type) -> GLuint;
  };
}
