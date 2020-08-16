#include "../util.hpp"

#include "../../engine/geometry/vector.hpp"
using namespace engine::geometry;

TEST(VectorTest, Size1) {
  Vector<1> v1;
  Vector<2> v2;
  Vector<3> v3;
  Vector<4> v4;

  EXPECT_EQ(sizeof(v1), 1 * sizeof(float));
  EXPECT_EQ(sizeof(v2), 2 * sizeof(float));
  EXPECT_EQ(sizeof(v3), 3 * sizeof(float));
  EXPECT_EQ(sizeof(v4), 4 * sizeof(float));
}

TEST(VectorTest, Constructor1) {
  Vector<2> v;
  EXPECT_EQ(v[0], 0.0F);
  EXPECT_EQ(v[1], 0.0F);
}

TEST(VectorTest, Constructor2) {
  Vector<3> v(3.4F, 0.5F, -40.2F);
  EXPECT_EQ(v[0], 3.4F);
  EXPECT_EQ(v[1], 0.5F);
  EXPECT_EQ(v[2], -40.2F);
}

TEST(VectorTest, Constructor3) {
  Vector<4> v(3.4F, -0.2F, -40.2F, 2.3F);
  auto vector2 = v;
  EXPECT_EQ(v, vector2);
}

TEST(VectorTest, Constructor4) {
  Vector<1> vector1(3.2F);
  Vector<2> vector2(vector1, -2.4F);
  Vector<3> vector3(vector2, 9.2F);
  Vector<4> vector4(vector3, -14.9F);

  EXPECT_EQ(vector2, Vector<2>(3.2F, -2.4F));
  EXPECT_EQ(vector3, Vector<3>(3.2F, -2.4F, 9.2F));
  EXPECT_EQ(vector4, Vector<4>(3.2F, -2.4F, 9.2F, -14.9F));
}

TEST(VectorTest, Constructor5) {
  Vector<1> vector(10.37F);
  EXPECT_EQ(vector[0], 10.37F);
}

TEST(VectorTest, Constructor6) {
  Point<2> from(3.4F, 2.4F);
  Point<2> to(1.8F, 3.8F);

  EXPECT_EQ(Vector<2>(from, to), Vector<2>(-1.6F, 1.4F));

  ASSERT_NO_THROW(Vector<2>(from, from));
  ASSERT_NO_THROW(Vector<2>(to, to));

  ASSERT_THROW(UnitVector<2>(from, from), std::runtime_error);
  ASSERT_THROW(UnitVector<2>(to, to), std::runtime_error);
}

TEST(VectorTest, Constructor7) {
  std::array<float, 3> arr{0.3F, -0.6F, 0.99124F};
  Vector<3> v(arr);
  EXPECT_EQ(v[0], +0.3F);
  EXPECT_EQ(v[1], -0.6F);
  EXPECT_EQ(v[2], +0.99124F);
}

TEST(VectorTest, Assignment1) {
  Vector<2> vector1(3.2F, -2.4F);
  Vector<2> vector2(1.3F, 9.2F);

  EXPECT_NE(vector1, vector2);
  vector1 = vector2;
  EXPECT_EQ(vector1, vector2);
}

TEST(VectorTest, Assignment2) {
  UnitVector<2> vector1(3.2F, -2.4F);
  UnitVector<2> vector2(1.3F, 9.2F);

  EXPECT_NE(vector1, vector2);
  vector1 = vector2;
  EXPECT_EQ(vector1, vector2);
}

TEST(VectorTest, Assignment3) {
  Vector<2> vector1(3.2F, -2.4F);
  Vector<2> vector2(1.3F, 9.2F);

  vector1 += vector2;
  EXPECT_EQ(vector1, Vector<2>(4.5F, 6.8F));

  vector1 -= vector2;
  EXPECT_EQ(vector1, Vector<2>(3.2F, -2.4F));

  vector1 -= vector2;
  EXPECT_EQ(vector1, Vector<2>(1.9F, -11.6F));

  vector1 += vector2;
  EXPECT_EQ(vector1, Vector<2>(3.2F, -2.4F));
}

TEST(VectorTest, Assignment4) {
  Vector<3> vector1(3.2F, -2.4F, 1.1F);
  Vector<3> vector2;
  EXPECT_EQ(vector1 + vector2, vector1);

  vector2 += vector1;
  EXPECT_EQ(vector1, vector2);

  vector1 -= vector2;
  EXPECT_EQ(vector1, Vector<3>());
}

TEST(VectorTest, AddsAndSubtracts1) {
  Vector<2> vector1(3.2F, -2.4F);
  Vector<2> vector2(1.3F, 9.2F);
  EXPECT_EQ(vector1 + vector2, Vector<2>(4.5F, 6.8F));
  EXPECT_EQ(vector1 - vector2, Vector<2>(1.9F, -11.6F));
  EXPECT_EQ(vector2 - vector1, Vector<2>(-1.9F, 11.6F));
  EXPECT_EQ(vector1 - vector1, Vector<2>());
  EXPECT_EQ(vector2 - vector2, Vector<2>());
}

TEST(VectorTest, AddsAndSubtracts2) {
  Vector<3> vector1(3.2F, -2.4F, 0.4F);
  Vector<3> vector2(1.3F, 9.2F, -0.1F);
  EXPECT_EQ(vector1 + vector2, Vector<3>(4.5F, 6.8F, 0.3F));
  EXPECT_EQ(vector1 - vector2, Vector<3>(1.9F, -11.6F, 0.5F));
  EXPECT_EQ(vector2 - vector1, Vector<3>(-1.9F, 11.6F, -0.5F));
  EXPECT_EQ(vector1 - vector1, Vector<3>());
  EXPECT_EQ(vector2 - vector2, Vector<3>());
}

TEST(VectorTest, Magnitude1) {
  Vector<1> v1(7.3F);
  Vector<2> v2(3.2F, -2.4F);
  Vector<3> v3(1.3F, 9.2F, -0.1F);
  Vector<4> v4(1.0F, 2.0F, 3.0F, 4.0F);

  EXPECT_EQ(v1.magnitude(), 7.3F);
  EXPECT_EQ(v2.magnitude(), 4.0F);
  EXPECT_EQ(v3.magnitude(), 9.29193198425F);
  EXPECT_EQ(v4.magnitude(), 5.47722557505F);
}

TEST(VectorTest, Affirmation1) {
  Vector<2> vector(3.2F, -2.4F);
  EXPECT_EQ(vector, vector);
  EXPECT_EQ(vector, +vector);
  EXPECT_EQ(+vector, +vector);
}

TEST(VectorTest, Affirmation2) {
  Vector<1> v1;
  Vector<2> v2;
  Vector<3> v3;
  Vector<4> v4;
  EXPECT_EQ(+v1, +v1);
  EXPECT_EQ(+v2, +v2);
  EXPECT_EQ(+v3, +v3);
  EXPECT_EQ(+v4, +v4);
}

TEST(VectorTest, Affirmation3) {
  UnitVector<1> v1;
  UnitVector<2> v2;
  UnitVector<3> v3;
  UnitVector<4> v4;
  EXPECT_EQ(+v1, +v1);
  EXPECT_EQ(+v2, +v2);
  EXPECT_EQ(+v3, +v3);
  EXPECT_EQ(+v4, +v4);
}

TEST(VectorTest, Negation1) {
  Vector<2> vector(3.2F, -2.4F);
  EXPECT_EQ(vector, vector);
  EXPECT_EQ(-(-vector), vector);
  EXPECT_EQ(-vector, -vector);
  EXPECT_NE(-vector, vector);
}

TEST(VectorTest, Negation2) {
  UnitVector<2> vector(3.2F, -2.4F);
  EXPECT_EQ(vector, vector);
  EXPECT_EQ(-(-vector), vector);
  EXPECT_EQ(-vector, -vector);
  EXPECT_NE(-vector, vector);
}

TEST(VectorTest, Negation3) {
  UnitVector<1> v1;
  UnitVector<2> v2;
  UnitVector<3> v3;
  UnitVector<4> v4;

  EXPECT_EQ(-v1, Vector<1>(-1.0F));
  EXPECT_EQ(-v2, Vector<2>(-1.0F, 0.0F));
  EXPECT_EQ(-v3, Vector<3>(-1.0F, 0.0F, 0.0F));
  EXPECT_EQ(-v4, Vector<4>(-1.0F, 0.0F, 0.0F, 0.0F));
}

TEST(VectorTest, Scales1) {
  Vector<2> vector(1.3F, 0.4F);
  EXPECT_EQ(1.5F * vector, Vector<2>(1.95F, 0.6F));
  EXPECT_EQ(vector * 1.5F, Vector<2>(1.95F, 0.6F));
  vector *= 1.5F;
  EXPECT_EQ(vector, Vector<2>(1.95F, 0.6F));
}

TEST(VectorTest, Scales2) {
  Vector<3> vector(1.0F, 2.0F, 3.0F);
  EXPECT_EQ(2.0F * vector, Vector<3>(2.0F, 4.0F, 6.0F));
  EXPECT_EQ(vector * 2.0F, Vector<3>(2.0F, 4.0F, 6.0F));
  vector *= 2.0F;
  EXPECT_EQ(vector, Vector<3>(2.0F, 4.0F, 6.0F));
}

TEST(VectorTest, Scales3) {
  Vector<3> vector(1.0F, 2.0F, 3.0F);
  ASSERT_THROW(vector = vector / 0.0F, std::runtime_error);
}

TEST(VectorTest, InnerProduct1) {
  Vector<1> vector1(0.9627590F);
  Vector<1> vector2(1.0F);
  EXPECT_EQ(vector1.inner_product(vector2), 0.9627590F);
}

TEST(VectorTest, InnerProduct2) {
  Vector<2> vector1(1.0F, 2.0F);
  Vector<2> vector2(1.0F, 1.0F);
  EXPECT_EQ(vector1.inner_product(vector2), 3.0F);
}

TEST(VectorTest, InnerProduct3) {
  Vector<3> vector1(1.0F, 0.0F, 2.0F);
  Vector<3> vector2(1.0F, 1.0F, 1.5F);
  EXPECT_EQ(vector1.inner_product(vector2), 4.0F);
}

TEST(VectorTest, InnerProduct5) {
  Vector<4> vector1(1.0F, 0.0F, 2.0F, -4.0F);
  Vector<4> vector2(1.0F, 1.0F, 0.5F, 2.0F);
  EXPECT_EQ(vector1.inner_product(vector2), -6.0F);
}

// TEST(VectorTest, CrossProduct1) {
//   Vector<2> vector1(1.3F, -0.2F);
//   Vector<2> vector2 = cross_product(vector1);
//   EXPECT_EQ(vector1.inner_product(vector2), 0.0F);
// }

// TEST(VectorTest, CrossProduct2) {
//   Vector<3> vector1(1.0F, 0.0F, 0.0F);
//   Vector<3> vector2(0.0F, 1.0F, 0.0F);
//   EXPECT_EQ(cross_product(vector1, vector2), Vector<3>(0.0F, 0.0F, 1.0F));
// }

TEST(VectorTest, Iterates1) {
  Vector<3> vector(1.4F, 3.8F, 0.1F);

  int i = 0;
  for (auto& e : vector)
    EXPECT_EQ(e, vector[i++]);
  EXPECT_EQ(i, 3);
}

TEST(VectorTest, Iterates2) {
  Vector<3> vector(1.4F, 3.8F, 0.1F);

  int i = 0;
  for (const float* it = vector.begin(); it != vector.end(); it++)
    EXPECT_EQ((*it), vector[i++]);
  EXPECT_EQ(i, 3);
}

TEST(VectorTest, Aliases1) {
  Vector<1> vector;
  vector[0] = 1.4F;

  EXPECT_EQ(vector.x(), vector[0]);
  EXPECT_EQ(vector.r(), vector[0]);
  EXPECT_EQ(vector.s(), vector[0]);
}

TEST(VectorTest, Aliases2) {
  Vector<2> vector;
  vector[0] = 1.4F;
  vector[1] = 3.8F;

  EXPECT_EQ(vector.x(), vector[0]);
  EXPECT_EQ(vector.y(), vector[1]);

  EXPECT_EQ(vector.r(), vector[0]);
  EXPECT_EQ(vector.g(), vector[1]);

  EXPECT_EQ(vector.s(), vector[0]);
  EXPECT_EQ(vector.t(), vector[1]);
}

TEST(VectorTest, Aliases3) {
  Vector<3> vector;
  vector[0] = 1.4F;
  vector[1] = 3.8F;
  vector[2] = -13.8F;

  EXPECT_EQ(vector.x(), vector[0]);
  EXPECT_EQ(vector.y(), vector[1]);
  EXPECT_EQ(vector.z(), vector[2]);

  EXPECT_EQ(vector.r(), vector[0]);
  EXPECT_EQ(vector.g(), vector[1]);
  EXPECT_EQ(vector.b(), vector[2]);

  EXPECT_EQ(vector.s(), vector[0]);
  EXPECT_EQ(vector.t(), vector[1]);
  EXPECT_EQ(vector.p(), vector[2]);
}

TEST(VectorTest, Aliases4) {
  Vector<4> vector;
  vector[0] = 1.4F;
  vector[1] = 3.8F;
  vector[2] = -13.8F;
  vector[3] = -5.2F;

  EXPECT_EQ(vector.x(), vector[0]);
  EXPECT_EQ(vector.y(), vector[1]);
  EXPECT_EQ(vector.z(), vector[2]);
  EXPECT_EQ(vector.w(), vector[3]);

  EXPECT_EQ(vector.r(), vector[0]);
  EXPECT_EQ(vector.g(), vector[1]);
  EXPECT_EQ(vector.b(), vector[2]);
  EXPECT_EQ(vector.a(), vector[3]);

  EXPECT_EQ(vector.s(), vector[0]);
  EXPECT_EQ(vector.t(), vector[1]);
  EXPECT_EQ(vector.p(), vector[2]);
  EXPECT_EQ(vector.q(), vector[3]);
}

TEST(VectorTest, Normalizes1) {
  Vector<2> vector;
  ASSERT_THROW(vector = vector.normalized(), std::runtime_error);
}

TEST(VectorTest, Normalizes2) {
  Vector<3> vector(1.0F, 2.0F, 3.0F);
  EXPECT_EQ(vector.normalized(), vector / sqrt(14.0F));
}

TEST(VectorTest, ConvertsToLowerDimension1) {
  Vector<4> vector1(1.4F, 3.8F, 0.1F, -93.4F);
  Vector<3> vector2(1.4F, 3.8F, 0.1F);
  EXPECT_EQ((Vector<3>) vector1, vector2);
}

TEST(VectorTest, ConvertsToHigherDimension1) {
  Vector<4> vector1(1.4F, 3.8F, 0.1F, 0.0F);
  Vector<3> vector2(1.4F, 3.8F, 0.1F);
  EXPECT_EQ(vector1, (Vector<4>) vector2);
}

TEST(VectorTest, ConvertsToArray1) {
  Vector<2> vector(1.4F, 3.8F);
  std::array<float, 2> arr{1.4F, 3.8F};
  EXPECT_EQ((std::array<float, 2>) vector, arr);
}

TEST(VectorTest, ConvertsToArray2) {
  Vector<3> vector(1.4F, 3.8F, 0.1F);
  std::array<float, 3> arr{1.4F, 3.8F, 0.1F};
  EXPECT_EQ((std::array<float, 3>) vector, arr);
}

TEST(VectorTest, ConvertsToArray3) {
  Vector<4> vector(1.4F, 3.8F, 0.1F, -93.4F);
  std::array<float, 4> arr{1.4F, 3.8F, 0.1F, -93.4F};
  EXPECT_EQ((std::array<float, 4>) vector, arr);
}

TEST(VectorTest, ConvertsToJSON1) {
  Vector<3> vector{1.4F, 3.8F, 0.1F};
  JSON json = {1.4F, 3.8F, 0.1F};
  EXPECT_EQ(vector.to_json(), json);
}

TEST(VectorTest, UnitVector1) {
  Vector<3> raw(1.4F, 3.8F, 0.1F);
  UnitVector<3> v = raw.normalized();

  EXPECT_EQ(v.magnitude(), 1.0F);
  EXPECT_NE(v, raw);
  EXPECT_EQ(v, raw.normalized());
}

TEST(VectorTest, UnitVector2) {
  UnitVector<1> v1;
  UnitVector<2> v2;
  UnitVector<3> v3;
  UnitVector<4> v4;
  UnitVector<5> v5;

  EXPECT_EQ(v1.magnitude(), 1.0F);
  EXPECT_EQ(v2.magnitude(), 1.0F);
  EXPECT_EQ(v3.magnitude(), 1.0F);
  EXPECT_EQ(v4.magnitude(), 1.0F);
  EXPECT_EQ(v5.magnitude(), 1.0F);

  EXPECT_EQ(v1[0], 1.0F);
  EXPECT_EQ(v2[0], 1.0F);
  EXPECT_EQ(v3[0], 1.0F);
  EXPECT_EQ(v4[0], 1.0F);
  EXPECT_EQ(v5[0], 1.0F);
}
