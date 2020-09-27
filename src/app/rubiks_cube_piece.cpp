#include "rubiks_cube_piece.hpp"

#include "../engine/graphics/component/cuboid.hpp"
#include "../engine/graphics/component/rectangle.hpp"

#include <utility>

using namespace engine;
using namespace app;

RubiksCubePiece::RubiksCubePiece(engine::scene::Node& node,
                                 geometry::Transform transform,
                                 ColorConfiguration color_config)
        : _transform(std::move(transform)) {

  node.add_component<graphics::component::Cuboid>(geometry::Cuboid(), graphics::Color());

  geometry::Vector<3> scale = _transform.scale();
  float offset              = 1.005F;

  struct FaceData {
    geometry::Vector<3> pos;
    geometry::Rotation rot;
    float width  = 0.0F;
    float height = 0.0F;
    engine::graphics::Color color;
  };
  std::vector<FaceData> face_data;

  if (color_config.left != graphics::Color()) {
    FaceData face;
    face.pos    = offset * geometry::Vector<3>(-scale.x() / 2.0F, 0, 0);
    face.rot    = geometry::Rotation(0, geometry::pi / 2.0F, 0);
    face.width  = scale.z();
    face.height = scale.y();
    face.color  = color_config.left;
    face_data.push_back(face);
  }

  if (color_config.right != graphics::Color()) {
    FaceData face;
    face.pos    = offset * geometry::Vector<3>(scale.x() / 2.0F, 0, 0);
    face.rot    = geometry::Rotation(0, -geometry::pi / 2.0F, 0);
    face.width  = scale.z();
    face.height = scale.y();
    face.color  = color_config.right;
    face_data.push_back(face);
  }

  if (color_config.bot != graphics::Color()) {
    FaceData face;
    face.pos    = offset * geometry::Vector<3>(0, -scale.y() / 2.0F, 0);
    face.rot    = geometry::Rotation(-geometry::pi / 2.0F, 0, 0);
    face.width  = scale.x();
    face.height = scale.z();
    face.color  = color_config.bot;
    face_data.push_back(face);
  }

  if (color_config.top != graphics::Color()) {
    FaceData face;
    face.pos    = offset * geometry::Vector<3>(0, scale.y() / 2.0F, 0);
    face.rot    = geometry::Rotation(geometry::pi / 2.0F, 0, 0);
    face.width  = scale.x();
    face.height = scale.z();
    face.color  = color_config.top;
    face_data.push_back(face);
  }

  if (color_config.back != graphics::Color()) {
    FaceData face;
    face.pos    = offset * geometry::Vector<3>(0, 0, -scale.z() / 2.0F);
    face.rot    = geometry::Rotation(0, geometry::pi, 0);
    face.width  = scale.x();
    face.height = scale.y();
    face.color  = color_config.back;
    face_data.push_back(face);
  }

  if (color_config.front != graphics::Color()) {
    FaceData face;
    face.pos    = offset * geometry::Vector<3>(0, 0, scale.z() / 2.0F);
    face.rot    = geometry::Rotation();
    face.width  = scale.x();
    face.height = scale.y();
    face.color  = color_config.front;
    face_data.push_back(face);
  }

  float face_ratio = 0.9F;
  for (auto& face : face_data) {
    auto& n = node.add_child();
    n.add_component<graphics::component::Rectangle>(geometry::Rectangle(geometry::Rigidbody(), face_ratio * face.width, face_ratio * face.height), face.color);
    n.add_component<geometry::Transform>(face.pos, face.rot);
  }
}

auto RubiksCubePiece::transform() -> engine::geometry::Transform& {
  return _transform;
}
