#include "collision_detection.hpp"

#include "plane.hpp"
#include "rectangle.hpp"
#include <utility>

using namespace engine::geometry;

auto engine::geometry::ray_plane_intersection(const Ray& ray, const Plane& plane) -> std::optional<Point<3>> {
  Vector<3> from   = ray.origin;
  Vector<3> dir    = ray.direction;
  Vector<3> normal = plane.normal;

  if (normal.inner_product(dir) == 0)
    return {};

  float d0      = -normal.inner_product(Vector<3>(plane.point));
  float t       = -(normal.inner_product(from) + d0) / normal.inner_product(dir);
  Vector<3> hit = from + dir * t;

  return hit.tip();
}

auto engine::geometry::ray_rectangle_intersection(const Ray& ray, const Rectangle& rectangle) -> std::optional<Point<3>> {
  std::optional<Point<3>> maybe_hit = ray_plane_intersection(ray, (Plane) rectangle);
  if (!maybe_hit)
    return {};

  Vector<3> hit = *maybe_hit;

  Vector<3> topleft  = rectangle.topleft();
  Vector<3> botleft  = rectangle.botleft();
  Vector<3> botright = rectangle.botright();

  Vector<3> OA = topleft - botleft;
  Vector<3> OB = botright - botleft;

  bool check1 = botleft.inner_product(OA) < hit.inner_product(OA) && hit.inner_product(OA) < topleft.inner_product(OA);
  bool check2 = botleft.inner_product(OB) < hit.inner_product(OB) && hit.inner_product(OB) < botright.inner_product(OB);

  return (check1 && check2) ? std::make_optional(hit.tip()) : std::nullopt;
}
