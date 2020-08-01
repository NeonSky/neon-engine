#include "shader.hpp"
#include "../debug/logger.hpp"

#include <boost/dll/runtime_symbol_info.hpp>
#include <fstream>
#include <stdexcept>
#include <utility>

using namespace engine::graphics;

Shader::Shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path) {
  this->vertex_shader   = load_shader_file(vertex_shader_path, GL_VERTEX_SHADER);
  this->fragment_shader = load_shader_file(fragment_shader_path, GL_FRAGMENT_SHADER);

  this->program = glCreateProgram();

  glAttachShader(this->program, vertex_shader);
  glDeleteShader(vertex_shader);
  glAttachShader(this->program, fragment_shader);
  glDeleteShader(fragment_shader);

  glLinkProgram(this->program);

  GLint ok = 0;
  glGetProgramiv(this->program, GL_LINK_STATUS, &ok);
  if (ok == 0)
    LOG_ERROR("Could not link program.");
}

void Shader::use() const {
  glUseProgram(this->program);
}

void Shader::set_uniform_vec3(const GLchar* uniform, const geometry::Vector<3>& vector) const {
  int loc = glGetUniformLocation(this->program, uniform);
  glUniform3fv(loc, 1, vector.begin());
}

void Shader::set_uniform_mat4(const GLchar* uniform, const geometry::Matrix<4>& matrix) const {
  int loc = glGetUniformLocation(this->program, uniform);

  // NOTE: OpenGL wants matrices in column-by-column, which means we have to transpose.
  std::array<std::array<float, 4>, 4> data = matrix.transpose();

  glUniformMatrix4fv(loc, 1, GL_FALSE, &data[0][0]);
}

auto Shader::load_shader_file(const std::string& shader_path, GLenum shader_type) -> GLuint {
  if (_cache.count(shader_path) != 0U)
    return _cache[shader_path];

  GLuint shader = glCreateShader(shader_type);

  std::string res_path         = boost::dll::program_location().parent_path().string() + "/../res/shaders/";
  std::string full_shader_path = res_path + shader_path;

  std::ifstream file(full_shader_path);
  std::string src((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

  const char* raw_shader = src.c_str();
  glShaderSource(shader, 1, &raw_shader, nullptr);

  glCompileShader(shader);

  int ok = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
  if (ok == 0)
    LOG_ERROR("Could not compile shader: " + shader_path);

  return _cache[shader_path] = shader;
}
