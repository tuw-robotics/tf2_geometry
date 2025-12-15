#include "gtest/gtest.h"
#include "tf2_geometry/linesegment2d.hpp"


TEST(Linesegment2D, constructor)
{
  double tolerance = 0.001;
  tf2::LineSegment2D l(1.0, 2.0, 3.0, 5.0);
  ASSERT_NEAR(-0.8320, l.a(), tolerance);
  ASSERT_NEAR(+0.5547, l.b(), tolerance);
  ASSERT_NEAR(-0.2773, l.c(), tolerance);
}


TEST(Linesegment2D, distanceTo)
{
  double tolerance = 0.001;
  tf2::LineSegment2D l(1.0, 2.0, 3.0, 5.0);
  ASSERT_NEAR( 1.0, l.distance_to(tf2::Point2D(1,1)), tolerance);
  ASSERT_NEAR(tf2::Vector2(1,2).length(), l.distance_to(tf2::Point2D(2,7)), tolerance);
}