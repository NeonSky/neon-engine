#pragma once

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <functional>
#include <glm/vec4.hpp>
#include <vector>

namespace engine::gui {

  class Window {
  public:
    Window();
    Window(unsigned int width, unsigned int height, const char* title);
    ~Window();

    // Mutators
    void init_gui();
    void update();
    void clear_screen() const;
    void add_on_key_callback(const std::function<void(GLFWwindow*, int)>& callback);
    void add_on_mouse_click_callback(const std::function<void(GLFWwindow*, int, int)>& callback);
    void add_on_mouse_move_callback(const std::function<void(GLFWwindow*, float, float)>& callback);
    void add_on_mouse_scroll_callback(const std::function<void(GLFWwindow*, float, float)>& callback);

    // Accessors
    [[nodiscard]] auto is_closing() const -> bool;
    [[nodiscard]] auto width() const -> unsigned int;
    [[nodiscard]] auto height() const -> unsigned int;

  private:
    GLFWwindow* window;
    unsigned int _width;
    unsigned int _height;
    glm::vec4 _clear_color;

    std::vector<std::function<void(GLFWwindow*, int)>> on_key_callbacks;
    std::vector<std::function<void(GLFWwindow*, int, int)>> on_mouse_click_callbacks;
    std::vector<std::function<void(GLFWwindow*, float, float)>> on_mouse_move_callbacks;
    std::vector<std::function<void(GLFWwindow*, float, float)>> on_mouse_scroll_callbacks;
  };

}
