#pragma once

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "spdlog/spdlog.h"
#include <glad/glad.h>
#include <stdexcept>

#include <sstream>
#include <string>

#define LOG_TRACE(...) SPDLOG_TRACE(__VA_ARGS__)
#define LOG_DEBUG(...) SPDLOG_DEBUG(__VA_ARGS__)
#define LOG_INFO(...) SPDLOG_INFO(__VA_ARGS__)
#define LOG_WARNING(...) SPDLOG_WARN(__VA_ARGS__)
#define LOG_ERROR(...)                     \
  {                                        \
    SPDLOG_ERROR(__VA_ARGS__);             \
    throw std::runtime_error(__VA_ARGS__); \
  }
#define LOG_CRITICAL(...)                  \
  {                                        \
    SPDLOG_CRITICAL(__VA_ARGS__);          \
    throw std::runtime_error(__VA_ARGS__); \
  }

auto checkGLError(const char* file, int line) -> bool;

#define CHECK_GL_ERROR() \
  { checkGLError(__FILE__, __LINE__); }

inline auto ADDRESS(const void* ptr) -> std::string {
  std::stringstream ss;
  ss << ptr;
  return ss.str();
}

namespace engine::debug {

  class Logger {
  public:
    enum Profile {
      DEBUG,
      DEV,
      RELEASE,
    };

    // Mutators
    static void set_profile(Profile profile);

  private:
    static void apply_debug_profile();
    static void apply_dev_profile();
    static void apply_release_profile();
  };
}
