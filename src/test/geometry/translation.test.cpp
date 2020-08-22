#include "../util.hpp"

#include "../../engine/geometry/translation.hpp"
using namespace engine::geometry;

TEST(TranslationTest, Translates1) {
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
  EXPECT_EQ(translation_matrix(Vector<2>(2.0F, 0.0F)) * m, expected);
}

TEST(TranslationTest, Translates2) {
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
  EXPECT_EQ(translation_matrix(Vector<2>(2.0F, -1.2F)) * m, expected);
}

TEST(TranslationTest, Translates3) {
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
  EXPECT_EQ(translation_matrix(Vector<2>(-4.5F, 3.8F)) * m, expected);
}

TEST(TranslationTest, Translates4) {
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
  EXPECT_EQ(translation_matrix({-4.5F, 3.8F, 2.4F}) * m, expected);
}
