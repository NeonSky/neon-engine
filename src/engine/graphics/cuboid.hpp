#pragma once

#include "../geometry/cuboid.hpp"
#include "color.hpp"
#include "renderer.hpp"
#include "shader.hpp"

namespace engine::graphics {

  /// @todo Consider relying on a geometry shader to go from Transform -> 8 corners. Sending a Transform is quite expensive though. Would be worthwhile if the cuboid was a AABB.
  /// @todo Add colored outline option by using Polygon Offset.
  /// @todo Remove transform..? Weird to have transform component and this transform.
  /// @todo REMOVE. Use component::cuboid.
  class Cuboid {
  public:
    Cuboid(Renderer& renderer, geometry::Cuboid geometry, const Color& color);

    void compile();
    void render(geometry::Matrix<4> view_projection);

    auto transform() -> geometry::Transform&;

  private:
    void update_vbos();

    std::reference_wrapper<Renderer> _renderer;
    geometry::Cuboid _geometry;
    Color _color;
    Shader _shader;
    unsigned int _vao  = 0;
    unsigned int _vbo  = 0;
    bool _draw_corners = false;
  };
}
