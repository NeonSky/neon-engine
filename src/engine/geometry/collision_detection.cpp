#include "collision_detection.hpp"

#include "plane.hpp"
#include "rectangle.hpp"
#include <utility>

using namespace engine::geometry;

Intersection::Intersection(Vector<3> point)
        : point(point) {}

auto engine::geometry::ray_plane_intersection(const Ray& ray, const Plane& plane) -> std::unique_ptr<Intersection> {
  Vector<3> from   = ray.origin;
  Vector<3> dir    = ray.direction;
  Vector<3> normal = plane.normal;

  if (normal.inner_product(dir) == 0)
    return nullptr;

  float d0      = -normal.inner_product(plane.point_on_plane);
  float t       = -(normal.inner_product(from) + d0) / normal.inner_product(dir);
  Vector<3> hit = from + dir * t;

  return std::make_unique<Intersection>(hit);
}

auto engine::geometry::ray_rectangle_intersection(const Ray& ray, const Rectangle& rectangle) -> std::unique_ptr<Intersection> {
  std::unique_ptr<Intersection> hit = ray_plane_intersection(ray, Plane(rectangle));
  if (hit == nullptr)
    return nullptr;

  Vector<3> topleft  = rectangle.topleft();
  Vector<3> botleft  = rectangle.botleft();
  Vector<3> botright = rectangle.botright();

  Vector<3> OA = topleft - botleft;
  Vector<3> OB = botright - botleft;

  bool check1 = botleft.inner_product(OA) < hit->point.inner_product(OA) && hit->point.inner_product(OA) < topleft.inner_product(OA);
  bool check2 = botleft.inner_product(OB) < hit->point.inner_product(OB) && hit->point.inner_product(OB) < botright.inner_product(OB);

  return (check1 && check2) ? std::move(hit) : nullptr;
}
