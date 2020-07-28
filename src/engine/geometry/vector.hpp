#pragma once

#include "../data/templates.hpp"
#include "../debug/json.hpp"
#include "../debug/logger.hpp"

#include <array>

namespace engine::geometry {

  template <unsigned int N>
  struct Vector {
    std::array<float, N> elements;

    float& x = elements[0];
    float& y = elements[1];
    float& z = elements[2];
    float& w = elements[3];

    float& r = elements[0];
    float& g = elements[1];
    float& b = elements[2];
    float& a = elements[3];

    float& s = elements[0];
    float& t = elements[1];
    float& p = elements[2];
    float& q = elements[3];

    Vector()
            : elements() {}

    Vector(std::initializer_list<float> elements) {
      if (elements.size() != N)
        LOG_ERROR("Must provide exactly N vector elements.");

      std::copy(elements.begin(), elements.end(), this->elements.begin());
    }

    Vector(std::array<float, N> elements)
            : elements(elements) {}

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
      // static_assert(M >= N, "Given vector may not have fewer dimensions than this vector.");

      std::copy(other.elements.begin(), other.elements.begin() + N, elements.begin());
    }

    // FIXME: https://stackoverflow.com/questions/9510514/integer-range-based-template-specialisation
    // template <unsigned int M, typename = Range<M < N>>
    Vector(const Vector<N>& other)
            : elements(other.elements) {}

    auto operator=(const Vector<N>& other) -> Vector<N>& {
      std::copy(other.elements.begin(), other.elements.begin() + N, elements.begin());
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

      std::copy(other.elements.begin(), other.elements.begin() + M, elements.begin());

      int i = M;
      for (auto& arg : {args...})
        elements[i++] = arg;
    }

    ~Vector() = default;

    auto operator[](unsigned int index) const -> const float& {
      return elements[index];
    }

    auto operator[](unsigned int index) -> float& {
      return elements[index];
    }

    auto operator==(const Vector<N>& other) const -> bool {
      const float tolerance = 0.00001F;
      for (unsigned int i = 0; i < N; i++)
        if (std::abs(elements[i] - other[i]) > tolerance)
          return false;

      return true;
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

    void operator+=(const Vector<N>& other) {
      for (unsigned int i = 0; i < N; i++)
        elements[i] += other[i];
    }

    void operator-=(const Vector<N>& other) {
      for (unsigned int i = 0; i < N; i++)
        elements[i] -= other[i];
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

    // TODO
    // Vector<N> cross_product() {
    //   https://math.stackexchange.com/questions/2517876/cross-product-for-3-vectors-in-4d
    //   https://math.stackexchange.com/questions/2371022/cross-product-in-higher-dimensions
    // }

    [[nodiscard]] auto euclidean_length_squared() const -> float {
      float sum = 0;
      for (auto& e : elements)
        sum += e * e;

      return sum;
    }

    [[nodiscard]] auto euclidean_length() const -> float {
      return std::sqrt(euclidean_length_squared());
    }

    auto normalized() const -> Vector<N> {
      return (*this) / euclidean_length();
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

    template <unsigned int M>
    auto outer_product(const Vector<M>& other) const -> std::array<std::array<float, M>, N> {
      std::array<std::array<float, M>, N> matrix;
      for (unsigned int r = 0; r < N; r++)
        for (unsigned int c = 0; c < M; c++)
          matrix[r][c] = elements[r] * other[c];

      return matrix;
    }

    operator std::array<float, N>() const {
      return elements;
    }

    [[nodiscard]] auto to_json() const -> debug::JSON {
      debug::JSON json = debug::JSON::array();
      for (auto& e : elements)
        json.emplace_back(e);

      return json;
    };
  };

  template <unsigned int N>
  auto operator*(float lhs, const Vector<N>& rhs) -> Vector<N> {
    return rhs * lhs;
  }

  // Vector<3> cross_product(Vector<3> v1, Vector<3> v2);
  // Vector<2> cross_product(Vector<2> vector);
}
