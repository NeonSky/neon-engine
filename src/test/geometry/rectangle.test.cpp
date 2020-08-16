#include "../util.hpp"

#include "../../engine/geometry/rectangle.hpp"
using namespace engine::geometry;

TEST(RectangleTest, Constructor1) {
  Rectangle r;

  EXPECT_EQ(r.rigidbody(), Rigidbody());
  EXPECT_EQ(r.width(), 1.0F);
  EXPECT_EQ(r.height(), 1.0F);

  EXPECT_EQ(r.botleft(), Point<3>(0.5F, -0.5F, 0.0F));
  EXPECT_EQ(r.botright(), Point<3>(-0.5F, -0.5F, 0.0F));
  EXPECT_EQ(r.topleft(), Point<3>(0.5F, 0.5F, 0.0F));
  EXPECT_EQ(r.topright(), Point<3>(-0.5F, 0.5F, 0.0F));
}

TEST(RectangleTest, Constructor2) {
  Rigidbody rig = Rigidbody(Vector<3>(1, 2, 3), Rotation());
  Rectangle r(rig);

  EXPECT_EQ(r.rigidbody(), rig);
  EXPECT_EQ(r.width(), 1.0F);
  EXPECT_EQ(r.height(), 1.0F);

  EXPECT_EQ(r.botleft(), Point<3>(1.5F, 1.5F, 3.0F));
  EXPECT_EQ(r.botright(), Point<3>(0.5F, 1.5F, 3.0F));
  EXPECT_EQ(r.topleft(), Point<3>(1.5F, 2.5F, 3.0F));
  EXPECT_EQ(r.topright(), Point<3>(0.5F, 2.5F, 3.0F));
}

TEST(RectangleTest, Constructor3) {
  Rigidbody rig = Rigidbody(Vector<3>(), Rotation(0, pi / 2.0F, 0));
  Rectangle r(rig, 2.0F, 0.5F);

  EXPECT_EQ(r.rigidbody(), rig);
  EXPECT_EQ(r.width(), 2.0F);
  EXPECT_EQ(r.height(), 0.5F);

  EXPECT_EQ(r.botleft(), Point<3>(0.0F, -0.25F, 1.0F));
  EXPECT_EQ(r.botright(), Point<3>(0.0F, -0.25F, -1.0F));
  EXPECT_EQ(r.topleft(), Point<3>(0.0F, 0.25F, 1.0F));
  EXPECT_EQ(r.topright(), Point<3>(0.0F, 0.25F, -1.0F));
}

TEST(RectangleTest, Constructor4) {
  Rigidbody rig = Rigidbody(Vector<3>(3, 2, 1), Rotation(0, pi / 2.0F, 0));
  Rectangle r(rig, 2.0F, 0.5F);

  EXPECT_EQ(r.rigidbody(), rig);
  EXPECT_EQ(r.width(), 2.0F);
  EXPECT_EQ(r.height(), 0.5F);

  EXPECT_EQ(r.botleft(), Point<3>(3.0F, 1.75F, 2.0F));
  EXPECT_EQ(r.botright(), Point<3>(3.0F, 1.75F, 0.0F));
  EXPECT_EQ(r.topleft(), Point<3>(3.0F, 2.25F, 2.0F));
  EXPECT_EQ(r.topright(), Point<3>(3.0F, 2.25F, 0.0F));
}

TEST(RectangleTest, ConvertsToPlane1) {
  Rectangle r;
  Plane p = r;

  EXPECT_EQ((Vector<3>) p.normal, r.rigidbody().forward());
  EXPECT_EQ(p.point, r.botleft());
}

TEST(RectangleTest, ConvertsToJSON1) {
  Rectangle r(Rigidbody(Vector<3>(1, 2, 3), Rotation(0, -pi, pi)));
  JSON json;
  json["rigidbody"] = r.rigidbody().to_json();
  json["width"]     = r.width();
  json["height"]    = r.height();
  EXPECT_EQ(r.to_json(), json);

  json["rigidbody"]         = r.rigidbody().to_json(true);
  json["debug"]["botleft"]  = r.botleft().to_json();
  json["debug"]["botright"] = r.botright().to_json();
  json["debug"]["topleft"]  = r.topleft().to_json();
  json["debug"]["topright"] = r.topright().to_json();
  EXPECT_EQ(r.to_json(true), json);
}
