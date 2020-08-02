#pragma once

#include "point.hpp"

#include "../data/templates.hpp"
#include "../debug/json.hpp"
#include "../debug/logger.hpp"

#include <array>

namespace engine::geometry {

  /// @todo Add cross product. Preferably generalized to N dimensions.
  /// @todo Consider renaming `elements` to `tip` to clarify that it's a point.
  template <unsigned int N>
  class Vector {
  public:
    Vector()
            : elements() {}

    Vector(std::initializer_list<float> elements) {
      if (elements.size() != N)
        LOG_ERROR("Must provide exactly N vector elements.");

      std::copy(elements.begin(), elements.end(), this->elements.begin());
    }

    Vector(Point<N> tip)
            : elements(tip) {}

    Vector(Point<N> from, Point<N> to) {
      if (from == to)
        LOG_ERROR("The provided points may not coincide.");

      for (unsigned int i = 0; i < N; i++)
        elements[i] = to[i] - from[i];
    }

    Vector(std::array<float, N> elements)
            : elements(Point<N>(elements)) {}

    template <class... Args,
              class Enable = std::enable_if_t<(... && is_convertible_no_narrowing<Args, float>::value)>>
    Vector(Args... args)
            : elements({args...}) {
      static_assert(sizeof...(args) == N, "Must provide exactly N vector elements.");
    }

    template <bool>
    struct Range;

    template <unsigned int M, typename = Range<(M >= N)>>
    Vector(const Vector<M>& other) {
      for (unsigned int i = 0; i < N; i++)
        elements[i] = other[i];
    }

    // FIXME: https://stackoverflow.com/questions/9510514/integer-range-based-template-specialisation
    // template <unsigned int M, typename = Range<M < N>>
    Vector(const Vector<N>& other)
            : elements(other.elements) {}

    auto operator=(const Vector<N>& other) -> Vector<N>& {
      for (unsigned int i = 0; i < N; i++)
        elements[i] = other[i];
      return *this;
    }

    Vector(Vector<N>&& other) noexcept {
      elements = other.elements;
    }

    auto operator=(Vector<N>&& other) noexcept -> Vector<N>& {
      elements = other.elements;
      return *this;
    }

    template <unsigned int M, class... Args, class Enable = std::enable_if_t<(... && is_convertible_no_narrowing<Args, float>::value)>>
    Vector(const Vector<M>& other, Args... args) {
      static_assert(M + sizeof...(args) == N, "Dimensions must match.");

      for (unsigned int i = 0; i < M; i++)
        elements[i] = other[i];

      int i = M;
      for (auto& arg : {args...})
        elements[i++] = arg;
    }

    ~Vector() = default;

    auto operator[](unsigned int index) const -> float {
      return elements[index];
    }

    auto operator[](unsigned int index) -> float& {
      return elements[index];
    }

    auto operator==(const Vector<N>& other) const -> bool {
      return elements == other.elements;
    }

    auto operator!=(const Vector<N>& other) const -> bool {
      return !(*this == other);
    }

    auto operator-() const -> Vector<N> {
      Vector<N> res(elements);
      for (auto& e : res)
        e = -e;

      return res;
    }

    auto operator+() const -> const Vector<N>& {
      return *this;
    }

    auto operator+(const Vector<N>& other) const -> Vector<N> {
      Vector<N> res;
      for (unsigned int i = 0; i < N; i++)
        res[i] = elements[i] + other[i];

      return res;
    }

    auto operator-(const Vector<N>& other) const -> Vector<N> {
      Vector<N> res(elements);
      for (unsigned int i = 0; i < N; i++)
        res[i] = elements[i] - other[i];

      return res;
    }

    void operator+=(const Vector<N>& other) {
      for (unsigned int i = 0; i < N; i++)
        elements[i] += other[i];
    }

    void operator-=(const Vector<N>& other) {
      for (unsigned int i = 0; i < N; i++)
        elements[i] -= other[i];
    }

    auto operator*(float scalar) const -> Vector<N> {
      Vector<N> res(elements);
      for (unsigned int i = 0; i < N; i++)
        res[i] *= scalar;

      return res;
    }

    auto operator/(float scalar) const -> Vector<N> {
      Vector<N> res(elements);
      for (unsigned int i = 0; i < N; i++)
        res[i] /= scalar;

      return res;
    }

    void operator*=(float scalar) {
      *this = (*this) * scalar;
    }

    void operator/=(float scalar) {
      *this = (*this) / scalar;
    }

    template <unsigned int D = N>
    auto x() const -> std::enable_if_t<(D >= 1), float> {
      return elements[0];
    }

    template <unsigned int D = N>
    auto y() const -> std::enable_if_t<(D >= 2), float> {
      return elements[1];
    }

    template <unsigned int D = N>
    auto z() const -> std::enable_if_t<(D >= 3), float> {
      return elements[2];
    }

    template <unsigned int D = N>
    auto w() const -> std::enable_if_t<(D >= 4), float> {
      return elements[3];
    }

    template <unsigned int D = N>
    auto r() const -> std::enable_if_t<(D >= 1), float> {
      return elements[0];
    }

    template <unsigned int D = N>
    auto g() const -> std::enable_if_t<(D >= 2), float> {
      return elements[1];
    }

    template <unsigned int D = N>
    auto b() const -> std::enable_if_t<(D >= 3), float> {
      return elements[2];
    }

    template <unsigned int D = N>
    auto a() const -> std::enable_if_t<(D >= 4), float> {
      return elements[3];
    }

    template <unsigned int D = N>
    auto s() const -> std::enable_if_t<(D >= 1), float> {
      return elements[0];
    }

    template <unsigned int D = N>
    auto t() const -> std::enable_if_t<(D >= 2), float> {
      return elements[1];
    }

    template <unsigned int D = N>
    auto p() const -> std::enable_if_t<(D >= 3), float> {
      return elements[2];
    }

    template <unsigned int D = N>
    auto q() const -> std::enable_if_t<(D >= 4), float> {
      return elements[3];
    }

    auto begin() const -> const float* {
      return elements.begin();
    }

    auto end() const -> const float* {
      return elements.end();
    }

    auto begin() -> float* {
      return elements.begin();
    }

    auto end() -> float* {
      return elements.end();
    }

    [[nodiscard]] auto manhattan_length() const -> float {
      float sum = 0;
      for (auto& e : elements)
        sum += e;

      return sum;
    }

    [[nodiscard]] auto magnitude() const -> float {
      // Vector mangnitude = distance between tip and origin
      return elements.euclidean_distance(Point<N>());
    }

    auto normalized() const -> Vector<N> {
      return (*this) / magnitude();
    }

    auto tip(Point<N> start = Point<N>()) const -> Point<N> {
      Point<N> res;
      for (unsigned int i = 0; i < N; i++)
        res[i] = start[i] + elements[i];

      return res;
    }

    auto multiply_elementwise(const Vector<N>& other) const -> Vector<N> {
      Vector<N> res;
      for (unsigned int i = 0; i < N; i++)
        res[i] = elements[i] * other[i];

      return res;
    }

    auto inner_product(const Vector<N>& other) const -> float {
      return multiply_elementwise(other).manhattan_length();
    }

    auto dot(const Vector<N>& other) const -> float {
      return inner_product(other);
    }

    // TODO: maybe remove? We already have this in Matrix. Write a matrix test for it and then remove here.
    template <unsigned int M>
    auto outer_product(const Vector<M>& other) const -> std::array<std::array<float, M>, N> {
      std::array<std::array<float, M>, N> matrix;
      for (unsigned int r = 0; r < N; r++)
        for (unsigned int c = 0; c < M; c++)
          matrix[r][c] = elements[r] * other[c];

      return matrix;
    }

    operator std::array<float, N>() const {
      std::array<float, N> arr;
      std::copy(elements.begin(), elements.end(), arr.begin());
      return arr;
    }

    [[nodiscard]] auto to_json() const -> debug::JSON {
      debug::JSON json = debug::JSON::array();
      for (auto& e : elements)
        json.emplace_back(e);

      return json;
    };

  private:
    Point<N> elements; //< We use a point to represent the elements since they can be thought of as representing the vector's relative tip.
  };

  template <unsigned int N>
  auto operator*(float lhs, const Vector<N>& rhs) -> Vector<N> {
    return rhs * lhs;
  }

}
