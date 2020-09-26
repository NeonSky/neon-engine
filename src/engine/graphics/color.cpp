#include "color.hpp"

using namespace engine::graphics;

Color::Color()
        : Color(0.0F, 0.0F, 0.0F, 1.0F) {}

Color::Color(float red, float green, float blue)
        : Color(red, green, blue, 1.0F) {}

Color::Color(float red, float green, float blue, float alpha)
        : _components{red, green, blue, alpha} {}

Color::Color(std::array<float, 3> components)
        : _components{components[0], components[1], components[2], 1.0F} {}

Color::Color(std::array<float, 4> components)
        : _components(components) {}

auto Color::operator==(const Color& other) const -> bool {
  return _components == other._components;
}

auto Color::operator!=(const Color& other) const -> bool {
  return !((*this) == other);
}

auto Color::begin() const -> const float* {
  return _components.begin();
}

auto Color::end() const -> const float* {
  return _components.end();
}

auto Color::red() const -> float {
  return _components[0];
}

auto Color::green() const -> float {
  return _components[1];
}

auto Color::blue() const -> float {
  return _components[2];
}

auto Color::alpha() const -> float {
  return _components[3];
}

auto Color::rgb() const -> std::array<float, 3> {
  return {_components[0], _components[1], _components[2]};
}
auto Color::rgba() const -> std::array<float, 4> {
  return _components;
}

auto Color::to_json() const -> debug::JSON {
  return _components;
}
