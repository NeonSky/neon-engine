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
