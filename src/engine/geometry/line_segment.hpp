#pragma once

#include "point.hpp"
#include "vector.hpp"

#include "../debug/logger.hpp"

namespace engine::geometry {

  /// @brief LineSegment represents a line between two finite points, A and B.
  ///
  /// @see https://www.wikiwand.com/en/Line_(geometry)
  template <unsigned int N>
  class LineSegment {
  public:
    /// @brief Creates a specific line segment.
    ///
    /// Creates a line segment between point \p a and point \p b.
    explicit LineSegment(const Point<N>& a, const Point<N>& b);

    /// @name Accessors
    /// @{

    /// @brief Point A.
    auto a() -> const Point<N>&;

    /// @brief Point B.
    auto b() -> const Point<N>&;

    /// @}

  private:
    /// @{
    /// Private state.
    Point<N> _a;
    Point<N> _b;
    /// @}
  };

  template <unsigned int N>
  LineSegment<N>::LineSegment(const Point<N>& a, const Point<N>& b)
          : _a(a),
            _b(b) {}

  template <unsigned int N>
  auto LineSegment<N>::a() -> const Point<N>& {
    return _a;
  }

  template <unsigned int N>
  auto LineSegment<N>::b() -> const Point<N>& {
    return _b;
  }
}
