#pragma once

#include "point.hpp"

#include "../debug/json.hpp"
#include "../debug/logger.hpp"

#include <array>

namespace engine::geometry {

  /// @todo Add cross product. Preferably generalized to N dimensions.
  /// @todo Consider renaming `elements` to `tip` to clarify that it's a point.
  template <unsigned int N>
  class Vector {
  public:
    Vector();
    Vector(float x);
    Vector(float x, float y);
    Vector(float x, float y, float z);
    Vector(float x, float y, float z, float w);

    Vector(std::array<float, N> elements);
    Vector(Point<N> tip);
    Vector(Point<N> from, Point<N> to);
    Vector(const Vector<N - 1>& other, float last);

    /// @name Mutators
    /// @{

    [[nodiscard]] auto begin() -> float*;

    [[nodiscard]] auto end() -> float*;

    auto operator[](unsigned int index) -> float&;

    void operator+=(const Vector<N>& other);

    void operator-=(const Vector<N>& other);

    void operator*=(float scalar);

    void operator/=(float scalar);

    /// @}
    /// @name Accessors
    /// @{

    auto operator[](unsigned int index) const -> float;

    auto operator==(const Vector<N>& other) const -> bool;

    auto operator!=(const Vector<N>& other) const -> bool;

    auto operator-() const -> Vector<N>;

    auto operator+() const -> const Vector<N>&;

    auto operator+(const Vector<N>& other) const -> Vector<N>;

    auto operator-(const Vector<N>& other) const -> Vector<N>;

    auto operator*(float scalar) const -> Vector<N>;

    auto operator/(float scalar) const -> Vector<N>;

    template <unsigned int D = N>
    auto x() const -> std::enable_if_t<(D >= 1), float>;

    template <unsigned int D = N>
    auto y() const -> std::enable_if_t<(D >= 2), float>;

    template <unsigned int D = N>
    auto z() const -> std::enable_if_t<(D >= 3), float>;

    template <unsigned int D = N>
    auto w() const -> std::enable_if_t<(D >= 4), float>;

    template <unsigned int D = N>
    auto r() const -> std::enable_if_t<(D >= 1), float>;

    template <unsigned int D = N>
    auto g() const -> std::enable_if_t<(D >= 2), float>;

    template <unsigned int D = N>
    auto b() const -> std::enable_if_t<(D >= 3), float>;

    template <unsigned int D = N>
    auto a() const -> std::enable_if_t<(D >= 4), float>;

    template <unsigned int D = N>
    auto s() const -> std::enable_if_t<(D >= 1), float>;

    template <unsigned int D = N>
    auto t() const -> std::enable_if_t<(D >= 2), float>;

    template <unsigned int D = N>
    auto p() const -> std::enable_if_t<(D >= 3), float>;

    template <unsigned int D = N>
    auto q() const -> std::enable_if_t<(D >= 4), float>;

    [[nodiscard]] auto begin() const -> const float*;

    [[nodiscard]] auto end() const -> const float*;

    [[nodiscard]] auto manhattan_length() const -> float;

    [[nodiscard]] auto magnitude() const -> float;

    auto normalized() const -> Vector<N>;

    auto tip(Point<N> start = Point<N>()) const -> Point<N>;

    auto multiply_elementwise(const Vector<N>& other) const -> Vector<N>;

    auto inner_product(const Vector<N>& other) const -> float;

    auto dot(const Vector<N>& other) const -> float;

    template <unsigned int M>
    operator Vector<M>() const;

    operator std::array<float, N>() const;

    [[nodiscard]] auto to_json() const -> debug::JSON;

    /// @}

  private:
    Point<N> elements; //< We use a point to represent the elements since they can be thought of as representing the vector's relative tip.
  };

  /////////////////////
  // Implementations //
  /////////////////////

  template <unsigned int N>
  Vector<N>::Vector() : elements() {}

  template <unsigned int N>
  Vector<N>::Vector(float x) : elements({x}) {}

  template <unsigned int N>
  Vector<N>::Vector(float x, float y) : elements({x, y}) {}

  template <unsigned int N>
  Vector<N>::Vector(float x, float y, float z) : elements({x, y, z}) {}

  template <unsigned int N>
  Vector<N>::Vector(float x, float y, float z, float w) : elements({x, y, z, w}) {}

  template <unsigned int N>
  Vector<N>::Vector(std::array<float, N> elements) : elements(Point<N>(elements)) {}

  template <unsigned int N>
  Vector<N>::Vector(Point<N> tip) : elements(tip) {}

  template <unsigned int N>
  Vector<N>::Vector(Point<N> from, Point<N> to) {
    if (from == to)
      LOG_ERROR("The provided points may not coincide."); // LCOV_EXCL_BR_LINE

    for (unsigned int i = 0; i < N; i++)
      elements[i] = to[i] - from[i];
  }

  template <unsigned int N>
  Vector<N>::Vector(const Vector<N - 1>& other, float last) {
    for (unsigned int i = 0; i < N - 1; i++)
      elements[i] = other[i];
    elements[N - 1] = last;
  }

  template <unsigned int N>
  [[nodiscard]] auto Vector<N>::begin() -> float* {
    return elements.begin();
  }

  template <unsigned int N>
  [[nodiscard]] auto Vector<N>::end() -> float* {
    return elements.end();
  }

  template <unsigned int N>
  auto Vector<N>::operator[](unsigned int index) -> float& {
    return elements[index];
  }

  template <unsigned int N>
  void Vector<N>::operator+=(const Vector<N>& other) {
    for (unsigned int i = 0; i < N; i++)
      elements[i] += other[i];
  }

  template <unsigned int N>
  void Vector<N>::operator-=(const Vector<N>& other) {
    for (unsigned int i = 0; i < N; i++)
      elements[i] -= other[i];
  }

  template <unsigned int N>
  void Vector<N>::operator*=(float scalar) {
    *this = (*this) * scalar;
  }

  template <unsigned int N>
  void Vector<N>::operator/=(float scalar) {
    *this = (*this) / scalar;
  }

  template <unsigned int N>
  auto Vector<N>::operator[](unsigned int index) const -> float {
    return elements[index];
  }

  template <unsigned int N>
  auto Vector<N>::operator==(const Vector<N>& other) const -> bool {
    return elements == other.elements;
  }

  template <unsigned int N>
  auto Vector<N>::operator!=(const Vector<N>& other) const -> bool {
    return !(*this == other);
  }

  template <unsigned int N>
  auto Vector<N>::operator-() const -> Vector<N> {
    Vector<N> res(elements);
    for (auto& e : res)
      e = -e;

    return res;
  }

  template <unsigned int N>
  auto Vector<N>::operator+() const -> const Vector<N>& {
    return *this;
  }

  template <unsigned int N>
  auto Vector<N>::operator+(const Vector<N>& other) const -> Vector<N> {
    Vector<N> res;
    for (unsigned int i = 0; i < N; i++)
      res[i] = elements[i] + other[i];

    return res;
  }

  template <unsigned int N>
  auto Vector<N>::operator-(const Vector<N>& other) const -> Vector<N> {
    Vector<N> res(elements);
    for (unsigned int i = 0; i < N; i++)
      res[i] = elements[i] - other[i];

    return res;
  }

  template <unsigned int N>
  auto Vector<N>::operator*(float scalar) const -> Vector<N> {
    Vector<N> res(elements);
    for (unsigned int i = 0; i < N; i++)
      res[i] *= scalar;

    return res;
  }

  template <unsigned int N>
  auto Vector<N>::operator/(float scalar) const -> Vector<N> {
    Vector<N> res(elements);
    for (unsigned int i = 0; i < N; i++)
      res[i] /= scalar;

    return res;
  }

  template <unsigned int N>
  template <unsigned int D>
  auto Vector<N>::x() const -> std::enable_if_t<(D >= 1), float> {
    return elements[0];
  }

  template <unsigned int N>
  template <unsigned int D>
  auto Vector<N>::y() const -> std::enable_if_t<(D >= 2), float> {
    return elements[1];
  }

  template <unsigned int N>
  template <unsigned int D>
  auto Vector<N>::z() const -> std::enable_if_t<(D >= 3), float> {
    return elements[2];
  }

  template <unsigned int N>
  template <unsigned int D>
  auto Vector<N>::w() const -> std::enable_if_t<(D >= 4), float> {
    return elements[3];
  }

  template <unsigned int N>
  template <unsigned int D>
  auto Vector<N>::r() const -> std::enable_if_t<(D >= 1), float> {
    return elements[0];
  }

  template <unsigned int N>
  template <unsigned int D>
  auto Vector<N>::g() const -> std::enable_if_t<(D >= 2), float> {
    return elements[1];
  }

  template <unsigned int N>
  template <unsigned int D>
  auto Vector<N>::b() const -> std::enable_if_t<(D >= 3), float> {
    return elements[2];
  }

  template <unsigned int N>
  template <unsigned int D>
  auto Vector<N>::a() const -> std::enable_if_t<(D >= 4), float> {
    return elements[3];
  }

  template <unsigned int N>
  template <unsigned int D>
  auto Vector<N>::s() const -> std::enable_if_t<(D >= 1), float> {
    return elements[0];
  }

  template <unsigned int N>
  template <unsigned int D>
  auto Vector<N>::t() const -> std::enable_if_t<(D >= 2), float> {
    return elements[1];
  }

  template <unsigned int N>
  template <unsigned int D>
  auto Vector<N>::p() const -> std::enable_if_t<(D >= 3), float> {
    return elements[2];
  }

  template <unsigned int N>
  template <unsigned int D>
  auto Vector<N>::q() const -> std::enable_if_t<(D >= 4), float> {
    return elements[3];
  }

  template <unsigned int N>
  [[nodiscard]] auto Vector<N>::begin() const -> const float* {
    return elements.begin();
  }

  template <unsigned int N>
  [[nodiscard]] auto Vector<N>::end() const -> const float* {
    return elements.end();
  }

  template <unsigned int N>
  [[nodiscard]] auto Vector<N>::manhattan_length() const -> float {
    float sum = 0;
    for (auto& e : elements)
      sum += e;

    return sum;
  }

  template <unsigned int N>
  [[nodiscard]] auto Vector<N>::magnitude() const -> float {
    // Vector mangnitude = distance between tip and origin
    return elements.euclidean_distance(Point<N>());
  }

  template <unsigned int N>
  auto Vector<N>::normalized() const -> Vector<N> {
    return (*this) / magnitude();
  }

  template <unsigned int N>
  auto Vector<N>::tip(Point<N> start) const -> Point<N> {
    Point<N> res;
    for (unsigned int i = 0; i < N; i++)
      res[i] = start[i] + elements[i];

    return res;
  }

  template <unsigned int N>
  auto Vector<N>::multiply_elementwise(const Vector<N>& other) const -> Vector<N> {
    Vector<N> res;
    for (unsigned int i = 0; i < N; i++)
      res[i] = elements[i] * other[i];

    return res;
  }

  template <unsigned int N>
  auto Vector<N>::inner_product(const Vector<N>& other) const -> float {
    return multiply_elementwise(other).manhattan_length();
  }

  template <unsigned int N>
  auto Vector<N>::dot(const Vector<N>& other) const -> float {
    return inner_product(other);
  }

  template <unsigned int N>
  template <unsigned int M>
  Vector<N>::operator Vector<M>() const {
    return Vector<M>(Point<M>(elements));
  }

  template <unsigned int N>
  Vector<N>::operator std::array<float, N>() const {
    std::array<float, N> arr;
    std::copy(begin(), end(), arr.begin());
    return arr;
  }

  template <unsigned int N>
  [[nodiscard]] auto Vector<N>::to_json() const -> debug::JSON {
    return elements.to_json();
  };

  /////////////////////
  // Local Functions //
  /////////////////////

  template <unsigned int N>
  auto operator*(float lhs, const Vector<N>& rhs) -> Vector<N> {
    return rhs * lhs;
  }
}
