#pragma once

#include "../debug/json.hpp"
#include "vector.hpp"

#include "glm/gtx/string_cast.hpp"

namespace engine::geometry {

  struct Ray {
    Vector<3> origin;
    Vector<3> direction; // TODO: Use a UnitVector<3> here instead.

    [[nodiscard]] auto to_json() const -> debug::JSON {
      return {
        {"origin", origin.to_json()},
        {"direction", direction.to_json()}};
    };
  };

}
