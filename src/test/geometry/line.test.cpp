#include "../util.hpp"

#include "../../engine/geometry/line.hpp"
using namespace engine::geometry;

TEST(LineTest, IntersectsWithPoint1) {
  Point<1> point({2});
  Line<1> line(Point<1>({0}), Point<1>({1}));

  EXPECT_TRUE(line.intersects(point));
}

TEST(LineTest, IntersectsWithPoint2) {
  Point<2> point1({2, 8});
  Point<2> point2({12, 3});
  Line<2> line(point1, point2);

  EXPECT_TRUE(line.intersects(point1));
  EXPECT_TRUE(line.intersects(point2));

  EXPECT_TRUE(line.intersects(Point<2>({4.0F, 7.0F})));
  EXPECT_TRUE(line.intersects(Point<2>({5.0F, 6.5F})));
  EXPECT_TRUE(line.intersects(Point<2>({8.0F, 5.0F})));

  EXPECT_FALSE(line.intersects(Point<2>()));
  EXPECT_FALSE(line.intersects(Point<2>({1.0F, 1.0F})));
  EXPECT_FALSE(line.intersects(Point<2>({0.0F, 1.0F})));
}

TEST(LineTest, IntersectsWithPoint3) {
  Point<3> point1({2, 8, 1});
  Point<3> point2({12, 3, 4});
  Line<3> line(point1, point2);
  EXPECT_TRUE(line.intersects(point1));
  EXPECT_TRUE(line.intersects(point2));

  EXPECT_FALSE(line.intersects(Point<3>()));
}
