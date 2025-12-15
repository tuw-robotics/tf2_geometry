#include "gtest/gtest.h"
#include "tf2_geometry/transform2d.hpp"


TEST(pose2d, constructor)
{
  double tolerance = 0.001;
  tf2::Transform2D pose0(3.0, -1.0, M_PI/4.0);
  ASSERT_NEAR(3, pose0.x(), tolerance);
  ASSERT_NEAR(-1, pose0.y(), tolerance);
  ASSERT_NEAR(M_PI/4, pose0.rotation(), tolerance);


  tf2::Point2D p0(3.0, -1.0);
  tf2::Point2D p1(4.0,  0.0);
  tf2::Transform2D pose1(p0, p1);
  ASSERT_NEAR(3, pose0.x(), tolerance);
  ASSERT_NEAR(-1, pose0.y(), tolerance);
  ASSERT_NEAR(M_PI/4, pose0.rotation(), tolerance);
}


TEST(pose2d, transform_into_base)
{
  // Point
  double tolerance = 0.001;
  tf2::Transform2D pose0(3.0, -1.0, M_PI/4.0);
  pose0.recompute_cached_cos_sin();
  tf2::Point2D point_in_target(sqrt(2), 0.0);
  tf2::Point2D point_in_base = pose0.transform_into_base(point_in_target);
  ASSERT_NEAR(4, point_in_base.x(), tolerance);
  ASSERT_NEAR(0, point_in_base.y(), tolerance);
  
  // Pose
  tf2::Transform2D pose_in_target(0.0, sqrt(2)*2, -M_PI/2.0);
  tf2::Transform2D pose_in_base = pose0.transform_into_base(pose_in_target);
  ASSERT_NEAR(1, pose_in_base.x(), tolerance);
  ASSERT_NEAR(1, pose_in_base.y(), tolerance);
  ASSERT_NEAR(-M_PI/4, pose_in_base.rotation(), tolerance);
}


TEST(pose2d, inverse)
{
  // Point
  double tolerance = 0.001;
  tf2::Transform2D pose0(3.0, -1.0, M_PI/4.0);
  pose0.recompute_cached_cos_sin();
  tf2::Transform2D pose0inv = pose0.inverse();
  pose0inv.recompute_cached_cos_sin();
  tf2::Point2D point_in_target(4, 0.0);
  tf2::Point2D point_in_base = pose0inv.transform_into_base(point_in_target);
  ASSERT_NEAR(sqrt(2), point_in_base.x(), tolerance);
  ASSERT_NEAR(0, point_in_base.y(), tolerance);
  
  // Pose
  tf2::Transform2D pose_in_target(0.0, sqrt(2)*2, -M_PI/2.0);
  tf2::Transform2D pose_in_base = pose0.transform_into_base(pose_in_target);
  ASSERT_NEAR(1, pose_in_base.x(), tolerance);
  ASSERT_NEAR(1, pose_in_base.y(), tolerance);
  ASSERT_NEAR(-M_PI/4, pose_in_base.rotation(), tolerance);
}