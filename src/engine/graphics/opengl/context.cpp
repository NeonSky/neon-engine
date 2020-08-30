#include "context.hpp"

#include "../../debug/logger.hpp"

using namespace engine::graphics::opengl;

unsigned int Context::_vao_count    = 0;
unsigned int Context::_buffer_count = 0;

Context::Context() {
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glEnable(GL_DEPTH_TEST);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

auto Context::gen_vao() -> unsigned int {
  GLuint vao;
  glGenVertexArrays(1, &vao);

  unsigned int id = (_vao_count++);
  _vao_db[id]     = vao;

  return id;
}

auto Context::vao(unsigned int id) -> GLuint {
  if (id >= _vao_count)
    LOG_ERROR("VAO with ID " + std::to_string(id) + " does not exist.");

  if (!_vao_db.count(id)) {
    GLuint vao;
    glGenVertexArrays(1, &vao);
    _vao_db[id] = vao;
  }

  return _vao_db.find(id)->second;
}

auto Context::is_vao(unsigned int id) -> bool {
  return _vao_db.count(id) > 0;
}

auto Context::gen_buffer() -> unsigned int {
  GLuint buffer = 0;
  glGenBuffers(1, &buffer);

  unsigned int id = (_buffer_count++);
  _buffer_db[id]  = buffer;

  return id;
}

auto Context::buffer(unsigned int id) -> GLuint {
  if (id >= _buffer_count)
    LOG_ERROR("Buffer with ID " + std::to_string(id) + " does not exist.");

  if (!_buffer_db.count(id)) {
    GLuint buffer;
    glGenBuffers(1, &buffer);
    _buffer_db[id] = buffer;
  }

  return _buffer_db.find(id)->second;
}
