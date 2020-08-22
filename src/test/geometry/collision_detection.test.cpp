#include "../util.hpp"

#include "../../engine/geometry/collision_detection.hpp"
using namespace engine::geometry;

TEST(CollisionDetectionTest, RayPlaneIntersection1) {
  Ray r;
  r.origin    = Point<3>();
  r.direction = UnitVector<3>(1.0F, 0.0F, 0.0F);

  Plane p;
  p.point  = Point<3>(0.0F, -1.0F, 0.0F);
  p.normal = UnitVector<3>(0.0F, 1.0F, 0.0F);

  auto res = ray_plane_intersection(r, p);
  EXPECT_EQ(res, std::nullopt);
}

TEST(CollisionDetectionTest, RayPlaneIntersection2) {
  Ray r;
  r.origin    = Point<3>();
  r.direction = UnitVector<3>(2.0F, -1.0F, 0.0F);

  Plane p;
  p.point  = Point<3>(0.0F, -1.0F, 0.0F);
  p.normal = UnitVector<3>(0.0F, 1.0F, 0.0F);

  auto res = ray_plane_intersection(r, p);
  EXPECT_EQ(*res, Point<3>(2.0F, -1.0F, 0.0F));
}

TEST(CollisionDetectionTest, RayRectangleIntersection1) {
  Ray r;
  r.origin    = Point<3>();
  r.direction = UnitVector<3>(1.0F, 0.0F, 0.0F);

  Rectangle rect(Rigidbody(Vector<3>(0.0F, -1.0F, 0.0F), Rotation(pi / 2.0F, 0.0F, 0.0F)), 0.5F, 2.0F);

  auto res = ray_rectangle_intersection(r, rect);
  EXPECT_EQ(res, std::nullopt);
}

TEST(CollisionDetectionTest, RayRectangleIntersection2) {
  Ray r;
  r.origin    = Point<3>();
  r.direction = UnitVector<3>(2.0F, -1.0F, 0.0F);

  Rectangle rect(Rigidbody(Vector<3>(0.0F, -1.0F, 0.0F), Rotation(pi / 2.0F, 0.0F, 0.0F)), 0.5F, 2.0F);

  auto res = ray_rectangle_intersection(r, rect);
  EXPECT_EQ(res, std::nullopt);
}

TEST(CollisionDetectionTest, RayRectangleIntersection3) {
  Ray r;
  r.origin    = Point<3>();
  r.direction = UnitVector<3>(0.0F, -1.0F, 2.0F);

  Rectangle rect(Rigidbody(Vector<3>(0.0F, -1.0F, 0.0F), Rotation(pi / 2.0F, 0.0F, 0.0F)), 0.5F, 4.0F);

  auto res = ray_rectangle_intersection(r, rect);
  EXPECT_EQ(*res, Point<3>(0.0F, -1.0F, 2.0F));
}

TEST(CollisionDetectionTest, RayRectangleIntersection4) {
  Ray r;
  r.origin    = Point<3>();
  r.direction = UnitVector<3>(0.0F, -1.0F, 2.1F);

  Rectangle rect(Rigidbody(Vector<3>(0.0F, -1.0F, 0.0F), Rotation(pi / 2.0F, 0.0F, 0.0F)), 0.5F, 4.0F);

  auto res = ray_rectangle_intersection(r, rect);
  EXPECT_EQ(res, std::nullopt);
}
