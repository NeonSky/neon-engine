#include "../util.hpp"

#include "../../engine/geometry/vector.hpp"
using namespace engine::geometry;

TEST(VectorTest, Size1) {
  Vector<1> v1;
  Vector<2> v2;
  Vector<3> v3;
  Vector<4> v4;

  EXPECT_EQ(sizeof(v1), 1 * sizeof(float));
  EXPECT_EQ(sizeof(v2), 2 * sizeof(float));
  EXPECT_EQ(sizeof(v3), 3 * sizeof(float));
  EXPECT_EQ(sizeof(v4), 4 * sizeof(float));
}

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
  auto vector2 = v;
  EXPECT_EQ(v, vector2);
}

TEST(VectorTest, InnerProduct1) {
  Vector<2> vector1(1.0F, 2.0F);
  Vector<2> vector2(1.0F, 1.0F);
  EXPECT_EQ(vector1.inner_product(vector2), 3.0F);
}

TEST(VectorTest, InnerProduct2) {
  Vector<3> vector1(1.0F, 0.0F, 2.0F);
  Vector<3> vector2(1.0F, 1.0F, 1.5F);
  EXPECT_EQ(vector1.inner_product(vector2), 4.0F);
}

TEST(VectorTest, InnerProduct4) {
  Vector<4> vector1(1.0F, 0.0F, 2.0F, -4.0F);
  Vector<4> vector2(1.0F, 1.0F, 0.5F, 2.0F);
  EXPECT_EQ(vector1.inner_product(vector2), -6.0F);
}

// TEST(VectorTest, CrossProduct1) {
//   Vector<2> vector1(1.3F, -0.2F);
//   Vector<2> vector2 = cross_product(vector1);
//   EXPECT_EQ(vector1.inner_product(vector2), 0.0F);
// }

// TEST(VectorTest, CrossProduct2) {
//   Vector<3> vector1(1.0F, 0.0F, 0.0F);
//   Vector<3> vector2(0.0F, 1.0F, 0.0F);
//   EXPECT_EQ(cross_product(vector1, vector2), Vector<3>(0.0F, 0.0F, 1.0F));
// }

TEST(VectorTest, OuterProduct1) {
  Vector<2> vector1(1.0F, 2.0F);
  Vector<2> vector2(0.5F, 1.5F);
  std::array<std::array<float, 2>, 2> expected = {{
    {0.5F, 1.5F},
    {1.0F, 3.0F},
  }};
  EXPECT_EQ(vector1.outer_product(vector2), expected);
}

TEST(VectorTest, OuterProduct2) {
  Vector<3> vector1(1.0F, 2.0F, 3.0F);
  Vector<2> vector2(4.0F, 5.0F);
  std::array<std::array<float, 2>, 3> expected = {{
    {4.0F, 5.0F},
    {8.0F, 10.0F},
    {12.0F, 15.0F},
  }};
  EXPECT_EQ(vector1.outer_product(vector2), expected);
}

TEST(VectorTest, Iterates1) {
  Vector<3> vector({1.4F, 3.8F, 0.1F});

  int i = 0;
  for (auto& e : vector)
    EXPECT_EQ(e, vector[i++]);
  EXPECT_EQ(i, 3);
}

TEST(VectorTest, Aliases1) {
  Vector<1> vector;
  vector[0] = 1.4F;

  EXPECT_EQ(vector.x(), vector[0]);
  EXPECT_EQ(vector.r(), vector[0]);
  EXPECT_EQ(vector.s(), vector[0]);
}

TEST(VectorTest, Aliases2) {
  Vector<2> vector;
  vector[0] = 1.4F;
  vector[1] = 3.8F;

  EXPECT_EQ(vector.x(), vector[0]);
  EXPECT_EQ(vector.y(), vector[1]);

  EXPECT_EQ(vector.r(), vector[0]);
  EXPECT_EQ(vector.g(), vector[1]);

  EXPECT_EQ(vector.s(), vector[0]);
  EXPECT_EQ(vector.t(), vector[1]);
}

TEST(VectorTest, Aliases3) {
  Vector<3> vector;
  vector[0] = 1.4F;
  vector[1] = 3.8F;
  vector[2] = -13.8F;

  EXPECT_EQ(vector.x(), vector[0]);
  EXPECT_EQ(vector.y(), vector[1]);
  EXPECT_EQ(vector.z(), vector[2]);

  EXPECT_EQ(vector.r(), vector[0]);
  EXPECT_EQ(vector.g(), vector[1]);
  EXPECT_EQ(vector.b(), vector[2]);

  EXPECT_EQ(vector.s(), vector[0]);
  EXPECT_EQ(vector.t(), vector[1]);
  EXPECT_EQ(vector.p(), vector[2]);
}

TEST(VectorTest, Aliases4) {
  Vector<4> vector;
  vector[0] = 1.4F;
  vector[1] = 3.8F;
  vector[2] = -13.8F;
  vector[3] = -5.2F;

  EXPECT_EQ(vector.x(), vector[0]);
  EXPECT_EQ(vector.y(), vector[1]);
  EXPECT_EQ(vector.z(), vector[2]);
  EXPECT_EQ(vector.w(), vector[3]);

  EXPECT_EQ(vector.r(), vector[0]);
  EXPECT_EQ(vector.g(), vector[1]);
  EXPECT_EQ(vector.b(), vector[2]);
  EXPECT_EQ(vector.a(), vector[3]);

  EXPECT_EQ(vector.s(), vector[0]);
  EXPECT_EQ(vector.t(), vector[1]);
  EXPECT_EQ(vector.p(), vector[2]);
  EXPECT_EQ(vector.q(), vector[3]);
}
