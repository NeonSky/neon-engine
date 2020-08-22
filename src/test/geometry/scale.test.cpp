#include "../util.hpp"

#include "../../engine/geometry/scale.hpp"
using namespace engine::geometry;

TEST(ScaleTest, Scales1) {
  Matrix<2, 2> m{
    {-2.7F, 5.0F},
    {8.0F, 1.3F},
  };
  Matrix<2, 2> expected{
    {-5.4F, 10.0F},
    {24.0F, 3.9F},
  };
  EXPECT_EQ(scale_matrix(Vector<2>(2.0F, 3.0F)) * m, expected);
}

TEST(ScaleTest, Scales2) {
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
  EXPECT_EQ(Matrix<4>(scale_matrix({2.0F, 0.8F, -1.0F})) * m, expected);
}
