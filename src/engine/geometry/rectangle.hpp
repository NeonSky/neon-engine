#pragma once

#include "rigidbody.hpp"
#include "vector.hpp"

namespace engine::geometry {

  /// @brief Rectangle represents a 2D rectangle in 3D space.
  ///
  /// @see https://www.wikiwand.com/en/Rectangle
  class Rectangle {
  public:
    /// @brief Creates a 1.0 x 1.0 square on the XY plane.
    Rectangle();

    /// @brief Creates a specific rectangle.
    ///
    /// The created rectangle will have the position and orientation specified
    /// by \p rigidbody and the dimensions specified by \p width and \p height.
    Rectangle(Rigidbody rigidbody, float width = 1.0F, float height = 1.0F);

    /// @name Accessors
    /// @{

    /// @brief The rigidbody of this rectangle.
    [[nodiscard]] auto rigidbody() const -> const Rigidbody&;

    /// @brief The width of this rectangle.
    [[nodiscard]] auto width() const -> float;

    /// @brief The height of this rectangle.
    [[nodiscard]] auto height() const -> float;

    /// @brief The bottom-left corner of this rectangle.
    [[nodiscard]] auto botleft() const -> Vector<3>;

    /// @brief The bottom-right corner of this rectangle.
    [[nodiscard]] auto botright() const -> Vector<3>;

    /// @brief The top-left corner of this rectangle.
    [[nodiscard]] auto topleft() const -> Vector<3>;

    /// @brief The top-right corner of this rectangle.
    [[nodiscard]] auto topright() const -> Vector<3>;

    /// @brief Serializes the current state to JSON.
    [[nodiscard]] auto to_json(bool debug = false) const -> debug::JSON;

    /// @}

  private:
    /// @brief Updates this rectangle's corners based on rigidbody, width and height.
    void update_corners();

    /// @{
    /// Private state.
    const Rigidbody _rigidbody;
    float _width;
    float _height;

    Vector<3> _botleft{};
    Vector<3> _botright{};
    Vector<3> _topleft{};
    Vector<3> _topright{};
    /// @}
  };
}
