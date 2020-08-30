#include "update_scheduler.hpp"

#include <utility>

#include "../debug/logger.hpp"

using namespace engine::time;

UpdateScheduler::UpdateScheduler(std::vector<Schedule> schedules)
        : _schedules(std::move(schedules)) {

  _accumulators.resize(_schedules.size());
  _ticks.resize(_schedules.size());
}

/// @see https://gafferongames.com/post/fix_your_timestep/
void UpdateScheduler::run(const bool& b) {
  auto time_before_update = std::chrono::system_clock::now();
  auto prev_log           = std::chrono::system_clock::now();

  while (b) {

    // NOTE: delta time (dt) in this case refers to time since last update.
    auto dt = std::chrono::system_clock::now() - time_before_update;

    time_before_update = std::chrono::system_clock::now();

    for (unsigned int i = 0; i < _schedules.size(); i++) {
      _accumulators[i] += dt;

      float dt_in_seconds = _schedules[i].fixed_dt
                              ? std::chrono::duration<float>((_schedules[i].target_dt)).count()
                              : std::chrono::duration<float>((dt)).count();

      while (_accumulators[i] > _schedules[i].target_dt) {
        if (_schedules[i].fixed_dt)
          _accumulators[i] -= _schedules[i].target_dt;
        else
          _accumulators[i] = std::chrono::nanoseconds::zero();

        _schedules[i].func(dt_in_seconds);
        _ticks[i]++;
      }
    }

    if (std::chrono::system_clock::now() - prev_log > std::chrono::seconds(1)) {
      LOG_DEBUG("Scheduler");
      for (auto& _tick : _ticks) {
        LOG_DEBUG(_tick);
        _tick = 0;
      }
      prev_log = std::chrono::system_clock::now();
    }
  }
}
