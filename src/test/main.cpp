#include "../engine/debug/logger.hpp"
#include <gtest/gtest.h>

int main(int argc, char** argv) {
  engine::debug::Logger::set_profile(engine::debug::Logger::Profile::DEBUG);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
