cmake_minimum_required(VERSION 3.17)

SET(CMAKE_TOOLCHAIN_FILE "/usr/share/vcpkg/scripts/buildsystems/vcpkg.cmake")
project(ECS_Scenes VERSION 1.0.0)

# Global options.
set(CMAKE_CXX_STANDARD 17)
set(OpenGL_GL_PREFERENCE "GLVND")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Global debug options.
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_MESSAGE_LOG_LEVEL "DEBUG")

# Load configuration cmake files from dependencies.
find_package(glfw3 3.3.2 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(spdlog 1.4.2 CONFIG REQUIRED)
find_package(nlohmann_json 3.7.3 CONFIG REQUIRED)
find_package(EnTT 3.4.0 CONFIG REQUIRED)
find_package(GTest 1.10.0 CONFIG REQUIRED)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost 1.72.0 REQUIRED COMPONENTS filesystem)

# Include local dependencies.
add_subdirectory("src/vendor")

# Configure executable.
file(GLOB_RECURSE src_files "src/engine/*.c" "src/engine/*.h" "src/engine/*.cpp" "src/engine/*.hpp")
add_library(Engine "${src_files}")
target_compile_options(Engine PUBLIC -Werror -Wall -Wextra)
file(COPY "res" DESTINATION ".")

# Code coverage
target_compile_options(Engine PUBLIC -fprofile-arcs -ftest-coverage)
target_link_libraries(Engine PUBLIC -lgcov)

# Link dependencies.
target_link_libraries(Engine PUBLIC glfw)
target_link_libraries(Engine PUBLIC eventpp)
target_link_libraries(Engine PUBLIC glad)
target_link_libraries(Engine PUBLIC imgui::imgui)
target_link_libraries(Engine PUBLIC imgui_glfw)
target_link_libraries(Engine PUBLIC spdlog::spdlog spdlog::spdlog_header_only)
target_link_libraries(Engine PUBLIC ssl)
target_link_libraries(Engine PUBLIC crypto)
target_link_libraries(Engine PUBLIC EnTT::EnTT)

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  target_link_libraries(Engine PUBLIC ${Boost_LIBRARIES})
endif()

# Application
file(GLOB_RECURSE src_files "src/app/*.c" "src/app/*.h" "src/app/*.cpp" "src/app/*.hpp")
add_executable(ECS_Scenes "${src_files}")
target_link_libraries(ECS_Scenes PRIVATE Engine)

# Engine Unit Tests
file(GLOB_RECURSE src_files "src/test/*.c" "src/test/*.h" "src/test/*.cpp" "src/test/*.hpp")
add_executable(ECS_Scenes_Test "${src_files}")
target_link_libraries(ECS_Scenes_Test PRIVATE Engine)
target_link_libraries(ECS_Scenes_Test PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

enable_testing()
add_test(EngineUnitTests ECS_Scenes_Test)
