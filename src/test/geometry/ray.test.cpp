#include <gtest/gtest.h>

#include "../../engine/geometry/ray.hpp"
using namespace engine::geometry;

TEST(RayTest, Constructor1) {
  Ray r;
  r.origin    = glm::vec3(0.0f);
  r.direction = glm::vec3(0.0f);

  EXPECT_EQ(glm::vec3(0.0f), r.origin);
  EXPECT_EQ(glm::vec3(0.0f), r.direction);
}
