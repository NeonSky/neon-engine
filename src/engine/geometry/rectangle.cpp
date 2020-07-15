#include "rectangle.hpp"

using namespace engine::geometry;

Rectangle::Rectangle() : Rectangle(Transform()) {}
Rectangle::Rectangle(const Transform& transform, float width, float height)
        : _transform(transform),
          _width(width),
          _height(height) {
  update_corners();
}

// Accessors
auto Rectangle::transform() const -> Transform { return this->_transform; }
auto Rectangle::width() const -> float { return this->_width; }
auto Rectangle::height() const -> float { return this->_height; }

auto Rectangle::topleft() const -> glm::vec3 { return this->_topleft; }
auto Rectangle::topright() const -> glm::vec3 { return this->_topright; }
auto Rectangle::botleft() const -> glm::vec3 { return this->_botleft; }
auto Rectangle::botright() const -> glm::vec3 { return this->_botright; }

// Mutators
void Rectangle::update_corners() {
  glm::vec3 xoffset = (this->_width / 2.0F) * Transform::world_right;
  glm::vec3 yoffset = (this->_height / 2.0F) * Transform::world_up;

  this->_topleft  = this->_transform.matrix() * glm::vec4(+xoffset + yoffset, 1.0F);
  this->_topright = this->_transform.matrix() * glm::vec4(-xoffset + yoffset, 1.0F);
  this->_botleft  = this->_transform.matrix() * glm::vec4(+xoffset - yoffset, 1.0F);
  this->_botright = this->_transform.matrix() * glm::vec4(-xoffset - yoffset, 1.0F);
}
