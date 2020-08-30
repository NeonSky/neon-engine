#pragma once

#include "../../os/window.hpp"
#include "../shader.hpp"

#include <map>

namespace engine::graphics::opengl {

  /// Context represents a OpenGL context.
  ///
  /// In general, objects that hold data (textures, vertex/pixel/element objects, renderbuffer objects) are shared, while objects that hold state (vertex array object, framebuffer object) are not.
  ///
  /// @see https://www.khronos.org/opengl/wiki/OpenGL_Context
  /// @todo Separate vao and buffer into different classes/structs and bind them here. Vao could have references to its buffers and recompile automagically.
  /// @todo Add debug option which wraps everything around CHECK_GL_ERROR()
  class Context {
  public:
    Context();

    /// @todo Support generating multiple vaos in one call
    auto gen_vao() -> unsigned int;
    /// @todo Don't expose GLuint. Have them bind through us instead.
    auto vao(unsigned int id) -> GLuint;
    auto is_vao(unsigned int id) -> bool;

    // TODO: change implementation. Buffers are shared between contexts.
    auto gen_buffer() -> unsigned int;
    auto buffer(unsigned int id) -> GLuint;

  private:
    static unsigned int _vao_count;
    static unsigned int _buffer_count;

    std::map<unsigned int, GLuint> _vao_db;
    std::map<unsigned int, GLuint> _buffer_db;
  };

}
