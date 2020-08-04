#include "debug_drawer.hpp"

#include "logger.hpp"

using namespace engine::debug;

DebugDrawer::DebugDrawer()
        : shader(graphics::Shader("color.vert", "color.frag")) {}

void DebugDrawer::render(const geometry::Matrix<4>& view_projection_matrix) {

  this->shader.use();

  std::vector<float> positions;
  for (auto& line : this->line_queue) {
    positions.emplace_back(line.A.x());
    positions.emplace_back(line.A.y());
    positions.emplace_back(line.A.z());
    positions.emplace_back(line.B.x());
    positions.emplace_back(line.B.y());
    positions.emplace_back(line.B.z());
  }

  unsigned int pos_buffer = 0;
  glGenBuffers(1, &pos_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, pos_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positions.size(), positions.data(), GL_STATIC_DRAW);

  std::vector<float> colors;
  for (auto& line : this->line_queue) {
    for (int i = 0; i < 2; i++) {
      colors.emplace_back(line.color.x());
      colors.emplace_back(line.color.y());
      colors.emplace_back(line.color.z());
    }
  }

  unsigned int color_buffer = 0;
  glGenBuffers(1, &color_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * colors.size(), colors.data(), GL_STATIC_DRAW);

  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, pos_buffer);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
  glEnableVertexAttribArray(1);

  glBindVertexArray(vao);

  this->shader.set_uniform_mat4("modelViewProjectionMatrix", view_projection_matrix);

  glLineWidth(this->line_width);
  glDrawArrays(GL_LINES, 0, 6 * this->line_queue.size()); // NOTE: 6 floats per line
  this->line_queue.clear();
}

void DebugDrawer::draw_line(const geometry::Vector<3>& from, const geometry::Vector<3>& to) {
  this->line_queue.emplace_back(from, to);
}

void DebugDrawer::draw_transform(const geometry::Transform& transform) {
  geometry::Vector<3> from = transform.position();
  this->line_queue.emplace_back(from, from + transform.right(), geometry::Vector<3>(1.0F, 0.0F, 0.0F));
  this->line_queue.emplace_back(from, from + transform.up(), geometry::Vector<3>(0.0F, 1.0F, 0.0F));
  this->line_queue.emplace_back(from, from + transform.forward(), geometry::Vector<3>(0.0F, 0.0F, 1.0F));
}

void DebugDrawer::draw_rectangle(const geometry::Rectangle& rectangle) {
  this->line_queue.emplace_back(rectangle.topleft(), rectangle.topright());
  this->line_queue.emplace_back(rectangle.topleft(), rectangle.botleft());
  this->line_queue.emplace_back(rectangle.botright(), rectangle.botleft());
  this->line_queue.emplace_back(rectangle.botright(), rectangle.topright());
}
