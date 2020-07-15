#pragma once

#include "ray.hpp"
#include "plane.hpp"
#include "rectangle.hpp"

#include <glm/vec3.hpp>

namespace engine::geometry {

  class Intersection {
  public:
    glm::vec3 point;

    Intersection(glm::vec3 point);
  };

  // Accessors
  auto ray_plane_intersection(Ray ray, engine::geometry::Plane plane) -> Intersection*;
  auto ray_rectangle_intersection(Ray ray, Rectangle rectangle) -> Intersection*;

}
