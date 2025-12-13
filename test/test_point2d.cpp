#include <gtest/gtest.h>
#include "tf2_geometry/point2d.hpp"

TEST(Point2D, constructor)
{
  tf2::Point2D p(3.0,1.4);
  p.x() = 3.0;
  p.y() = 1.4;
  ASSERT_TRUE(p.x() == 3.0);
  ASSERT_TRUE(p.y() == 1.4);
}

TEST(Point2D, distance_to)
{
  tf2::Point2D p0(3.0,1.4);
  tf2::Point2D p1(1.0,1.4);
  tf2Scalar d = p0.distanceTo(p1);
  ASSERT_TRUE((d == 2.0));
}
