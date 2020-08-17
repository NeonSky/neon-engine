#pragma once

#include "rectangle.hpp"
#include "transform.hpp"

namespace engine::geometry {

  /// @brief Cuboid represents a 3D rectangular cuboid such as a cube.
  ///
  /// @see https://www.wikiwand.com/en/Cuboid
  /// @see https://www.wikiwand.com/en/Cube
  class Cuboid {
  public:
    /// @brief Creates a 1.0 x 1.0 x 1.0 cube at the origin.
    Cuboid();

    /// @brief Creates a specific cuboid.
    ///
    /// The created cuboid will have \p transform as its transform.
    Cuboid(Transform transform);

    /// @name Mutators
    /// @{

    /// @brief The transform of this cuboid.
    auto transform() -> Transform&;

    /// @}
    /// @name Accessors
    /// @{

    /// @brief The left face of this cuboid.
    auto left_face() -> Rectangle;

    /// @brief The right face of this cuboid.
    auto right_face() -> Rectangle;

    /// @brief The bottom face of this cuboid.
    auto bottom_face() -> Rectangle;

    /// @brief The top face of this cuboid.
    auto top_face() -> Rectangle;

    /// @brief The back face of this cuboid.
    auto back_face() -> Rectangle;

    /// @brief The front face of this cuboid.
    auto front_face() -> Rectangle;

    /// @}

  private:
    /// @{
    /// Private state.
    Transform _transform;
    /// @}
  };

}
