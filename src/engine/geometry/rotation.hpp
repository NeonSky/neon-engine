#pragma once

#include "angle.hpp"
#include "matrix.hpp"

namespace engine::geometry {

  /// @brief Rotation represents an affine rotation in 3D space using aircraft principal axes.
  /// Angles are applied in the following order.
  /// 1. Pitch (x-axis)
  /// 2. Yaw   (y-axis)
  /// 3. Roll  (z-axis)
  ///
  /// @see https://www.wikiwand.com/en/Rotation
  /// @see https://www.wikiwand.com/en/Aircraft_principal_axes
  /// @see https://www.wikiwand.com/en/Euler_angles
  /// @see https://www.wikiwand.com/simple/Pitch,_yaw,_and_roll
  class Rotation {
  public:
    /// @brief Creates the identity rotation.
    explicit Rotation();

    /// @brief Creates a specific rotation.
    ///
    /// The created rotation will rotate by \p pitch about the x-axis, \p yaw about the y-axis, and \p roll about the z-axis.
    /// \p pitch, \p yaw, and \p roll are all assumed to be provided in the \p angle_unit unit.
    explicit Rotation(float pitch, float yaw, float roll, Angle::Unit angle_unit = Angle::Unit::RADIANS);

    /// @brief Creates a specific rotation.
    ///
    /// The created rotation will rotate by \p pitch about the x-axis, \p yaw about the y-axis, and \p roll about the z-axis.
    explicit Rotation(Angle pitch, Angle yaw, Angle roll);

    /// @name Mutators
    /// @{

    /// @brief The pitch of this rotation.
    auto pitch() -> Angle&;

    /// @brief The yaw of this rotation.
    auto yaw() -> Angle&;

    /// @brief The roll of this rotation.
    auto roll() -> Angle&;

    /// @}
    /// @name Accessors
    /// @{

    /// @brief Checks if this rotation is equal to rotation \p other.
    auto operator==(const Rotation& other) const -> bool;

    /// @brief Checks if this rotation differs from to rotation \p other.
    auto operator!=(const Rotation& other) const -> bool;

    /// @brief The pitch of this rotation.
    [[nodiscard]] auto pitch() const -> const Angle&;

    /// @brief The yaw of this rotation.
    [[nodiscard]] auto yaw() const -> const Angle&;

    /// @brief The roll of this rotation.
    [[nodiscard]] auto roll() const -> const Angle&;

    /// @brief Creates a rotation matrix from the current rotation.
    ///
    /// Uses the bottom matrix for the computation.
    ///
    /// @image html geometry/img1.png
    /// @see https://www.wikiwand.com/en/Rotation_matrix
    [[nodiscard]] auto matrix() const -> Matrix<3>;

    /// @brief Creates a rotation matrix from the current rotation.
    ///
    /// Uses the 3 top matrices for the computation.
    ///
    /// @image html geometry/img1.png
    /// @see https://www.wikiwand.com/en/Rotation_matrix
    [[nodiscard]] auto matrix_slow() const -> Matrix<3>;

    /// @brief Serializes the current state to JSON.
    [[nodiscard]] auto to_json(bool debug = false) const -> debug::JSON;

    /// @}

  private:
    /// @{
    /// Private state.
    Angle _pitch;
    Angle _yaw;
    Angle _roll;
    /// @}
  };
}
