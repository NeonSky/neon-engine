#pragma once

#include "../architecture/interface.hpp"

#include <string>

namespace engine::os {

  struct IWindow : public architecture::Interface {
    [[nodiscard]] virtual auto title() const -> std::string   = 0;
    [[nodiscard]] virtual auto is_closing() const -> bool     = 0;
    [[nodiscard]] virtual auto width() const -> unsigned int  = 0;
    [[nodiscard]] virtual auto height() const -> unsigned int = 0;
  };

}
