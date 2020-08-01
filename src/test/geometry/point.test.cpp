#include "../util.hpp"

#include "../../engine/geometry/point.hpp"
using namespace engine::geometry;

TEST(PointTest, Size1) {
  Point<1> p1;
  Point<2> p2;
  Point<3> p3;
  Point<4> p4;

  EXPECT_EQ(sizeof(p1), 1 * sizeof(float));
  EXPECT_EQ(sizeof(p2), 2 * sizeof(float));
  EXPECT_EQ(sizeof(p3), 3 * sizeof(float));
  EXPECT_EQ(sizeof(p4), 4 * sizeof(float));
}

TEST(PointTest, ConstructsIdentityPoint1) {
  Point<1> point1;
  EXPECT_EQ(point1[0], 0.0F);

  Point<2> point2;
  EXPECT_EQ(point2[0], 0.0F);
  EXPECT_EQ(point2[1], 0.0F);

  Point<3> point3;
  EXPECT_EQ(point3[0], 0.0F);
  EXPECT_EQ(point3[1], 0.0F);
  EXPECT_EQ(point3[2], 0.0F);

  Point<4> point4;
  EXPECT_EQ(point4[0], 0.0F);
  EXPECT_EQ(point4[1], 0.0F);
  EXPECT_EQ(point4[2], 0.0F);
  EXPECT_EQ(point4[3], 0.0F);
}

TEST(PointTest, ConstructsSpecificPoint1) {
  Point<1> point1({1.4F});
  EXPECT_EQ(point1[0], 1.4F);

  Point<2> point2({3.8F, -2.1F});
  EXPECT_EQ(point2[0], 3.8F);
  EXPECT_EQ(point2[1], -2.1F);

  Point<3> point3({1.0F, 2.0F, 3.3F});
  EXPECT_EQ(point3[0], 1.0F);
  EXPECT_EQ(point3[1], 2.0F);
  EXPECT_EQ(point3[2], 3.3F);

  Point<4> point4({-0.5F, -2.4F, 88.3F, 12000.0F});
  EXPECT_EQ(point4[0], -0.5F);
  EXPECT_EQ(point4[1], -2.4F);
  EXPECT_EQ(point4[2], 88.3F);
  EXPECT_EQ(point4[3], 12000.0F);
}

TEST(PointTest, ComparesEquality1) {
  Point<3> point1({1.1F, -2.8F, 3.3F});
  Point<3> point2({1.1F, -2.8F, 3.3F});
  EXPECT_EQ(point1, point2);
}

TEST(PointTest, ComparesEquality2) {
  Point<3> point1({1.1F, -2.8F, 3.3F});
  Point<3> point2;
  EXPECT_NE(point1, point2);

  point1 = point2;
  EXPECT_EQ(point1, point2);
}

TEST(PointTest, ComparesEquality3) {
  Point<3> point1({1.1F, -2.8F, 3.3F});
  Point<3> point2({2.1F, -2.1F, 33.0F});
  EXPECT_NE(point1, point2);

  point2 = point1;
  EXPECT_EQ(point1, point2);
}

TEST(PointTest, ConvertsToLowerDimension1) {
  Point<2> point1({1.4F, 3.8F});
  Point<1> point2({1.4F});
  EXPECT_EQ((Point<1>) point1, point2);
}

TEST(PointTest, ConvertsToHigherDimension1) {
  Point<3> point1({1.4F, 3.8F, 0.0F});
  Point<2> point2({1.4F, 3.8F});
  EXPECT_EQ(point1, (Point<3>) point2);
}

TEST(PointTest, Iterates1) {
  Point<3> point({1.4F, 3.8F, 0.1F});

  int i = 0;
  for (auto& c : point)
    EXPECT_EQ(c, point[i++]);
  EXPECT_EQ(i, 3);
}

TEST(PointTest, Iterates2) {
  Point<3> point1({1.4F, 3.8F, 0.1F});
  Point<3> point2({2.4F, 4.8F, 1.1F});
  EXPECT_NE(point1, point2);

  for (auto& c : point1)
    c += 1.0F;
  EXPECT_EQ(point1, point2);
}

TEST(PointTest, Iterates3) {
  Point<3> point1({1.4F, 3.8F, 0.1F});
  Point<3> point2({2.4F, 4.8F, 1.1F});
  EXPECT_NE(point1, point2);

  for (auto it = point2.begin(); it != point2.end(); it++)
    (*it) -= 1.0F;

  EXPECT_EQ(point1, point2);
}

TEST(PointTest, Iterates4) {
  Point<4> point({1.4F, 3.8F, 0.1F, 33.22F});

  unsigned int i = 0;
  for (auto it = point.begin(); it != point.end(); it++)
    EXPECT_EQ((*it), point[i++]);
}

TEST(PointTest, Iterates5) {
  Point<4> point({1.4F, 3.8F, 0.1F, 33.22F});
  EXPECT_EQ((float*) point.begin(), &point[0]);
}

TEST(PointTest, ConvertsToJSON1) {
  Point<3> point({1.4F, 3.8F, 0.1F});
  JSON json = {1.4F, 3.8F, 0.1F};
  EXPECT_EQ(point.to_json(), json);
}
