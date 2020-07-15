#include <gtest/gtest.h>

#include "../../engine/geometry/vector.hpp"
using namespace engine::geometry;

TEST(VectorTest, Constructor1) {
  Vector2 p1(0.0f);
  Vector2 p2(0.0f);
  EXPECT_EQ(p1, p2);
  EXPECT_EQ(p1, -p2);
}

TEST(VectorTest, Constructor2) {
  Vector3 p1(3.4f, -0.2f, -40.2f);
  Vector3 p2(3.4f, -0.2f, -40.2f);
  EXPECT_EQ(p1, p2);
  EXPECT_NE(p1, -p2);
}

TEST(VectorTest, Constructor3) {
  Vector4 p1 = Vector4(3.4f, -0.2f, -40.2f, 2.3f);
  Vector4 p2 = Vector4(3.4f, -0.2f, -40.2f, 2.3f);
  EXPECT_EQ(p1, p2);
  EXPECT_NE(p1, -p2);
}
