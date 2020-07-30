#include "../util.hpp"

#include "../../engine/geometry/matrix.hpp"
using namespace engine::geometry;

TEST(MatrixTest, Trace1) {
  Matrix<2> m({
    {1, 2},
    {3, 4},
  });
  EXPECT_EQ(m.trace(), 5.0F);
}

TEST(MatrixTest, MinorMatrix1) {
  Matrix<2> m({
    {1, 2},
    {3, 4},
  });
  EXPECT_EQ(m.minor_matrix(0, 0)[0][0], 4.0F);
  EXPECT_EQ(m.minor_matrix(0, 1)[0][0], 3.0F);
  EXPECT_EQ(m.minor_matrix(1, 0)[0][0], 2.0F);
  EXPECT_EQ(m.minor_matrix(1, 1)[0][0], 1.0F);
}

TEST(MatrixTest, Determinant1) {
  Matrix<1> m({
    {-17.3F},
  });
  EXPECT_EQ(m.determinant(), -17.3F);
}

TEST(MatrixTest, Determinant2) {
  Matrix<2> m({
    {1, 2},
    {3, 4},
  });
  EXPECT_EQ(m.determinant(), -2.0F);
}

TEST(MatrixTest, Determinant3) {
  Matrix<2> m({
    {-5, -4},
    {-2, -3},
  });
  EXPECT_EQ(m.determinant(), 7.0F);
}

TEST(MatrixTest, Determinant4) {
  Matrix<3> m({
    {2, -3, 1},
    {2, 0, -1},
    {1, 4, 5},
  });
  EXPECT_EQ(m.determinant(), 49.0F);
}

TEST(MatrixTest, Transpose1) {
  Matrix<3> m1({
    {1, 2, 3},
    {0, 4, 5},
    {1, 0, 6},
  });
  Matrix<3> m2({
    {1, 0, 1},
    {2, 4, 0},
    {3, 5, 6},
  });
  EXPECT_EQ(m1.transpose(), m2);
  EXPECT_EQ(m1, m2.transpose());
  EXPECT_EQ(m1.transpose().transpose(), m1);
  EXPECT_EQ(m2.transpose().transpose(), m2);
}

TEST(MatrixTest, Transpose2) {
  Matrix<2, 1> m1({
    {7},
    {9},
  });
  Matrix<1, 2> m2({
    {7, 9},
  });
  EXPECT_EQ(m1.transpose(), m2);
  EXPECT_EQ(m1, m2.transpose());
  EXPECT_EQ(m1.transpose().transpose(), m1);
  EXPECT_EQ(m2.transpose().transpose(), m2);
}

TEST(MatrixTest, Transpose3) {
  Matrix<3, 1> m1({
    {1},
    {2},
    {3},
  });
  Matrix<1, 3> m2({
    {1, 2, 3},
  });
  EXPECT_EQ(m1.transpose(), m2);
  EXPECT_EQ(m1, m2.transpose());
  EXPECT_EQ(m1.transpose().transpose(), m1);
  EXPECT_EQ(m2.transpose().transpose(), m2);
}

TEST(MatrixTest, Transpose4) {
  Matrix<3, 2> m1({
    {1, 4},
    {2, 5},
    {3, 6},
  });
  Matrix<2, 3> m2({
    {1, 2, 3},
    {4, 5, 6},
  });
  EXPECT_EQ(m1.transpose(), m2);
  EXPECT_EQ(m1, m2.transpose());
  EXPECT_EQ(m1.transpose().transpose(), m1);
  EXPECT_EQ(m2.transpose().transpose(), m2);
}

TEST(MatrixTest, Transpose5) {
  Matrix<2, 3> m1({
    {7, 0, 4},
    {9, 3, 5},
  });
  Matrix<3, 2> m2({
    {7, 9},
    {0, 3},
    {4, 5},
  });
  EXPECT_EQ(m1.transpose(), m2);
  EXPECT_EQ(m1, m2.transpose());
  EXPECT_EQ(m1.transpose().transpose(), m1);
  EXPECT_EQ(m2.transpose().transpose(), m2);
}

TEST(MatrixTest, CofactorMatrix1) {
  Matrix<3> m({
    {1, 2, 3},
    {0, 4, 5},
    {1, 0, 6},
  });
  Matrix<3> expected({
    {24, 5, -4},
    {-12, 3, 2},
    {-2, -5, 4},
  });
  EXPECT_EQ(m.cofactor_matrix(), expected);
}
