#pragma once

#include "point.hpp"

#include "../debug/json.hpp"
#include "../debug/logger.hpp"

#include <array>

namespace engine::geometry {

  /// @brief Vector represents a N-dimensional Euclidean vector.
  ///
  /// @todo Add cross product. Preferably generalized to N dimensions.
  /// @see https://www.wikiwand.com/en/Euclidean_vector
  template <unsigned int N>
  class Vector {
  public:
    /// @brief Creates the identity Vector.
    Vector();

    /// @brief Creates a vector along the x-axis.
    Vector(float x);

    /// @brief Creates a vector along the xy-plane.
    Vector(float x, float y);

    /// @brief Creates a vector in the xyz-space.
    Vector(float x, float y, float z);

    /// @brief Creates a vector in the xyzw-space.
    Vector(float x, float y, float z, float w);

    /// @brief Creates a specific vector.
    ///
    /// The created vector will have elements equal to those of \p elements.
    Vector(std::array<float, N> elements);

    /// @brief Creates a higher dimensional vector from an existing vector.
    ///
    /// The created vector will have the same elements as \p other, but be of 1 higher dimension.
    /// The element belonging to the new dimension will be given the value of \p last.
    Vector(const Vector<N - 1>& other, float last);

    /// @brief Creates a specific vector.
    ///
    /// The created vector will go from the origin to the point \p tip.
    Vector(Point<N> tip);

    /// @brief Creates a vector from one point to another.
    ///
    /// The created vector will go from point \p from to point \p to.
    Vector(Point<N> from, Point<N> to);

    /// @name Mutators
    /// @{

    /// @brief The memory address of the first element.
    [[nodiscard]] auto begin() -> float*;

    /// @brief The memory address following the last element.
    [[nodiscard]] auto end() -> float*;

    /// @brief The \p i th element.
    auto operator[](unsigned int i) -> float&;

    /// @brief Adds the direction and magnitude of vector \p other to this vector.
    void operator+=(const Vector<N>& other);

    /// @brief Subtracts the direction and magnitude of vector \p other to this vector.
    void operator-=(const Vector<N>& other);

    /// @brief Multiplies the magnitude of this vector by \p scalar.
    void operator*=(float scalar);

    /// @brief Divides the magnitude of this vector by \p scalar.
    void operator/=(float scalar);

    /// @}
    /// @name Accessors
    /// @{

    /// @brief The \p i th element.
    auto operator[](unsigned int i) const -> float;

    /// @brief Checks if this vector has the same direction and magnitude as vector \p other.
    auto operator==(const Vector<N>& other) const -> bool;

    /// @brief Checks if this vector differs in direction or magnitude from vector \p other.
    auto operator!=(const Vector<N>& other) const -> bool;

    /// @brief This vector unchanged.
    auto operator+() const -> const Vector<N>&;

    /// @brief This vector with its direction inverted.
    auto operator-() const -> Vector<N>;

    /// @brief The sum of this vector and vector \p other.
    auto operator+(const Vector<N>& other) const -> Vector<N>;

    /// @brief The difference between this vector and vector \p other.
    ///
    /// The resulting vector can equally be described as the vector from \p other's tip to the tip of this vector.
    auto operator-(const Vector<N>& other) const -> Vector<N>;

    /// @brief This vector with its magnitude multiplied by \p scalar.
    auto operator*(float scalar) const -> Vector<N>;

    /// @brief This vector with its magnitude divided by \p scalar.
    auto operator/(float scalar) const -> Vector<N>;

    /// @brief The 1st element.
    template <unsigned int D = N>
    auto x() const -> std::enable_if_t<(D >= 1), float>;

    /// @brief The 2nd element.
    template <unsigned int D = N>
    auto y() const -> std::enable_if_t<(D >= 2), float>;

    /// @brief The 3rd element.
    template <unsigned int D = N>
    auto z() const -> std::enable_if_t<(D >= 3), float>;

    /// @brief The 4th element.
    template <unsigned int D = N>
    auto w() const -> std::enable_if_t<(D >= 4), float>;

    /// @brief The 1st element.
    template <unsigned int D = N>
    auto r() const -> std::enable_if_t<(D >= 1), float>;

    /// @brief The 2nd element.
    template <unsigned int D = N>
    auto g() const -> std::enable_if_t<(D >= 2), float>;

    /// @brief The 3rd element.
    template <unsigned int D = N>
    auto b() const -> std::enable_if_t<(D >= 3), float>;

    /// @brief The 4th element.
    template <unsigned int D = N>
    auto a() const -> std::enable_if_t<(D >= 4), float>;

    /// @brief The 1st element.
    template <unsigned int D = N>
    auto s() const -> std::enable_if_t<(D >= 1), float>;

    /// @brief The 2nd element.
    template <unsigned int D = N>
    auto t() const -> std::enable_if_t<(D >= 2), float>;

    /// @brief The 3rd element.
    template <unsigned int D = N>
    auto p() const -> std::enable_if_t<(D >= 3), float>;

    /// @brief The 4th element.
    template <unsigned int D = N>
    auto q() const -> std::enable_if_t<(D >= 4), float>;

    /// @brief The memory address of the first element.
    [[nodiscard]] auto begin() const -> const float*;

    /// @brief The memory address following the last element.
    [[nodiscard]] auto end() const -> const float*;

    /// @brief The magnitude of this vector.
    [[nodiscard]] auto magnitude() const -> float;

    /// @brief The normalized version of this vector.
    ///
    /// Throws an exception if the current vector has no magnitude.
    auto normalized() const -> Vector<N>;

    /// @brief The tip of this vector if it were to start from point \p start.
    auto tip(Point<N> start = Point<N>()) const -> Point<N>;

    /// @brief The element-wise multiplication between this vector and vector \p other.
    auto multiply_elementwise(const Vector<N>& other) const -> Vector<N>;

    /// @brief The inner product between this vector and vector \p other.
    auto inner_product(const Vector<N>& other) const -> float;

    /// @brief The dot product between this vector and vector \p other.
    auto dot(const Vector<N>& other) const -> float;

    /// @brief Converts this vector to a different dimension.
    ///
    /// If the new vector has fewer dimensions, then elements of higher dimensions will be omitted.
    /// If the new vector has more dimensions, then the new elements will be set to 0.
    template <unsigned int M>
    operator Vector<M>() const;

    /// @brief Converts this vector to an array.
    operator std::array<float, N>() const;

    /// @brief Serializes the current state to JSON.
    [[nodiscard]] auto to_json() const -> debug::JSON;

    /// @}

  private:
    /// @{
    /// Private state.
    Point<N> _elements; //< We use a point to represent the elements since they can be thought of as representing the vector's relative tip.
    /// @}
  };

  /////////////////////
  // Implementations //
  /////////////////////

  template <unsigned int N>
  Vector<N>::Vector() : _elements() {}

  template <unsigned int N>
  Vector<N>::Vector(float x) : _elements({x}) {}

  template <unsigned int N>
  Vector<N>::Vector(float x, float y) : _elements({x, y}) {}

  template <unsigned int N>
  Vector<N>::Vector(float x, float y, float z) : _elements({x, y, z}) {}

  template <unsigned int N>
  Vector<N>::Vector(float x, float y, float z, float w) : _elements({x, y, z, w}) {}

  template <unsigned int N>
  Vector<N>::Vector(std::array<float, N> elements) : _elements(Point<N>(elements)) {}

  template <unsigned int N>
  Vector<N>::Vector(Point<N> tip) : _elements(tip) {}

  template <unsigned int N>
  Vector<N>::Vector(Point<N> from, Point<N> to) {
    if (from == to)
      LOG_ERROR("The provided points may not coincide."); // LCOV_EXCL_BR_LINE

    for (unsigned int i = 0; i < N; i++)
      _elements[i] = to[i] - from[i];
  }

  template <unsigned int N>
  Vector<N>::Vector(const Vector<N - 1>& other, float last) {
    for (unsigned int i = 0; i < N - 1; i++)
      _elements[i] = other[i];
    _elements[N - 1] = last;
  }

  template <unsigned int N>
  [[nodiscard]] auto Vector<N>::begin() -> float* {
    return _elements.begin();
  }

  template <unsigned int N>
  [[nodiscard]] auto Vector<N>::end() -> float* {
    return _elements.end();
  }

  template <unsigned int N>
  auto Vector<N>::operator[](unsigned int i) -> float& {
    return _elements[i];
  }

  template <unsigned int N>
  void Vector<N>::operator+=(const Vector<N>& other) {
    for (unsigned int i = 0; i < N; i++)
      _elements[i] += other[i];
  }

  template <unsigned int N>
  void Vector<N>::operator-=(const Vector<N>& other) {
    for (unsigned int i = 0; i < N; i++)
      _elements[i] -= other[i];
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
  auto Vector<N>::operator[](unsigned int i) const -> float {
    return _elements[i];
  }

  template <unsigned int N>
  auto Vector<N>::operator==(const Vector<N>& other) const -> bool {
    return _elements == other._elements;
  }

  template <unsigned int N>
  auto Vector<N>::operator!=(const Vector<N>& other) const -> bool {
    return !(*this == other);
  }

  template <unsigned int N>
  auto Vector<N>::operator-() const -> Vector<N> {
    Vector<N> res(_elements);
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
      res[i] = _elements[i] + other[i];

    return res;
  }

  template <unsigned int N>
  auto Vector<N>::operator-(const Vector<N>& other) const -> Vector<N> {
    Vector<N> res(_elements);
    for (unsigned int i = 0; i < N; i++)
      res[i] = _elements[i] - other[i];

    return res;
  }

  template <unsigned int N>
  auto Vector<N>::operator*(float scalar) const -> Vector<N> {
    Vector<N> res(_elements);
    for (unsigned int i = 0; i < N; i++)
      res[i] *= scalar;

    return res;
  }

  template <unsigned int N>
  auto Vector<N>::operator/(float scalar) const -> Vector<N> {
    Vector<N> res(_elements);
    for (unsigned int i = 0; i < N; i++)
      res[i] /= scalar;

    return res;
  }

  template <unsigned int N>
  template <unsigned int D>
  auto Vector<N>::x() const -> std::enable_if_t<(D >= 1), float> {
    return _elements[0];
  }

  template <unsigned int N>
  template <unsigned int D>
  auto Vector<N>::y() const -> std::enable_if_t<(D >= 2), float> {
    return _elements[1];
  }

  template <unsigned int N>
  template <unsigned int D>
  auto Vector<N>::z() const -> std::enable_if_t<(D >= 3), float> {
    return _elements[2];
  }

  template <unsigned int N>
  template <unsigned int D>
  auto Vector<N>::w() const -> std::enable_if_t<(D >= 4), float> {
    return _elements[3];
  }

  template <unsigned int N>
  template <unsigned int D>
  auto Vector<N>::r() const -> std::enable_if_t<(D >= 1), float> {
    return _elements[0];
  }

  template <unsigned int N>
  template <unsigned int D>
  auto Vector<N>::g() const -> std::enable_if_t<(D >= 2), float> {
    return _elements[1];
  }

  template <unsigned int N>
  template <unsigned int D>
  auto Vector<N>::b() const -> std::enable_if_t<(D >= 3), float> {
    return _elements[2];
  }

  template <unsigned int N>
  template <unsigned int D>
  auto Vector<N>::a() const -> std::enable_if_t<(D >= 4), float> {
    return _elements[3];
  }

  template <unsigned int N>
  template <unsigned int D>
  auto Vector<N>::s() const -> std::enable_if_t<(D >= 1), float> {
    return _elements[0];
  }

  template <unsigned int N>
  template <unsigned int D>
  auto Vector<N>::t() const -> std::enable_if_t<(D >= 2), float> {
    return _elements[1];
  }

  template <unsigned int N>
  template <unsigned int D>
  auto Vector<N>::p() const -> std::enable_if_t<(D >= 3), float> {
    return _elements[2];
  }

  template <unsigned int N>
  template <unsigned int D>
  auto Vector<N>::q() const -> std::enable_if_t<(D >= 4), float> {
    return _elements[3];
  }

  template <unsigned int N>
  [[nodiscard]] auto Vector<N>::begin() const -> const float* {
    return _elements.begin();
  }

  template <unsigned int N>
  [[nodiscard]] auto Vector<N>::end() const -> const float* {
    return _elements.end();
  }

  template <unsigned int N>
  [[nodiscard]] auto Vector<N>::magnitude() const -> float {
    // mangnitude = distance between tip and origin
    return _elements.euclidean_distance(Point<N>());
  }

  template <unsigned int N>
  auto Vector<N>::normalized() const -> Vector<N> {
    float m = magnitude();
    if (m == 0.0F)
      LOG_ERROR("A vector with 0 magnitude can not be normalized."); // LCOV_EXCL_BR_LINE

    return (*this) / m;
  }

  template <unsigned int N>
  auto Vector<N>::tip(Point<N> start) const -> Point<N> {
    Point<N> res;
    for (unsigned int i = 0; i < N; i++)
      res[i] = start[i] + _elements[i];

    return res;
  }

  template <unsigned int N>
  auto Vector<N>::multiply_elementwise(const Vector<N>& other) const -> Vector<N> {
    Vector<N> res;
    for (unsigned int i = 0; i < N; i++)
      res[i] = _elements[i] * other[i];

    return res;
  }

  template <unsigned int N>
  auto Vector<N>::inner_product(const Vector<N>& other) const -> float {
    Vector<N> v = multiply_elementwise(other);
    return std::accumulate(v.begin(), v.end(), 0.0F, std::plus<>());
  }

  template <unsigned int N>
  auto Vector<N>::dot(const Vector<N>& other) const -> float {
    return inner_product(other);
  }

  template <unsigned int N>
  template <unsigned int M>
  Vector<N>::operator Vector<M>() const {
    return Vector<M>(Point<M>(_elements));
  }

  template <unsigned int N>
  Vector<N>::operator std::array<float, N>() const {
    std::array<float, N> arr;
    std::copy(begin(), end(), arr.begin());
    return arr;
  }

  template <unsigned int N>
  [[nodiscard]] auto Vector<N>::to_json() const -> debug::JSON {
    return _elements.to_json();
  };

  /////////////////////
  // Local Functions //
  /////////////////////

  template <unsigned int N>
  auto operator*(float lhs, const Vector<N>& rhs) -> Vector<N> {
    return rhs * lhs;
  }
}
