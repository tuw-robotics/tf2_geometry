#ifndef TF2_GEOMETRY__ROS_HPP
#define TF2_GEOMETRY__ROS_HPP


#include "tf2/LinearMath/Transform.hpp"
#include "tf2_geometry/transform2d.hpp"
#include "tf2_geometry/line2d.hpp"
#include "tf2_geometry/utils.hpp"

namespace tf2
{


double getYawFromEigenMatrix(const tf2::Matrix3x3& R) {
    // Extract yaw from rotation matrix
    double yaw = std::atan2(R[1][0], R[0][0]);
    return yaw;
}

/** converts a tf2::Transform into a tf2::Transform2D
 * @param des transform2d
 * @param tf tf2::Transform
 * @return reference to des
 **/
TF2SIMD_FORCE_INLINE Transform2D &to_2D(Transform2D &des, const Transform &tf) {
    double roll, pitch, yaw;
    tf.getBasis().getEulerYPR(roll, pitch, yaw);
    des.set(tf.getOrigin().x(), tf.getOrigin().y() , yaw);
    return des;
}

/** converts a tf2::Transform into a tf2::Transform2D
 * @param des transform2d
 * @param tf tf2::Transform
 * @return reference to des
 **/
TF2SIMD_FORCE_INLINE Transform2D to_Transform2D(const Transform &tf) {
    Transform2D des;
    return to_2D(des, tf);
}

/** converts a tf2::Transform into a tf2::Transform2D
 * @param des transform2d
 * @param tf tf2::Transform
 * @return reference to des
 **/
TF2SIMD_FORCE_INLINE Point2D &to_2D(Point2D &des, const Transform &tf) {
    des.set(tf.getOrigin().x(), tf.getOrigin().y());
    return des;
}

/** converts a tf2::Transform into a tf2::Transform2D
 * @param des transform2d
 * @param tf tf2::Transform
 * @return reference to des
 **/
TF2SIMD_FORCE_INLINE Point2D to_Point2D(const Transform &tf) {
    Point2D des;
    return to_2D(des, tf);
}

}  // namespace tf2

#endif  // TF2_GEOMETRY__ROS_HPP
