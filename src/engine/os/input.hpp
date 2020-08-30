#pragma once

namespace engine::os {

  using KeyCode = int;

  enum class KeyAction {
    PRESS,
    REPEAT,
    RELEASE
  };

  using MouseCode = int;

  enum class MouseAction {
    PRESS,
    RELEASE
  };

  struct ActivatedModifiers {
    bool shift     = false;
    bool control   = false;
    bool alt       = false;
    bool super     = false;
    bool caps_lock = false;
    bool num_lock  = false;
  };

}
