#include "gtest/gtest.h"
#include "tf2_geometry/vector4.hpp"


TEST(Vector4, constructor)
{
  double tolerance = 0.001;
  tf2::Vector4 v0(1.0, 2.0, 3.0, 4.0);
  ASSERT_NEAR(1, v0[0], tolerance);
  ASSERT_NEAR(2, v0[1], tolerance);
  ASSERT_NEAR(3, v0[2], tolerance);
  ASSERT_NEAR(4, v0[3], tolerance);
}

TEST(Vector4, length)
{
  double tolerance = 0.001;
  tf2::Vector4 v0(3.0, 4.0, 5.0, 6.0);
  ASSERT_NEAR(86.0, v0.length2(), tolerance);
  ASSERT_NEAR(std::sqrt(86), v0.length(), tolerance);
}

TEST(Vector4, head)
{
  double tolerance = 0.001;
  tf2::Vector4 v0(3.0, 4.0, 5.0, 6.0);
  v0.head() = tf2::Vector3(1.0, 2.0, 3.0);
  ASSERT_NEAR(1, v0[0], tolerance);
  ASSERT_NEAR(2, v0[1], tolerance);
  ASSERT_NEAR(3, v0[2], tolerance);
}


TEST(Vector4, math)
{
  double tolerance = 0.001;
  tf2::Vector4 v0(3.0, 4.0, 5.0, 6.0);
  tf2::Vector4 v1(3.0, 4.0, 5.0, 6.0);
  tf2::Vector4 v2 = v0 + v1;
  ASSERT_NEAR(6, v2[0], tolerance);
  ASSERT_NEAR(8, v2[1], tolerance);
  ASSERT_NEAR(10, v2[2], tolerance);
  ASSERT_NEAR(12, v2[3], tolerance);
  tf2::Vector4 v3 = v2 / 2.0;
  ASSERT_TRUE( v0 == v3);
  tf2::Vector4 v4 = v0 * 2.0;
  ASSERT_TRUE( v4 == v2);
  tf2::Vector4 v5 = -v0 + (v1 * 3.0);
  ASSERT_TRUE( v5 == v2);
}
