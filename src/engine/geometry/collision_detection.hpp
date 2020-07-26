#pragma once

#include "plane.hpp"
#include "ray.hpp"
#include "rectangle.hpp"
#include "vector.hpp"

#include <memory>

namespace engine::geometry {

  class Intersection {
  public:
    Vector<3> point;

    Intersection(Vector<3> point);
  };

  // Accessors
  auto ray_plane_intersection(const Ray& ray, const engine::geometry::Plane& plane) -> std::unique_ptr<Intersection>;
  auto ray_rectangle_intersection(const Ray& ray, const Rectangle& rectangle) -> std::unique_ptr<Intersection>;

}
