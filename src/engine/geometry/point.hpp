#pragma once

#include "../debug/json.hpp"

#include <array>

namespace engine::geometry {

  /// @brief Point represents a position in N-dimensional space.
  ///
  /// @see https://www.wikiwand.com/en/Point_(geometry)
  template <unsigned int N>
  class Point {
  public:
    /// @brief Creates the origin.
    ///
    /// @see https://www.wikiwand.com/en/Origin_(mathematics)
    explicit Point();

    /// @brief Creates a point in the x-axis.
    template <unsigned int N2 = N, typename std::enable_if_t<(N2 == 1), int> = 0>
    explicit Point(float x);

    /// @brief Creates a point in the xy-plane.
    template <unsigned int N2 = N, typename std::enable_if_t<(N2 == 2), int> = 0>
    explicit Point(float x, float y);

    /// @brief Creates a point in the xyz-space.
    template <unsigned int N2 = N, typename std::enable_if_t<(N2 == 3), int> = 0>
    explicit Point(float x, float y, float z);

    /// @brief Creates a point in the xyzw-space.
    template <unsigned int N2 = N, typename std::enable_if_t<(N2 == 4), int> = 0>
    explicit Point(float x, float y, float z, float w);

    /// @brief Creates a specific point.
    ///
    /// The created point will have \p coordinates as its coordinates.
    explicit Point(std::array<float, N> coordinates);

    /// @name Mutators
    /// @{

    /// @brief The memory address of the first coordinate.
    [[nodiscard]] auto begin() -> float*;

    /// @brief The memory address following the last coordinate.
    [[nodiscard]] auto end() -> float*;

    /// @brief The \p i th coordinate.
    auto operator[](unsigned int index) -> float&;

    /// @}
    /// @name Accessors
    /// @{

    /// @brief Converts this point to a different dimension.
    ///
    /// If the new point has fewer dimensions, then coordinates of higher dimensions will be omitted.
    /// If the new point has more dimensions, then the new coordinates will be set to 0.
    template <unsigned int M>
    [[nodiscard]] operator Point<M>() const;

    /// @brief The \p i th coordinate.
    [[nodiscard]] auto operator[](unsigned int i) const -> float;

    /// @brief Checks if this point has the same coordinates as point \p other.
    [[nodiscard]] auto operator==(const Point<N>& other) const -> bool;

    /// @brief Checks if this point has different coordinates than point \p other.
    [[nodiscard]] auto operator!=(const Point<N>& other) const -> bool;

    /// @brief The memory address of the first coordinate.
    [[nodiscard]] auto begin() const -> const float*;

    /// @brief The memory address following the last coordinate.
    [[nodiscard]] auto end() const -> const float*;

    /// @brief The squared euclidean distance between this point and point \p other.
    ///
    /// @see https://www.wikiwand.com/en/Euclidean_distance
    [[nodiscard]] auto euclidean_distance_squared(const Point<N>& other) const -> float;

    /// @brief The euclidean distance between this point and point \p other.
    ///
    /// @see https://www.wikiwand.com/en/Euclidean_distance
    [[nodiscard]] auto euclidean_distance(const Point<N>& other) const -> float;

    /// @brief The manhattan distance between this point and point \p other.
    ///
    /// @see https://en.wiktionary.org/wiki/Manhattan_distance
    /// @see https://www.wikiwand.com/en/Taxicab_geometry
    [[nodiscard]] auto manhattan_distance(const Point<N>& other) const -> float;

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
  template <unsigned int N2, typename std::enable_if_t<(N2 == 1), int>>
  Point<N>::Point(float x)
          : _coordinates(std::array<float, N2>{x}) {}

  template <unsigned int N>
  template <unsigned int N2, typename std::enable_if_t<(N2 == 2), int>>
  Point<N>::Point(float x, float y)
          : _coordinates(std::array<float, N2>{x, y}) {}

  template <unsigned int N>
  template <unsigned int N2, typename std::enable_if_t<(N2 == 3), int>>
  Point<N>::Point(float x, float y, float z)
          : _coordinates(std::array<float, N2>{x, y, z}) {}

  template <unsigned int N>
  template <unsigned int N2, typename std::enable_if_t<(N2 == 4), int>>
  Point<N>::Point(float x, float y, float z, float w)
          : _coordinates(std::array<float, N2>{x, y, z, w}) {}

  template <unsigned int N>
  Point<N>::Point(std::array<float, N> coordinates)
          : _coordinates(coordinates) {}

  /// @internal We copy as much data as we can from this point and let the remaining coordinates be their default value.
  template <unsigned int N>
  template <unsigned int M>
  Point<N>::operator Point<M>() const {
    Point<M> res;

    const float* src_start = _coordinates.begin();
    const float* src_end   = std::min(_coordinates.begin() + M, _coordinates.end());
    std::copy(src_start, src_end, res.begin()); // LCOV_EXCL_BR_LINE

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
    static const float tolerance = 0.00001F;

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
  auto Point<N>::euclidean_distance_squared(const Point<N>& other) const -> float {
    float sum = 0.0F;
    for (unsigned int i = 0; i < N; i++)
      sum += std::pow(_coordinates[i] - other[i], 2); // See: https://stackoverflow.com/a/6321226/8418261

    return sum;
  }

  template <unsigned int N>
  auto Point<N>::euclidean_distance(const Point<N>& other) const -> float {
    return sqrt(euclidean_distance_squared(other));
  }

  template <unsigned int N>
  auto Point<N>::manhattan_distance(const Point<N>& other) const -> float {
    float sum = 0;
    for (unsigned int i = 0; i < N; i++)
      sum += std::abs(_coordinates[i] - other[i]);

    return sum;
  }

  template <unsigned int N>
  auto Point<N>::to_json() const -> debug::JSON {
    debug::JSON json = debug::JSON::array();
    for (auto& c : _coordinates)
      json.emplace_back(c); // LCOV_EXCL_BR_LINE

    return json;
  };

}
