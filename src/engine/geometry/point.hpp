#pragma once

#include "../debug/json.hpp"

#include <array>

namespace engine::geometry {

  /// @brief Point represents a position in space.
  ///
  /// Its responsibility is to provide a common data structure for N-dimensional positions.
  ///
  /// @see https://www.wikiwand.com/en/Point_(geometry)
  template <unsigned int N>
  class Point {
  public:
    /// @brief Creates the origin.
    ///
    /// @see https://www.wikiwand.com/en/Origin_(mathematics)
    explicit Point();

    /// @brief Creates a specific point.
    ///
    /// The created point will have \p coordinates as its coordinates.
    explicit Point(std::array<float, N> coordinates);

    /// @name Mutators
    /// @{

    /// @brief The \p i th coordinate.
    auto operator[](unsigned int index) -> float&;

    /// @brief The memory address of the first coordinate.
    auto begin() -> float*;

    /// @brief The memory address following the last coordinate.
    auto end() -> float*;

    /// @}
    /// @name Accessors
    /// @{

    /// @brief Converts the point to a different dimension.
    ///
    /// If the new point has fewer dimensions, then coordinates of higher dimensions will be omitted.
    /// If the new point has more dimensions, then the new coordinates will be set to 0.
    template <unsigned int M>
    operator Point<M>();

    /// @brief The \p i th coordinate.
    auto operator[](unsigned int i) const -> float;

    /// @brief Checks if this point has the same coordinates as point \p other.
    auto operator==(const Point<N>& other) const -> bool;

    /// @brief Checks if this point has different coordinates than point \p other.
    auto operator!=(const Point<N>& other) const -> bool;

    /// @brief The memory address of the first coordinate.
    auto begin() const -> const float*;

    /// @brief The memory address following the last coordinate.
    auto end() const -> const float*;

    /// @brief Serializes the current state to JSON.
    [[nodiscard]] auto to_json() const -> debug::JSON;

    /// @}

  private:
    /// @{
    /// Private state.
    std::array<float, N> _coordinates{};
    /// @}
  };

  template <unsigned int N>
  Point<N>::Point() = default;

  template <unsigned int N>
  Point<N>::Point(std::array<float, N> coordinates)
          : _coordinates(coordinates) {}

  template <unsigned int N>
  template <unsigned int M>
  Point<N>::operator Point<M>() {
    Point<M> res;
    if constexpr (M < N)
      std::copy(_coordinates.begin(), _coordinates.begin() + M, res.begin());
    else
      std::copy(_coordinates.begin(), _coordinates.end(), res.begin());
    return res;
  }

  template <unsigned int N>
  auto Point<N>::operator[](unsigned int i) -> float& {
    return _coordinates[i];
  }

  template <unsigned int N>
  auto Point<N>::begin() -> float* {
    return _coordinates.begin();
  }

  template <unsigned int N>
  auto Point<N>::end() -> float* {
    return _coordinates.end();
  }

  template <unsigned int N>
  auto Point<N>::operator[](unsigned int i) const -> float {
    return _coordinates[i];
  }

  template <unsigned int N>
  auto Point<N>::operator==(const Point<N>& other) const -> bool {
    static const float tolerance = 0.000001F;

    // Each coordinate must match with `tolerance` precision.
    for (unsigned int i = 0; i < N; i++)
      if (std::abs(_coordinates[i] - other._coordinates[i]) > tolerance)
        return false;

    return true;
  }

  template <unsigned int N>
  auto Point<N>::operator!=(const Point<N>& other) const -> bool {
    return !(*this == other);
  }

  template <unsigned int N>
  auto Point<N>::begin() const -> const float* {
    return _coordinates.begin();
  }

  template <unsigned int N>
  auto Point<N>::end() const -> const float* {
    return _coordinates.end();
  }

  template <unsigned int N>
  auto Point<N>::to_json() const -> debug::JSON {
    debug::JSON json = debug::JSON::array();
    for (auto& c : _coordinates)
      json.emplace_back(c);

    return json;
  };

}
