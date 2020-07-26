#pragma once

#include "angle.hpp"
#include "matrix.hpp"
#include "vector.hpp"

namespace engine::geometry {

  class Transform {
  public:
    Transform();
    Transform(const Vector<3>& position);
    Transform(const Vector<3>& position, const Vector<3>& rotation);
    Transform(Vector<3> position, Vector<3> rotation, Vector<3> scale);

    // Mutators
    void set_rotation(float yaw, float pitch, float roll);
    void flip_rotation();

    // Accessors
    static const Vector<4> world_right;
    static const Vector<4> world_up;
    static const Vector<4> world_forward;

    auto operator+(const Transform& other) const -> Transform;

    [[nodiscard]] auto matrix() const -> Matrix<4>;
    [[nodiscard]] auto forward() const -> Vector<3>;
    [[nodiscard]] auto up() const -> Vector<3>;
    [[nodiscard]] auto right() const -> Vector<3>;

    [[nodiscard]] auto yaw() const -> float;
    [[nodiscard]] auto pitch() const -> float;
    [[nodiscard]] auto roll() const -> float;

    Vector<3> position;
    Vector<3> rotation;
    Vector<3> scale;

  private:
    // Accessors
    [[nodiscard]] auto rotation_matrix() const -> Matrix<4>;
    [[nodiscard]] auto rotation_matrix_slow() const -> Matrix<4>;
  };
}
