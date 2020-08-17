#pragma once

namespace engine::geometry {

  /// @brief A set of constants commonly used with angles.
  /// @{
  const float pi  = 3.14159265359F; ///< @see https://www.wikiwand.com/en/Pi
  const float tau = 2.0F * pi;      ///< @see https://www.wikiwand.com/en/Tau
  /// @}

  /// @brief Angle provides a uniform interface for storing angles.
  ///
  /// Its responsibility is to abstract away the relation between turns, radians, degrees, and gradians.
  ///
  /// @see https://www.wikiwand.com/en/Angle
  /// @see https://www.wikiwand.com/en/Turn_(angle)
  /// @see https://www.wikiwand.com/en/Radian
  /// @see https://www.wikiwand.com/en/Degree_(angle)
  /// @see https://www.wikiwand.com/en/Gradian
  class Angle {
  public:
    /// @brief Unit enumerates all the supported angle units.
    enum class Unit {
      TURNS,
      RADIANS,
      DEGREES,
      GRADIANS,
    };

    /// @brief Creates the identity angle.
    explicit Angle();

    /// @brief Creates a specific angle.
    ///
    /// The created angle will be of \p angle amount in the \p unit angle unit.
    explicit Angle(float angle, Unit unit = Unit::RADIANS);

    /// @name Mutators
    /// @{

    /// @brief Sets this angle to the sum of this angle and angle \p other.
    auto operator+=(const Angle& other) -> Angle;

    /// @brief Sets this angle to the difference of this angle and angle \p other.
    auto operator-=(const Angle& other) -> Angle;

    /// @brief Sets the current angle.
    ///
    /// The new angle will be set to \p angle amount in the \p unit angle unit.
    void set(float angle, Unit unit = Unit::RADIANS);

    /// @}
    /// @name Accessors
    /// @{

    /// @brief Checks if this angle is equal to angle \p other.
    [[nodiscard]] auto operator==(const Angle& other) const -> bool;

    /// @brief Checks if this angle differs from angle \p other.
    [[nodiscard]] auto operator!=(const Angle& other) const -> bool;

    /// @brief Creates the sum angle of this angle and angle \p other.
    [[nodiscard]] auto operator+(const Angle& other) const -> Angle;

    /// @brief Creates the difference angle of this angle and angle \p other.
    [[nodiscard]] auto operator-(const Angle& other) const -> Angle;

    /// @brief Creates a copy of this angle that is multiplied by \p scalar.
    [[nodiscard]] auto operator*(float scalar) const -> Angle;

    /// @brief Creates a copy of this angle that is divided by \p scalar.
    [[nodiscard]] auto operator/(float scalar) const -> Angle;

    /// @brief Creates a duplicate of this angle, but wrapped around the range [0, \p modulo].
    [[nodiscard]] auto modulo(const Angle& modulo = Angle(tau)) const -> Angle;

    /// @brief The current angle in turns.
    [[nodiscard]] auto turns() const -> float;

    /// @brief The current angle in radians.
    [[nodiscard]] auto radians() const -> float;

    /// @brief The current angle in degrees.
    [[nodiscard]] auto degrees() const -> float;

    /// @brief The current angle in gradians.
    [[nodiscard]] auto gradians() const -> float;

    /// @}

  private:
    /// @{
    /// Private state.
    float _angle_in_radians = 0.0F;
    /// @}
  };

}
