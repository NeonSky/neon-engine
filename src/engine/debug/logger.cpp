#include "logger.hpp"

#include <string>

using namespace engine::debug;

void Logger::set_profile(Logger::Profile profile) {
  switch (profile) {
  case Profile::DEBUG:
    apply_debug_profile();
    break;
  case Profile::DEV:
    apply_dev_profile();
    break;
  case Profile::RELEASE:
    apply_release_profile();
    break;
  }
}

void Logger::apply_debug_profile() {
  spdlog::set_level(spdlog::level::debug);
}

void Logger::apply_dev_profile() {
  spdlog::set_level(spdlog::level::info);
}

void Logger::apply_release_profile() {
  spdlog::set_level(spdlog::level::err);
}
