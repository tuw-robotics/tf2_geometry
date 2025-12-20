#include "gtest/gtest.h"
#include <random>
#include <cmath>
#include <array>
#include "tf2_geometry/convert.hpp"


TEST(convert, getAnglesFromRotationMatrix)
{
  std::mt19937 gen(std::random_device{}());
  std::uniform_real_distribution<double> dis(-M_PI, M_PI);
  tf2::Matrix3x3 R;
  tf2Scalar roll, pitch, yaw;

  tf2Scalar tolerance = 0.001;
  std::vector<std::array<tf2Scalar, 3>> rpy;
  // boardercases
  rpy.push_back({0., 0., 0.});
  rpy.push_back({M_PI/4., 0., M_PI / 3.});
  rpy.push_back({0, M_PI_4, 0.3});

  for (int i = 0; i < 1000; i++)
    rpy.push_back({dis(gen), dis(gen), dis(gen)});
  
  for(auto rot: rpy){
    R.setRPY(rot[0], rot[1], rot[2]);
    R.getRPY(roll, pitch, yaw);
    tf2Scalar r = getRollFromRotationMatrix(R);
    tf2Scalar p = getPitchFromRotationMatrix(R);
    tf2Scalar y = getYawFromRotationMatrix(R);
    ASSERT_NEAR(r, roll, tolerance);
    ASSERT_NEAR(p, pitch, tolerance);
    ASSERT_NEAR(y, yaw, tolerance);
  }
}

