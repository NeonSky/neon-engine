#include "rectangle.hpp"

#include "../debug/logger.hpp"

#include <vector>

using namespace engine::graphics;

Rectangle::Rectangle(const geometry::Rectangle& rectangle, const Color& color)
        : _color(color) {

  _shader = std::make_unique<Shader>("unicolor.vert", "color.frag");

  geometry::Vector<3> botleft  = rectangle.botleft();
  geometry::Vector<3> botright = rectangle.botright();
  geometry::Vector<3> topleft  = rectangle.topleft();
  geometry::Vector<3> topright = rectangle.topright();

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

  unsigned int pos_buffer = 0;
  glGenBuffers(1, &pos_buffer); // Gen buffer object and store buffer id
  glBindBuffer(GL_ARRAY_BUFFER, pos_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positions.size(), positions.data(), GL_STATIC_DRAW);

  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  unsigned int index_buffer      = 0;
  const std::vector<int> indices = {
    0,
    1,
    2,

    2,
    3,
    0,
  };

  glGenBuffers(1, &index_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), indices.data(), GL_STATIC_DRAW);

  // Assign position attribute of vertex shader
  glBindBuffer(GL_ARRAY_BUFFER, pos_buffer);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
  glEnableVertexAttribArray(0);

  _vao = vao;
}

auto Rectangle::transform() -> geometry::Transform& {
  return _transform;
}

void Rectangle::render(const geometry::Matrix<4>& view_projection_matrix) {
  _shader->use();

  geometry::Matrix<4> model_view_projection = view_projection_matrix * geometry::Matrix<4>(_transform.matrix());
  _shader->set_uniform_mat4("model_view_projection", model_view_projection);
  _shader->set_uniform_rgb("color", _color);

  glBindVertexArray(_vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
