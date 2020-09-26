#include "context.hpp"
#include "opengl/context.hpp"

using namespace engine::graphics;

Context::Context()
        : _implementation(std::make_unique<opengl::Context>()) {}
