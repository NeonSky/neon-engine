#include "../util.hpp"

#include "../../engine/geometry/rotation.hpp"
using namespace engine::geometry;

TEST(RotationTest, Constructor1) {
  Rotation rotation(0.01F, pi / 2.0F, -3.0F * pi / 4.0F);

  EXPECT_EQ(rotation.pitch().radians(), 0.01F);
  EXPECT_EQ(rotation.yaw().radians(), pi / 2.0F);
  EXPECT_EQ(rotation.roll().radians(), -3.0F * pi / 4.0F);

  EXPECT_EQ(std::as_const(rotation).pitch().radians(), rotation.pitch().radians());
  EXPECT_EQ(std::as_const(rotation).yaw().radians(), rotation.yaw().radians());
  EXPECT_EQ(std::as_const(rotation).roll().radians(), rotation.roll().radians());
}

TEST(RotationTest, Constructor2) {
  Rotation rotation(0.01F, pi / 2.0F, -3.0F * pi / 4.0F);

  EXPECT_EQ(rotation.pitch().radians(), 0.01F);
  EXPECT_EQ(rotation.yaw().radians(), pi / 2.0F);
  EXPECT_EQ(rotation.roll().radians(), -3.0F * pi / 4.0F);

  EXPECT_EQ(std::as_const(rotation).pitch().radians(), rotation.pitch().radians());
  EXPECT_EQ(std::as_const(rotation).yaw().radians(), rotation.yaw().radians());
  EXPECT_EQ(std::as_const(rotation).roll().radians(), rotation.roll().radians());
}

TEST(RotationTest, RotationMatrix1) {
  Rotation r;
  EXPECT_EQ(r.matrix(), (Matrix<3>({
                          {1.0F, 0.0F, 0.0F},
                          {0.0F, 1.0F, 0.0F},
                          {0.0F, 0.0F, 1.0F},
                        })));
  EXPECT_EQ(r.matrix_slow(), r.matrix());
}

TEST(RotationTest, RotationMatrix2) {
  Rotation r(pi / 2.0F, 0.0F, 0.0F);
  EXPECT_EQ(r.matrix(), (Matrix<3>({
                          {+1.0F, +0.0F, +0.0F},
                          {+0.0F, +0.0F, +1.0F},
                          {+0.0F, -1.0F, +0.0F},
                        })));
  EXPECT_EQ(r.matrix_slow(), r.matrix());

  r.pitch() = Angle(pi);
  EXPECT_EQ(r.matrix(), (Matrix<3>({
                          {+1.0F, +0.0F, +0.0F},
                          {+0.0F, -1.0F, +0.0F},
                          {+0.0F, +0.0F, -1.0F},
                        })));
  EXPECT_EQ(r.matrix_slow(), r.matrix());
}

TEST(RotationTest, RotationMatrix3) {
  Rotation r(0.0F, pi / 2.0F, 0.0F);
  EXPECT_EQ(r.matrix(), (Matrix<3>({
                          {+0.0F, +0.0F, -1.0F},
                          {+0.0F, +1.0F, +0.0F},
                          {+1.0F, +0.0F, +0.0F},
                        })));
  EXPECT_EQ(r.matrix_slow(), r.matrix());

  r.yaw() = Angle(pi);
  EXPECT_EQ(r.matrix(), (Matrix<3>({
                          {-1.0F, +0.0F, +0.0F},
                          {+0.0F, +1.0F, +0.0F},
                          {+0.0F, +0.0F, -1.0F},
                        })));
  EXPECT_EQ(r.matrix_slow(), r.matrix());
}

TEST(RotationTest, RotationMatrix4) {
  Rotation r(0.0F, 0.0F, pi / 2.0F);
  EXPECT_EQ(r.matrix(), (Matrix<3>({
                          {+0.0F, +1.0F, +0.0F},
                          {-1.0F, +0.0F, +0.0F},
                          {+0.0F, +0.0F, +1.0F},
                        })));
  EXPECT_EQ(r.matrix_slow(), r.matrix());

  r.roll() = Angle(pi);
  EXPECT_EQ(r.matrix(), (Matrix<3>({
                          {-1.0F, +0.0F, +0.0F},
                          {+0.0F, -1.0F, +0.0F},
                          {+0.0F, +0.0F, +1.0F},
                        })));
  EXPECT_EQ(r.matrix_slow(), r.matrix());
}

TEST(RotationTest, RotationMatrix5) {
  Rotation r(0.0F, -pi / 2.0F, -pi / 2.0F);
  EXPECT_EQ(r.matrix(), (Matrix<3>({
                          {+0.0F, -1.0F, +0.0F},
                          {+0.0F, +0.0F, +1.0F},
                          {-1.0F, +0.0F, +0.0F},
                        })));
  EXPECT_EQ(r.matrix_slow(), r.matrix());
}

TEST(RotationTest, RotationMatrix6) {
  Rotation r(pi / 2.0F, pi, 2.0F * pi * 0.75F);
  EXPECT_EQ(r.matrix(), (Matrix<3>({
                          {+0.0F, +0.0F, -1.0F},
                          {-1.0F, +0.0F, +0.0F},
                          {+0.0F, +1.0F, +0.0F},
                        })));
  EXPECT_EQ(r.matrix_slow(), r.matrix());
}

TEST(RotationTest, ConvertsToJSON1) {
  Rotation rotation(0, -pi, pi);
  JSON json;
  json["roll"]  = rotation.roll().radians();
  json["pitch"] = rotation.pitch().radians();
  json["yaw"]   = rotation.yaw().radians();
  EXPECT_EQ(rotation.to_json(), json);

  json["debug"]["matrix"] = rotation.matrix().to_json();
  EXPECT_EQ(rotation.to_json(true), json);
}
