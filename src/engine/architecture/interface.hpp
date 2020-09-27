#pragma once

namespace engine::architecture {

  /// @brief Interface abstracts away the design of the interface pattern.
  // NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
  struct Interface {
    virtual ~Interface() = 0;
  };

}
