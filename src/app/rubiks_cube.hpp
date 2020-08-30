#pragma once

#include "../engine/geometry/transform.hpp"
#include "../engine/graphics/renderer.hpp"
#include "../engine/graphics/shader.hpp"
#include "rubiks_cube_piece.hpp"

namespace app {

  class RubiksCube {
  public:
    RubiksCube(engine::graphics::Renderer& renderer);
    RubiksCube(engine::graphics::Renderer& renderer, engine::geometry::Transform transform);

    auto transform() -> engine::geometry::Transform&;

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

    /// @brief Renders this model's current state.
    void render(engine::geometry::Matrix<4> view_projection);

  private:
    /// @{
    /// Private state.
    std::reference_wrapper<engine::graphics::Renderer> _renderer;
    engine::geometry::Transform _transform;
    std::array<std::array<std::array<std::unique_ptr<RubiksCubePiece>, 3>, 3>, 3> _pieces;
    /// @}
  };

}
