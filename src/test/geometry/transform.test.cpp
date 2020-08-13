#include "../util.hpp"

#include "../../engine/geometry/transform.hpp"
using namespace engine::geometry;

TEST(TransformTest, Equality1) {
  Transform t1;
  Transform t2;
  EXPECT_EQ(t1, t2);

  t1.position() = Vector<3>(0, 1, 0);
  EXPECT_NE(t1, t2);

  t2.position() = Vector<3>(0, 1, 0);
  EXPECT_EQ(t1, t2);

  t1.orientation() = Rotation(0, pi, pi);
  EXPECT_NE(t1, t2);

  t2.orientation() = Rotation(0, pi, pi);
  EXPECT_EQ(t1, t2);

  t1.scale() = Vector<3>(1, 2, 3);
  EXPECT_NE(t1, t2);

  t2.scale() = Vector<3>(1, 2, 3);
  EXPECT_EQ(t1, t2);

  t2.orientation() = Rotation(pi, 0, 0);
  EXPECT_EQ(t1, t2);
}

TEST(TransformTest, Constructor1) {
  Transform t;
  EXPECT_EQ(Vector<3>(), t.position());
  EXPECT_EQ(Orientation(), t.orientation());
  EXPECT_EQ(Vector<3>(1.0F, 1.0F, 1.0F), t.scale());
}

TEST(TransformTest, Constructor2) {
  Vector<3> v(1.2f, 3.5f, -0.5f);
  Transform t(v);
  EXPECT_EQ(v, t.position());
}

TEST(TransformTest, Constructor3) {
  Vector<3> position(-12.3F, 2.9F, 1.3F);
  Orientation orientation(Rotation(pi / 2.0F, 0.0F, pi, Angle::Unit::RADIANS));
  Vector<3> scale(1.2f, 3.5f, -0.5f);

  Transform t(position, orientation, scale);

  EXPECT_EQ(t.position(), position);
  EXPECT_EQ(t.orientation(), orientation);
  EXPECT_EQ(t.scale(), scale);

  EXPECT_EQ(std::as_const(t).position(), position);
  EXPECT_EQ(std::as_const(t).orientation(), orientation);
  EXPECT_EQ(std::as_const(t).scale(), scale);
}

TEST(TransformTest, VectorBasis1) {
  Transform t;

  EXPECT_EQ(t.right(), t.orientation().right());
  EXPECT_EQ(t.up(), t.orientation().up());
  EXPECT_EQ(t.forward(), t.orientation().forward());
}

TEST(TransformTest, VectorBasis2) {
  Transform t;
  t.orientation() = Rotation(pi / 2.0F, -pi / 2.0F, 0.0F);

  EXPECT_EQ(t.right(), t.orientation().right());
  EXPECT_EQ(t.up(), t.orientation().up());
  EXPECT_EQ(t.forward(), t.orientation().forward());
}

TEST(TransformTest, VectorBasis3) {
  Transform t;
  t.orientation() = Rotation(pi / 2.0F, pi / 2.0F, pi / 2.0F);

  EXPECT_EQ(t.right(), t.orientation().right());
  EXPECT_EQ(t.up(), t.orientation().up());
  EXPECT_EQ(t.forward(), t.orientation().forward());
}

TEST(TransformTest, Matrix1) {
  Transform t;
  EXPECT_EQ(t.matrix(), (Matrix<4>({
                          {1.0F, 0.0F, 0.0F, 0.0F},
                          {0.0F, 1.0F, 0.0F, 0.0F},
                          {0.0F, 0.0F, 1.0F, 0.0F},
                          {0.0F, 0.0F, 0.0F, 1.0F},
                        })));

  t.scale() = Vector<3>(2.0F, 2.0F, 2.0F);
  EXPECT_EQ(t.matrix(), (Matrix<4>({
                          {2.0F, 0.0F, 0.0F, 0.0F},
                          {0.0F, 2.0F, 0.0F, 0.0F},
                          {0.0F, 0.0F, 2.0F, 0.0F},
                          {0.0F, 0.0F, 0.0F, 1.0F},
                        })));

  t.orientation() = Rotation(0, 0, pi);
  EXPECT_EQ(t.matrix(), (Matrix<4>({
                          {-2.0F, 0.0F, 0.0F, 0.0F},
                          {0.0F, -2.0F, 0.0F, 0.0F},
                          {0.0F, 0.0F, 2.0F, 0.0F},
                          {0.0F, 0.0F, 0.0F, 1.0F},
                        })));

  t.position() = Vector<3>(1.0F, 1.0F, 1.0F);
  EXPECT_EQ(t.matrix(), (Matrix<4>({
                          {-2.0F, 0.0F, 0.0F, 1.0F},
                          {0.0F, -2.0F, 0.0F, 1.0F},
                          {0.0F, 0.0F, 2.0F, 1.0F},
                          {0.0F, 0.0F, 0.0F, 1.0F},
                        })));
}

TEST(TransformTest, Matrix2) {
  Transform t;
  t.scale()       = Vector<3>(2.0F, 0.5F, 1.0F);
  t.orientation() = Rotation(0.0F, 0.0F, pi / 2.0F);
  t.position()    = Vector<3>(1.0F, 1.0F, 1.0F);

  EXPECT_EQ(t.matrix(), (Matrix<4>({
                          {+0.0F, +0.5F, +0.0F, +1.0F},
                          {-2.0F, +0.0F, +0.0F, +1.0F},
                          {+0.0F, +0.0F, +1.0F, +1.0F},
                          {+0.0F, +0.0F, +0.0F, +1.0F},
                        })));
}

TEST(TransformTest, Matrix3) {
  // Cube coordinates
  Vector<3> left_down_back(-1.0F, -1.0F, -1.0F);
  Vector<3> right_down_back(1.0F, -1.0F, -1.0F);
  Vector<3> left_up_back(-1.0F, 1.0F, -1.0F);
  Vector<3> right_up_back(1.0F, 1.0F, -1.0F);
  Vector<3> left_down_front(-1.0F, -1.0F, 1.0F);
  Vector<3> right_down_front(1.0F, -1.0F, 1.0F);
  Vector<3> left_up_front(-1.0F, 1.0F, 1.0F);
  Vector<3> right_up_front(1.0F, 1.0F, 1.0F);

  Transform t;
  t.position()    = Vector<3>(0.5F, 0.5F, 0.5F);
  t.orientation() = Rotation(0.0F, pi, 0.0F);
  t.scale()       = Vector<3>(0.5F, 0.5F, 0.5F);

  EXPECT_EQ(t.matrix() * Vector<4>(left_down_back, 1.0F),
            Vector<4>(1.0F, 0.0F, 1.0F, 1.0F));
  EXPECT_EQ(t.matrix() * Vector<4>(right_down_back, 1.0F),
            Vector<4>(0.0F, 0.0F, 1.0F, 1.0F));
  EXPECT_EQ(t.matrix() * Vector<4>(left_up_back, 1.0F),
            Vector<4>(1.0F, 1.0F, 1.0F, 1.0F));
  EXPECT_EQ(t.matrix() * Vector<4>(right_up_back, 1.0F),
            Vector<4>(0.0F, 1.0F, 1.0F, 1.0F));
  EXPECT_EQ(t.matrix() * Vector<4>(left_down_front, 1.0F),
            Vector<4>(1.0F, 0.0F, 0.0F, 1.0F));
  EXPECT_EQ(t.matrix() * Vector<4>(right_down_front, 1.0F),
            Vector<4>(0.0F, 0.0F, 0.0F, 1.0F));
  EXPECT_EQ(t.matrix() * Vector<4>(left_up_front, 1.0F),
            Vector<4>(1.0F, 1.0F, 0.0F, 1.0F));
  EXPECT_EQ(t.matrix() * Vector<4>(right_up_front, 1.0F),
            Vector<4>(0.0F, 1.0F, 0.0F, 1.0F));
}

TEST(TransformTest, ConvertsToJSON1) {
  Transform t(Vector<3>(1, 2, 3), Rotation(0, -pi, pi), Vector<3>(1, 2, 3));
  JSON json;
  json["position"]    = t.position().to_json();
  json["orientation"] = t.orientation().to_json();
  json["scale"]       = t.scale().to_json();
  EXPECT_EQ(t.to_json(), json);

  json["orientation"] = t.orientation().to_json(true);
  EXPECT_EQ(t.to_json(true), json);
}
