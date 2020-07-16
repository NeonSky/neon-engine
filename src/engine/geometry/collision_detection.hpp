#pragma once

#include "plane.hpp"
#include "ray.hpp"
#include "rectangle.hpp"

#include <glm/vec3.hpp>

#include <memory>

namespace engine::geometry {

  class Intersection {
  public:
    glm::vec3 point;

    Intersection(glm::vec3 point);
  };

  // Accessors
  auto ray_plane_intersection(Ray ray, engine::geometry::Plane plane) -> std::unique_ptr<Intersection>;
  auto ray_rectangle_intersection(Ray ray, const Rectangle& rectangle) -> std::unique_ptr<Intersection>;

}
