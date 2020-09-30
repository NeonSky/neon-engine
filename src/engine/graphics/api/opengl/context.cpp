#include "context.hpp"

#include "../../../debug/logger.hpp"

using namespace engine::graphics::api::opengl;

unsigned int Context::_vao_count    = 0;
unsigned int Context::_buffer_count = 0;

Context::Context() {
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glEnable(GL_DEPTH_TEST);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_LINE_SMOOTH);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

  // glEnable(GL_POLYGON_SMOOTH);
  // glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
  // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

auto Context::gen_vao() -> unsigned int {
  GLuint vao = 0;
  glGenVertexArrays(1, &vao);

  unsigned int id = ++_vao_count;
  _vao_db[id]     = vao;

  return id;
}

auto Context::vao(unsigned int id) -> GLuint {
  if (id > _vao_count)
    LOG_ERROR("VAO with ID " + std::to_string(id) + " does not exist.");

  if (_vao_db.count(id) == 0) {
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    _vao_db[id] = vao;
  }

  return _vao_db.find(id)->second;
}

auto Context::is_vao(unsigned int id) -> bool {
  return _vao_db.count(id) > 0;
}
