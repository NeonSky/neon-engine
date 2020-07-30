#include "../util.hpp"

#include "../../engine/geometry/angle.hpp"
using namespace engine::geometry;

TEST(AngleTest, ConstructsIdentityAngle1) {
  Angle angle;
  EXPECT_EQ(angle.turns(), 0.0F);
  EXPECT_EQ(angle.radians(), 0.0F);
  EXPECT_EQ(angle.degrees(), 0.0F);
  EXPECT_EQ(angle.gradians(), 0.0F);
}

TEST(AngleTest, ConstructsIdentityAngle2) {
  Angle angle(0.0F, Angle::Unit::TURNS);
  EXPECT_EQ(angle.turns(), 0.0F);
  EXPECT_EQ(angle.radians(), 0.0F);
  EXPECT_EQ(angle.degrees(), 0.0F);
  EXPECT_EQ(angle.gradians(), 0.0F);
}

TEST(AngleTest, ConstructsIdentityAngle3) {
  Angle angle(0.0F, Angle::Unit::RADIANS);
  EXPECT_EQ(angle.turns(), 0.0F);
  EXPECT_EQ(angle.radians(), 0.0F);
  EXPECT_EQ(angle.degrees(), 0.0F);
  EXPECT_EQ(angle.gradians(), 0.0F);
}

TEST(AngleTest, ConstructsIdentityAngle4) {
  Angle angle(0.0F, Angle::Unit::DEGREES);
  EXPECT_EQ(angle.turns(), 0.0F);
  EXPECT_EQ(angle.radians(), 0.0F);
  EXPECT_EQ(angle.degrees(), 0.0F);
  EXPECT_EQ(angle.gradians(), 0.0F);
}

TEST(AngleTest, ConstructsIdentityAngle5) {
  Angle angle(0.0F, Angle::Unit::GRADIANS);
  EXPECT_EQ(angle.turns(), 0.0F);
  EXPECT_EQ(angle.radians(), 0.0F);
  EXPECT_EQ(angle.degrees(), 0.0F);
  EXPECT_EQ(angle.gradians(), 0.0F);
}

TEST(AngleTest, ConstructsSpecificAngleWithTurns1) {
  Angle angle(0.5F, Angle::Unit::TURNS);
  EXPECT_EQ(angle.turns(), 0.5F);
  EXPECT_EQ(angle.radians(), pi);
  EXPECT_EQ(angle.degrees(), 180.0F);
  EXPECT_EQ(angle.gradians(), 200.0F);
}

TEST(AngleTest, ConstructsSpecificAngleWithRadians1) {
  Angle angle(1.5F * pi, Angle::Unit::RADIANS);
  EXPECT_EQ(angle.turns(), 0.75F);
  EXPECT_EQ(angle.radians(), 1.5F * pi);
  EXPECT_EQ(angle.degrees(), 270.0F);
  EXPECT_EQ(angle.gradians(), 300.0F);
}

TEST(AngleTest, ConstructsSpecificAngleWithDegrees1) {
  Angle angle(-90.0F, Angle::Unit::DEGREES);
  EXPECT_EQ(angle.turns(), -0.25F);
  EXPECT_EQ(angle.radians(), -phi);
  EXPECT_EQ(angle.degrees(), -90.0F);
  EXPECT_EQ(angle.gradians(), -100.0F);
}

TEST(AngleTest, ConstructsSpecificAngleWithGradians1) {
  Angle angle(-400, Angle::Unit::GRADIANS);
  EXPECT_EQ(angle.turns(), -1.0F);
  EXPECT_EQ(angle.radians(), -tau);
  EXPECT_EQ(angle.degrees(), -360.0F);
  EXPECT_EQ(angle.gradians(), -400.0F);
}

TEST(AngleTest, ReassignsWithDifferentUnits1) {
  Angle angle;

  angle.set(-15.0F, Angle::Unit::DEGREES);
  EXPECT_EQ(angle.degrees(), -15.0F);

  angle.set(5.3F, Angle::Unit::TURNS);
  EXPECT_EQ(angle.turns(), 5.3F);

  angle.set(-7.2F, Angle::Unit::RADIANS);
  EXPECT_EQ(angle.radians(), -7.2F);

  angle.set(1080.0F, Angle::Unit::GRADIANS);
  EXPECT_EQ(angle.gradians(), 1080.0F);
}
