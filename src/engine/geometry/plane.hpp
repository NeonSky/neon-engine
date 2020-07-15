#pragma once

#include "rectangle.hpp"

#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>

namespace engine::geometry {

  struct Plane {
    glm::vec3 point_on_plane;
    glm::vec3 normal;

    Plane() {
      this->point_on_plane = glm::vec3(0.0F);
      this->normal         = glm::vec3(0.0F, 1.0F, 0.0F);
    }

    Plane(Rectangle rectangle) {
      this->point_on_plane = rectangle.botleft();
      this->normal         = rectangle.transform().forward();
    }
  };

}
