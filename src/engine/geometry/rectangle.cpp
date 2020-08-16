#include "rectangle.hpp"

#include <utility>

using namespace engine::geometry;

Rectangle::Rectangle()
        : Rectangle(Rigidbody()) {}

Rectangle::Rectangle(Rigidbody rigidbody, float width, float height)
        : _rigidbody(std::move(rigidbody)),
          _width(width),
          _height(height) {

  update_corners();
}

auto Rectangle::rigidbody() const -> const Rigidbody& { return _rigidbody; }
auto Rectangle::width() const -> float { return _width; }
auto Rectangle::height() const -> float { return _height; }

auto Rectangle::botleft() const -> Point<3> { return _botleft; }
auto Rectangle::botright() const -> Point<3> { return _botright; }
auto Rectangle::topleft() const -> Point<3> { return _topleft; }
auto Rectangle::topright() const -> Point<3> { return _topright; }

Rectangle::operator Plane() const {
  Plane plane;
  plane.point  = _botleft;
  plane.normal = _rigidbody.forward();
  return plane;
}

auto Rectangle::to_json(bool debug) const -> debug::JSON {
  debug::JSON json;
  json["rigidbody"] = _rigidbody.to_json(debug);
  json["width"]     = _width;
  json["height"]    = _height;

  if (debug) {
    json["debug"]["botleft"]  = botleft().to_json();
    json["debug"]["botright"] = botright().to_json();
    json["debug"]["topleft"]  = topleft().to_json();
    json["debug"]["topright"] = topright().to_json();
  }

  return json;
}

void Rectangle::update_corners() {
  Vector<3> xoffset = (_width / 2.0F) * Orientation::world_right;
  Vector<3> yoffset = (_height / 2.0F) * Orientation::world_up;

  _botleft  = (_rigidbody.matrix() * Vector<4>(+xoffset - yoffset, 1.0F)).tip();
  _botright = (_rigidbody.matrix() * Vector<4>(-xoffset - yoffset, 1.0F)).tip();
  _topleft  = (_rigidbody.matrix() * Vector<4>(+xoffset + yoffset, 1.0F)).tip();
  _topright = (_rigidbody.matrix() * Vector<4>(-xoffset + yoffset, 1.0F)).tip();
}
