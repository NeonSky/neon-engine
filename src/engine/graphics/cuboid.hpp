#pragma once

#include "../geometry/cuboid.hpp"
#include "shader.hpp"

namespace engine::graphics {

  /// @todo Consider relying on a geometry shader to go from Transform -> 8 corners. Sending a Transform is quite expensive though. Would be worthwhile if the cuboid was a AABB.
  /// @todo Add colored outline option by using Polygon Offset.
  class Cuboid {
  public:
    Cuboid(geometry::Cuboid geometry, geometry::Vector<3> color);

    void render(geometry::Matrix<4> view_projection, bool draw_corners = false);

    auto transform() -> geometry::Transform&;

  private:
    void update_vbos();

    geometry::Cuboid _geometry;
    geometry::Vector<3> _color;
    Shader _shader;
    GLuint _vao = 0;
    GLuint _vbo = 0;
  };
}
