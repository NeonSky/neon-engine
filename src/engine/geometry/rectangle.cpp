#include "rectangle.hpp"

#include <utility>

#include "matrix.hpp"
#include "orientation.hpp"

using namespace engine::geometry;

Rectangle::Rectangle()
        : Rectangle(Transform()) {}

Rectangle::Rectangle(Transform transform, float width, float height)
        : _transform(transform),
          _width(width),
          _height(height) {

  update_corners();
}

// Accessors
auto Rectangle::transform() const -> Transform { return _transform; }
auto Rectangle::width() const -> float { return _width; }
auto Rectangle::height() const -> float { return _height; }

auto Rectangle::botleft() const -> Vector<3> { return _botleft; }
auto Rectangle::botright() const -> Vector<3> { return _botright; }
auto Rectangle::topleft() const -> Vector<3> { return _topleft; }
auto Rectangle::topright() const -> Vector<3> { return _topright; }

auto Rectangle::to_json() const -> debug::JSON {
  debug::JSON json;
  json["botleft"]  = botleft().to_json();
  json["botright"] = botright().to_json();
  json["topleft"]  = topleft().to_json();
  json["topright"] = topright().to_json();
  return json;
}

// Mutators
void Rectangle::update_corners() {
  Vector<3> xoffset = (_width / 2.0F) * Orientation::world_right;
  Vector<3> yoffset = (_height / 2.0F) * Orientation::world_up;

  _botleft  = _transform.matrix() * Vector<4>(+xoffset - yoffset, 1.0F);
  _botright = _transform.matrix() * Vector<4>(-xoffset - yoffset, 1.0F);
  _topleft  = _transform.matrix() * Vector<4>(+xoffset + yoffset, 1.0F);
  _topright = _transform.matrix() * Vector<4>(-xoffset + yoffset, 1.0F);
}
