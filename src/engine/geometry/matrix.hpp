#pragma once

#include "../debug/logger.hpp"
#include "angle.hpp"
#include "vector.hpp"

#include <array>

namespace engine::geometry {

  /// @brief Matrix represents a R-by-C-dimensional matrix of floats.
  ///
  /// @todo add augmented_matrix(other_matrix) https://www.wikiwand.com/en/Augmented_matrix
  /// @todo add coefficient_matrix() which returns all but the last column https://www.wikiwand.com/en/Augmented_matrix
  /// @todo add is_diagonal() https://www.wikiwand.com/en/Diagonal_matrix
  /// @todo add adjoint()
  /// @see https://www.wikiwand.com/en/Matrix_(mathematics)
  template <unsigned int R, unsigned int C = R>
  class Matrix {
  public:
    /// @brief Creates the identity matrix for square matrices, while a zero-filled matrix otherwise.
    Matrix();

    /// @brief Creates a specific matrix.
    Matrix(std::initializer_list<Vector<C>> elements);

    /// @brief Creates a specific matrix.
    Matrix(std::array<Vector<C>, R> elements);

    /// @brief Creates a higher dimensional matrix from an existing matrix.
    ///
    /// 1. a matrix of equal dimensions is constructed by Matrix().
    /// 2. this new matrix is then filled with elements from \p other.
    ///
    /// The elements not overriden will thus either be all zero or form a diagonal of 1:s depending on if the created matrix is a square matrix.
    template <unsigned int M, class Enable = std::enable_if_t<(M <= R && M <= C)>>
    Matrix(const Matrix<M>& other);

    /// @brief The outer product of vector \p lhs and vector \p rhs as a Matrix.
    [[nodiscard]] static auto outer_product(Vector<R> lhs, Vector<C> rhs) -> Matrix<R, C>;

    /// @name Mutators
    /// @{

    /// @brief The memory address of the top-left most element.
    [[nodiscard]] auto begin() -> float*;

    /// @brief The memory address following the bottom-right most element.
    [[nodiscard]] auto end() -> float*;

    /// @brief The \p i th row.
    auto operator[](unsigned int i) -> Vector<C>&;

    /// @brief Swaps the rows indexed by \p i and \p j.
    auto swap_rows(unsigned int i, unsigned int j);

    /// @}
    /// @name Accessors
    /// @{

    /// @brief The memory address of the top-left most element.
    [[nodiscard]] auto begin() const -> const float*;

    /// @brief The memory address following the bottom-right most element.
    [[nodiscard]] auto end() const -> const float*;

    /// @brief The \p i th row.
    auto operator[](unsigned int i) const -> const Vector<C>&;

    /// @brief Checks if this matrix has identical elements to matrix \p other.
    auto operator==(const Matrix<R, C>& other) const -> bool;

    /// @brief Checks if this matrix does not have identical elements to matrix \p other.
    auto operator!=(const Matrix<R, C>& other) const -> bool;

    /// @brief Negated version of this matrix.
    auto operator-() const -> Matrix<R, C>;

    /// @brief This matrix but with all of its elements multiplied by \p scalar.
    auto operator*(float scalar) const -> Matrix<R, C>;

    /// @brief This matrix but with all of its elements divided by \p scalar.
    auto operator/(float scalar) const -> Matrix<R, C>;

    /// @brief This matrix multiplied with vector \p vector.
    auto operator*(const Vector<C>& vector) const -> Vector<R>;

    /// @brief This matrix multiplied with matrix \p other.
    template <unsigned int C2>
    auto operator*(const Matrix<C, C2>& other) const -> Matrix<R, C2>;

    /// @brief The transpose of this matrix.
    [[nodiscard]] auto transpose() const -> Matrix<C, R>;

    /// @brief The reduced row echelon form of this matrix.
    ///
    /// @see https://www.wikiwand.com/en/Gaussian_elimination
    /// @see https://www.wikiwand.com/en/Row_echelon_form
    [[nodiscard]] auto reduced_row_echelon_form() const -> Matrix<R, C>;

    /// @brief The rank of this matrix.
    ///
    /// @see https://www.wikiwand.com/en/Rank_(linear_algebra)
    /// @see https://www.wikiwand.com/en/Linear_independence
    [[nodiscard]] auto rank() const -> unsigned int;

    /// @brief Checks if this matrix has full rank.
    [[nodiscard]] auto has_full_rank() const -> bool;

    /// @brief The rank deficiency of this matrix.
    [[nodiscard]] auto rank_deficiency() const -> unsigned int;

    /// @brief The row vector at row \p r.
    [[nodiscard]] auto row_vector(unsigned int r) const -> Vector<C>;

    /// @brief The column vector at column \p c.
    [[nodiscard]] auto column_vector(unsigned int c) const -> Vector<R>;

    /// @brief Converts this matrix into a 2D array.
    operator std::array<std::array<float, C>, R>() const;

    /// @brief Serializes the current state to JSON.
    [[nodiscard]] auto to_json() const -> debug::JSON;

    /// @}
    /// @name Square Matrix Accessors
    /// @{

    /// @brief The main diagonal of this matrix.
    ///
    /// @see https://www.wikiwand.com/en/Main_diagonal
    template <unsigned int N = R>
    auto main_diagonal() const -> std::enable_if_t<(N == R && R == C), Vector<N>>;

    /// @brief The trace of this matrix.
    ///
    /// @see https://www.wikiwand.com/en/Trace_(linear_algebra)
    template <unsigned int N = R>
    auto trace() const -> std::enable_if_t<(N == R && R == C), float>;

    /// @brief The minor matrix obtained from excluding row \p r and column \p c.
    ///
    /// @see https://www.wikiwand.com/en/Minor_(linear_algebra)
    template <unsigned int N = R>
    auto minor_matrix(unsigned int r, unsigned int c) const -> std::enable_if_t<(N == R && R == C), Matrix<N - 1, N - 1>>;

    /// @brief The determinant of the minor matrix obtained from excluding row \p r and column \p c.
    ///
    /// @see https://www.wikiwand.com/en/Minor_(linear_algebra)
    template <unsigned int N = R>
    auto minor(unsigned int r, unsigned int c) const -> std::enable_if_t<(N == R && R == C), float>;

    /// @brief The cofactor of the element at row \p r and column \p c.
    ///
    /// @see https://www.mathwords.com/c/cofactor_matrix.htm
    /// @see https://www.wikiwand.com/en/Minor_(linear_algebra)
    template <unsigned int N = R>
    auto cofactor(unsigned int r, unsigned int c) const -> std::enable_if_t<(N == R && R == C), float>;

    /// @brief The cofactor matrix of this matrix.
    ///
    /// @see https://www.mathwords.com/c/cofactor_matrix.htm
    /// @see https://www.wikiwand.com/en/Minor_(linear_algebra)
    template <unsigned int N = R>
    auto cofactor_matrix() const -> std::enable_if_t<(N == R && R == C), Matrix<N>>;

    /// @brief The adjugate matrix of this matrix.
    ///
    /// The adjugate matrix is the transpose of the cofactor matrix.
    ///
    /// @see https://www.wikiwand.com/en/Adjugate_matrix
    template <unsigned int N = R>
    auto adjugate() const -> std::enable_if_t<(N == R && R == C), Matrix<N>>;

    /// @brief The inverse of this matrix.
    ///
    /// @see https://www.wikiwand.com/en/Invertible_matrix
    template <unsigned int N = R>
    auto inverse() const -> std::enable_if_t<(N == R && R == C), Matrix<N>>;

    /// @brief The determinant of this matrix.
    ///
    /// This is the base case, which is equal to the only element in the matrix.
    ///
    /// @see https://www.wikiwand.com/en/Determinant
    template <unsigned int N = R>
    auto determinant() const -> std::enable_if_t<(N == R && R == C && N == 1), float>;

    /// @brief The determinant of this matrix.
    ///
    /// @see https://www.wikiwand.com/en/Determinant
    template <unsigned int N = R>
    auto determinant() const -> std::enable_if_t<(N == R && R == C && N > 1), float>;

    /// @brief This matrix but with the translation vector \p translation added.
    ///
    /// @see https://www.wikiwand.com/en/Translation_(geometry)
    /// @see https://www.wikiwand.com/en/Transformation_matrix
    template <unsigned int N = R>
    auto translate(Vector<N - 1> translation) const -> std::enable_if_t<(N == R && R == C), Matrix<N>>;

    /// @brief This matrix rotated by \p angle around the vector \p axis.
    ///
    /// @see https://www.wikiwand.com/en/Rotation_matrix
    template <unsigned int N = R>
    auto rotate(Angle angle, Vector<N - 1> axis) const -> std::enable_if_t<(N == R && R == C && N == 4), Matrix<N>>;

    /// @brief This matrix scaled by the vector \p scale.
    ///
    /// @see https://www.wikiwand.com/en/Scaling_(geometry)
    template <unsigned int N = R>
    auto scale(Vector<N - 1> scale) const -> std::enable_if_t<(N == R && R == C), Matrix<N>>;

    /// @}

  private:
    /// @{
    /// Private state.
    std::array<Vector<C>, R> elements;
    /// @}

    /// @brief Performs elementary row operations to clear the column of the pivot at row \p row and column \p col.
    void row_echelon_clear_pivot_column(unsigned int row, unsigned int col);

    /// @brief Swaps the specified row with the row below that has the leftmost pivot.
    ///
    /// If the current row has the leftmost pivot, nothing happens.
    /// No pivots above row \p row are considered.
    /// No pivots to the left of column \p col are considered.
    void row_echelon_swap_with_leftmost_pivot_row(unsigned int row, unsigned int col);

    /// @brief The leftmost pivot (leading coefficient) in row \p row.
    [[nodiscard]] auto leftmost_pivot(unsigned int row) const -> int;
  };

  /////////////////////
  // Implementations //
  /////////////////////

  template <unsigned int R, unsigned int C>
  Matrix<R, C>::Matrix() : elements() {
    if constexpr (R == C)
      for (unsigned int i = 0; i < R; i++)
        elements[i][i] = 1.0F;
  }

  template <unsigned int R, unsigned int C>
  Matrix<R, C>::Matrix(std::initializer_list<Vector<C>> elements) {
    if (elements.size() != R)
      LOG_ERROR("Must provide exactly R elements."); // LCOV_EXCL_BR_LINE

    std::copy(elements.begin(), elements.end(), this->elements.begin());
  }

  template <unsigned int R, unsigned int C>
  Matrix<R, C>::Matrix(std::array<Vector<C>, R> elements) : elements(elements) {}

  template <unsigned int R, unsigned int C>
  template <unsigned int M, class Enable>
  Matrix<R, C>::Matrix(const Matrix<M>& other)
          : Matrix() {

    for (unsigned int r = 0; r < M; r++)
      for (unsigned int c = 0; c < M; c++)
        elements[r][c] = other[r][c];
  }

  template <unsigned int R, unsigned int C>
  [[nodiscard]] static auto outer_product(Vector<R> lhs, Vector<C> rhs) -> Matrix<R, C> {
    Matrix<R, C> matrix;
    for (unsigned int r = 0; r < R; r++)
      for (unsigned int c = 0; c < C; c++)
        matrix[r][c] = lhs[r] * rhs[c];
    return matrix;
  }

  template <unsigned int R, unsigned int C>
  [[nodiscard]] auto Matrix<R, C>::begin() -> float* {
    return elements[0].begin();
  }

  template <unsigned int R, unsigned int C>
  [[nodiscard]] auto Matrix<R, C>::end() -> float* {
    return elements[R - 1].end();
  }

  template <unsigned int R, unsigned int C>
  auto Matrix<R, C>::swap_rows(unsigned int i, unsigned int j) {
    for (unsigned int c = 0; c < C; c++)
      std::swap(elements[i][c], elements[j][c]);
  }

  template <unsigned int R, unsigned int C>
  [[nodiscard]] auto Matrix<R, C>::begin() const -> const float* {
    return elements[0].begin();
  }

  template <unsigned int R, unsigned int C>
  [[nodiscard]] auto Matrix<R, C>::end() const -> const float* {
    return elements[R - 1].end();
  }

  template <unsigned int R, unsigned int C>
  Matrix<R, C>::operator std::array<std::array<float, C>, R>() const {
    std::array<std::array<float, C>, R> m;
    for (unsigned int i = 0; i < R; i++)
      m[i] = elements[i];
    return m;
  }

  template <unsigned int R, unsigned int C>
  auto Matrix<R, C>::operator[](unsigned int i) const -> const Vector<C>& {
    return elements[i];
  }

  template <unsigned int R, unsigned int C>
  auto Matrix<R, C>::operator[](unsigned int i) -> Vector<C>& {
    return elements[i];
  }

  template <unsigned int R, unsigned int C>
  auto Matrix<R, C>::operator==(const Matrix<R, C>& other) const -> bool {
    for (unsigned int r = 0; r < R; r++)
      if (elements[r] != other[r])
        return false;

    return true;
  }

  template <unsigned int R, unsigned int C>
  auto Matrix<R, C>::operator!=(const Matrix<R, C>& other) const -> bool {
    return !(*this == other);
  }

  template <unsigned int R, unsigned int C>
  auto Matrix<R, C>::operator-() const -> Matrix<R, C> {
    Matrix<R, C> res = *this;
    for (unsigned int r = 0; r < R; r++)
      for (unsigned int c = 0; c < C; c++)
        res[r][c] *= -1;

    return res;
  }

  template <unsigned int R, unsigned int C>
  auto Matrix<R, C>::operator*(float scalar) const -> Matrix<R, C> {
    Matrix<R, C> res = *this;
    for (unsigned int r = 0; r < R; r++)
      for (unsigned int c = 0; c < C; c++)
        res[r][c] *= scalar;

    return res;
  }

  template <unsigned int R, unsigned int C>
  auto Matrix<R, C>::operator/(float scalar) const -> Matrix<R, C> {
    Matrix<R, C> res = *this;
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

  // TODO: Pivot is a (row, col). Maybe rename to `elimate` or something?
  template <unsigned int R, unsigned int C>
  void Matrix<R, C>::row_echelon_clear_pivot_column(unsigned int row, unsigned int col) {
    for (unsigned int r = 0; r < R; r++)
      if (r != row)
        elements[r] -= elements[row] * (elements[r][col] / elements[row][col]);
    elements[row] /= elements[row][col];
  }

  template <unsigned int R, unsigned int C>
  void Matrix<R, C>::row_echelon_swap_with_leftmost_pivot_row(unsigned int row, unsigned int col) {
    for (unsigned int j = col; j < C; j++) {

      // If current row has the leftmost pivot, do nothing.
      if (elements[row][j] != 0)
        return;

      for (unsigned int i = row + 1; i < R; i++) {
        // If this row has the leftmost pivot, we swap with it.
        if (elements[i][j] != 0) {
          swap_rows(row, i);
          return;
        }
      }
    }
  }

  /// @internal
  /// Returns the column of the provided row's leftmost pivot.
  /// If there is no pivot element it will return -1.
  template <unsigned int R, unsigned int C>
  auto Matrix<R, C>::leftmost_pivot(unsigned int row) const -> int {
    for (unsigned int col = 0; col < C; col++)
      if (elements[row][col])
        return (int) col;
    return -1;
  }

  /// @internal
  /// For each row (top -> bottom), we consider
  /// 1. the pivot (a.k.a. leading coefficient) of the current row.
  /// 2. if any row below it has a pivot further to the left.
  ///
  /// If 2., we swap that row with the current one so the current row has the leftmost pivot amongst the rows considered.
  /// Then we clear the elements directly above and below the pivot, and scale the current row such that the pivot becomes 1.
  template <unsigned int R, unsigned int C>
  auto Matrix<R, C>::reduced_row_echelon_form() const -> Matrix<R, C> {
    Matrix<R, C> m = *this;
    unsigned int r = 0;
    unsigned int c = 0;
    while (r < R && c < C) {

      m.row_echelon_swap_with_leftmost_pivot_row(r, c);

      int potential_pivot = m.leftmost_pivot(r);
      if (potential_pivot == -1)
        break;

      m.row_echelon_clear_pivot_column(r, potential_pivot);

      r++;
      c = potential_pivot + 1;
    }

    return m;
  }

  template <unsigned int R, unsigned int C>
  [[nodiscard]] auto Matrix<R, C>::rank() const -> unsigned int {
    Matrix<R, C> reduced = reduced_row_echelon_form();

    unsigned int rank = 0;
    // Count amount of rows that are not just zeroes.
    for (unsigned int r = 0; r < R; r++) {
      for (unsigned int c = 0; c < C; c++) {
        if (reduced[r][c] != 0) {
          rank++;
          break;
        }
      }
    }

    return rank;
  }

  template <unsigned int R, unsigned int C>
  [[nodiscard]] auto Matrix<R, C>::has_full_rank() const -> bool {
    return rank() == std::min(R, C);
  }

  template <unsigned int R, unsigned int C>
  [[nodiscard]] auto Matrix<R, C>::rank_deficiency() const -> unsigned int {
    return std::min(R, C) - rank();
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
  [[nodiscard]] auto Matrix<R, C>::to_json() const -> debug::JSON {
    debug::JSON json = debug::JSON::array();
    for (auto& row : elements)
      json.emplace_back(row.to_json());

    return json;
  };

  /////////////////////////////
  // Square matrix functions //
  /////////////////////////////

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
      LOG_ERROR("Determinant is 0, which means that this matrix is singular/degenerate."); // LCOV_EXCL_BR_LINE

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
  auto Matrix<R, C>::rotate(Angle angle, Vector<N - 1> axis) const -> std::enable_if_t<(N == R && R == C && N == 4), Matrix<N>> {
    axis = axis.normalized();

    // NOTE: pair = point + axis
    // 1. Rotate the pair so that the axis is in the XZ-plane.
    float xy_len   = sqrt(std::pow(axis.x(), 2) + std::pow(axis.y(), 2));
    Matrix<3> m_xz = {
      {axis.x() / xy_len, axis.y() / xy_len, 0},
      {-axis.y() / xy_len, axis.x() / xy_len, 0},
      {0, 0, 1},
    };

    // 2. Rotate the pair so that the axis is equivalent to the Z-axis.
    float xz_len  = sqrt(std::pow(axis.x(), 2) + std::pow(axis.z(), 2));
    Matrix<3> m_z = {
      {axis.z() / xz_len, 0, -axis.x() / xz_len},
      {0, 1, 0},
      {axis.x() / xz_len, 0, axis.z() / xz_len},
    };

    // 3. Rotate the point about the z-axis by the desired rotation angle.
    float rads = angle.radians();
    Matrix<3> rot_z{
      // NOTE: Left-handed z-rotation
      {std::cos(rads), std::sin(rads), 0},
      {-std::sin(rads), std::cos(rads), 0},
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
