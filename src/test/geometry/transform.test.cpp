#include "../util.hpp"

#include "../../engine/geometry/transform.hpp"
using namespace engine::geometry;

TEST(TransformTest, Constructor1) {
  Transform t;
  EXPECT_EQ(Vector<3>(), t.position());
  EXPECT_EQ(Vector<3>(), t.rotation());
  EXPECT_EQ(Vector<3>(1.0F, 1.0F, 1.0F), t.scale());
}

TEST(TransformTest, Constructor2) {
  Vector<3> v(1.2f, 3.5f, -0.5f);
  Transform t(v);
  EXPECT_EQ(v, t.position());
}

TEST(TransformTest, Constructor3) {
  Vector<3> v1(-12.3F, 2.9F, 1.3F);
  Vector<3> v2(pi / 2.0F, 0.0F, pi);
  Vector<3> v3(1.2f, 3.5f, -0.5f);

  Transform t(v1, v2, v3);

  EXPECT_EQ(t.position(), v1);
  EXPECT_EQ(t.rotation(), v2);
  EXPECT_EQ(t.scale(), v3);
}

TEST(TransformTest, VectorBasis1) {
  Transform t;

  EXPECT_EQ(t.right().magnitude(), 1.0F);
  EXPECT_EQ(t.up().magnitude(), 1.0F);
  EXPECT_EQ(t.forward().magnitude(), 1.0F);

  EXPECT_EQ(t.forward().dot(t.up()), 0);
  EXPECT_EQ(t.forward().dot(t.right()), 0);
  EXPECT_EQ(t.up().dot(t.right()), 0);
}

TEST(TransformTest, VectorBasis2) {
  Transform t(Vector<3>(), Vector<3>(pi, 0.0F, 0.0F));

  EXPECT_EQ(t.right(), Vector<3>(1.0F, 0.0F, 0.0F));
  EXPECT_EQ(t.up(), Vector<3>(0.0F, -1.0F, 0.0F));
  EXPECT_EQ(t.forward(), Vector<3>(0.0F, 0.0F, -1.0F));
}

TEST(TransformTest, VectorBasis3) {
  Transform t(Vector<3>(), Vector<3>(pi / 2.0F, 0.0F, 0.0F));

  EXPECT_EQ(t.right(), Vector<3>(1.0F, 0.0F, 0.0F));
  EXPECT_EQ(t.up(), Vector<3>(0.0F, 0.0F, -1.0F));
  EXPECT_EQ(t.forward(), Vector<3>(0.0F, 1.0F, 0.0F));
}

TEST(TransformTest, VectorBasis4) {
  Transform t(Vector<3>(), Vector<3>(pi / 4.0F, 0.0F, 0.0F));

  EXPECT_EQ(t.right(), Vector<3>(1.0F, 0.0F, 0.0F));
  EXPECT_EQ(t.up(), Vector<3>(0.0F, sqrtf(0.5), -sqrtf(0.5)));
  EXPECT_EQ(t.forward(), Vector<3>(0.0F, sqrtf(0.5), sqrtf(0.5)));
}

TEST(TransformTest, VectorBasis5) {
  Transform t(Vector<3>(), Vector<3>(0.0F, pi / 2.0F, 0.0F));

  EXPECT_EQ(t.right(), Vector<3>(0.0F, 0.0F, 1.0F));
  EXPECT_EQ(t.up(), Vector<3>(0.0F, 1.0F, 0.0F));
  EXPECT_EQ(t.forward(), Vector<3>(-1.0F, 0.0F, 0.0F));
}

TEST(TransformTest, VectorBasis6) {
  Transform t(Vector<3>(), Vector<3>(0.0F, pi / 4.0F, 0.0F));

  EXPECT_EQ(t.right(), Vector<3>(sqrtf(0.5), 0.0F, sqrtf(0.5)));
  EXPECT_EQ(t.up(), Vector<3>(0.0F, 1.0F, 0.0F));
  EXPECT_EQ(t.forward(), Vector<3>(-sqrtf(0.5), 0.0F, sqrtf(0.5)));
}

TEST(TransformTest, VectorBasis7) {
  Transform t(Vector<3>(), Vector<3>(0.0F, 0.0F, pi / 2.0F));

  EXPECT_EQ(t.right(), Vector<3>(0.0F, -1.0F, 0.0F));
  EXPECT_EQ(t.up(), Vector<3>(1.0F, 0.0F, 0.0F));
  EXPECT_EQ(t.forward(), Vector<3>(0.0F, 0.0F, 1.0F));
}

TEST(TransformTest, VectorBasis8) {
  Transform t(Vector<3>(), Vector<3>(0.0F, 0.0F, pi / 4.0F));

  EXPECT_EQ(t.right(), Vector<3>(sqrtf(0.5), -sqrtf(0.5), 0.0F));
  EXPECT_EQ(t.up(), Vector<3>(sqrtf(0.5), sqrtf(0.5), 0.0F));
  EXPECT_EQ(t.forward(), Vector<3>(0.0F, 0.0F, 1.0F));
}

TEST(TransformTest, VectorBasis9) {
  Transform t(Vector<3>(), Vector<3>(pi / 2.0F, -pi / 2.0F, 0.0F));

  EXPECT_EQ(t.right(), Vector<3>(0.0F, 0.0F, -1.0F));
  EXPECT_EQ(t.up(), Vector<3>(-1.0F, 0.0F, 0.0F));
  EXPECT_EQ(t.forward(), Vector<3>(0.0F, 1.0F, 0.0F));
}

TEST(TransformTest, VectorBasis10) {
  Transform t(Vector<3>(), Vector<3>(pi / 2.0F, pi / 2.0F, pi / 2.0F));

  EXPECT_EQ(t.right(), Vector<3>(-1.0F, 0.0F, 0.0F));
  EXPECT_EQ(t.up(), Vector<3>(0.0F, 0.0F, 1.0F));
  EXPECT_EQ(t.forward(), Vector<3>(0.0F, 1.0F, 0.0F));
}

TEST(TransformTest, FlipRotation1) {
  Transform t(Vector<3>(-4.2F, 3.2F, -0.3F));

  EXPECT_EQ(t.right(), Vector<3>(1.0F, 0.0F, 0.0F));
  EXPECT_EQ(t.up(), Vector<3>(0.0F, 1.0F, 0.0F));
  EXPECT_EQ(t.forward(), Vector<3>(0.0F, 0.0F, 1.0F));

  t.flip_rotation();

  EXPECT_EQ(t.right(), Vector<3>(-1.0F, 0.0F, 0.0F));
  EXPECT_EQ(t.up(), Vector<3>(0.0F, 1.0F, 0.0F));
  EXPECT_EQ(t.forward(), Vector<3>(0.0F, 0.0F, -1.0F));

  t.flip_rotation();

  EXPECT_EQ(t.right(), Vector<3>(1.0F, 0.0F, 0.0F));
  EXPECT_EQ(t.up(), Vector<3>(0.0F, 1.0F, 0.0F));
  EXPECT_EQ(t.forward(), Vector<3>(0.0F, 0.0F, 1.0F));
}

TEST(TransformTest, FlipRotation2) {
  Transform t(Vector<3>(-12.3F, 2.9F, 1.3F), Vector<3>(pi / 4.0F, 0.0F, 0.0F));

  EXPECT_EQ(t.right(), Vector<3>(1.0F, 0.0F, 0.0F));
  EXPECT_EQ(t.up(), Vector<3>(0.0F, sqrtf(0.5), -sqrtf(0.5)));
  EXPECT_EQ(t.forward(), Vector<3>(0.0F, sqrtf(0.5), sqrtf(0.5)));

  t.flip_rotation();

  EXPECT_EQ(t.right(), Vector<3>(-1.0F, 0.0F, 0.0F));
  EXPECT_EQ(t.up(), Vector<3>(0.0F, sqrtf(0.5), -sqrtf(0.5)));
  EXPECT_EQ(t.forward(), Vector<3>(0.0F, -sqrtf(0.5), -sqrtf(0.5)));

  t.flip_rotation();

  EXPECT_EQ(t.right(), Vector<3>(1.0F, 0.0F, 0.0F));
  EXPECT_EQ(t.up(), Vector<3>(0.0F, sqrtf(0.5), -sqrtf(0.5)));
  EXPECT_EQ(t.forward(), Vector<3>(0.0F, sqrtf(0.5), sqrtf(0.5)));
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

  t.set_rotation(0, 0, pi);
  EXPECT_EQ(t.matrix(), (Matrix<4>({
                          {-2.0F, 0.0F, 0.0F, 0.0F},
                          {0.0F, 2.0F, 0.0F, 0.0F},
                          {0.0F, 0.0F, -2.0F, 0.0F},
                          {0.0F, 0.0F, 0.0F, 1.0F},
                        })));

  t.position() = Vector<3>(1.0F, 1.0F, 1.0F);
  EXPECT_EQ(t.matrix(), (Matrix<4>({
                          {-2.0F, 0.0F, 0.0F, 1.0F},
                          {0.0F, 2.0F, 0.0F, 1.0F},
                          {0.0F, 0.0F, -2.0F, 1.0F},
                          {0.0F, 0.0F, 0.0F, 1.0F},
                        })));
}

TEST(TransformTest, Matrix2) {
  Transform t;
  t.scale()    = Vector<3>(2.0F, 0.5F, 1.0F);
  t.rotation() = Vector<3>(0.0F, 0.0F, pi / 2.0F);
  t.position() = Vector<3>(1.0F, 1.0F, 1.0F);

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
  t.rotation() = Vector<3>(0.0F, pi, 0.0F);
  t.position() = Vector<3>(0.5F, 0.5F, 0.5F);
  t.scale()    = Vector<3>(0.5F, 0.5F, 0.5F);

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
