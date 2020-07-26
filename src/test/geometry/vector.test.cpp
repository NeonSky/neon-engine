#include "../../engine/debug/logger.hpp"
#include <gtest/gtest.h>

#include "../../engine/geometry/vector.hpp"
using namespace engine::geometry;

TEST(VectorTest, Constructor1) {
  Vector<2> v;
  EXPECT_EQ(v[0], 0.0F);
  EXPECT_EQ(v[1], 0.0F);
}

TEST(VectorTest, Constructor2) {
  Vector<3> v(3.4F, 0.5F, -40.2F);
  EXPECT_EQ(v[0], 3.4F);
  EXPECT_EQ(v[1], 0.5F);
  EXPECT_EQ(v[2], -40.2F);
}

TEST(VectorTest, Constructor3) {
  Vector<4> v(3.4F, -0.2F, -40.2F, 2.3F);
  auto v2 = v;
  EXPECT_EQ(v, v2);
}

TEST(VectorTest, InnerProduct1) {
  Vector<2> v1(1.0F, 2.0F);
  Vector<2> v2(1.0F, 1.0F);
  EXPECT_EQ(v1.inner_product(v2), 3.0F);
}

TEST(VectorTest, InnerProduct2) {
  Vector<3> v1(1.0F, 0.0F, 2.0F);
  Vector<3> v2(1.0F, 1.0F, 1.5F);
  EXPECT_EQ(v1.inner_product(v2), 4.0F);
}

TEST(VectorTest, InnerProduct4) {
  Vector<4> v1(1.0F, 0.0F, 2.0F, -4.0F);
  Vector<4> v2(1.0F, 1.0F, 0.5F, 2.0F);
  EXPECT_EQ(v1.inner_product(v2), -6.0F);
}

// TEST(VectorTest, CrossProduct1) {
//   Vector<2> v1(1.3F, -0.2F);
//   Vector<2> v2 = cross_product(v1);
//   EXPECT_EQ(v1.inner_product(v2), 0.0F);
// }

// TEST(VectorTest, CrossProduct3) {
//   Vector<3> v1(1.0F, 0.0F, 0.0F);
//   Vector<3> v2(0.0F, 1.0F, 0.0F);
//   EXPECT_EQ(cross_product(v1, v2), Vector<3>(0.0F, 0.0F, 1.0F));
// }

TEST(VectorTest, OuterProduct1) {
  Vector<2> v1(1.0F, 2.0F);
  Vector<2> v2(0.5F, 1.5F);
  std::array<std::array<float, 2>, 2> expected = {{
    {0.5F, 1.5F},
    {1.0F, 3.0F},
  }};
  EXPECT_EQ(v1.outer_product(v2), expected);
}

TEST(VectorTest, OuterProduct2) {
  Vector<3> v1(1.0F, 2.0F, 3.0F);
  Vector<2> v2(4.0F, 5.0F);
  std::array<std::array<float, 2>, 3> expected = {{
    {4.0F, 5.0F},
    {8.0F, 10.0F},
    {12.0F, 15.0F},
  }};
  EXPECT_EQ(v1.outer_product(v2), expected);
}
