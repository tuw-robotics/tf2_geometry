#include "gtest/gtest.h"
#include "tf2_geometry/line2d.hpp"


TEST(Line2D, constructor)
{
  double tolerance = 0.001;
  tf2::Line2D l(1.0, 2.0, 3.0, 5.0);
  ASSERT_NEAR(-0.8320, l[0], tolerance);
  ASSERT_NEAR(+0.5547, l[1], tolerance);
  ASSERT_NEAR(-0.2773, l[2], tolerance);
}



TEST(Line2D, distanceTo)
{
  double tolerance = 0.001;
  tf2::Line2D l(2.0, -2.0, 2.0, 2.0);
  ASSERT_NEAR( 1.0, l.distance_to(tf2::Point2D(1,0)), tolerance);
  ASSERT_NEAR( 0.0, l.distance_to(tf2::Point2D(2,0)), tolerance);
  ASSERT_NEAR(-1.0, l.distance_to(tf2::Point2D(3,0)), tolerance);
}

TEST(Line2D, pointOnLine)
{
  tf2::Line2D l(2.0, -2.0, 2.0, 2.0);
  ASSERT_TRUE( tf2::Point2D(2,0) == l.point_on_line(tf2::Point2D(1,0)));
}