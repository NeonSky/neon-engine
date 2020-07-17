#include <gtest/gtest.h>

#include "../../engine/geometry/transform.hpp"
using namespace engine::geometry;

TEST(TransformTest, Constructor1) {
  Transform t;
  EXPECT_EQ(glm::vec3(0.0f), t.position);
}

TEST(TransformTest, Constructor2) {
  Transform t(glm::vec3(1.2f, 3.5f, -0.5f));
  EXPECT_EQ(glm::vec3(1.2f, 3.5f, -0.5f), t.position);
}

TEST(TransformTest, VectorBasis) {
  Transform t;
  EXPECT_EQ(glm::dot(t.forward(), t.up()), 0);
  EXPECT_EQ(glm::dot(t.forward(), t.right()), 0);
  EXPECT_EQ(glm::dot(t.up(), t.right()), 0);
}
