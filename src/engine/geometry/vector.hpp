#pragma once

#include "point.hpp"

#include "../debug/json.hpp"
#include "../debug/logger.hpp"

#include <array>

namespace engine::geometry {

  /// @brief Vector represents a N-dimensional Euclidean vector.
  ///
  /// When U is true, the vector is guaranteed to be normalized.
  /// Otherwise, the vector may or may not be normalized.
  ///
  /// @see https://www.wikiwand.com/en/Euclidean_vector
  /// @todo Add cross product. Preferably generalized to N dimensions.
  /// @todo Mutators should be disabled for U = true i.e. unit vectors.
  template <unsigned int N, bool U = false>
  class Vector {
  public:
    /// @brief Creates the identity Vector.
    Vector();

    /// @brief Creates a vector along the x-axis.
    template <unsigned int N2 = N, typename std::enable_if_t<(N2 == 1), int> = 0>
    Vector(float x);

    /// @brief Creates a vector along the xy-plane.
    template <unsigned int N2 = N, typename std::enable_if_t<(N2 == 2), int> = 0>
    Vector(float x, float y);

    /// @brief Creates a vector in the xyz-space.
    template <unsigned int N2 = N, typename std::enable_if_t<(N2 == 3), int> = 0>
    Vector(float x, float y, float z);

    /// @brief Creates a vector in the xyzw-space.
    template <unsigned int N2 = N, typename std::enable_if_t<(N2 == 4), int> = 0>
    Vector(float x, float y, float z, float w);

    /// @brief Creates a higher dimensional vector from an existing vector.
    ///
    /// The created vector will have the same elements as \p other, but be of 1 higher dimension.
    /// The element belonging to the new dimension will be given the value of \p last.
    template <unsigned int N2 = N, typename std::enable_if_t<(N2 > 1), int> = 0>
    Vector(const Vector<N - 1, false>& other, float last);

    /// @brief Creates a specific vector.
    ///
    /// The created vector will have elements equal to those of \p elements.
    Vector(std::array<float, N> elements);

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
    [[nodiscard]] auto operator[](unsigned int i) -> float&;

    /// @brief Adds the direction and magnitude of vector \p other to this vector.
    template <bool U2>
    void operator+=(const Vector<N, U2>& other);

    /// @brief Subtracts the direction and magnitude of vector \p other to this vector.
    template <bool U2>
    void operator-=(const Vector<N, U2>& other);

    /// @brief Multiplies the magnitude of this vector by \p scalar.
    void operator*=(float scalar);

    /// @brief Divides the magnitude of this vector by \p scalar.
    void operator/=(float scalar);

    /// @}
    /// @name Accessors
    /// @{

    /// @brief The \p i th element.
    [[nodiscard]] auto operator[](unsigned int i) const -> float;

    /// @brief Checks if this vector has the same direction and magnitude as vector \p other.
    template <bool U2>
    [[nodiscard]] auto operator==(const Vector<N, U2>& other) const -> bool;

    /// @brief Checks if this vector differs in direction or magnitude from vector \p other.
    template <bool U2>
    [[nodiscard]] auto operator!=(const Vector<N, U2>& other) const -> bool;

    /// @brief This vector unchanged.
    [[nodiscard]] auto operator+() const -> const Vector<N, U>&;

    /// @brief This vector with its direction inverted.
    [[nodiscard]] auto operator-() const -> Vector<N, false>;

    /// @brief The sum of this vector and vector \p other.
    template <bool U2>
    [[nodiscard]] auto operator+(const Vector<N, U2>& other) const -> Vector<N>;

    /// @brief The difference between this vector and vector \p other.
    ///
    /// The resulting vector can equally be described as the vector from \p other's tip to the tip of this vector.
    template <bool U2>
    [[nodiscard]] auto operator-(const Vector<N, U2>& other) const -> Vector<N>;

    /// @brief This vector with its magnitude multiplied by \p scalar.
    [[nodiscard]] auto operator*(float scalar) const -> Vector<N>;

    /// @brief This vector with its magnitude divided by \p scalar.
    [[nodiscard]] auto operator/(float scalar) const -> Vector<N>;

    /// @brief The 1st element.
    template <unsigned int D = N>
    [[nodiscard]] auto x() const -> std::enable_if_t<(D >= 1), float>;

    /// @brief The 2nd element.
    template <unsigned int D = N>
    [[nodiscard]] auto y() const -> std::enable_if_t<(D >= 2), float>;

    /// @brief The 3rd element.
    template <unsigned int D = N>
    [[nodiscard]] auto z() const -> std::enable_if_t<(D >= 3), float>;

    /// @brief The 4th element.
    template <unsigned int D = N>
    [[nodiscard]] auto w() const -> std::enable_if_t<(D >= 4), float>;

    /// @brief The 1st element.
    template <unsigned int D = N>
    [[nodiscard]] auto r() const -> std::enable_if_t<(D >= 1), float>;

    /// @brief The 2nd element.
    template <unsigned int D = N>
    [[nodiscard]] auto g() const -> std::enable_if_t<(D >= 2), float>;

    /// @brief The 3rd element.
    template <unsigned int D = N>
    [[nodiscard]] auto b() const -> std::enable_if_t<(D >= 3), float>;

    /// @brief The 4th element.
    template <unsigned int D = N>
    [[nodiscard]] auto a() const -> std::enable_if_t<(D >= 4), float>;

    /// @brief The 1st element.
    template <unsigned int D = N>
    [[nodiscard]] auto s() const -> std::enable_if_t<(D >= 1), float>;

    /// @brief The 2nd element.
    template <unsigned int D = N>
    [[nodiscard]] auto t() const -> std::enable_if_t<(D >= 2), float>;

    /// @brief The 3rd element.
    template <unsigned int D = N>
    [[nodiscard]] auto p() const -> std::enable_if_t<(D >= 3), float>;

    /// @brief The 4th element.
    template <unsigned int D = N>
    [[nodiscard]] auto q() const -> std::enable_if_t<(D >= 4), float>;

    /// @brief The memory address of the first element.
    [[nodiscard]] auto begin() const -> const float*;

    /// @brief The memory address following the last element.
    [[nodiscard]] auto end() const -> const float*;

    /// @brief The magnitude of this vector.
    [[nodiscard]] auto magnitude() const -> float;

    /// @brief The normalized version of this vector.
    ///
    /// Throws an exception if the current vector has no magnitude.
    [[nodiscard]] auto normalized() const -> Vector<N, true>;

    /// @brief The tip of this vector if it were to start from point \p start.
    [[nodiscard]] auto tip(Point<N> start = Point<N>()) const -> Point<N>;

    /// @brief The element-wise multiplication between this vector and vector \p other.
    template <bool U2>
    [[nodiscard]] auto multiply_elementwise(const Vector<N, U2>& other) const -> Vector<N>;

    /// @brief The inner product between this vector and vector \p other.
    template <bool U2>
    [[nodiscard]] auto inner_product(const Vector<N, U2>& other) const -> float;

    /// @brief The dot product between this vector and vector \p other.
    template <bool U2>
    [[nodiscard]] auto dot(const Vector<N, U2>& other) const -> float;

    /// @brief Converts this vector to a different dimension.
    ///
    /// If the new vector has fewer dimensions, then elements of higher dimensions will be omitted.
    /// If the new vector has more dimensions, then the new elements will be set to 0.
    ///
    /// This operator can also be used to convert a unit vector to a non-unit vector.
    template <unsigned int M>
    [[nodiscard]] operator Vector<M, false>() const;

    /// @brief Converts this vector to an array.
    [[nodiscard]] operator std::array<float, N>() const;

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

  template <unsigned int N, bool U>
  Vector<N, U>::Vector()
          : Vector(U ? Vector(Point<N>({1.0F})) : Vector(Point<N>())) {}

  template <unsigned int N, bool U>
  template <unsigned int N2, typename std::enable_if_t<(N2 == 1), int>>
  Vector<N, U>::Vector(float x)
          : Vector(Point<N>(x)) {}

  template <unsigned int N, bool U>
  template <unsigned int N2, typename std::enable_if_t<(N2 == 2), int>>
  Vector<N, U>::Vector(float x, float y)
          : Vector(Point<N>(x, y)) {}

  template <unsigned int N, bool U>
  template <unsigned int N2, typename std::enable_if_t<(N2 == 3), int>>
  Vector<N, U>::Vector(float x, float y, float z)
          : Vector(Point<N>(x, y, z)) {}

  template <unsigned int N, bool U>
  template <unsigned int N2, typename std::enable_if_t<(N2 == 4), int>>
  Vector<N, U>::Vector(float x, float y, float z, float w)
          : Vector(Point<N>(x, y, z, w)) {}

  template <unsigned int N, bool U>
  template <unsigned int N2, typename std::enable_if_t<(N2 > 1), int>>
  Vector<N, U>::Vector(const Vector<N - 1, false>& other, float last) {
    for (unsigned int i = 0; i < N - 1; i++)
      _elements[i] = other[i];
    _elements[N - 1] = last;
  }

  template <unsigned int N, bool U>
  Vector<N, U>::Vector(std::array<float, N> elements)
          : Vector(Point<N>(elements)) {}

  template <unsigned int N, bool U>
  Vector<N, U>::Vector(Point<N> tip)
          : Vector(Point<N>(), tip) {}

  template <unsigned int N, bool U>
  Vector<N, U>::Vector(Point<N> from, Point<N> to) {
    for (unsigned int i = 0; i < N; i++)
      _elements[i] = to[i] - from[i];

    if constexpr (U)
      (*this) /= magnitude();
  }

  template <unsigned int N, bool U>
  auto Vector<N, U>::begin() -> float* {
    return _elements.begin();
  }

  template <unsigned int N, bool U>
  auto Vector<N, U>::end() -> float* {
    return _elements.end();
  }

  template <unsigned int N, bool U>
  auto Vector<N, U>::operator[](unsigned int i) -> float& {
    return _elements[i];
  }

  template <unsigned int N, bool U>
  template <bool U2>
  void Vector<N, U>::operator+=(const Vector<N, U2>& other) {
    for (unsigned int i = 0; i < N; i++)
      _elements[i] += other[i];
  }

  template <unsigned int N, bool U>
  template <bool U2>
  void Vector<N, U>::operator-=(const Vector<N, U2>& other) {
    for (unsigned int i = 0; i < N; i++)
      _elements[i] -= other[i];
  }

  template <unsigned int N, bool U>
  void Vector<N, U>::operator*=(float scalar) {
    for (unsigned int i = 0; i < N; i++)
      _elements[i] *= scalar;
  }

  template <unsigned int N, bool U>
  void Vector<N, U>::operator/=(float scalar) {
    if (scalar == 0.0F) {
      if (magnitude() == 0.0F) {
        LOG_ERROR("Can't divide vector by 0. This is the identity vector, so this error might have occured from an attempt to normalize it."); // LCOV_EXCL_BR_LINE
      } else {
        LOG_ERROR("Can't divide vector by 0."); // LCOV_EXCL_BR_LINE
      }
    }

    for (unsigned int i = 0; i < N; i++)
      _elements[i] /= scalar;
  }

  template <unsigned int N, bool U>
  auto Vector<N, U>::operator[](unsigned int i) const -> float {
    return _elements[i];
  }

  template <unsigned int N, bool U>
  template <bool U2>
  auto Vector<N, U>::operator==(const Vector<N, U2>& other) const -> bool {
    return _elements == other.tip();
  }

  template <unsigned int N, bool U>
  template <bool U2>
  auto Vector<N, U>::operator!=(const Vector<N, U2>& other) const -> bool {
    return !(*this == other);
  }

  template <unsigned int N, bool U>
  auto Vector<N, U>::operator-() const -> Vector<N, false> {
    Vector<N> res(_elements);
    for (auto& e : res)
      e = -e;

    return res;
  }

  template <unsigned int N, bool U>
  auto Vector<N, U>::operator+() const -> const Vector<N, U>& {
    return *this;
  }

  template <unsigned int N, bool U>
  template <bool U2>
  auto Vector<N, U>::operator+(const Vector<N, U2>& other) const -> Vector<N> {
    Vector<N> res(_elements);
    res += other;
    return res;
  }

  template <unsigned int N, bool U>
  template <bool U2>
  auto Vector<N, U>::operator-(const Vector<N, U2>& other) const -> Vector<N> {
    Vector<N> res(_elements);
    res -= other;
    return res;
  }

  template <unsigned int N, bool U>
  auto Vector<N, U>::operator*(float scalar) const -> Vector<N> {
    Vector<N> res(_elements);
    res *= scalar;
    return res;
  }

  template <unsigned int N, bool U>
  auto Vector<N, U>::operator/(float scalar) const -> Vector<N> {
    Vector<N> res(_elements);
    res /= scalar;
    return res;
  }

  template <unsigned int N, bool U>
  template <unsigned int D>
  auto Vector<N, U>::x() const -> std::enable_if_t<(D >= 1), float> {
    return _elements[0];
  }

  template <unsigned int N, bool U>
  template <unsigned int D>
  auto Vector<N, U>::y() const -> std::enable_if_t<(D >= 2), float> {
    return _elements[1];
  }

  template <unsigned int N, bool U>
  template <unsigned int D>
  auto Vector<N, U>::z() const -> std::enable_if_t<(D >= 3), float> {
    return _elements[2];
  }

  template <unsigned int N, bool U>
  template <unsigned int D>
  auto Vector<N, U>::w() const -> std::enable_if_t<(D >= 4), float> {
    return _elements[3];
  }

  template <unsigned int N, bool U>
  template <unsigned int D>
  auto Vector<N, U>::r() const -> std::enable_if_t<(D >= 1), float> {
    return _elements[0];
  }

  template <unsigned int N, bool U>
  template <unsigned int D>
  auto Vector<N, U>::g() const -> std::enable_if_t<(D >= 2), float> {
    return _elements[1];
  }

  template <unsigned int N, bool U>
  template <unsigned int D>
  auto Vector<N, U>::b() const -> std::enable_if_t<(D >= 3), float> {
    return _elements[2];
  }

  template <unsigned int N, bool U>
  template <unsigned int D>
  auto Vector<N, U>::a() const -> std::enable_if_t<(D >= 4), float> {
    return _elements[3];
  }

  template <unsigned int N, bool U>
  template <unsigned int D>
  auto Vector<N, U>::s() const -> std::enable_if_t<(D >= 1), float> {
    return _elements[0];
  }

  template <unsigned int N, bool U>
  template <unsigned int D>
  auto Vector<N, U>::t() const -> std::enable_if_t<(D >= 2), float> {
    return _elements[1];
  }

  template <unsigned int N, bool U>
  template <unsigned int D>
  auto Vector<N, U>::p() const -> std::enable_if_t<(D >= 3), float> {
    return _elements[2];
  }

  template <unsigned int N, bool U>
  template <unsigned int D>
  auto Vector<N, U>::q() const -> std::enable_if_t<(D >= 4), float> {
    return _elements[3];
  }

  template <unsigned int N, bool U>
  auto Vector<N, U>::begin() const -> const float* {
    return _elements.begin();
  }

  template <unsigned int N, bool U>
  auto Vector<N, U>::end() const -> const float* {
    return _elements.end();
  }

  template <unsigned int N, bool U>
  auto Vector<N, U>::magnitude() const -> float {
    // magnitude = distance between tip and origin
    return _elements.euclidean_distance(Point<N>());
  }

  template <unsigned int N, bool U>
  auto Vector<N, U>::normalized() const -> Vector<N, true> {
    return Vector<N, true>(_elements);
  }

  template <unsigned int N, bool U>
  auto Vector<N, U>::tip(Point<N> start) const -> Point<N> {
    Point<N> res;
    for (unsigned int i = 0; i < N; i++)
      res[i] = start[i] + _elements[i];

    return res;
  }

  template <unsigned int N, bool U>
  template <bool U2>
  auto Vector<N, U>::multiply_elementwise(const Vector<N, U2>& other) const -> Vector<N> {
    Vector<N> res;
    for (unsigned int i = 0; i < N; i++)
      res[i] = _elements[i] * other[i];

    return res;
  }

  template <unsigned int N, bool U>
  template <bool U2>
  auto Vector<N, U>::inner_product(const Vector<N, U2>& other) const -> float {
    Vector<N> v = multiply_elementwise(other);
    return std::accumulate(v.begin(), v.end(), 0.0F, std::plus<>());
  }

  template <unsigned int N, bool U>
  template <bool U2>
  auto Vector<N, U>::dot(const Vector<N, U2>& other) const -> float {
    return inner_product(other);
  }

  template <unsigned int N, bool U>
  template <unsigned int M>
  Vector<N, U>::operator Vector<M, false>() const {
    return Vector<M>(Point<M>(_elements));
  }

  template <unsigned int N, bool U>
  Vector<N, U>::operator std::array<float, N>() const {
    std::array<float, N> arr;
    std::copy(begin(), end(), arr.begin());
    return arr;
  }

  template <unsigned int N, bool U>
  auto Vector<N, U>::to_json() const -> debug::JSON {
    return _elements.to_json();
  };

  /////////////////////
  // Local Functions //
  /////////////////////

  template <unsigned int N, bool U>
  auto operator*(float lhs, const Vector<N, U>& rhs) -> Vector<N> {
    return rhs * lhs;
  }

  template <unsigned int N>
  using UnitVector = Vector<N, true>;
}
