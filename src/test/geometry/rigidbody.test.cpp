#include "../util.hpp"

#include "../../engine/geometry/rigidbody.hpp"
using namespace engine::geometry;

TEST(RigidbodyTest, Equality1) {
  Rigidbody r1;
  Rigidbody r2;
  EXPECT_EQ(r1, r2);

  r1.position() = Vector<3>(0, 1, 0);
  EXPECT_NE(r1, r2);

  r2.position() = Vector<3>(0, 1, 0);
  EXPECT_EQ(r1, r2);

  r1.orientation() = Rotation(0, pi, pi);
  EXPECT_NE(r1, r2);

  r2.orientation() = Rotation(0, pi, pi);
  EXPECT_EQ(r1, r2);

  r2.orientation() = Rotation(pi, 0, 0);
  EXPECT_EQ(r1, r2);
}

TEST(RigidbodyTest, Constructor1) {
  Rigidbody r(Vector<3>(2.4F, -3.2F, 0.11F));
  EXPECT_EQ(r.position(), Vector<3>(2.4F, -3.2F, 0.11F));
  EXPECT_EQ(r.orientation(), Orientation());
}

TEST(RigidbodyTest, Matrix1) {
  Rigidbody r;
  EXPECT_EQ(r.matrix(), (Matrix<4>({
                          {1.0F, 0.0F, 0.0F, 0.0F},
                          {0.0F, 1.0F, 0.0F, 0.0F},
                          {0.0F, 0.0F, 1.0F, 0.0F},
                          {0.0F, 0.0F, 0.0F, 1.0F},
                        })));

  r.orientation() = Rotation(0, 0, pi);
  EXPECT_EQ(r.matrix(), (Matrix<4>({
                          {-1.0F, 0.0F, 0.0F, 0.0F},
                          {0.0F, -1.0F, 0.0F, 0.0F},
                          {0.0F, 0.0F, 1.0F, 0.0F},
                          {0.0F, 0.0F, 0.0F, 1.0F},
                        })));

  r.position() = Vector<3>(2.0F, 3.0F, 4.0F);
  EXPECT_EQ(r.matrix(), (Matrix<4>({
                          {-1.0F, 0.0F, 0.0F, 2.0F},
                          {0.0F, -1.0F, 0.0F, 3.0F},
                          {0.0F, 0.0F, 1.0F, 4.0F},
                          {0.0F, 0.0F, 0.0F, 1.0F},
                        })));
}

TEST(RigidbodyTest, Matrix2) {
  Rigidbody r;
  r.orientation() = Rotation(0.0F, 0.0F, pi / 2.0F);
  r.position()    = Vector<3>(1.0F, 1.0F, 1.0F);

  EXPECT_EQ(r.matrix(), (Matrix<4>({
                          {+0.0F, +1.0F, +0.0F, +1.0F},
                          {-1.0F, +0.0F, +0.0F, +1.0F},
                          {+0.0F, +0.0F, +1.0F, +1.0F},
                          {+0.0F, +0.0F, +0.0F, +1.0F},
                        })));
}

TEST(RigidbodyTest, Matrix3) {
  // Cube coordinates
  Vector<3> left_down_back(-1.0F, -1.0F, -1.0F);
  Vector<3> right_down_back(1.0F, -1.0F, -1.0F);
  Vector<3> left_up_back(-1.0F, 1.0F, -1.0F);
  Vector<3> right_up_back(1.0F, 1.0F, -1.0F);
  Vector<3> left_down_front(-1.0F, -1.0F, 1.0F);
  Vector<3> right_down_front(1.0F, -1.0F, 1.0F);
  Vector<3> left_up_front(-1.0F, 1.0F, 1.0F);
  Vector<3> right_up_front(1.0F, 1.0F, 1.0F);

  Rigidbody r;
  r.position()    = Vector<3>(1.0F, 1.0F, 1.0F);
  r.orientation() = Rotation(0.0F, pi, 0.0F);

  EXPECT_EQ(r.matrix() * Vector<4>(left_down_back, 1.0F),
            Vector<4>(2.0F, 0.0F, 2.0F, 1.0F));
  EXPECT_EQ(r.matrix() * Vector<4>(right_down_back, 1.0F),
            Vector<4>(0.0F, 0.0F, 2.0F, 1.0F));
  EXPECT_EQ(r.matrix() * Vector<4>(left_up_back, 1.0F),
            Vector<4>(2.0F, 2.0F, 2.0F, 1.0F));
  EXPECT_EQ(r.matrix() * Vector<4>(right_up_back, 1.0F),
            Vector<4>(0.0F, 2.0F, 2.0F, 1.0F));
  EXPECT_EQ(r.matrix() * Vector<4>(left_down_front, 1.0F),
            Vector<4>(2.0F, 0.0F, 0.0F, 1.0F));
  EXPECT_EQ(r.matrix() * Vector<4>(right_down_front, 1.0F),
            Vector<4>(0.0F, 0.0F, 0.0F, 1.0F));
  EXPECT_EQ(r.matrix() * Vector<4>(left_up_front, 1.0F),
            Vector<4>(2.0F, 2.0F, 0.0F, 1.0F));
  EXPECT_EQ(r.matrix() * Vector<4>(right_up_front, 1.0F),
            Vector<4>(0.0F, 2.0F, 0.0F, 1.0F));
}

TEST(RigidbodyTest, ConvertsToJSON1) {
  Rigidbody r(Vector<3>(1, 2, 3), Rotation(0, -pi, pi));
  JSON json;
  json["position"]    = r.position().to_json();
  json["orientation"] = r.orientation().to_json();
  EXPECT_EQ(r.to_json(), json);

  json["orientation"] = r.orientation().to_json(true);
  EXPECT_EQ(r.to_json(true), json);
}
