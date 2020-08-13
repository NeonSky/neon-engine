#pragma once

#include "matrix.hpp"
#include "orientation.hpp"
#include "vector.hpp"

namespace engine::geometry {

  /// @brief Transform models a generic 3D affine transformation.
  ///
  /// Its responsibility is to combine specific affine transformations such as translation, reflection, and scale.
  /// The order in which these separate transformations are applied is:
  /// 1. Scale
  /// 2. Rotation
  /// 3. Translation
  ///
  /// @see https://www.wikiwand.com/en/Transformation_(function)
  /// @see https://www.wikiwand.com/en/Affine_transformation
  /// @todo extract rigid body. Doesn't make sense that camera has scale.
  class Transform {
  public:
    /// @brief Creates the identity transform.
    Transform();

    /// @brief Creates a transform that only translates.
    ///
    /// The created transform translates by \p position.
    Transform(const Vector<3>& position);

    /// @brief Creates a transform that only rotates and translates.
    ///
    /// The created transform rotates by \p rotation and translates by \p position.
    Transform(const Vector<3>& position, const Orientation& orientation);

    /// @brief Creates a transform that scales, rotates, and translates.
    ///
    /// The created transform scales by \p scale, rotates by \p rotation, and translates by \p position.
    Transform(const Vector<3>& position, const Orientation& orientation, const Vector<3>& scale);

    /// @name Mutators
    /// @{

    /// @brief The position of this transform.
    [[nodiscard]] auto position() -> Vector<3>&;

    /// @brief The orientation of this transform.
    [[nodiscard]] auto orientation() -> Orientation&;

    /// @brief The scale of this transform.
    [[nodiscard]] auto scale() -> Vector<3>&;

    /// @}
    /// @name Accessors
    /// @{

    /// @brief Checks if this transform is equal to transform \p other.
    [[nodiscard]] auto operator==(const Transform& other) const -> bool;

    /// @brief Checks if this transform differs from transform \p other.
    [[nodiscard]] auto operator!=(const Transform& other) const -> bool;

    /// @brief Creates a column-major matrix in homogeneous coordinates that represents this transform.
    ///
    /// The individual transforms are applied in the following order.
    /// 1. Scale
    /// 2. Rotate
    /// 3. Translate
    [[nodiscard]] auto matrix() const -> Matrix<4>;

    /// @brief The position of this transform.
    [[nodiscard]] auto position() const -> const Vector<3>&;

    /// @brief The orientation of this transform.
    [[nodiscard]] auto orientation() const -> const Orientation&;

    /// @brief The scale of this transform.
    [[nodiscard]] auto scale() const -> const Vector<3>&;

    /// @brief This transform's right vector.
    [[nodiscard]] auto right() const -> Vector<3>;

    /// @brief This transform's up vector.
    [[nodiscard]] auto up() const -> Vector<3>;

    /// @brief This transform's forward vector.
    [[nodiscard]] auto forward() const -> Vector<3>;

    /// @brief Serializes the current state to JSON.
    [[nodiscard]] auto to_json(bool debug = false) const -> debug::JSON;

    /// @}

  private:
    /// @{
    /// Private state.
    Vector<3> _position;
    Orientation _orientation;
    Vector<3> _scale;
    /// @}
  };
}
