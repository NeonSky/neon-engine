#pragma once

#include "../geometry/matrix.hpp"
#include "../geometry/rectangle.hpp"
#include "../geometry/transform.hpp"
#include "../graphics/shader.hpp"

#include <utility>
#include <vector>

namespace engine::debug {

  struct Line {
    geometry::Vector<3> A, B;
    geometry::Vector<3> color;

    Line(const geometry::Vector<3>& A, const geometry::Vector<3>& B)
            : Line(A, B, geometry::Vector<3>(1.0F, 0.0F, 0.0F)) {}

    Line(geometry::Vector<3> A, geometry::Vector<3> B, geometry::Vector<3> color)
            : A(A),
              B(B),
              color(color) {}
  };

  class DebugDrawer {
  public:
    DebugDrawer();

    // Mutators
    void render(const geometry::Matrix<4>& view_projection_matrix);
    void draw_line(const geometry::Vector<3>& from, const geometry::Vector<3>& to);
    void draw_line(const geometry::Vector<3>& from, const geometry::Vector<3>& to, const geometry::Vector<3>& color);
    void draw_transform(const geometry::Transform& transform);
    void draw_rectangle(const geometry::Rectangle& rectangle);
    void set_line_width(float width);

  private:
    float line_width = 1.0F;

    graphics::Shader shader;

    std::vector<Line> line_queue;
  };

}
