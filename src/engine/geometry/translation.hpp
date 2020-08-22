#pragma once

#include "matrix.hpp"

namespace engine::geometry {

  /// @brief Creates the column-major matrix that translates by vector \p v.
  ///
  /// @see https://www.wikiwand.com/en/Translation_(geometry)
  /// @see https://www.wikiwand.com/en/Transformation_matrix
  template <unsigned int N = 3>
  auto translation_matrix(Vector<N> v) -> Matrix<N + 1> {
    Matrix<N + 1> m;
    for (unsigned int r = 0; r < N; r++)
      m[r][N] = v[r];

    return m;
  }

}
