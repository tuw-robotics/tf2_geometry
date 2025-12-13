#ifndef Tf2_GEOMETRY__UTILS_HPP
#define Tf2_GEOMETRY__UTILS_HPP


#include <tf2_geometry/core.hpp>

namespace tuw2
{

/**
 * normalizes an angle between min_angle and max_angle but max_angle - min_angle >= 2PI
 * @param angle to normalize
 * @param min_angle
 * @param max_angle
 * @return normalize angle
 **/
inline tf2Scalar angle_normalize(tf2Scalar angle, tf2Scalar min_angle = -M_PI, tf2Scalar max_angle = +M_PI)
{
  while (angle > max_angle) {
    angle -= (2. * M_PI);
  }
  while (angle < min_angle) {
    angle += (2. * M_PI);
  }
  return angle;
}
/**
 * computes the angle difference between two angles by taking into account the circular space
 * @param alpha0
 * @param angle1
 * @return difference
 **/
inline tf2Scalar angle_difference(tf2Scalar alpha0, tf2Scalar angle1)
{
  return atan2(sin(alpha0 - angle1), cos(alpha0 - angle1));
}

/**
 * Euler Pitch to Quaternion roation arount Y
 * @see https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
 **/
template<typename Quaternion>
void EulerPitchToQuaternion(tf2Scalar pitch, Quaternion & q)
{
  tf2Scalar cp = cos(pitch * 0.5);
  tf2Scalar sp = sin(pitch * 0.5);

  q.w = cp;
  q.x = 0;
  q.y = sp;
  q.z = 0;
}

/**
 * Euler Roll to Quaternion roation arount X
 * @see https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
 **/
template<typename Quaternion>
void EulerToQuaternion(tf2Scalar roll, const Quaternion & q)
{
  tf2Scalar cr = cos(roll * 0.5);
  tf2Scalar sr = sin(roll * 0.5);

  q.w = cr;
  q.x = sr;
  q.y = 0.;
  q.z = 0.;
}

/**
 * Euler Yaw to Quaternion rotation around Z
 * @see https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
 **/
template<typename Quaternion>
void EulerYawToQuaternion(tf2Scalar yaw, Quaternion & q)
{
  tf2Scalar cy = cos(yaw * 0.5);
  tf2Scalar sy = sin(yaw * 0.5);

  q.w = cy;
  q.x = 0.;
  q.y = 0.;
  q.z = sy;
}

/**
 * Euler to Quaternion
 * @see https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
 **/
template<typename Quaternion>
void EulerToQuaternion(tf2Scalar pitch, tf2Scalar roll, tf2Scalar yaw, Quaternion & q)
{
  tf2Scalar cy = cos(yaw * 0.5);
  tf2Scalar sy = sin(yaw * 0.5);
  tf2Scalar cr = cos(roll * 0.5);
  tf2Scalar sr = sin(roll * 0.5);
  tf2Scalar cp = cos(pitch * 0.5);
  tf2Scalar sp = sin(pitch * 0.5);

  q.w = cy * cr * cp + sy * sr * sp;
  q.x = cy * sr * cp - sy * cr * sp;
  q.y = cy * cr * sp + sy * sr * cp;
  q.z = sy * cr * cp - cy * sr * sp;
  return q;
}

/**
 * Quaternion to an euler roll angle
 * @see https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
 * @param q Quaterion with x,y,z and w public members
 * @param roll angle to compute
 * @return angle to computed
 **/
template<typename Quaternion>
tf2Scalar & QuaternionToRoll(const Quaternion & q, tf2Scalar & roll)
{
  // roll (x-axis rotation)
  tf2Scalar sinr = +2.0 * (q.w * q.x + q.y * q.z);
  tf2Scalar cosr = +1.0 - 2.0 * (q.x * q.x + q.y * q.y);
  roll = atan2(sinr, cosr);
  return roll;
}
/**
 * Quaternion to an euler roll angle
 * @see https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
 * @param q Quaterion with x,y,z and w public members
 * @return angle to computed
 **/
template<typename Quaternion>
tf2Scalar QuaternionToRoll(const Quaternion & q)
{
  tf2Scalar roll;
  return QuaternionToYaw(q, roll);
}
/**
 * Quaternion to an euler pitch angle
 * @see https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
 * @param q Quaterion with x,y,z and w public members
 * @param pitch angle to compute
 * @return angle to computed
 **/
template<typename Quaternion>
tf2Scalar & QuaternionToPitch(const Quaternion & q, tf2Scalar & pitch)
{
  // pitch (y-axis rotation)
  tf2Scalar sinp = +2.0 * (q.w * q.y - q.z * q.x);
  if (fabs(sinp) >= 1) {
    pitch = copysign(M_PI / 2, sinp);  // use 90 degrees if out of range
  } else {
    pitch = asin(sinp);
  }
  return pitch;
}
/**
 * Quaternion to an euler pitch angle
 * @see https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
 * @param q Quaterion with x,y,z and w public members
 * @param pitch angle to compute
 * @return angle to computed
 **/
template<typename Quaternion>
tf2Scalar QuaternionToPitch(const Quaternion & q)
{
  tf2Scalar pitch;
  return QuaternionToYaw(q, pitch);
}
/**
 * Quaternion to an euler yaw angle
 * @see https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
 * @param q Quaterion with x,y,z and w public members
 * @param yaw angle to compute
 * @return angle to computed
 **/
template<typename Quaternion>
tf2Scalar & QuaternionToYaw(const Quaternion & q, tf2Scalar & yaw)
{
  // yaw (z-axis rotation)
  tf2Scalar siny = +2.0 * (q.w * q.z + q.x * q.y);
  tf2Scalar cosy = +1.0 - 2.0 * (q.y * q.y + q.z * q.z);
  yaw = atan2(siny, cosy);
  return yaw;
}
/**
 * Quaternion to an euler yaw angle
 * @see https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
 * @param q Quaterion with x,y,z and w public members
 * @return yaw angle to compute
 **/
template<typename Quaternion>
tf2Scalar QuaternionToYaw(const Quaternion & q)
{
  tf2Scalar yaw;
  return QuaternionToYaw(q, yaw);
}

/**
 * Quaternion to euler angles
 * @see https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
 **/
template<typename Quaternion>
void QuaternionToEuler(const Quaternion & q, tf2Scalar & roll, tf2Scalar & pitch, tf2Scalar & yaw)
{
  QuaternionToRoll(q, roll), QuaternionToPitch(q, pitch), QuaternionToYaw(q, yaw);
}

}  // namespace tf2

#endif  // Tf2_GEOMETRY__UTILS_HPP
