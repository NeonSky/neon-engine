#pragma once

#include "../engine/geometry/transform.hpp"
#include "../engine/graphics/shader.hpp"
#include "../engine/scene/node.hpp"
#include "rubiks_cube_piece.hpp"

#include <experimental/memory>

namespace app {

  class RubiksCube {
  public:
    RubiksCube(engine::scene::Node& node);

    /// @brief Rotates the left face by 90 degrees.
    ///
    /// The rotation will be done counter-clockwise if \p ccw is true, otherwise the rotation will be clockwise.
    void rotate_left(bool ccw = true);

    /// @brief Rotates the right face by 90 degrees.
    ///
    /// The rotation will be done counter-clockwise if \p ccw is true, otherwise the rotation will be clockwise.
    void rotate_right(bool ccw = true);

    /// @brief Rotates the bottom face by 90 degrees.
    ///
    /// The rotation will be done counter-clockwise if \p ccw is true, otherwise the rotation will be clockwise.
    void rotate_bot(bool ccw = true);

    /// @brief Rotates the top face by 90 degrees.
    ///
    /// The rotation will be done counter-clockwise if \p ccw is true, otherwise the rotation will be clockwise.
    void rotate_top(bool ccw = true);

    /// @brief Rotates the back face by 90 degrees.
    ///
    /// The rotation will be done counter-clockwise if \p ccw is true, otherwise the rotation will be clockwise.
    void rotate_back(bool ccw = true);

    /// @brief Rotates the front face by 90 degrees.
    ///
    /// The rotation will be done counter-clockwise if \p ccw is true, otherwise the rotation will be clockwise.
    void rotate_front(bool ccw = true);

  private:
    /// @{
    /// Private state.
    std::array<std::array<std::array<std::experimental::observer_ptr<engine::scene::Node>, 3>, 3>, 3> _pieces;
    /// @}
  };

}
