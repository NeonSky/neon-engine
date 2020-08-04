#pragma once

#include "angle.hpp"
#include "matrix.hpp"
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
  /// @todo Add to_json
  /// @see https://www.wikiwand.com/en/Transformation_(function)
  /// @see https://www.wikiwand.com/en/Affine_transformation
  class Transform {
  public:
    /// @brief Creates the identity transform.
    Transform();

    /// @brief Creates a transform that translates.
    ///
    /// The created transform translates by \p position.
    Transform(const Vector<3>& position);

    /// @brief Creates a transform that rotates and translates.
    ///
    /// The created transform rotates by \p rotation and translates by \p position.
    Transform(const Vector<3>& position, const Vector<3>& rotation);

    /// @brief Creates a transform that scales, rotates, and translates.
    ///
    /// The created transform scales by \p scale, rotates by \p rotation, and translates by \p position.
    Transform(Vector<3> position, Vector<3> rotation, Vector<3> scale);

    /// @name Mutators
    /// @{

    /// @brief Sets the current rotation using aircraft principal axes.
    ///
    /// The new rotation will rotate by \p yaw around the yaw axis, \p pitch around the pitch axis, and \p roll around the roll axis.
    ///
    /// @see https://www.wikiwand.com/en/Aircraft_principal_axes
    void set_rotation(float yaw, float pitch, float roll);
    void flip_rotation();

    [[nodiscard]] auto position() -> Vector<3>&;
    [[nodiscard]] auto rotation() -> Vector<3>&;
    [[nodiscard]] auto scale() -> Vector<3>&;

    /// @}
    /// @name Accessors
    /// @{

    // Accessors
    static const Vector<4> world_right;
    static const Vector<4> world_up;
    static const Vector<4> world_forward;

    auto operator+(const Transform& other) const -> Transform;

    [[nodiscard]] auto matrix() const -> Matrix<4>;
    [[nodiscard]] auto forward() const -> Vector<3>;
    [[nodiscard]] auto up() const -> Vector<3>;
    [[nodiscard]] auto right() const -> Vector<3>;

    [[nodiscard]] auto yaw() const -> float;
    [[nodiscard]] auto pitch() const -> float;
    [[nodiscard]] auto roll() const -> float;

    [[nodiscard]] auto position() const -> const Vector<3>&;
    [[nodiscard]] auto rotation() const -> const Vector<3>&;
    [[nodiscard]] auto scale() const -> const Vector<3>&;

    /// @}

  private:
    /// @{
    /// Private state.
    Vector<3> _position;
    Vector<3> _rotation;
    Vector<3> _scale;
    /// @}

    /// @name Accessors
    /// @{

    /// @brief Produces a rotation matrix from the current rotation.
    ///
    /// Here we apply y-rotation (yaw), then x-rotation (pitch), and finally z-rotation (roll).
    [[nodiscard]] auto rotation_matrix() const -> Matrix<4>;

    /// @brief Produces a rotation matrix from the current rotation.
    ///
    /// Here we apply y-rotation (yaw), then x-rotation (pitch), and finally z-rotation (roll).
    [[nodiscard]] auto rotation_matrix_slow() const -> Matrix<4>;

    /// @}
  };
}
