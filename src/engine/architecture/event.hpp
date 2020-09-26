#pragma once

#include "eventpp/callbacklist.h"

// THIS FILE IS NOT USED AT THE MOMENT
// Maybe just use a typedef/using statement?

#include <vector>

namespace engine::architecture {
  namespace event = eventpp;

  template <class F>
  class Event {

    void trigger() {
      for (auto& c : _callbacks)
        c();
    }

    void listen(std::function<F> callback) const {
      _callbacks.push_back(callback);
    }

  private:
    mutable std::vector<std::function<F>> _callbacks;
  };

}
