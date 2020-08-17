#include "../util.hpp"

#include "../../engine/geometry/matrix.hpp"
using namespace engine::geometry;

TEST(MatrixTest, Constructor1) {
  ASSERT_THROW(Matrix<2>({{1, 2}}), std::runtime_error);
}

TEST(MatrixTest, Constructor2) {
  std::array<Vector<2>, 3> values{
    {{2.0F, 2.5F},
     {4.0F, 5.0F},
     {6.0F, 7.5F}}};

  Matrix<3, 2> expected{
    {2.0F, 2.5F},
    {4.0F, 5.0F},
    {6.0F, 7.5F}};

  Matrix<3, 2> m(values);
  EXPECT_EQ(m, expected);
}

TEST(MatrixTest, Constructor3) {
  Matrix<4> m;
  EXPECT_EQ(m, Matrix<4>({
                 {1, 0, 0, 0},
                 {0, 1, 0, 0},
                 {0, 0, 1, 0},
                 {0, 0, 0, 1},
               }));
}

TEST(MatrixTest, Constructor4) {
  Matrix<3, 3> m{
    UnitVector<3>{0.0F, 0.0F, 1.0F},
    UnitVector<3>{0.0F, 1.0F, 0.0F},
    UnitVector<3>{1.0F, 0.0F, 0.0F},
  };
  Matrix<3, 3> expected{
    {0.0F, 0.0F, 1.0F},
    {0.0F, 1.0F, 0.0F},
    {1.0F, 0.0F, 0.0F},
  };

  EXPECT_EQ(m, expected);
}

TEST(MatrixTest, Size1) {
  Matrix<1> m1;
  Matrix<2> m2;
  Matrix<3> m3;
  Matrix<4> m4;

  EXPECT_EQ(sizeof(m1), 1 * 1 * sizeof(float));
  EXPECT_EQ(sizeof(m2), 2 * 2 * sizeof(float));
  EXPECT_EQ(sizeof(m3), 3 * 3 * sizeof(float));
  EXPECT_EQ(sizeof(m4), 4 * 4 * sizeof(float));
}

TEST(MatrixTest, Size2) {
  Matrix<1, 3> m1;
  Matrix<3, 1> m2;
  Matrix<2, 4> m3;
  Matrix<4, 2> m4;

  EXPECT_EQ(sizeof(m1), 1 * 3 * sizeof(float));
  EXPECT_EQ(sizeof(m2), 3 * 1 * sizeof(float));
  EXPECT_EQ(sizeof(m3), 2 * 4 * sizeof(float));
  EXPECT_EQ(sizeof(m4), 4 * 2 * sizeof(float));
}

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

TEST(MatrixTest, MinorMatrix2) {
  Matrix<4> m{
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16},
  };
  EXPECT_EQ(m.minor_matrix(0, 0), Matrix<3>({
                                    {6, 7, 8},
                                    {10, 11, 12},
                                    {14, 15, 16},
                                  }));
  EXPECT_EQ(m.minor_matrix(1, 2), Matrix<3>({
                                    {1, 2, 4},
                                    {9, 10, 12},
                                    {13, 14, 16},
                                  }));
  EXPECT_EQ(m.minor_matrix(3, 3), Matrix<3>({
                                    {1, 2, 3},
                                    {5, 6, 7},
                                    {9, 10, 11},
                                  }));
}

TEST(MatrixTest, Adjugate1) {
  Matrix<4> m{
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16},
  };
  EXPECT_EQ(m.adjugate(), Matrix<4>({
                            {0, 0, 0, 0},
                            {0, 0, 0, 0},
                            {0, 0, 0, 0},
                            {0, 0, 0, 0},
                          }));
}

TEST(MatrixTest, Adjugate2) {
  Matrix<4> m{
    {-1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16},
  };
  EXPECT_EQ(m.adjugate(), Matrix<4>({
                            {0, 0, 0, 0},
                            {0, 8, -16, 8},
                            {0, -16, 32, -16},
                            {0, 8, -16, 8},
                          }));
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

TEST(MatrixTest, Determinant5) {
  Matrix<4> m({
    {2, -3, 1, 7},
    {2, 0, -1, 3},
    {1, 4, 5, 5},
    {0, 1, 2, 3},
  });
  EXPECT_EQ(m.determinant(), 71.0F);
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

TEST(MatrixTest, Negates1) {
  Matrix<2, 3> m({
    {7, 0, -4},
    {-9, 3, 5},
  });
  Matrix<2, 3> expected({
    {-7, 0, 4},
    {9, -3, -5},
  });
  EXPECT_EQ(-m, expected);
}

TEST(MatrixTest, Inverse1) {
  Matrix<2> m({
    {4, 7},
    {2, 6},
  });
  Matrix<2> expected({
    {0.6F, -0.7F},
    {-0.2F, 0.4F},
  });
  EXPECT_EQ(m.inverse(), expected);
}

TEST(MatrixTest, Inverse2) {
  Matrix<3> m({
    {1, 2, 3},
    {0, 4, 5},
    {1, 0, 6},
  });
  Matrix<3> expected({
    {12.0F / 11.0F, -6.0F / 11.0F, -1.0F / 11.0F},
    {5.0F / 22.0F, 3.0F / 22.0F, -5.0F / 22.0F},
    {-2.0F / 11.0F, 1.0F / 11.0F, 2.0F / 11.0F},
  });
  EXPECT_EQ(m.inverse(), expected);
}

TEST(MatrixTest, Inverse3) {
  Matrix<4> m{
    {1, 2, 3, 4},
    {4, 3, 2, 1},
    {9, 1, 1, 12},
    {2, 3, 2, 1},
  };
  Matrix<4> expected = Matrix<4>{
                         {0, -55, 0, 55},
                         {46, 86, -10, -150},
                         {-70, -95, 20, 135},
                         {2, 42, -10, -40},
                       } /
                       -110.0F; // -110 is the determinant for m
  EXPECT_EQ(m.inverse(), expected);
}

TEST(MatrixTest, Inverse4) {
  Matrix<2> m({
    {-1.0F, 1.5F},
    {2.0F / 3.0F, -1.0F},
  });
  ASSERT_THROW(m.inverse(), std::runtime_error);
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

TEST(MatrixTest, ReducedRowEchelonForm1) {
  Matrix<3, 4> m({
    {2, 1, -1, 8},
    {-3, -1, 2, -11},
    {-2, 1, 2, -3},
  });
  Matrix<3, 4> expected({
    {1, 0, 0, 2},
    {0, 1, 0, 3},
    {0, 0, 1, -1},
  });
  EXPECT_EQ(m.reduced_row_echelon_form(), expected);
}

TEST(MatrixTest, ReducedRowEchelonForm2) {
  Matrix<3, 4> m({
    {1, 2, -4, 2},
    {7, 6, -2, -5},
    {0, -3, -5, -8},
  });
  Matrix<3, 4> expected({
    {1, 0, 0, -2.8983051F},
    {0, 1, 0, 2.5677967F},
    {0, 0, 1, 0.0593220F},
  });
  EXPECT_EQ(m.reduced_row_echelon_form(), expected);
}

TEST(MatrixTest, ReducedRowEchelonForm3) {
  Matrix<2, 3> m({
    {1, 3, -1},
    {0, 1, 7},
  });
  Matrix<2, 3> expected({
    {1, 0, -22},
    {0, 1, 7},
  });
  EXPECT_EQ(m.reduced_row_echelon_form(), expected);
}

TEST(MatrixTest, ReducedRowEchelonForm4) {
  Matrix<3, 3> m({
    {0, 0, 1},
    {0, 1, 0},
    {1, 0, 0},
  });
  Matrix<3, 3> expected({
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1},
  });
  EXPECT_EQ(m.reduced_row_echelon_form(), expected);
}

TEST(MatrixTest, ReducedRowEchelonForm5) {
  Matrix<3, 4> m({
    {1, 3, 1, 9},
    {1, 1, -1, 1},
    {3, 11, 5, 35},
  });
  Matrix<3, 4> expected({
    {1, 0, -2, -3},
    {0, 1, 1, 4},
    {0, 0, 0, 0},
  });
  EXPECT_EQ(m.reduced_row_echelon_form(), expected);
}

TEST(MatrixTest, Rank1) {
  Matrix<3, 3> m({
    {1, 0, 1},
    {-2, -3, 1},
    {3, 3, 0},
  });
  int rank = m.rank();
  EXPECT_EQ(rank, 2);
  EXPECT_EQ(rank, m.transpose().rank());

  EXPECT_FALSE(m.has_full_rank());
  EXPECT_EQ(m.rank_deficiency(), 1);
}

TEST(MatrixTest, Rank2) {
  Matrix<2, 4> m({
    {1, 1, 0, 2},
    {-1, -1, 0, -2},
  });
  int rank = m.rank();
  EXPECT_EQ(rank, 1);
  EXPECT_EQ(rank, m.transpose().rank());

  EXPECT_FALSE(m.has_full_rank());
  EXPECT_EQ(m.rank_deficiency(), 1);
}

TEST(MatrixTest, Rank3) {
  Matrix<2, 3> m({
    {1, 3, -1},
    {0, 1, 7},
  });
  int rank = m.rank();
  EXPECT_EQ(rank, 2);
  EXPECT_EQ(rank, m.transpose().rank());

  EXPECT_TRUE(m.has_full_rank());
  EXPECT_EQ(m.rank_deficiency(), 0);
}

TEST(MatrixTest, Rank4) {
  Matrix<3, 3> m({
    {0, 0, -1},
    {0, 1, 7},
    {1, 1, 7},
  });
  int rank = m.rank();
  EXPECT_EQ(rank, 3);
  EXPECT_EQ(rank, m.transpose().rank());
  EXPECT_TRUE(m.has_full_rank());
  EXPECT_EQ(m.rank_deficiency(), 0);
}

TEST(MatrixTest, MainDiagonal1) {
  Matrix<3, 3> m({
    {0, 1, 2},
    {3, 4, 5},
    {6, 7, 8},
  });
  EXPECT_EQ(m.main_diagonal(), Vector<3>(0, 4, 8));
}

TEST(MatrixTest, Iterates1) {
  Matrix<3, 3> m({
    {0, 1, 2},
    {3, 4, 5},
    {6, 7, 8},
  });

  int i = 0;
  for (auto& e : std::as_const(m)) {
    EXPECT_EQ(e, m[(i / 3)][(i % 3)]);
    i++;
  }

  EXPECT_EQ(i, 9);
}

TEST(MatrixTest, Iterates2) {
  Matrix<4> m{
    {0, 1, 2, 3},
    {4, 5, 6, 7},
    {8, 9, 10, 11},
    {12, 13, 14, 15},
  };

  int i = 0;
  for (auto& e : std::as_const(m)) {
    EXPECT_EQ(e, m[(i / 4)][(i % 4)]);
    i++;
  }

  EXPECT_EQ(i, 16);
}

TEST(MatrixTest, Iterates3) {
  Matrix<3, 3> m({
    {0, 1, 2},
    {3, 4, 5},
    {6, 7, 8},
  });
  Matrix<3, 3> expected({
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9},
  });
  EXPECT_NE(m, expected);

  for (auto& e : m)
    e += 1.0F;

  EXPECT_EQ(m, expected);
}

TEST(MatrixTest, OuterProduct1) {
  Vector<2> vector1(1.0F, 2.0F);
  Vector<2> vector2(0.5F, 1.5F);
  Matrix<2> expected{
    {0.5F, 1.5F},
    {1.0F, 3.0F}};
  EXPECT_EQ(outer_product(vector1, vector2), expected);
}

TEST(MatrixTest, OuterProduct2) {
  Vector<3> vector1(1.0F, 2.0F, 3.0F);
  Vector<2> vector2(4.0F, 5.0F);
  Matrix<3, 2> expected{
    {4.0F, 5.0F},
    {8.0F, 10.0F},
    {12.0F, 15.0F},
  };
  EXPECT_EQ(outer_product(vector1, vector2), expected);
}

TEST(MatrixTest, SwapsRows1) {
  Matrix<3, 2> m1{
    {4.0F, 5.0F},
    {8.0F, 10.0F},
    {12.0F, 15.0F},
  };
  Matrix<3, 2> m2{
    {8.0F, 10.0F},
    {4.0F, 5.0F},
    {12.0F, 15.0F},
  };

  auto m = m1;
  EXPECT_EQ(m, m1);

  m.swap_rows(0, 1);
  EXPECT_EQ(m, m2);

  m.swap_rows(0, 1);
  EXPECT_EQ(m, m1);

  m.swap_rows(0, 0);
  EXPECT_EQ(m, m1);
  m.swap_rows(1, 1);
  EXPECT_EQ(m, m1);
  m.swap_rows(2, 2);
  EXPECT_EQ(m, m1);
}

TEST(MatrixTest, SwapsRows2) {
  Matrix<3> m;

  m.swap_rows(0, 2);
  EXPECT_EQ(m, Matrix<3>({
                 {0.0F, 0.0F, 1.0F},
                 {0.0F, 1.0F, 0.0F},
                 {1.0F, 0.0F, 0.0F},
               }));

  m.swap_rows(1, 2);
  EXPECT_EQ(m, Matrix<3>({
                 {0.0F, 0.0F, 1.0F},
                 {1.0F, 0.0F, 0.0F},
                 {0.0F, 1.0F, 0.0F},
               }));
}

TEST(MatrixTest, SwapsRows3) {
  Matrix<4> m;
  m.swap_rows(0, 3);
  m.swap_rows(1, 2);

  EXPECT_EQ(m, Matrix<4>({
                 {0.0F, 0.0F, 0.0F, 1.0F},
                 {0.0F, 0.0F, 1.0F, 0.0F},
                 {0.0F, 1.0F, 0.0F, 0.0F},
                 {1.0F, 0.0F, 0.0F, 0.0F},
               }));
}

TEST(MatrixTest, SwapsRows4) {
  Matrix<2> m{
    {1.0F, 4.0F},
    {2.0F, 3.0F},
  };
  m.swap_rows(0, 1);

  EXPECT_EQ(m, Matrix<2>({
                 {2.0F, 3.0F},
                 {1.0F, 4.0F},
               }));
}

TEST(MatrixTest, SwapsRows5) {
  Matrix<1> m{
    {-5.0F}};
  m.swap_rows(0, 0);
  EXPECT_EQ(m, Matrix<1>({
                 {-5.0F},
               }));
}

TEST(MatrixTest, SwapsRows6) {
  Matrix<2, 3> m1{
    {1.0F, 2.0F, 3.0F},
    {1.0F, 2.0F, 3.0F}};
  auto m = m1;

  m.swap_rows(0, 0);
  EXPECT_EQ(m, m1);

  m.swap_rows(0, 1);
  EXPECT_EQ(m, m1);

  m.swap_rows(1, 1);
  EXPECT_EQ(m, m1);
}

TEST(MatrixTest, SwapsRows7) {
  Matrix<3, 1> m{
    {-1.0F},
    {-2.0F},
    {-3.0F}};
  m.swap_rows(1, 2);
  EXPECT_EQ(m, (Matrix<3, 1>({{-1.0F}, {-3.0F}, {-2.0F}})));
}

TEST(MatrixTest, SwapsRows8) {
  Matrix<2, 4> m1{
    {-1.0F, 2.0F, -3.0F, -4.3F},
    {-1.0F, 2.0F, -3.0F, -4.3F}};
  auto m = m1;

  m.swap_rows(0, 0);
  EXPECT_EQ(m, m1);

  m.swap_rows(0, 1);
  EXPECT_EQ(m, m1);

  m.swap_rows(1, 1);
  EXPECT_EQ(m, m1);
}

TEST(MatrixTest, SwapsRows9) {
  Matrix<3, 4> m{
    {0.0F, 9.0F, 9.0F, 0.0F},
    {7.7F, 0.0F, 0.0F, 7.7F},
    {0.0F, 3.0F, 3.0F, 0.0F}};
  m.swap_rows(0, 0);
  m.swap_rows(1, 2);
  m.swap_rows(2, 2);
  EXPECT_EQ(m, (Matrix<3, 4>({
                 {0.0F, 9.0F, 9.0F, 0.0F},
                 {0.0F, 3.0F, 3.0F, 0.0F},
                 {7.7F, 0.0F, 0.0F, 7.7F},
               })));
}

TEST(MatrixTest, SwapsRows10) {
  Matrix<4, 2> m{
    {1.0F, 4.0F},
    {3.0F, 2.0F},
    {2.0F, 3.0F},
    {4.0F, 1.0F}};

  m.swap_rows(0, 3);
  EXPECT_EQ(m, (Matrix<4, 2>({
                 {4.0F, 1.0F},
                 {3.0F, 2.0F},
                 {2.0F, 3.0F},
                 {1.0F, 4.0F},
               })));
}

TEST(MatrixTest, Submatrix1) {
  Matrix<3, 4> m{
    {0.0F, 9.0F, 9.0F, 0.0F},
    {7.7F, 0.0F, 0.0F, 7.7F},
    {0.0F, 3.0F, 3.0F, 0.0F}};

  EXPECT_EQ((m.submatrix<3, 3>()), (Matrix<3>({
                                     {0.0F, 9.0F, 9.0F},
                                     {7.7F, 0.0F, 0.0F},
                                     {0.0F, 3.0F, 3.0F},
                                   })));
  EXPECT_EQ((m.submatrix<2, 4>()), (Matrix<2, 4>({
                                     {0.0F, 9.0F, 9.0F, 0.0F},
                                     {7.7F, 0.0F, 0.0F, 7.7F},
                                   })));
}

TEST(MatrixTest, Submatrix2) {
  Matrix<3, 4> m{
    {1.0F, 2.0F, 3.0F, 4.0F},
    {5.0F, 6.0F, 7.0F, 8.0F},
    {4.0F, 3.0F, 2.0F, 1.0F}};

  EXPECT_EQ((m.submatrix<2, 2>()), (Matrix<2>({
                                     {1, 2},
                                     {5, 6},
                                   })));
  EXPECT_EQ((m.submatrix<2, 2>(1)), (Matrix<2>({
                                      {5, 6},
                                      {4, 3},
                                    })));

  EXPECT_EQ((m.submatrix<2, 2>(0, 1)), (Matrix<2>({
                                         {2, 3},
                                         {6, 7},
                                       })));
  EXPECT_EQ((m.submatrix<2, 2>(1, 1)), (Matrix<2>({
                                         {6, 7},
                                         {3, 2},
                                       })));

  EXPECT_EQ((m.submatrix<2, 2>(0, 2)), (Matrix<2>({
                                         {3, 4},
                                         {7, 8},
                                       })));
  EXPECT_EQ((m.submatrix<2, 2>(1, 2)), (Matrix<2>({
                                         {7, 8},
                                         {2, 1},
                                       })));
}

TEST(MatrixTest, Submatrix3) {
  Matrix<3, 4> m{
    {1.0F, 2.0F, 3.0F, 4.0F},
    {5.0F, 6.0F, 7.0F, 8.0F},
    {4.0F, 3.0F, 2.0F, 1.0F}};

  ASSERT_NO_THROW((m = m.submatrix()));
  ASSERT_NO_THROW((m = m.submatrix<3, 4>()));

  ASSERT_THROW((m = m.submatrix<3, 4>(1, 0)), std::runtime_error);
  ASSERT_THROW((m = m.submatrix<3, 4>(0, 1)), std::runtime_error);
  ASSERT_THROW((m = m.submatrix<3, 4>(1, 1)), std::runtime_error);
}

TEST(MatrixTest, Translates1) {
  Matrix<3> m{
    {2.0F, 0.0F, 0.0F},
    {0.0F, 1.0F, 0.0F},
    {0.0F, 0.0F, 1.0F},
  };
  Matrix<3> expected{
    {2.0F, 0.0F, 2.0F},
    {0.0F, 1.0F, 0.0F},
    {0.0F, 0.0F, 1.0F},
  };
  EXPECT_EQ(m.translate({2.0F, 0.0F}), expected);
}

TEST(MatrixTest, Translates2) {
  Matrix<3> m{
    {1.5F, 0.0F, 0.0F},
    {0.0F, 3.0F, 0.0F},
    {0.0F, 0.0F, 1.0F},
  };
  Matrix<3> expected{
    {1.5F, 0.0F, 2.0F},
    {0.0F, 3.0F, -1.2F},
    {0.0F, 0.0F, 1.0F},
  };
  EXPECT_EQ(m.translate({2.0F, -1.2F}), expected);
}

TEST(MatrixTest, Translates3) {
  Matrix<3> m{
    {-2.7F, 5.0F, 12.0F},
    {8.0F, 1.3F, 0.0F},
    {-22.0F, 2.3F, 1.0F},
  };
  Matrix<3> expected{
    {96.3F, -5.35F, 7.5F},
    {-75.6F, 10.04F, 3.8F},
    {-22.0F, 2.3F, 1.0F},
  };
  EXPECT_EQ(m.translate({-4.5F, 3.8F}), expected);
}

TEST(MatrixTest, Translates4) {
  Matrix<4> m{
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1},
  };
  Matrix<4> expected{
    {1, 0, 0, -4.5F},
    {0, 1, 0, 3.8F},
    {0, 0, 1, 2.4F},
    {0, 0, 0, 1},
  };
  EXPECT_EQ(m.translate({-4.5F, 3.8F, 2.4F}), expected);
}

TEST(MatrixTest, Rotates1) {
  Matrix<3> m{
    {1.0F, 0.0F, 0.0F},
    {0.0F, 1.0F, 0.0F},
    {0.0F, 0.0F, 1.0F},
  };
  Matrix<3> expected{
    {1.0F, 0.0F, 0.0F},
    {0.0F, 0.0F, 1.0F},
    {0.0F, -1.0F, 0.0F},
  };
  m = m.rotate(Angle(90, Angle::Unit::DEGREES), UnitVector<3>(1.0F, 0.0F, 0.0F));
  EXPECT_EQ(m, expected);

  for (auto& e : m)
    EXPECT_FALSE(std::isnan(e));
}

TEST(MatrixTest, Rotates2) {
  Matrix<3> m{
    {1.0F, 0.0F, 0.0F},
    {0.0F, 1.0F, 0.0F},
    {0.0F, 0.0F, 1.0F},
  };
  Matrix<3> expected{
    {0.0F, 0.0F, -1.0F},
    {0.0F, 1.0F, 0.0F},
    {1.0F, 0.0F, 0.0F},
  };
  m = m.rotate(Angle(90, Angle::Unit::DEGREES), UnitVector<3>(0.0F, 1.0F, 0.0F));
  EXPECT_EQ(m, expected);

  for (auto& e : m)
    EXPECT_FALSE(std::isnan(e));
}

TEST(MatrixTest, Rotates3) {
  Matrix<3> m{
    {1.0F, 0.0F, 0.0F},
    {0.0F, 1.0F, 0.0F},
    {0.0F, 0.0F, 1.0F},
  };
  Matrix<3> expected{
    {0.0F, 1.0F, 0.0F},
    {-1.0F, 0.0F, 0.0F},
    {0.0F, 0.0F, 1.0F},
  };
  m = m.rotate(Angle(90, Angle::Unit::DEGREES), UnitVector<3>(0.0F, 0.0F, 1.0F));
  EXPECT_EQ(m, expected);

  for (auto& e : m)
    EXPECT_FALSE(std::isnan(e));
}

TEST(MatrixTest, Scales1) {
  Matrix<3, 2> m{
    {4.0F, 5.0F},
    {8.0F, 10.0F},
    {12.0F, 15.0F},
  };
  Matrix<3, 2> expected{
    {4.8F, 6.0F},
    {9.6F, 12.0F},
    {14.4F, 18.0F},
  };
  EXPECT_EQ(m * 1.2F, expected);
}

TEST(MatrixTest, Scales2) {
  Matrix<3, 2> m{
    {4.0F, 5.0F},
    {8.0F, 10.0F},
    {12.0F, 15.0F},
  };
  Matrix<3, 2> expected{
    {2.0F, 2.5F},
    {4.0F, 5.0F},
    {6.0F, 7.5F},
  };
  EXPECT_EQ(m / 2.0F, expected);
}

TEST(MatrixTest, Scales3) {
  Matrix<2, 2> m{
    {-2.7F, 5.0F},
    {8.0F, 1.3F},
  };
  Matrix<2, 2> expected{
    {-5.4F, 10.0F},
    {24.0F, 3.9F},
  };
  EXPECT_EQ(m.scale({2.0F, 3.0F}), expected);
}

TEST(MatrixTest, Scales4) {
  Matrix<4> m{
    {1.0F, 1.0F, 1.0F, 1.0F},
    {1.0F, 1.0F, 1.0F, 1.0F},
    {1.0F, 1.0F, 1.0F, 1.0F},
    {1.0F, 1.0F, 1.0F, 1.0F},
  };
  Matrix<4> expected{
    {2.0F, 2.0F, 2.0F, 2.0F},
    {0.8F, 0.8F, 0.8F, 0.8F},
    {-1.0F, -1.0F, -1.0F, -1.0F},
    {1.0F, 1.0F, 1.0F, 1.0F},
  };
  EXPECT_EQ(m.scale(Vector<3>(2.0F, 0.8F, -1.0F)), expected);
}

TEST(MatrixTest, ConvertsTo2DArray1) {
  Matrix<3, 2> m{
    {2.0F, 2.5F},
    {4.0F, 5.0F},
    {6.0F, 7.5F},
  };
  std::array<std::array<float, 2>, 3> expected{
    {{2.0F, 2.5F},
     {4.0F, 5.0F},
     {6.0F, 7.5F}}};
  EXPECT_EQ((std::array<std::array<float, 2>, 3>) m, expected);
}

TEST(MatrixTest, ConvertsToJSON1) {
  Matrix<3, 2> m{
    {2.0F, 2.5F},
    {4.0F, 5.0F},
    {6.0F, 7.5F},
  };
  JSON json = {
    {2.0F, 2.5F},
    {4.0F, 5.0F},
    {6.0F, 7.5F},
  };
  EXPECT_EQ(m.to_json(), json);
}
