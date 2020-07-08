#pragma once

#include <glm/vec3.hpp>

namespace engine::geometry {

  struct Ray {
    glm::vec3 origin;
    glm::vec3 direction;
  };

}
