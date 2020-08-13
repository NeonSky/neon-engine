#pragma once

#include "matrix.hpp"
#include "orientation.hpp"
#include "vector.hpp"

namespace engine::geometry {

  /// @brief Rigidbody models a 3D affine transformation that preserves mass distribution.
  ///
  /// Its responsibility is to combine the specific affine transformations translation and rotation.
  /// The order in which these separate transformations are applied is:
  /// 1. Rotation
  /// 2. Translation
  ///
  /// @see https://www.wikiwand.com/en/Rigid_body
  /// @see https://www.wikiwand.com/en/Transformation_(function)
  /// @see https://www.wikiwand.com/en/Affine_transformation
  class Rigidbody {
  public:
    /// @brief Creates the identity rigidbody.
    Rigidbody();

    /// @brief Creates a rigidbody that only translates.
    ///
    /// The created rigidbody translates by \p position.
    Rigidbody(const Vector<3>& position);

    /// @brief Creates a rigidbody that only rotates and translates.
    ///
    /// The created rigidbody rotates by \p rotation and translates by \p position.
    Rigidbody(const Vector<3>& position, const Orientation& orientation);

    /// @name Mutators
    /// @{

    /// @brief The position of this rigidbody.
    [[nodiscard]] auto position() -> Vector<3>&;

    /// @brief The orientation of this rigidbody.
    [[nodiscard]] auto orientation() -> Orientation&;

    /// @}
    /// @name Accessors
    /// @{

    /// @brief Checks if this rigidbody is equal to rigidbody \p other.
    [[nodiscard]] auto operator==(const Rigidbody& other) const -> bool;

    /// @brief Checks if this rigidbody differs from rigidbody \p other.
    [[nodiscard]] auto operator!=(const Rigidbody& other) const -> bool;

    /// @brief Creates a column-major matrix in homogeneous coordinates that represents this rigidbody.
    ///
    /// The individual rigidbodys are applied in the following order.
    /// 1. Rotate
    /// 2. Translate
    [[nodiscard]] virtual auto matrix() const -> Matrix<4>;

    /// @brief The position of this rigidbody.
    [[nodiscard]] auto position() const -> const Vector<3>&;

    /// @brief The orientation of this rigidbody.
    [[nodiscard]] auto orientation() const -> const Orientation&;

    /// @brief This rigidbody's right vector.
    [[nodiscard]] auto right() const -> Vector<3>;

    /// @brief This rigidbody's up vector.
    [[nodiscard]] auto up() const -> Vector<3>;

    /// @brief This rigidbody's forward vector.
    [[nodiscard]] auto forward() const -> Vector<3>;

    /// @brief Serializes the current state to JSON.
    [[nodiscard]] virtual auto to_json(bool debug = false) const -> debug::JSON;

    /// @}

  protected:
    /// @{
    /// Protected state.
    Vector<3> _position;
    Orientation _orientation;
    /// @}
  };
}
