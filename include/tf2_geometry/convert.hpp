#ifndef TF2_GEOMETRY__ROS_HPP
#define TF2_GEOMETRY__ROS_HPP


#include "tf2/LinearMath/Transform.hpp"
#include "tf2_geometry/transform2d.hpp"
#include "tf2_geometry/line2d.hpp"
#include "tf2_geometry/utils.hpp"

namespace tf2
{


template<typename TMatrix3x3>
TF2SIMD_FORCE_INLINE tf2Scalar getYawFromRotationMatrix(const TMatrix3x3& R) {
    // Extract yaw from rotation matrix
    double yaw = tf2Atan2(R[1][0], R[0][0]);
    return yaw;
}

template<typename TMatrix3x3>
TF2SIMD_FORCE_INLINE tf2Scalar getPitchFromRotationMatrix(const TMatrix3x3& R) {
    // Extract pitch from rotation matrix
    double pitch = tf2Atan2(-R[2][0], tf2Sqrt(R[2][1]*R[2][1] + R[2][2]*R[2][2]));
    return pitch; 
}
template<typename TMatrix3x3>
TF2SIMD_FORCE_INLINE tf2Scalar getRollFromRotationMatrix(const TMatrix3x3& R) {
    // Extract roll from rotation matrix
    double roll = tf2Atan2(R[2][1], R[2][2]);
    return roll; 
}

/** converts a tf2::Transform into a tf2::Transform2D
 * @param src tf2::Transform
 * @param des tf2::Transform2D
 * @return reference to des
 **/
TF2SIMD_FORCE_INLINE Transform2D &to_2D(const Transform &src, Transform2D &des) {
    double roll, pitch, yaw;
    src.getBasis().getRPY(roll, pitch, yaw);
    des.set(src.getOrigin().x(), src.getOrigin().y() , yaw);
    return des;
}

/** converts a tf2::Transform into a tf2::Transform2D
 * @param src tf2::Transform
 * @return tf2::Transform2D object
 **/
TF2SIMD_FORCE_INLINE Transform2D to_Transform2D(const Transform &src) {
    Transform2D des;
    return to_2D(src, des);
}

/** converts a tf2::Transform into a tf2::Transform2D
 * @param src tf2::Transform
 * @param des tf2::Point2D
 * @return reference to des
 **/
TF2SIMD_FORCE_INLINE Point2D &to_2D(const Transform &src, Point2D &des) {
    des.set(src.getOrigin().x(), src.getOrigin().y());
    return des;
}

/** converts a tf2::Transform into a tf2::Transform2D
 * @param src tf2::Transform
 * @return tf2::Point2D object
 **/
TF2SIMD_FORCE_INLINE Point2D to_Point2D(const Transform &src) {
    Point2D des;
    return to_2D(src, des);
}

}  // namespace tf2

#endif  // TF2_GEOMETRY__ROS_HPP
