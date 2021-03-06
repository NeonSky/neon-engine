#pragma once

#include "../context.hpp"

#include "../../../os/window.hpp"
#include "../../shader.hpp"

#include <map>

namespace engine::graphics::api::opengl {

  /// @brief Context represents a OpenGL context.
  ///
  /// In general, objects that hold data (textures, vertex/pixel/element objects, renderbuffer objects) are shared, while objects that hold state (vertex array object, framebuffer object) are not.
  ///
  /// @see https://www.khronos.org/opengl/wiki/OpenGL_Context
  /// @todo Separate vao and buffer into different classes/structs and bind them here. Vao could have references to its buffers and recompile automagically.
  /// @todo Add debug option which wraps everything around CHECK_GL_ERROR()
  class Context : public IContext {
  public:
    Context();

    /// @todo Support generating multiple vaos in one call
    auto gen_vao() -> unsigned int override;
    /// @todo Don't expose GLuint. Have them bind through us instead.
    auto vao(unsigned int id) -> GLuint override;
    auto is_vao(unsigned int id) -> bool override;

  private:
    static unsigned int _vao_count;
    static unsigned int _buffer_count;

    std::map<unsigned int, GLuint> _vao_db;
    std::map<unsigned int, GLuint> _buffer_db;
  };

}
