#include "rectangle.hpp"

#include "../debug/logger.hpp"

#include <vector>

using namespace engine::graphics;

// TODO: Don't take a pointer. Simply have a function that doesn't take a texture as alternative.
Rectangle::Rectangle(const geometry::Rectangle& rectangle, const Texture* texture)
        : _texture(texture) {

  _shader = std::make_unique<Shader>("texture.vert", "texture.frag");

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

  unsigned int uv_buffer = 0;
  if (_texture != nullptr) {
    glGenBuffers(1, &uv_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
    const std::vector<float> uv_coords = {
      0.0F,
      0.0F,

      1.0F,
      0.0F,

      1.0F,
      1.0F,

      0.0F,
      1.0F,
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * uv_coords.size(), uv_coords.data(), GL_STATIC_DRAW);
  }

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

  if (_texture != nullptr) {
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);
  }

  _vao = vao;
}

auto Rectangle::transform() -> geometry::Transform& {
  return _transform;
}

void Rectangle::render(const geometry::Matrix<4>& view_projection_matrix) {
  _shader->use();

  geometry::Matrix<4> model_view_projection = view_projection_matrix * geometry::Matrix<4>(_transform.matrix());
  _shader->set_uniform_mat4("mvp_matrix", model_view_projection);

  if (_texture != nullptr) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture->id());
  }

  glBindVertexArray(_vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
