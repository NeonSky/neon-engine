#pragma once

#include <chrono>
#include <functional>
#include <vector>

namespace engine::time {
  class UpdateScheduler {
  public:
    struct Schedule {
      std::function<void(float)> func;
      std::chrono::nanoseconds target_dt = std::chrono::seconds(1);
      bool fixed_dt                      = false;
    };

    /// The functions will be updated in order of the vector.
    UpdateScheduler(std::vector<Schedule> schedules);

    /// Will run until \p b is false.
    void run(const bool& b);

  private:
    std::vector<Schedule> _schedules;
    std::vector<std::chrono::nanoseconds> _accumulators;
    std::vector<unsigned int> _ticks;
  };
};
