#pragma once

#include "../engine/geometry/transform.hpp"
#include "../engine/graphics/shader.hpp"
#include "rubiks_cube_piece.hpp"

namespace app {

  class RubiksCube {
  public:
    RubiksCube();
    RubiksCube(const engine::geometry::Transform& transform);

    auto transform() -> engine::geometry::Transform&;

    void render(engine::geometry::Matrix<4> view_projection);

  private:
    engine::geometry::Transform _transform;
    std::array<std::array<std::array<RubiksCubePiece, 3>, 3>, 3> _pieces;
  };

}
