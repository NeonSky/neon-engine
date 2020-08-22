#pragma once

#include "matrix.hpp"

namespace engine::geometry {

  /// @brief Creates the matrix that uniformly scales by \p c.
  ///
  /// @see https://www.wikiwand.com/en/Scaling_(geometry)
  template <unsigned int N = 3>
  auto scale_matrix(float c) -> Matrix<N> {
    Matrix<N> m;
    m[N - 1][N - 1] = c;
    return m;
  }

  /// @brief Creates the matrix that scales by vector \p v.
  ///
  /// @see https://www.wikiwand.com/en/Scaling_(geometry)
  template <unsigned int N = 3>
  auto scale_matrix(Vector<N> v) -> Matrix<N> {
    Matrix<N> m;
    for (unsigned int i = 0; i < N; i++)
      m[i][i] = v[i];

    return m;
  }

}
