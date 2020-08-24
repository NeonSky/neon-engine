#pragma once

#include <array>

namespace engine::graphics {

  /// Color represents a 16-byte color evenly split into the 4 RGBA components.
  ///
  /// @see https://www.wikiwand.com/en/RGB_color_model
  /// @todo Support HSLA.
  class Color {
  public:
    /// @brief Creates a fully opaque black color.
    Color();

    /// @brief Creates a specific opaque color using the RGB model.
    Color(float red, float green, float blue);

    /// @brief Creates a specific color using the RGBA model.
    Color(float red, float green, float blue, float alpha);

    /// @brief Creates a specific opaque color using the RGB model.
    Color(std::array<float, 3> components);

    /// @brief Creates a specific color using the RGBA model.
    Color(std::array<float, 4> components);

    /// @name Accessors
    /// @{

    /// @brief Checks if this color is equal to color \p other.
    [[nodiscard]] auto operator==(const Color& other) const -> bool;

    /// @brief Checks if this color differs from color \p other.
    [[nodiscard]] auto operator!=(const Color& other) const -> bool;

    /// @brief The memory address of the first element.
    [[nodiscard]] auto begin() const -> const float*;

    /// @brief The memory address following the last element.
    [[nodiscard]] auto end() const -> const float*;

    /// @brief The red component of this color.
    [[nodiscard]] auto red() const -> float;

    /// @brief The green component of this color.
    [[nodiscard]] auto green() const -> float;

    /// @brief The blue component of this color.
    [[nodiscard]] auto blue() const -> float;

    /// @brief The transparency value of this color.
    [[nodiscard]] auto alpha() const -> float;

    /// @brief This color in the RGB model.
    [[nodiscard]] auto rgb() const -> std::array<float, 3>;

    /// @brief This color in the RGBA model.
    [[nodiscard]] auto rgba() const -> std::array<float, 4>;

    /// @}

  private:
    /// @{
    /// Private state.
    std::array<float, 4> _components;
    /// @}
  };

}
