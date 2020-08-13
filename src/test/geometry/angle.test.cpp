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

TEST(AngleTest, Equality1) {
  Angle angle1(1.5F);
  Angle angle2(1.5F);
  Angle angle3(0.5F);

  EXPECT_EQ(angle1, angle2);
  EXPECT_NE(angle1, angle3);
  EXPECT_NE(angle2, angle3);
}

TEST(AngleTest, Adds1) {
  EXPECT_EQ(Angle(1.5F * pi) + Angle(0.5F * pi), Angle(tau));
  EXPECT_EQ(Angle(1.5F * pi) + Angle(-0.5F * pi), Angle(pi));
}

TEST(AngleTest, Subtracts1) {
  EXPECT_EQ(Angle(1.5F * pi) - Angle(0.5F * pi), Angle(pi));
  EXPECT_EQ(Angle(1.5F * pi) - Angle(-0.5F * pi), Angle(tau));
}

TEST(AngleTest, Scales1) {
  EXPECT_EQ(Angle(pi) * 1.5F, Angle(pi * 1.5F));
  EXPECT_EQ(Angle(-pi) * 0.5F, Angle(-pi * 0.5F));
  EXPECT_EQ(Angle(pi) / 1.5F, Angle(pi / 1.5F));
  EXPECT_EQ(Angle(-pi) / 0.5F, Angle(-pi / 0.5F));
}

TEST(AngleTest, Modulo1) {
  EXPECT_EQ(Angle(0).modulo(), Angle(0));
  EXPECT_EQ(Angle(pi).modulo(), Angle(pi));
  EXPECT_EQ(Angle(tau).modulo(), Angle(0));
  EXPECT_EQ(Angle(tau + pi).modulo(), Angle(pi));
  EXPECT_EQ(Angle(2.0F * tau).modulo(), Angle(0.0F));
  EXPECT_EQ(Angle(2.0F * tau + pi).modulo(), Angle(pi));
}

TEST(AngleTest, Modulo2) {
  EXPECT_EQ(Angle(0).modulo(), Angle(0));
  EXPECT_EQ(Angle(-pi).modulo(), Angle(pi));
  EXPECT_EQ(Angle(-tau).modulo(), Angle(0));
  EXPECT_EQ(Angle(-tau - pi).modulo(), Angle(pi));
  EXPECT_EQ(Angle(-2.0F * tau).modulo(), Angle(0.0F));
  EXPECT_EQ(Angle(-2.0F * tau - pi).modulo(), Angle(pi));
}

TEST(AngleTest, Modulo3) {
  EXPECT_EQ(Angle(-90, Angle::Unit::DEGREES).modulo(Angle(pi)), Angle(90, Angle::Unit::DEGREES));
  EXPECT_EQ(Angle(-45, Angle::Unit::DEGREES).modulo(Angle(pi)), Angle(135, Angle::Unit::DEGREES));
  EXPECT_EQ(Angle(-30, Angle::Unit::DEGREES).modulo(Angle(pi)), Angle(150, Angle::Unit::DEGREES));
  EXPECT_EQ(Angle(0, Angle::Unit::DEGREES).modulo(Angle(pi)), Angle());
  EXPECT_EQ(Angle(90, Angle::Unit::DEGREES).modulo(Angle(pi)), Angle(90, Angle::Unit::DEGREES));
  EXPECT_EQ(Angle(179.9F, Angle::Unit::DEGREES).modulo(Angle(pi)), Angle(179.9F, Angle::Unit::DEGREES));
  EXPECT_EQ(Angle(180, Angle::Unit::DEGREES).modulo(Angle(pi)), Angle());
  EXPECT_EQ(Angle(210, Angle::Unit::DEGREES).modulo(Angle(pi)), Angle(30, Angle::Unit::DEGREES));
  EXPECT_EQ(Angle(270, Angle::Unit::DEGREES).modulo(Angle(pi)), Angle(90, Angle::Unit::DEGREES));
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
  EXPECT_EQ(angle.radians(), -pi / 2.0F);
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

TEST(AngleTest, ReassignWithInvalidUnit1) {
  Angle angle;
  ASSERT_THROW(angle.set(-15.0F, (Angle::Unit) -1), std::runtime_error);
}
