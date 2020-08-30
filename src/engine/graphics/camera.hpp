#pragma once

#include "../geometry/matrix.hpp"
#include "../geometry/rigidbody.hpp"

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
    explicit Camera(geometry::Rigidbody);

    // Mutators
    auto rigidbody() -> geometry::Rigidbody&;
    void move(Direction dir);
    void look_at(geometry::Vector<3> target);
    void lookat_mouse(float mouse_xpos, float mouse_ypos);
    void set_zoom(float zoom_level);

    // Accessors
    [[nodiscard]] auto view_matrix() const -> geometry::Matrix<4>;
    [[nodiscard]] auto projection_matrix(ProjectionType projection_type = ProjectionType::PERSPECTIVE) const -> geometry::Matrix<4>;

  private:
    struct Perspective {
      geometry::Angle fov;
      float aspect_ratio;
      float near;
      float far;

      Perspective() {
        fov          = geometry::Angle(45.0F, geometry::Angle::Unit::DEGREES);
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

    geometry::Rigidbody _rigidbody;
    Perspective _perspective;
    Orthographic _orthographic;
    float _movement_speed = 0.5F;
    float _rotation_speed = 0.1F;

    [[nodiscard]] auto perspective_projection_matrix() const -> geometry::Matrix<4>;
    [[nodiscard]] auto orthographic_projection_matrix() const -> geometry::Matrix<4>;
  };

};
