#pragma once

#include "../geometry/transform.hpp"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace engine::graphics {

  // TODO: Move, remove or potentially change name. Maybe to player_camera
  enum Direction {
    FORWARD,
    BACKWARD,
    RIGHT,
    LEFT,
    UP,
    DOWN,
  };

  enum ProjectionType {
    PERSPECTIVE,
    ORTHOGRAPHIC,
  };

  class Camera {
  public:
    Camera();
    explicit Camera(const geometry::Transform&);
    ~Camera();

    geometry::Transform transform;

    // Mutators
    void move(Direction dir);
    void look_at(glm::vec3 target);
    void lookat_mouse(float mouse_xpos, float mouse_ypos);
    void set_zoom(float zoom_level);

    // Accessors
    [[nodiscard]] auto view_matrix() const -> glm::mat4;
    [[nodiscard]] auto projection_matrix(ProjectionType projection_type) const -> glm::mat4;

  private:
    struct Perspective {
      float fov;
      float aspect_ratio;
      float near;
      float far;

      Perspective() {
        fov          = 45.0F;
        aspect_ratio = 16.0F / 9.0F;
        near         = 0.1F;
        far          = 300.0F;
      }
    };

    struct Orthographic {
      float left;
      float right;
      float bot;
      float top;
      float near;
      float far;

      Orthographic() {
        left  = -1.0F;
        right = 1.0F;
        bot   = -1.0F;
        top   = 1.0F;
        near  = 0.1F;
        far   = 300.0F;
      }
    };

    Perspective perspective;
    Orthographic orthographic;
    float movement_speed = 0.5F;
    float rotation_speed = 0.1F;
  };

};
