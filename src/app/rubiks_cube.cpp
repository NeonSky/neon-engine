#include "rubiks_cube.hpp"

#include <utility>

#include "../engine/debug/logger.hpp"
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

RubiksCube::RubiksCube(engine::scene::Node& node) {

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

        _pieces[z][y][x] = std::experimental::make_observer(&node.add_child());
        _pieces[z][y][x]->add_component<RubiksCubePiece>(*_pieces[z][y][x], geometry::Transform(pos), color_config);
        _pieces[z][y][x]->add_component<engine::geometry::Transform>(pos);
      }
    }
  }
}

void RubiksCube::rotate_left(bool ccw) {
  geometry::Rotation rot = geometry::Rotation(geometry::pi / 2.0F * (ccw ? 1.0F : -1.0F), 0.0F, 0.0F);

  for (unsigned int z = 0; z < 3; z++) {
    for (unsigned int y = 0; y < 3; y++) {
      auto& t = _pieces[z][y][0]->component<geometry::Transform>();
      t                      = geometry::Transform(rot.matrix() * t.position(),
                              rot * t.orientation().rotation());
    }
  }

  // Move corner pieces
  std::swap(_pieces[0][0][0], _pieces[2][0][0]);
  std::swap(_pieces[0][2][0], _pieces[2][2][0]);

  if (ccw)
    std::swap(_pieces[0][0][0], _pieces[2][2][0]);
  else
    std::swap(_pieces[2][0][0], _pieces[0][2][0]);

  // Move center pieces
  std::swap(_pieces[0][1][0], _pieces[1][0][0]);
  std::swap(_pieces[2][1][0], _pieces[1][2][0]);

  if (ccw)
    std::swap(_pieces[0][1][0], _pieces[2][1][0]);
  else
    std::swap(_pieces[1][0][0], _pieces[1][2][0]);
}

void RubiksCube::rotate_right(bool ccw) {
  geometry::Rotation rot = geometry::Rotation(geometry::pi / 2.0F * (ccw ? 1.0F : -1.0F), 0.0F, 0.0F);

  for (unsigned int z = 0; z < 3; z++) {
    for (unsigned int y = 0; y < 3; y++) {
      auto& t = _pieces[z][y][2]->component<geometry::Transform>();
      t                      = geometry::Transform(rot.matrix() * t.position(),
                              rot * t.orientation().rotation());
    }
  }

  // Move corner pieces
  std::swap(_pieces[0][0][2], _pieces[2][0][2]);
  std::swap(_pieces[0][2][2], _pieces[2][2][2]);

  if (ccw)
    std::swap(_pieces[0][0][2], _pieces[2][2][2]);
  else
    std::swap(_pieces[2][0][2], _pieces[0][2][2]);

  // Move center pieces
  std::swap(_pieces[0][1][2], _pieces[1][0][2]);
  std::swap(_pieces[2][1][2], _pieces[1][2][2]);

  if (ccw)
    std::swap(_pieces[0][1][2], _pieces[2][1][2]);
  else
    std::swap(_pieces[1][0][2], _pieces[1][2][2]);
}

void RubiksCube::rotate_bot(bool ccw) {
  geometry::Rotation rot = geometry::Rotation(0.0F, geometry::pi / 2.0F * (ccw ? 1.0F : -1.0F), 0.0F);

  for (unsigned int z = 0; z < 3; z++) {
    for (unsigned int x = 0; x < 3; x++) {
      auto& t = _pieces[z][0][x]->component<geometry::Transform>();
      t                      = geometry::Transform(rot.matrix() * t.position(),
                              rot * t.orientation().rotation());
    }
  }

  // Move corner pieces
  std::swap(_pieces[0][0][0], _pieces[2][0][0]);
  std::swap(_pieces[0][0][2], _pieces[2][0][2]);

  if (ccw)
    std::swap(_pieces[0][0][2], _pieces[2][0][0]);
  else
    std::swap(_pieces[0][0][0], _pieces[2][0][2]);

  // Move center pieces
  std::swap(_pieces[0][0][1], _pieces[1][0][0]);
  std::swap(_pieces[1][0][2], _pieces[2][0][1]);

  if (ccw)
    std::swap(_pieces[1][0][0], _pieces[1][0][2]);
  else
    std::swap(_pieces[0][0][1], _pieces[2][0][1]);
}

void RubiksCube::rotate_top(bool ccw) {
  geometry::Rotation rot = geometry::Rotation(0.0F, (ccw ? 1.0F : -1.0F) * geometry::pi / 2.0F, 0.0F);

  for (unsigned int z = 0; z < 3; z++) {
    for (unsigned int x = 0; x < 3; x++) {
      auto& t = _pieces[z][2][x]->component<geometry::Transform>();
      t                      = geometry::Transform(rot.matrix() * t.position(),
                              rot * t.orientation().rotation());
    }
  }

  // // Move corner pieces
  std::swap(_pieces[0][2][0], _pieces[2][2][0]);
  std::swap(_pieces[0][2][2], _pieces[2][2][2]);

  if (ccw)
    std::swap(_pieces[0][2][2], _pieces[2][2][0]);
  else
    std::swap(_pieces[0][2][0], _pieces[2][2][2]);

  // // Move center pieces
  std::swap(_pieces[0][2][1], _pieces[1][2][0]);
  std::swap(_pieces[1][2][2], _pieces[2][2][1]);

  if (ccw)
    std::swap(_pieces[1][2][0], _pieces[1][2][2]);
  else
    std::swap(_pieces[0][2][1], _pieces[2][2][1]);
}

void RubiksCube::rotate_back(bool ccw) {
  geometry::Rotation rot = geometry::Rotation(0.0F, 0.0F, geometry::pi / 2.0F * (ccw ? 1.0F : -1.0F));

  for (unsigned int y = 0; y < 3; y++) {
    for (unsigned int x = 0; x < 3; x++) {
      auto& t = _pieces[0][y][x]->component<geometry::Transform>();
      t                      = geometry::Transform(rot.matrix() * t.position(),
                              rot * t.orientation().rotation());
    }
  }

  // Move corner pieces
  std::swap(_pieces[0][0][0], _pieces[0][0][2]);
  std::swap(_pieces[0][2][0], _pieces[0][2][2]);

  if (ccw)
    std::swap(_pieces[0][2][0], _pieces[0][0][2]);
  else
    std::swap(_pieces[0][0][0], _pieces[0][2][2]);

  // Move center pieces
  std::swap(_pieces[0][1][0], _pieces[0][0][1]);
  std::swap(_pieces[0][2][1], _pieces[0][1][2]);

  if (ccw)
    std::swap(_pieces[0][0][1], _pieces[0][2][1]);
  else
    std::swap(_pieces[0][1][0], _pieces[0][1][2]);
}

void RubiksCube::rotate_front(bool ccw) {
  geometry::Rotation rot = geometry::Rotation(0.0F, 0.0F, geometry::pi / 2.0F * (ccw ? 1.0F : -1.0F));

  for (unsigned int y = 0; y < 3; y++) {
    for (unsigned int x = 0; x < 3; x++) {
      auto& t = _pieces[2][y][x]->component<geometry::Transform>();
      t                      = geometry::Transform(rot.matrix() * t.position(),
                              rot * t.orientation().rotation());
    }
  }

  // Move corner pieces
  std::swap(_pieces[2][0][0], _pieces[2][0][2]);
  std::swap(_pieces[2][2][0], _pieces[2][2][2]);

  if (ccw)
    std::swap(_pieces[2][2][0], _pieces[2][0][2]);
  else
    std::swap(_pieces[2][0][0], _pieces[2][2][2]);

  // Move center pieces
  std::swap(_pieces[2][1][0], _pieces[2][0][1]);
  std::swap(_pieces[2][2][1], _pieces[2][1][2]);

  if (ccw)
    std::swap(_pieces[2][0][1], _pieces[2][2][1]);
  else
    std::swap(_pieces[2][1][0], _pieces[2][1][2]);
}
