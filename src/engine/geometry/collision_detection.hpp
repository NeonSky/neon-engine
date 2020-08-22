#pragma once

#include "plane.hpp"
#include "ray.hpp"
#include "rectangle.hpp"
#include "vector.hpp"

#include <optional>

namespace engine::geometry {

  /// @brief Finds the intersection point between ray \p ray and plane \p plane, if any.
  auto ray_plane_intersection(const Ray& ray, const engine::geometry::Plane& plane) -> std::optional<Point<3>>;

  /// @brief Finds the intersection point between ray \p ray and rectangle \p rectangle, if any.
  auto ray_rectangle_intersection(const Ray& ray, const Rectangle& rectangle) -> std::optional<Point<3>>;

}
