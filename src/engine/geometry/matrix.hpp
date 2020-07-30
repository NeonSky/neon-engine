#pragma once

#include "../data/templates.hpp"
#include "../debug/logger.hpp"
#include "vector.hpp"

#include <array>

namespace engine::geometry {

  template <unsigned int R, unsigned int C = R>
  struct Matrix {
    std::array<std::array<float, C>, R> elements;

    Matrix();
    Matrix(std::initializer_list<std::array<float, C>> elements);
    Matrix(std::array<std::array<float, C>, R> elements);

    template <class... Args, class Enable = std::enable_if_t<(... && is_convertible_no_narrowing<Args, std::array<float, C>>::value)>>
    Matrix(Args... args);

    auto operator[](unsigned int index) const -> const std::array<float, C>&;

    auto operator[](unsigned int index) -> std::array<float, C>&;

    auto operator==(const Matrix<R, C>& other) const -> bool;

    auto operator!=(const Matrix<R, C>& other) const -> bool;

    auto operator-() const -> Matrix<R, C>;

    auto operator/(float scalar) const -> Matrix<R, C>;

    auto operator*(float scalar) const -> Matrix<R, C>;

    template <unsigned int C2>
    auto operator*(const Matrix<C, C2>& other) const -> Matrix<R, C2>;

    auto operator*(const Vector<C>& vector) const -> Vector<R>;

    [[nodiscard]] auto transpose() const -> Matrix<C, R>;

    /// @see https://www.wikiwand.com/en/Gaussian_elimination
    template <unsigned int N = R>
    [[nodiscard]] auto reduced_row_echelon_form() const -> std::enable_if_t<(N < C), Matrix<R, C>>;

    [[nodiscard]] auto row_vector(unsigned int r) const -> Vector<C>;

    [[nodiscard]] auto column_vector(unsigned int c) const -> Vector<R>;

    // TODO: Convert from either row or column depending on dimensions.
    // Maybe remove?
    [[nodiscard]] auto to_vector() const -> Vector<R>;

    [[nodiscard]] auto to_json() const -> debug::JSON;

    //////////////////////////
    // Square matrix functions
    //////////////////////////
    template <unsigned int N = R, unsigned int M, class Enable = std::enable_if_t<(N == R && R == C && M <= N)>>
    Matrix(const Matrix<M>& other);

    template <unsigned int N = R>
    auto main_diagonal() const -> std::enable_if_t<(N == R && R == C), Vector<N>>;

    template <unsigned int N = R>
    auto trace() const -> std::enable_if_t<(N == R && R == C), float>;

    template <unsigned int N = R>
    auto minor_matrix(unsigned int r, unsigned int c) const -> std::enable_if_t<(N == R && R == C), Matrix<N - 1, N - 1>>;

    template <unsigned int N = R>
    auto minor(unsigned int r, unsigned int c) const -> std::enable_if_t<(N == R && R == C), float>;

    template <unsigned int N = R>
    auto cofactor(unsigned int r, unsigned int c) const -> std::enable_if_t<(N == R && R == C), float>;

    template <unsigned int N = R>
    auto cofactor_matrix() const -> std::enable_if_t<(N == R && R == C), Matrix<N>>;

    template <unsigned int N = R>
    auto adjugate() const -> std::enable_if_t<(N == R && R == C), Matrix<N>>;

    template <unsigned int N = R>
    auto inverse() const -> std::enable_if_t<(N == R && R == C), Matrix<N>>;

    template <unsigned int N = R>
    auto determinant() const -> std::enable_if_t<(N == R && R == C && N == 1), float>;

    template <unsigned int N = R>
    auto determinant() const -> std::enable_if_t<(N == R && R == C && N > 1), float>;

    template <unsigned int N = R>
    auto translate(Vector<N - 1> translation) const -> std::enable_if_t<(N == R && R == C), Matrix<N>>;

    template <unsigned int N = R>
    auto rotate(float angle, Vector<N - 1> axis) const -> std::enable_if_t<(N == R && R == C), Matrix<N>>;

    template <unsigned int N = R>
    auto scale(Vector<N - 1> scale) const -> std::enable_if_t<(N == R && R == C), Matrix<N>>;
  };

  /////////////////////
  // Implementations //
  /////////////////////

  template <unsigned int R, unsigned int C>
  Matrix<R, C>::Matrix()
          : elements() {

    if constexpr (R == C)
      for (unsigned int i = 0; i < R; i++)
        elements[i][i] = 1.0F;
  }

  template <unsigned int R, unsigned int C>
  Matrix<R, C>::Matrix(std::initializer_list<std::array<float, C>> elements) {
    if (elements.size() != R)
      LOG_ERROR("Must provide exactly R elements.");

    std::copy(elements.begin(), elements.end(), this->elements.begin());
  }

  template <unsigned int R, unsigned int C>
  Matrix<R, C>::Matrix(std::array<std::array<float, C>, R> elements) : elements(elements) {}

  template <unsigned int R, unsigned int C>
  template <class... Args, class Enable>
  Matrix<R, C>::Matrix(Args... args)
          : elements({args...}) {
    static_assert(sizeof...(args) == R, "Must provide exactly R elements.");
  }

  template <unsigned int R, unsigned int C>
  auto Matrix<R, C>::operator[](unsigned int index) const -> const std::array<float, C>& {
    return elements[index];
  }

  template <unsigned int R, unsigned int C>
  auto Matrix<R, C>::operator[](unsigned int index) -> std::array<float, C>& {
    return elements[index];
  }

  template <unsigned int R, unsigned int C>
  auto Matrix<R, C>::operator==(const Matrix<R, C>& other) const -> bool {
    const float tolerance = 0.00001F;
    for (unsigned int r = 0; r < R; r++)
      for (unsigned int c = 0; c < C; c++)
        if (std::abs(elements[r][c] - other[r][c]) > tolerance)
          return false;

    return true;
  }

  template <unsigned int R, unsigned int C>
  auto Matrix<R, C>::operator!=(const Matrix<R, C>& other) const -> bool {
    return !(*this == other);
  }

  template <unsigned int R, unsigned int C>
  auto Matrix<R, C>::operator-() const -> Matrix<R, C> {
    Matrix<R, C> res(elements);
    for (unsigned int r = 0; r < R; r++)
      for (unsigned int c = 0; c < C; c++)
        res[r][c] *= -1;

    return res;
  }

  template <unsigned int R, unsigned int C>
  auto Matrix<R, C>::operator*(float scalar) const -> Matrix<R, C> {
    Matrix<R, C> res(elements);
    for (unsigned int r = 0; r < R; r++)
      for (unsigned int c = 0; c < C; c++)
        res[r][c] *= scalar;

    return res;
  }

  template <unsigned int R, unsigned int C>
  auto Matrix<R, C>::operator/(float scalar) const -> Matrix<R, C> {
    Matrix<R, C> res(elements);
    for (unsigned int r = 0; r < R; r++)
      for (unsigned int c = 0; c < C; c++)
        res[r][c] /= scalar;

    return res;
  }

  template <unsigned int R, unsigned int C>
  template <unsigned int C2>
  auto Matrix<R, C>::operator*(const Matrix<C, C2>& other) const -> Matrix<R, C2> {
    Matrix<R, C2> res;
    for (unsigned int r = 0; r < R; r++)
      for (unsigned int c = 0; c < C2; c++)
        res[r][c] = row_vector(r).inner_product(other.column_vector(c));

    return res;
  }

  template <unsigned int R, unsigned int C>
  auto Matrix<R, C>::operator*(const Vector<C>& vector) const -> Vector<R> {
    Vector<R> res;
    for (unsigned int r = 0; r < R; r++) {

      float sum = 0.0F;
      for (unsigned int c = 0; c < C; c++)
        sum += elements[r][c] * vector[c];

      res[r] = sum;
    }

    return res;
  }

  template <unsigned int R, unsigned int C>
  [[nodiscard]] auto Matrix<R, C>::transpose() const -> Matrix<C, R> {
    Matrix<C, R> res;
    for (unsigned int r = 0; r < R; r++)
      for (unsigned int c = 0; c < C; c++)
        res[c][r] = elements[r][c];

    return res;
  }

  template <unsigned int R, unsigned int C>
  template <unsigned int N>
  [[nodiscard]] auto Matrix<R, C>::reduced_row_echelon_form() const -> std::enable_if_t<(N < C), Matrix<R, C>> {
    Matrix<R, C> res = *this;

    // Convert to echelon/triangular form (clear lower triangle)
    for (unsigned int d = 0; d < R - 1; d++) {   // `d` represents the diagonal index.
      for (unsigned int r = d + 1; r < R; r++) { // `r` represents the row index.

        // To make res[r][d] = 0, we need to add row `d` to row `r` by a factor of ...
        float factor = -(res[r][d] / res[d][d]);

        // Now we perform the addition.
        for (unsigned int c = d; c < C; c++)
          res[r][c] += factor * res[d][c];
      }
    }

    // Form leading 1:s
    for (unsigned int d = 0; d < R; d++) {
      for (unsigned int c = d + 1; c < C; c++)
        res[d][c] /= res[d][d];
      res[d][d] = 1.0F;
    }

    // Clear upper triangle
    for (int d = R - 1; d > 0; d--) {    // `d` represents the diagonal index.
      for (int r = d - 1; r >= 0; r--) { // `r` represents the row index.

        // To make res[r][d] = 0, we need to add row `d` to row `r` by a factor of ...
        float factor = -res[r][d]; // we know that row[d][d] = 1 here

        // Now we perform the addition.
        for (unsigned int c = d; c < C; c++)
          res[r][c] += factor * res[d][c];
      }
    }

    Vector<R> v;
    for (unsigned int i = 0; i < R; i++)
      v[i] = res[i][C] / res[i][i];

    return res;
  }
  template <unsigned int R, unsigned int C>
  [[nodiscard]] auto Matrix<R, C>::row_vector(unsigned int r) const -> Vector<C> {
    return Vector<C>(elements[r]);
  }

  template <unsigned int R, unsigned int C>
  [[nodiscard]] auto Matrix<R, C>::column_vector(unsigned int c) const -> Vector<R> {
    Vector<R> res;
    for (unsigned int r = 0; r < R; r++)
      res[r] = elements[r][c];

    return res;
  }

  template <unsigned int R, unsigned int C>
  [[nodiscard]] auto Matrix<R, C>::to_vector() const -> Vector<R> {
    static_assert(C == 1, "Matrix must have a single column to be converted to vector.");
    return column_vector(0);
  }

  template <unsigned int R, unsigned int C>
  [[nodiscard]] auto Matrix<R, C>::to_json() const -> debug::JSON {
    debug::JSON json = debug::JSON::array();
    for (auto& row : elements)
      json.emplace_back(row);

    return json;
  };

  //////////////////////////
  // Square matrix functions

  template <unsigned int R, unsigned int C>
  template <unsigned int N, unsigned int M, class Enable>
  Matrix<R, C>::Matrix(const Matrix<M>& other)
          : elements() {

    for (unsigned int r = 0; r < M; r++)
      for (unsigned int c = 0; c < M; c++)
        elements[r][c] = other.elements[r][c];

    for (unsigned int i = M; i < N; i++)
      elements[i][i] = 1.0F;
  }

  template <unsigned int R, unsigned int C>
  template <unsigned int N>
  auto Matrix<R, C>::main_diagonal() const -> std::enable_if_t<(N == R && R == C), Vector<N>> {
    Vector<N> res;
    for (unsigned int i = 0; i < N; i++)
      res[i] = elements[i][i];

    return res;
  }

  template <unsigned int R, unsigned int C>
  template <unsigned int N>
  auto Matrix<R, C>::trace() const -> std::enable_if_t<(N == R && R == C), float> {
    float res = 0.0F;
    for (unsigned int i = 0; i < N; i++)
      res += elements[i][i];

    return res;
  }

  template <unsigned int R, unsigned int C>
  template <unsigned int N>
  auto Matrix<R, C>::minor_matrix(unsigned int r, unsigned int c) const -> std::enable_if_t<(N == R && R == C), Matrix<N - 1, N - 1>> {
    Matrix<N - 1, N - 1> res;
    for (unsigned int i = 0; i < N; i++)
      for (unsigned int j = 0; j < N; j++)
        if (i != r && j != c)
          res[i - static_cast<unsigned int>(r < i)][j - static_cast<unsigned int>(c < j)] = elements[i][j];

    return res;
  }

  template <unsigned int R, unsigned int C>
  template <unsigned int N>
  auto Matrix<R, C>::minor(unsigned int r, unsigned int c) const -> std::enable_if_t<(N == R && R == C), float> {
    return minor_matrix(r, c).determinant();
  }

  template <unsigned int R, unsigned int C>
  template <unsigned int N>
  auto Matrix<R, C>::cofactor(unsigned int r, unsigned int c) const -> std::enable_if_t<(N == R && R == C), float> {
    int sign = ((r + c) & 1) != 0 ? -1 : 1;
    return sign * minor(r, c);
  }

  template <unsigned int R, unsigned int C>
  template <unsigned int N>
  auto Matrix<R, C>::cofactor_matrix() const -> std::enable_if_t<(N == R && R == C), Matrix<N>> {
    Matrix<N> res;
    for (unsigned int r = 0; r < N; r++)
      for (unsigned int c = 0; c < N; c++)
        res[r][c] = cofactor(r, c);

    return res;
  }

  template <unsigned int R, unsigned int C>
  template <unsigned int N>
  auto Matrix<R, C>::adjugate() const -> std::enable_if_t<(N == R && R == C), Matrix<N>> {
    return cofactor_matrix().transpose();
  }

  template <unsigned int R, unsigned int C>
  template <unsigned int N>
  auto Matrix<R, C>::inverse() const -> std::enable_if_t<(N == R && R == C), Matrix<N>> {
    float d = determinant();
    if (d == 0.0F)
      LOG_ERROR("Determinant is 0, which means that this matrix is singular/degenerate.");

    return cofactor_matrix() / d;
  }

  template <unsigned int R, unsigned int C>
  template <unsigned int N>
  auto Matrix<R, C>::determinant() const -> std::enable_if_t<(N == R && R == C && N == 1), float> {
    return elements[0][0];
  }

  template <unsigned int R, unsigned int C>
  template <unsigned int N>
  auto Matrix<R, C>::determinant() const -> std::enable_if_t<(N == R && R == C && N > 1), float> {
    float res = 0.0F;
    for (unsigned int c = 0; c < N; c++)
      res += elements[0][c] * cofactor(0, c);
    return res;
  }

  template <unsigned int R, unsigned int C>
  template <unsigned int N>
  auto Matrix<R, C>::translate(Vector<N - 1> translation) const -> std::enable_if_t<(N == R && R == C), Matrix<N>> {
    Matrix<N> m;
    for (unsigned int r = 0; r < N - 1; r++)
      m[r][N - 1] += translation[r];

    return (*this) * m;
  }

  // See section 9.2: https://repository.lboro.ac.uk/articles/Modelling_CPV/9523520
  template <unsigned int R, unsigned int C>
  template <unsigned int N>
  auto Matrix<R, C>::rotate(float angle, Vector<N - 1> axis) const -> std::enable_if_t<(N == R && R == C), Matrix<N>> {
    static_assert(N == 4, "Rotation only defined for 4D matrices.");

    axis = axis.normalized();

    // NOTE: pair = point + axis
    // 1. Rotate the pair so that the axis is in the XZ-plane.
    float xy_len   = sqrt(axis.x * axis.x + axis.y * axis.y);
    Matrix<3> m_xz = {
      {axis.x / xy_len, axis.y / xy_len, 0},
      {-axis.y / xy_len, axis.x / xy_len, 0},
      {0, 0, 1},
    };

    // 2. Rotate the pair so that the axis is equivalent to the Z-axis.
    float xz_len  = sqrt(axis.x * axis.x + axis.z * axis.z);
    Matrix<3> m_z = {
      {axis.z / xz_len, 0, -axis.x / xz_len},
      {0, 1, 0},
      {axis.x / xz_len, 0, axis.z / xz_len},
    };

    // 3. Rotate the point about the z-axis by the desired rotation angle.
    Matrix<3> rot_z{
      // NOTE: Left-handed z-rotation
      {std::cos(angle), std::sin(angle), 0},
      {-std::sin(angle), std::cos(angle), 0},
      {0, 0, 1},
    };

    // 4. Reverse rotate the pair from z-axis so that the axis is in the XY-plane as before.
    Matrix<3> inv_m_z = m_z.transpose(); // We could also have flipped sign of angles.

    // 5. Reverse rotate the pair from the XZ-plane so that the axis is as it was initially.
    Matrix<3> inv_m_xz = m_xz.transpose();

    Matrix<4> m = Matrix<3>(m_xz * m_z * rot_z * inv_m_z * inv_m_xz);

    return (*this) * m;
  }

  template <unsigned int R, unsigned int C>
  template <unsigned int N>
  auto Matrix<R, C>::scale(Vector<N - 1> scale) const -> std::enable_if_t<(N == R && R == C), Matrix<N>> {
    Matrix<N> m;
    for (unsigned int i = 0; i < N - 1; i++)
      m[i][i] *= scale[i];

    return (*this) * m;
  }

}
