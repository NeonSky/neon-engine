#pragma once

#include "rotation.hpp"
#include "vector.hpp"

namespace engine::geometry {

  /// @brief Orientation defines the reference orientation of the world.
  ///
  /// @see https://www.wikiwand.com/en/Orientation_(geometry)
  /// @todo flip() implementation should not have to extract submatrix.
  class Orientation {
  public:
    /// @brief The reference right direction of the world.
    static const UnitVector<3> world_right;

    /// @brief The reference up direction of the world.
    static const UnitVector<3> world_up;

    /// @brief The reference forward direction of the world.
    static const UnitVector<3> world_forward;

    /// @brief Creates the identity orientation.
    Orientation();

    /// @brief Creates a specific orientation.
    ///
    /// The created orientation will be rotated by \p rotation relative to the world reference directions.
    Orientation(Rotation rotation);

    /// @name Mutators
    /// @{

    /// @brief This orientation's rotation relative to the world reference directions.
    [[nodiscard]] auto rotation() -> Rotation&;

    /// @brief Flips the current orientation about the axis spanned by \p axis.
    void flip(UnitVector<3> axis = world_up);

    /// @}
    /// @name Accessors
    /// @{

    /// @brief Checks if this orientation is equal to orientation \p other.
    [[nodiscard]] auto operator==(const Orientation& other) const -> bool;

    /// @brief Checks if this orientation differs from orientation \p other.
    [[nodiscard]] auto operator!=(const Orientation& other) const -> bool;

    /// @brief This orientation's rotation relative to the world reference directions.
    [[nodiscard]] auto rotation() const -> const Rotation&;

    /// @brief This orientation's right vector.
    [[nodiscard]] auto right() const -> UnitVector<3>;

    /// @brief This orientation's up vector.
    [[nodiscard]] auto up() const -> UnitVector<3>;

    /// @brief This orientation's forward vector.
    [[nodiscard]] auto forward() const -> UnitVector<3>;

    /// @brief Serializes the current state to JSON.
    [[nodiscard]] auto to_json(bool debug = false) const -> debug::JSON;

    /// @}

  private:
    /// @{
    /// Private state.
    Rotation _rotation;
    /// @}
  };
}
