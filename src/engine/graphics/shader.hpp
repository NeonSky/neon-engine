#pragma once

#include "../geometry/matrix.hpp"
#include "color.hpp"

#include <glad/glad.h>

#include <map>
#include <string>

namespace engine::graphics {

  class Shader {
  public:
    Shader(std::string vertex_shader_path, std::string fragment_shader_path);

    // Mutators
    void use();
    void set_uniform_rgb(const GLchar* uniform, const Color& color) const;
    void set_uniform_rgba(const GLchar* uniform, const Color& color) const;
    void set_uniform_vec3(const GLchar* uniform, const geometry::Vector<3>& vector) const;
    void set_uniform_mat4(const GLchar* uniform, const geometry::Matrix<4>& matrix) const;

  private:
    GLuint _program = 0;
    std::string _vertex_shader_path;
    std::string _fragment_shader_path;

    inline static std::map<std::string, GLuint> _cache = std::map<std::string, GLuint>();

    // Accessors
    static auto load_shader_file(const std::string& shader_path, GLenum shader_type) -> GLuint;

    // Mutators
    void compile();
  };
}
