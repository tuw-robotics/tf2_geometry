#include <gtest/gtest.h>
#include "tf2_geometry/plane3d.hpp"

TEST(Plane3D, constructor)
{
  
  double tolerance = 0.001;
  tf2::Point3D p0( 5.0, -1.0,  7.0);
  tf2::Point3D p1(-2.0,  0.0,  6.0);
  tf2::Point3D p2( 2.0,  4.0,  8.0);

  tf2::Plane3D plane0(p0, p1, p2, false);

  ASSERT_NEAR(plane0.a(),   6.0, tolerance);
  ASSERT_NEAR(plane0.b(),  10.0, tolerance);
  ASSERT_NEAR(plane0.c(), -32.0, tolerance);
  ASSERT_NEAR(plane0.d(), 204.0, tolerance);


  tf2::Plane3D plane1(p0, p1, p2, true);
  plane0.nomalize();
}
