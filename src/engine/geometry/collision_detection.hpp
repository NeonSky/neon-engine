#pragma once

#include "ray.hpp"
#include "plane.hpp"
#include "rectangle.hpp"

#include <glm/vec3.hpp>

namespace engine::geometry {

  class Intersection {
  public:
    Intersection(glm::vec3 point);
    glm::vec3 point;
  };

  // Accessors
  Intersection* ray_plane_intersection(Ray ray, engine::geometry::Plane plane);
  Intersection* ray_rectangle_intersection(Ray ray, Rectangle rectangle);

}
