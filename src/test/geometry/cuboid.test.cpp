#include "../util.hpp"

#include "../../engine/geometry/cuboid.hpp"
using namespace engine::geometry;

TEST(CuboidTest, Faces1) {
  Cuboid c;

  EXPECT_EQ(c.left_face().botright(), Point<3>(-0.5F, -0.5F, -0.5F));
  EXPECT_EQ(c.bottom_face().botright(), Point<3>(-0.5F, -0.5F, -0.5F));
  EXPECT_EQ(c.back_face().botleft(), Point<3>(-0.5F, -0.5F, -0.5F));

  EXPECT_EQ(c.right_face().botleft(), Point<3>(0.5F, -0.5F, -0.5F));
  EXPECT_EQ(c.bottom_face().botleft(), Point<3>(0.5F, -0.5F, -0.5F));
  EXPECT_EQ(c.back_face().botright(), Point<3>(0.5F, -0.5F, -0.5F));

  EXPECT_EQ(c.left_face().topright(), Point<3>(-0.5F, 0.5F, -0.5F));
  EXPECT_EQ(c.top_face().topright(), Point<3>(-0.5F, 0.5F, -0.5F));
  EXPECT_EQ(c.back_face().topleft(), Point<3>(-0.5F, 0.5F, -0.5F));

  EXPECT_EQ(c.right_face().topleft(), Point<3>(0.5F, 0.5F, -0.5F));
  EXPECT_EQ(c.top_face().topleft(), Point<3>(0.5F, 0.5F, -0.5F));
  EXPECT_EQ(c.back_face().topright(), Point<3>(0.5F, 0.5F, -0.5F));

  EXPECT_EQ(c.left_face().botleft(), Point<3>(-0.5F, -0.5F, 0.5F));
  EXPECT_EQ(c.bottom_face().topright(), Point<3>(-0.5F, -0.5F, 0.5F));
  EXPECT_EQ(c.front_face().botright(), Point<3>(-0.5F, -0.5F, 0.5F));

  EXPECT_EQ(c.right_face().botright(), Point<3>(0.5F, -0.5F, 0.5F));
  EXPECT_EQ(c.bottom_face().topleft(), Point<3>(0.5F, -0.5F, 0.5F));
  EXPECT_EQ(c.front_face().botleft(), Point<3>(0.5F, -0.5F, 0.5F));

  EXPECT_EQ(c.left_face().topleft(), Point<3>(-0.5F, 0.5F, 0.5F));
  EXPECT_EQ(c.top_face().botright(), Point<3>(-0.5F, 0.5F, 0.5F));
  EXPECT_EQ(c.front_face().topright(), Point<3>(-0.5F, 0.5F, 0.5F));

  EXPECT_EQ(c.right_face().topright(), Point<3>(0.5F, 0.5F, 0.5F));
  EXPECT_EQ(c.top_face().botleft(), Point<3>(0.5F, 0.5F, 0.5F));
  EXPECT_EQ(c.front_face().topleft(), Point<3>(0.5F, 0.5F, 0.5F));
}

TEST(CuboidTest, Faces2) {
  Cuboid c;
  c.transform().scale() = Vector<3>(2.0F, 3.0F, 4.0F);

  EXPECT_EQ(c.left_face().botright(), Point<3>(-1.0F, -1.5F, -2.0F));
  EXPECT_EQ(c.bottom_face().botright(), Point<3>(-1.0F, -1.5F, -2.0F));
  EXPECT_EQ(c.back_face().botleft(), Point<3>(-1.0F, -1.5F, -2.0F));

  EXPECT_EQ(c.right_face().botleft(), Point<3>(1.0F, -1.5F, -2.0F));
  EXPECT_EQ(c.bottom_face().botleft(), Point<3>(1.0F, -1.5F, -2.0F));
  EXPECT_EQ(c.back_face().botright(), Point<3>(1.0F, -1.5F, -2.0F));

  EXPECT_EQ(c.left_face().topright(), Point<3>(-1.0F, 1.5F, -2.0F));
  EXPECT_EQ(c.top_face().topright(), Point<3>(-1.0F, 1.5F, -2.0F));
  EXPECT_EQ(c.back_face().topleft(), Point<3>(-1.0F, 1.5F, -2.0F));

  EXPECT_EQ(c.right_face().topleft(), Point<3>(1.0F, 1.5F, -2.0F));
  EXPECT_EQ(c.top_face().topleft(), Point<3>(1.0F, 1.5F, -2.0F));
  EXPECT_EQ(c.back_face().topright(), Point<3>(1.0F, 1.5F, -2.0F));

  EXPECT_EQ(c.left_face().botleft(), Point<3>(-1.0F, -1.5F, 2.0F));
  EXPECT_EQ(c.bottom_face().topright(), Point<3>(-1.0F, -1.5F, 2.0F));
  EXPECT_EQ(c.front_face().botright(), Point<3>(-1.0F, -1.5F, 2.0F));

  EXPECT_EQ(c.right_face().botright(), Point<3>(1.0F, -1.5F, 2.0F));
  EXPECT_EQ(c.bottom_face().topleft(), Point<3>(1.0F, -1.5F, 2.0F));
  EXPECT_EQ(c.front_face().botleft(), Point<3>(1.0F, -1.5F, 2.0F));

  EXPECT_EQ(c.left_face().topleft(), Point<3>(-1.0F, 1.5F, 2.0F));
  EXPECT_EQ(c.top_face().botright(), Point<3>(-1.0F, 1.5F, 2.0F));
  EXPECT_EQ(c.front_face().topright(), Point<3>(-1.0F, 1.5F, 2.0F));

  EXPECT_EQ(c.right_face().topright(), Point<3>(1.0F, 1.5F, 2.0F));
  EXPECT_EQ(c.top_face().botleft(), Point<3>(1.0F, 1.5F, 2.0F));
  EXPECT_EQ(c.front_face().topleft(), Point<3>(1.0F, 1.5F, 2.0F));
}

TEST(CuboidTest, Faces3) {
  Cuboid c;
  c.transform().orientation().rotation().pitch() = Angle(pi / 2.0F);

  EXPECT_EQ(c.left_face().botright(), Point<3>(-0.5F, -0.5F, 0.5F));
  EXPECT_EQ(c.bottom_face().botright(), Point<3>(-0.5F, -0.5F, 0.5F));
  EXPECT_EQ(c.back_face().botleft(), Point<3>(-0.5F, -0.5F, 0.5F));

  EXPECT_EQ(c.right_face().botleft(), Point<3>(0.5F, -0.5F, 0.5F));
  EXPECT_EQ(c.bottom_face().botleft(), Point<3>(0.5F, -0.5F, 0.5F));
  EXPECT_EQ(c.back_face().botright(), Point<3>(0.5F, -0.5F, 0.5F));

  EXPECT_EQ(c.left_face().topright(), Point<3>(-0.5F, -0.5F, -0.5F));
  EXPECT_EQ(c.top_face().topright(), Point<3>(-0.5F, -0.5F, -0.5F));
  EXPECT_EQ(c.back_face().topleft(), Point<3>(-0.5F, -0.5F, -0.5F));

  EXPECT_EQ(c.right_face().topleft(), Point<3>(0.5F, -0.5F, -0.5F));
  EXPECT_EQ(c.top_face().topleft(), Point<3>(0.5F, -0.5F, -0.5F));
  EXPECT_EQ(c.back_face().topright(), Point<3>(0.5F, -0.5F, -0.5F));

  EXPECT_EQ(c.left_face().botleft(), Point<3>(-0.5F, 0.5F, 0.5F));
  EXPECT_EQ(c.bottom_face().topright(), Point<3>(-0.5F, 0.5F, 0.5F));
  EXPECT_EQ(c.front_face().botright(), Point<3>(-0.5F, 0.5F, 0.5F));

  EXPECT_EQ(c.right_face().botright(), Point<3>(0.5F, 0.5F, 0.5F));
  EXPECT_EQ(c.bottom_face().topleft(), Point<3>(0.5F, 0.5F, 0.5F));
  EXPECT_EQ(c.front_face().botleft(), Point<3>(0.5F, 0.5F, 0.5F));

  EXPECT_EQ(c.left_face().topleft(), Point<3>(-0.5F, 0.5F, -0.5F));
  EXPECT_EQ(c.top_face().botright(), Point<3>(-0.5F, 0.5F, -0.5F));
  EXPECT_EQ(c.front_face().topright(), Point<3>(-0.5F, 0.5F, -0.5F));

  EXPECT_EQ(c.right_face().topright(), Point<3>(0.5F, 0.5F, -0.5F));
  EXPECT_EQ(c.top_face().botleft(), Point<3>(0.5F, 0.5F, -0.5F));
  EXPECT_EQ(c.front_face().topleft(), Point<3>(0.5F, 0.5F, -0.5F));
}

TEST(CuboidTest, Faces4) {
  Cuboid c;
  c.transform().orientation().rotation().yaw() = Angle(pi / 2.0F);

  EXPECT_EQ(c.left_face().botright(), Point<3>(0.5F, -0.5F, -0.5F));
  EXPECT_EQ(c.bottom_face().botright(), Point<3>(0.5F, -0.5F, -0.5F));
  EXPECT_EQ(c.back_face().botleft(), Point<3>(0.5F, -0.5F, -0.5F));

  EXPECT_EQ(c.right_face().botleft(), Point<3>(0.5F, -0.5F, 0.5F));
  EXPECT_EQ(c.bottom_face().botleft(), Point<3>(0.5F, -0.5F, 0.5F));
  EXPECT_EQ(c.back_face().botright(), Point<3>(0.5F, -0.5F, 0.5F));

  EXPECT_EQ(c.left_face().topright(), Point<3>(0.5F, 0.5F, -0.5F));
  EXPECT_EQ(c.top_face().topright(), Point<3>(0.5F, 0.5F, -0.5F));
  EXPECT_EQ(c.back_face().topleft(), Point<3>(0.5F, 0.5F, -0.5F));

  EXPECT_EQ(c.right_face().topleft(), Point<3>(0.5F, 0.5F, 0.5F));
  EXPECT_EQ(c.top_face().topleft(), Point<3>(0.5F, 0.5F, 0.5F));
  EXPECT_EQ(c.back_face().topright(), Point<3>(0.5F, 0.5F, 0.5F));

  EXPECT_EQ(c.left_face().botleft(), Point<3>(-0.5F, -0.5F, -0.5F));
  EXPECT_EQ(c.bottom_face().topright(), Point<3>(-0.5F, -0.5F, -0.5F));
  EXPECT_EQ(c.front_face().botright(), Point<3>(-0.5F, -0.5F, -0.5F));

  EXPECT_EQ(c.right_face().botright(), Point<3>(-0.5F, -0.5F, 0.5F));
  EXPECT_EQ(c.bottom_face().topleft(), Point<3>(-0.5F, -0.5F, 0.5F));
  EXPECT_EQ(c.front_face().botleft(), Point<3>(-0.5F, -0.5F, 0.5F));

  EXPECT_EQ(c.left_face().topleft(), Point<3>(-0.5F, 0.5F, -0.5F));
  EXPECT_EQ(c.top_face().botright(), Point<3>(-0.5F, 0.5F, -0.5F));
  EXPECT_EQ(c.front_face().topright(), Point<3>(-0.5F, 0.5F, -0.5F));

  EXPECT_EQ(c.right_face().topright(), Point<3>(-0.5F, 0.5F, 0.5F));
  EXPECT_EQ(c.top_face().botleft(), Point<3>(-0.5F, 0.5F, 0.5F));
  EXPECT_EQ(c.front_face().topleft(), Point<3>(-0.5F, 0.5F, 0.5F));
}

TEST(CuboidTest, Faces5) {
  Cuboid c;
  c.transform().orientation().rotation().roll() = Angle(pi / 2.0F);

  EXPECT_EQ(c.left_face().botright(), Point<3>(-0.5F, 0.5F, -0.5F));
  EXPECT_EQ(c.bottom_face().botright(), Point<3>(-0.5F, 0.5F, -0.5F));
  EXPECT_EQ(c.back_face().botleft(), Point<3>(-0.5F, 0.5F, -0.5F));

  EXPECT_EQ(c.right_face().botleft(), Point<3>(-0.5F, -0.5F, -0.5F));
  EXPECT_EQ(c.bottom_face().botleft(), Point<3>(-0.5F, -0.5F, -0.5F));
  EXPECT_EQ(c.back_face().botright(), Point<3>(-0.5F, -0.5F, -0.5F));

  EXPECT_EQ(c.left_face().topright(), Point<3>(0.5F, 0.5F, -0.5F));
  EXPECT_EQ(c.top_face().topright(), Point<3>(0.5F, 0.5F, -0.5F));
  EXPECT_EQ(c.back_face().topleft(), Point<3>(0.5F, 0.5F, -0.5F));

  EXPECT_EQ(c.right_face().topleft(), Point<3>(0.5F, -0.5F, -0.5F));
  EXPECT_EQ(c.top_face().topleft(), Point<3>(0.5F, -0.5F, -0.5F));
  EXPECT_EQ(c.back_face().topright(), Point<3>(0.5F, -0.5F, -0.5F));

  EXPECT_EQ(c.left_face().botleft(), Point<3>(-0.5F, 0.5F, 0.5F));
  EXPECT_EQ(c.bottom_face().topright(), Point<3>(-0.5F, 0.5F, 0.5F));
  EXPECT_EQ(c.front_face().botright(), Point<3>(-0.5F, 0.5F, 0.5F));

  EXPECT_EQ(c.right_face().botright(), Point<3>(-0.5F, -0.5F, 0.5F));
  EXPECT_EQ(c.bottom_face().topleft(), Point<3>(-0.5F, -0.5F, 0.5F));
  EXPECT_EQ(c.front_face().botleft(), Point<3>(-0.5F, -0.5F, 0.5F));

  EXPECT_EQ(c.left_face().topleft(), Point<3>(0.5F, 0.5F, 0.5F));
  EXPECT_EQ(c.top_face().botright(), Point<3>(0.5F, 0.5F, 0.5F));
  EXPECT_EQ(c.front_face().topright(), Point<3>(0.5F, 0.5F, 0.5F));

  EXPECT_EQ(c.right_face().topright(), Point<3>(0.5F, -0.5F, 0.5F));
  EXPECT_EQ(c.top_face().botleft(), Point<3>(0.5F, -0.5F, 0.5F));
  EXPECT_EQ(c.front_face().topleft(), Point<3>(0.5F, -0.5F, 0.5F));
}
