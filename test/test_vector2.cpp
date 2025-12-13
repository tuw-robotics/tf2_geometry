#include "gtest/gtest.h"
#include "tf2_geometry/vector2.hpp"


TEST(Vector2, constructor)
{
  double tolerance = 0.001;
  tf2::Vector2 v0(1.0, 2.0);
  ASSERT_NEAR(1, v0[0], tolerance);
  ASSERT_NEAR(2, v0[1], tolerance);
}



TEST(Vector2, length)
{
  double tolerance = 0.001;
  tf2::Vector2 v0(3.0, 4.0);
  ASSERT_NEAR(25.0, v0.length2(), tolerance);
  ASSERT_NEAR(5.0, v0.length(), tolerance);
}



TEST(Vector2, math)
{
  double tolerance = 0.001;
  tf2::Vector2 v0(3.0, 4.0);
  tf2::Vector2 v1(3.0, 4.0);
  tf2::Vector2 v2 = v0 + v1;
  ASSERT_NEAR(6, v2[0], tolerance);
  ASSERT_NEAR(8, v2[1], tolerance);
  tf2::Vector2 v3 = v2 / 2.0;
  ASSERT_TRUE( v0 == v3);
  tf2::Vector2 v4 = v0 * 2.0;
  ASSERT_TRUE( v4 == v2);
  tf2::Vector2 v5 = -v0 + (v1 * 3.0);
  ASSERT_TRUE( v5 == v2);
}
