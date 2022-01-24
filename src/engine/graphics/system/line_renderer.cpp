#include "line_renderer.hpp"

#include "../component/render_info.hpp"

using namespace engine::graphics::system;

LineRenderer::LineRenderer()
        : _shader(graphics::Shader("color.vert", "color.frag")) {

  std::array<GLfloat, 2> width_range{};
  glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, width_range.data());
  _min_line_width = width_range[0];
  _max_line_width = width_range[1];
}

void LineRenderer::render(const geometry::Matrix<4>& view_projection) {
  if (_line_queue.empty())
    return;

  std::vector<geometry::LineSegment<3>> positions;
  for (auto& line : _line_queue)
    positions.emplace_back(line.geometry);

  std::vector<std::array<float, 3>> colors;
  for (auto& line : _line_queue)
    for (int i = 0; i < 2; i++)
      colors.push_back(line.color.rgb());

  _shader.use();

  unsigned int pos_buffer = 0;
  glGenBuffers(1, &pos_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, pos_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(geometry::LineSegment<3>) * positions.size(), positions.data(), GL_STATIC_DRAW);

  unsigned int color_buffer = 0;
  glGenBuffers(1, &color_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(std::array<float, 3>) * colors.size(), colors.data(), GL_STATIC_DRAW);

  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, pos_buffer);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
  glEnableVertexAttribArray(1);

  _shader.set_uniform_mat4("model_view_projection", view_projection);

  auto end = _line_queue.begin();
  do {
    auto start  = end;
    float width = start->width;
    glLineWidth(width);

    end = std::partition_point(start,
                               _line_queue.end(),
                               [&](const component::LineSegment& line) {
                                 // NOTE: partition_point uses binary search so we can't use == here.
                                 return line.width <= width;
                               });

    // NOTE: 2 indices per line
    GLenum mode   = GL_LINES;
    GLint first   = 2 * std::distance(_line_queue.begin(), start);
    GLsizei count = 2 * std::distance(start, end);
    glDrawArrays(mode, first, count);

  } while (end != _line_queue.end());
}

void LineRenderer::clear() {
  _line_queue.clear();
}

/// @todo Don't create new stuff every update, store refs to the buffers in the component.
void LineRenderer::update([[maybe_unused]] architecture::ECS& ecs) {
  auto& render_info = ecs.get<component::RenderInfo>(ecs.view<component::RenderInfo>()[0]);
  // auto& ctx         = render_info.context.get();

  _shader.use();

  for (auto entity : ecs.view<component::LineSegments>()) {
    auto& line_segments = ecs.get<component::LineSegments>(entity).line_segments;

    std::vector<geometry::LineSegment<3>> positions;
    std::vector<std::array<float, 3>> colors;
    for (auto& line_segment : line_segments) {
      positions.emplace_back(line_segment.geometry);
      for (int i = 0; i < 2; i++)
        colors.push_back(line_segment.color.rgb());
    }

    unsigned int pos_buffer = 0;
    glGenBuffers(1, &pos_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, pos_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(geometry::LineSegment<3>) * positions.size(), positions.data(), GL_STATIC_DRAW);

    unsigned int color_buffer = 0;
    glGenBuffers(1, &color_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(std::array<float, 3>) * colors.size(), colors.data(), GL_STATIC_DRAW);

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

    _shader.set_uniform_mat4("model_view_projection", render_info.view_projection);

    auto end = line_segments.begin();
    do {
      auto start  = end;
      float width = start->width;
      glLineWidth(width);

      end = std::partition_point(start,
                                 line_segments.end(),
                                 [&](const component::LineSegment& line) {
                                   // NOTE: partition_point uses binary search so we can't use == here.
                                   return line.width <= width;
                                 });

      // NOTE: 2 indices per line
      GLenum mode   = GL_LINES;
      GLint first   = 2 * std::distance(line_segments.begin(), start);
      GLsizei count = 2 * std::distance(start, end);
      glDrawArrays(mode, first, count);

    } while (end != line_segments.end());
  }
}

void LineRenderer::add_line(component::LineSegment&& line) {
  line.width = std::clamp(line.width, _min_line_width, _max_line_width);
  auto it    = std::upper_bound(_line_queue.begin(),
                             _line_queue.end(),
                             line,
                             [](auto& a, auto& b) {
                               return a.width < b.width;
                             });
  _line_queue.insert(it, line);
}
