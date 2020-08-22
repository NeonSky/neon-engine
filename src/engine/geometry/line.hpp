#pragma once

#include "point.hpp"
#include "vector.hpp"

#include "../debug/logger.hpp"

namespace engine::geometry {

  /// @brief Line represents an infinite line in N-dimensional space.
  ///
  /// @see https://www.wikiwand.com/en/Line_(geometry)
  template <unsigned int N>
  class Line {
  public:
    /// @brief Creates a specific line.
    ///
    /// The creates line will intersect point \p a and point \p b.
    explicit Line(const Point<N>& a, const Point<N>& b);

    /// @name Accessors
    /// @{

    /// @brief Checks if this line spans the same points as line \p other.
    auto operator==(const Line<N>& other) const -> bool;

    /// @brief Checks if this line is different from line \p other.
    auto operator!=(const Line<N>& other) const -> bool;

    /// @brief Checks if the point \p other intersects with this line.
    auto intersects(Point<N> other) const -> bool;

    /// @brief Checks if the line \p other intersects with this line.
    ///
    /// The returned pointed is a null pointer if the lines do not intersect.
    /// Otherwise, it will be equal to the intersection point.
    auto intersects(Line<N> other) const -> Point<N>*;

    /// @}

  private:
    /// @{
    /// Private state.
    Point<N> _pivot;
    UnitVector<N> _vector; //< All points reachable by this vector as it is rescaled belongs to this line.
    /// @}
  };

  template <unsigned int N>
  Line<N>::Line(const Point<N>& a, const Point<N>& b)
          : _pivot(a),
            _vector(Vector<N, true>(a, b)) {}

  template <unsigned int N>
  auto Line<N>::operator==(const Line<N>& other) const -> bool {
    // Sufficient to check insterection with any 2 unique points from other line.
    bool check1 = intersects(other._pivot);
    bool check2 = intersects(other._vector.tip(other._pivot));

    return check1 && check2;
  }

  template <unsigned int N>
  auto Line<N>::operator!=(const Line<N>& other) const -> bool {
    return !(*this == other);
  }

  template <unsigned int N>
  auto Line<N>::intersects(Point<N> other) const -> bool {
    // In 1D there only exists one line (the x-axis) and it intersects with all points.
    if constexpr (N == 1)
      return true;

    float dist       = _pivot.euclidean_distance(other);
    Vector<N> scaled = _vector * dist;

    return scaled.tip(_pivot) == other || (-scaled).tip(_pivot) == other;
  }

  template <unsigned int N>
  auto Line<N>::intersects(Line<N> other) const -> Point<N>* {
    LOG_ERROR("Not implemented yet");
    other;
    return nullptr;
  }
}
