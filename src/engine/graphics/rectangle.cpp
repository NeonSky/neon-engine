#include "rectangle.hpp"

#include "../debug/logger.hpp"

#include <vector>

using namespace engine;
using namespace engine::graphics;

Rectangle::Rectangle(Renderer& renderer, const geometry::Rectangle& rectangle, const Color& color)
        : _renderer(renderer),
          _model(rectangle),
          _color(color) {

  _shader = std::make_unique<Shader>("unicolor.vert", "color.frag");

  _vao          = _renderer.get().current_context().gen_vao();
  _index_buffer = _renderer.get().current_context().gen_buffer();
  _pos_buffer   = _renderer.get().current_context().gen_buffer();

  compile();
}

void Rectangle::compile() {
  glBindVertexArray(_renderer.get().current_context().vao(_vao));

  geometry::Vector<3> botleft  = _model.botleft();
  geometry::Vector<3> botright = _model.botright();
  geometry::Vector<3> topleft  = _model.topleft();
  geometry::Vector<3> topright = _model.topright();

  std::vector<float> positions = {
    botleft.x(),
    botleft.y(),
    botleft.z(),

    botright.x(),
    botright.y(),
    botright.z(),

    topright.x(),
    topright.y(),
    topright.z(),

    topleft.x(),
    topleft.y(),
    topleft.z(),
  };

  glBindBuffer(GL_ARRAY_BUFFER, _renderer.get().current_context().buffer(_pos_buffer));
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positions.size(), positions.data(), GL_STATIC_DRAW);

  const std::vector<int> indices = {
    0,
    1,
    2,

    2,
    3,
    0,
  };
  CHECK_GL_ERROR();

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _renderer.get().current_context().buffer(_index_buffer));
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), indices.data(), GL_STATIC_DRAW);
  CHECK_GL_ERROR();

  // Assign position attribute of vertex shader
  glBindBuffer(GL_ARRAY_BUFFER, _renderer.get().current_context().buffer(_pos_buffer));
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
  glEnableVertexAttribArray(0);
  CHECK_GL_ERROR();
}

auto Rectangle::transform() -> geometry::Transform& {
  return _transform;
}

void Rectangle::render(const geometry::Matrix<4>& view_projection_matrix) {
  if (!_renderer.get().current_context().is_vao(_vao))
    compile();

  _shader->use();

  geometry::Matrix<4> model_view_projection = view_projection_matrix * geometry::Matrix<4>(_transform.matrix());
  _shader->set_uniform_mat4("model_view_projection", model_view_projection);
  _shader->set_uniform_rgb("color", _color);

  glBindVertexArray(_renderer.get().current_context().vao(_vao));
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
