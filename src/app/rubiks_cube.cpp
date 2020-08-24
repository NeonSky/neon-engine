#include "rubiks_cube.hpp"

#include <utility>

#include "../engine/debug/logger.hpp"
#include "../engine/graphics/cuboid.hpp"
#include "../engine/graphics/rectangle.hpp"

using namespace app;
using namespace engine;

static const graphics::Color blue(0.0F, 0.0F, 1.0F);
static const graphics::Color white(1.0F, 1.0F, 1.0F);
static const graphics::Color yellow(1.0F, 1.0F, 0.0F);
static const graphics::Color green(0.0F, 0.5F, 0.0F);
static const graphics::Color orange(1.0F, 0.65F, 0.0F);
static const graphics::Color red(1.0F, 0.0F, 0.0F);
static const graphics::Color black(0.0F, 0.0F, 0.0F);

RubiksCube::RubiksCube()
        : RubiksCube(geometry::Transform()) {}

RubiksCube::RubiksCube(engine::geometry::Transform transform)
        : _transform(std::move(transform)) {

  for (int z = 0; z < 3; z++) {
    for (int y = 0; y < 3; y++) {
      for (int x = 0; x < 3; x++) {

        auto pos = geometry::Vector<3>((float) x - 1.0F, (float) y - 1.0F, (float) z - 1.0F);

        RubiksCubePiece::ColorConfiguration color_config;
        color_config.left  = x == 0 ? yellow : black;
        color_config.right = x == 2 ? white : black;
        color_config.bot   = y == 0 ? green : black;
        color_config.top   = y == 2 ? blue : black;
        color_config.back  = z == 0 ? red : black;
        color_config.front = z == 2 ? orange : black;

        _pieces[z][y][x] = RubiksCubePiece(geometry::Transform(pos), color_config);
      }
    }
  }
}

auto RubiksCube::transform() -> engine::geometry::Transform& {
  return _transform;
}

void RubiksCube::render(geometry::Matrix<4> view_projection) {
  for (unsigned int z = 0; z < 3; z++)
    for (unsigned int y = 0; y < 3; y++)
      for (unsigned int x = 0; x < 3; x++)
        _pieces[z][y][x].render(view_projection * _transform.matrix());
}
