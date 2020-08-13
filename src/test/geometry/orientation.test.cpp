#include "../util.hpp"

#include "../../engine/geometry/orientation.hpp"
using namespace engine::geometry;

TEST(OrientationTest, Equality1) {
  Orientation orientation1(Rotation(0, pi / 2.0F, pi / 2.0F));
  Orientation orientation2(Rotation(pi / 2.0F, pi / 2.0F, 0));

  EXPECT_EQ(orientation1, orientation2);

  orientation2.rotation().yaw() = Angle(pi);
  EXPECT_NE(orientation1, orientation2);

  orientation2.rotation().yaw() = Angle(tau);
  EXPECT_NE(orientation1, orientation2);

  orientation2.rotation().yaw() = Angle(tau + pi / 2.0F);
  EXPECT_EQ(orientation1, orientation2);

  orientation2.rotation().yaw() = Angle(-tau + pi / 2.0F);
  EXPECT_EQ(orientation1, orientation2);
}

TEST(OrientationTest, VectorBasis1) {
  Orientation orientation;

  EXPECT_EQ(orientation.right().magnitude(), 1.0F);
  EXPECT_EQ(orientation.up().magnitude(), 1.0F);
  EXPECT_EQ(orientation.forward().magnitude(), 1.0F);

  EXPECT_EQ(orientation.forward().dot(orientation.up()), 0);
  EXPECT_EQ(orientation.forward().dot(orientation.right()), 0);
  EXPECT_EQ(orientation.up().dot(orientation.right()), 0);
}

TEST(OrientationTest, VectorBasis2) {
  Orientation orientation(Rotation(pi, 0.0F, 0.0F));

  EXPECT_EQ(orientation.right(), Vector<3>(1.0F, 0.0F, 0.0F));
  EXPECT_EQ(orientation.up(), Vector<3>(0.0F, -1.0F, 0.0F));
  EXPECT_EQ(orientation.forward(), Vector<3>(0.0F, 0.0F, -1.0F));
}

TEST(OrientationTest, VectorBasis3) {
  Orientation orientation(Rotation(pi / 2.0F, 0.0F, 0.0F));

  EXPECT_EQ(orientation.right(), Vector<3>(1.0F, 0.0F, 0.0F));
  EXPECT_EQ(orientation.up(), Vector<3>(0.0F, 0.0F, -1.0F));
  EXPECT_EQ(orientation.forward(), Vector<3>(0.0F, 1.0F, 0.0F));
}

TEST(OrientationTest, VectorBasis4) {
  Orientation orientation(Rotation(pi / 4.0F, 0.0F, 0.0F));

  EXPECT_EQ(orientation.right(), Vector<3>(1.0F, 0.0F, 0.0F));
  EXPECT_EQ(orientation.up(), Vector<3>(0.0F, sqrtf(0.5), -sqrtf(0.5)));
  EXPECT_EQ(orientation.forward(), Vector<3>(0.0F, sqrtf(0.5), sqrtf(0.5)));
}

TEST(OrientationTest, VectorBasis5) {
  Orientation orientation(Rotation(0.0F, pi / 2.0F, 0.0F));

  EXPECT_EQ(orientation.right(), Vector<3>(0.0F, 0.0F, 1.0F));
  EXPECT_EQ(orientation.up(), Vector<3>(0.0F, 1.0F, 0.0F));
  EXPECT_EQ(orientation.forward(), Vector<3>(-1.0F, 0.0F, 0.0F));
}

TEST(OrientationTest, VectorBasis6) {
  Orientation orientation(Rotation(0.0F, pi / 4.0F, 0.0F));

  EXPECT_EQ(orientation.right(), Vector<3>(sqrtf(0.5), 0.0F, sqrtf(0.5)));
  EXPECT_EQ(orientation.up(), Vector<3>(0.0F, 1.0F, 0.0F));
  EXPECT_EQ(orientation.forward(), Vector<3>(-sqrtf(0.5), 0.0F, sqrtf(0.5)));
}

TEST(OrientationTest, VectorBasis7) {
  Orientation orientation(Rotation(0.0F, 0.0F, pi / 2.0F));

  EXPECT_EQ(orientation.right(), Vector<3>(0.0F, -1.0F, 0.0F));
  EXPECT_EQ(orientation.up(), Vector<3>(1.0F, 0.0F, 0.0F));
  EXPECT_EQ(orientation.forward(), Vector<3>(0.0F, 0.0F, 1.0F));
}

TEST(OrientationTest, VectorBasis8) {
  Orientation orientation(Rotation(0.0F, 0.0F, pi / 4.0F));

  EXPECT_EQ(orientation.right(), Vector<3>(sqrtf(0.5), -sqrtf(0.5), 0.0F));
  EXPECT_EQ(orientation.up(), Vector<3>(sqrtf(0.5), sqrtf(0.5), 0.0F));
  EXPECT_EQ(orientation.forward(), Vector<3>(0.0F, 0.0F, 1.0F));
}

TEST(OrientationTest, VectorBasis9) {
  Orientation orientation(Rotation(pi / 2.0F, -pi / 2.0F, 0.0F));

  EXPECT_EQ(orientation.right(), Vector<3>(0.0F, 0.0F, -1.0F));
  EXPECT_EQ(orientation.up(), Vector<3>(-1.0F, 0.0F, 0.0F));
  EXPECT_EQ(orientation.forward(), Vector<3>(0.0F, 1.0F, 0.0F));
}

TEST(OrientationTest, VectorBasis10) {
  Orientation orientation(Rotation(pi / 2.0F, pi / 2.0F, pi / 2.0F));

  EXPECT_EQ(orientation.right(), Vector<3>(0.0F, 0.0F, 1.0F));
  EXPECT_EQ(orientation.up(), Vector<3>(0.0F, -1.0F, 0.0F));
  EXPECT_EQ(orientation.forward(), Vector<3>(1.0F, 0.0F, 0.0F));
}

TEST(OrientationTest, Flip1) {
  Orientation orientation;

  EXPECT_EQ(orientation.right(), Vector<3>(1.0F, 0.0F, 0.0F));
  EXPECT_EQ(orientation.up(), Vector<3>(0.0F, 1.0F, 0.0F));
  EXPECT_EQ(orientation.forward(), Vector<3>(0.0F, 0.0F, 1.0F));

  orientation.flip();

  EXPECT_EQ(orientation.right(), Vector<3>(-1.0F, 0.0F, 0.0F));
  EXPECT_EQ(orientation.up(), Vector<3>(0.0F, 1.0F, 0.0F));
  EXPECT_EQ(orientation.forward(), Vector<3>(0.0F, 0.0F, -1.0F));

  orientation.flip();

  EXPECT_EQ(orientation.right(), Vector<3>(1.0F, 0.0F, 0.0F));
  EXPECT_EQ(orientation.up(), Vector<3>(0.0F, 1.0F, 0.0F));
  EXPECT_EQ(orientation.forward(), Vector<3>(0.0F, 0.0F, 1.0F));
}

TEST(OrientationTest, Flip2) {
  Orientation orientation(Rotation(pi / 4.0F, 0.0F, 0.0F, Angle::Unit::RADIANS));

  EXPECT_EQ(orientation.right(), Vector<3>(1.0F, 0.0F, 0.0F));
  EXPECT_EQ(orientation.up(), Vector<3>(0.0F, sqrtf(0.5), -sqrtf(0.5)));
  EXPECT_EQ(orientation.forward(), Vector<3>(0.0F, sqrtf(0.5), sqrtf(0.5)));

  orientation.flip();

  EXPECT_EQ(orientation.right(), Vector<3>(-1.0F, 0.0F, 0.0F));
  EXPECT_EQ(orientation.up(), Vector<3>(0.0F, sqrtf(0.5), sqrtf(0.5)));
  EXPECT_EQ(orientation.forward(), Vector<3>(0.0F, sqrtf(0.5), -sqrtf(0.5)));

  orientation.flip();

  EXPECT_EQ(orientation.right(), Vector<3>(1.0F, 0.0F, 0.0F));
  EXPECT_EQ(orientation.up(), Vector<3>(0.0F, sqrtf(0.5), -sqrtf(0.5)));
  EXPECT_EQ(orientation.forward(), Vector<3>(0.0F, sqrtf(0.5), sqrtf(0.5)));
}

TEST(OrientationTest, Flip3) {
  Orientation orientation(Rotation(0.0F, pi / 2.0F, 0.0F, Angle::Unit::RADIANS));

  EXPECT_EQ(orientation.right(), Vector<3>(0.0F, 0.0F, 1.0F));
  EXPECT_EQ(orientation.up(), Vector<3>(0.0F, 1.0F, 0.0F));
  EXPECT_EQ(orientation.forward(), Vector<3>(-1.0F, 0.0F, 0.0F));

  orientation.flip();

  EXPECT_EQ(orientation.right(), Vector<3>(0.0F, 0.0F, -1.0F));
  EXPECT_EQ(orientation.up(), Vector<3>(0.0F, 1.0F, 0.0F));
  EXPECT_EQ(orientation.forward(), Vector<3>(1.0F, 0.0F, 0.0F));

  orientation.flip();

  EXPECT_EQ(orientation.right(), Vector<3>(0.0F, 0.0F, 1.0F));
  EXPECT_EQ(orientation.up(), Vector<3>(0.0F, 1.0F, 0.0F));
  EXPECT_EQ(orientation.forward(), Vector<3>(-1.0F, 0.0F, 0.0F));
}

TEST(OrientationTest, Flip4) {
  Orientation orientation(Rotation(45, 45, 0, Angle::Unit::DEGREES));

  // Since we x-axis rotation is applied first, the remaining vector magnitudes in the xz-plane
  // will be less for the up and forward vectors. The right vector remains unaffected.
  EXPECT_EQ(orientation.right(), Vector<3>(sqrt(1.0F / 2.0F), 0.0F, sqrt(1.0F / 2.0F)));
  EXPECT_EQ(orientation.up(), Vector<3>(cos(pi / 4) * sqrt(0.5F), sqrt(1.0F / 2.0F), -cos(pi / 4) * sqrt(0.5F)));
  EXPECT_EQ(orientation.forward(), Vector<3>(-cos(pi / 4) * sqrt(0.5F), sqrt(1.0F / 2.0F), cos(pi / 4) * sqrt(0.5F)));

  orientation.flip();

  EXPECT_EQ(orientation.right(), Vector<3>(-sqrt(1.0F / 2.0F), 0.0F, -sqrt(1.0F / 2.0F)));
  EXPECT_EQ(orientation.up(), Vector<3>(-cos(pi / 4) * sqrt(0.5F), sqrt(1.0F / 2.0F), cos(pi / 4) * sqrt(0.5F)));
  EXPECT_EQ(orientation.forward(), Vector<3>(cos(pi / 4) * sqrt(0.5F), sqrt(1.0F / 2.0F), -cos(pi / 4) * sqrt(0.5F)));

  orientation.flip();

  EXPECT_EQ(orientation.right(), Vector<3>(sqrt(1.0F / 2.0F), 0.0F, sqrt(1.0F / 2.0F)));
  EXPECT_EQ(orientation.up(), Vector<3>(cos(pi / 4) * sqrt(0.5F), sqrt(1.0F / 2.0F), -cos(pi / 4) * sqrt(0.5F)));
  EXPECT_EQ(orientation.forward(), Vector<3>(-cos(pi / 4) * sqrt(0.5F), sqrt(1.0F / 2.0F), cos(pi / 4) * sqrt(0.5F)));
}

TEST(OrientationTest, ConvertsToJSON1) {
  Orientation orientation(Rotation(0, -pi, pi, Angle::Unit::RADIANS));
  JSON json;
  json["rotation"] = orientation.rotation().to_json();
  EXPECT_EQ(orientation.to_json(), json);

  json["rotation"]         = orientation.rotation().to_json(true);
  json["debug"]["right"]   = orientation.right().to_json();
  json["debug"]["up"]      = orientation.up().to_json();
  json["debug"]["forward"] = orientation.forward().to_json();
  EXPECT_EQ(orientation.to_json(true), json);
}
