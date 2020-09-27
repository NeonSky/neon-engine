#pragma once

#include "rigidbody.hpp"

namespace engine::geometry {

  /// @brief Transform models a generic 3D affine transformation.
  ///
  /// It builds upon the Rigidbody geometry which supports all mass-preserving transformations.
  /// Transform expands its features by also supporting scale.
  /// The order in which these separate transformations are applied is:
  /// 1. Scale
  /// 2. Rotation
  /// 3. Translation
  ///
  /// @see https://www.wikiwand.com/en/Transformation_(function)
  /// @see https://www.wikiwand.com/en/Affine_transformation
  class Transform final : public Rigidbody {
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
    [[nodiscard]] auto matrix() const -> Matrix<4> override;

    /// @brief The scale of this transform.
    [[nodiscard]] auto scale() const -> const Vector<3>&;

    /// @brief Serializes the current state to JSON.
    [[nodiscard]] auto to_json(bool debug = false) const -> debug::JSON override;

    /// @}

  private:
    /// @{
    /// Private state.
    Vector<3> _scale;
    /// @}
  };
}
