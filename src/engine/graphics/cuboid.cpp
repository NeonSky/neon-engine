#include "cuboid.hpp"

using namespace engine::graphics;

Cuboid::Cuboid(geometry::Cuboid geometry, geometry::Vector<3> color)
        : _geometry(geometry),
          _color(color),
          _shader(Shader("unicolor.vert", "color.frag")) {

  glGenVertexArrays(1, &_vao);
  glBindVertexArray(_vao);
  glGenBuffers(1, &_vbo);

  update_vbos();

  glVertexAttribPointer(0, 3, GL_FLOAT, 0U, 0, nullptr);
  glEnableVertexAttribArray(0);

  // Indices
  GLuint index_buffer = 0;
  glGenBuffers(1, &index_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
  std::array<std::array<unsigned int, 3>, 12> indices = {{
    // Left face
    {5, 0, 7},
    {2, 7, 0},
    // Right face
    {1, 4, 3},
    {6, 3, 4},
    // Bottom face
    {5, 4, 0},
    {1, 0, 4},
    // Top face
    {2, 3, 7},
    {6, 7, 3},
    // Back face
    {0, 1, 2},
    {3, 2, 1},
    // Front face
    {4, 5, 6},
    {7, 6, 5},
  }};
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);
}

void Cuboid::render(geometry::Matrix<4> view_projection, bool draw_corners) {
  update_vbos();

  _shader.use();
  _shader.set_uniform_mat4("model_view_projection", view_projection);
  _shader.set_uniform_vec3("color", _color);

  glBindVertexArray(_vao);

  glDrawElements(GL_TRIANGLES, 3 * 12, GL_UNSIGNED_INT, nullptr);
  if (draw_corners) {
    glPointSize(10.0F);
    glDrawElements(GL_POINTS, 3 * 12, GL_UNSIGNED_INT, nullptr);
  }

  glBindVertexArray(0);
}

auto Cuboid::transform() -> geometry::Transform& {
  return _geometry.transform();
}

void Cuboid::update_vbos() {
  std::array<geometry::Vector<3>, 8> vertices;

  geometry::Rectangle back_face = _geometry.back_face();
  vertices[0]                   = back_face.botleft();
  vertices[1]                   = back_face.botright();
  vertices[2]                   = back_face.topleft();
  vertices[3]                   = back_face.topright();

  geometry::Rectangle front_face = _geometry.front_face();
  vertices[4]                    = front_face.botleft();
  vertices[5]                    = front_face.botright();
  vertices[6]                    = front_face.topleft();
  vertices[7]                    = front_face.topright();

  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
}
