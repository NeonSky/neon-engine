#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace engine::geometry {

  class Transform {
  public:
    Transform();
    Transform(glm::vec3 position);
    Transform(glm::vec3 position, glm::vec3 rotation);
    Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    ~Transform();

    // Mutators
    void set_rotation(float yaw, float pitch, float roll);
    void flip_rotation();

    // Accessors
    static constexpr glm::vec4 world_right   = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
    static constexpr glm::vec4 world_up      = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
    static constexpr glm::vec4 world_forward = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);

    auto operator+(const Transform& other) const -> Transform;

    [[nodiscard]] auto matrix() const -> glm::mat4;
    [[nodiscard]] auto forward() const -> glm::vec3;
    [[nodiscard]] auto up() const -> glm::vec3;
    [[nodiscard]] auto right() const -> glm::vec3;

    [[nodiscard]] auto yaw() const -> float { return rotation.y; };
    [[nodiscard]] auto pitch() const -> float { return rotation.x; };
    [[nodiscard]] auto roll() const -> float { return rotation.z; };

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

  private:
    // Accessors
    [[nodiscard]] auto rotation_matrix() const -> glm::mat4;
  };
}
