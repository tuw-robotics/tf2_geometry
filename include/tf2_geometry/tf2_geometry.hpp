#ifndef TF2_GEOMETRY__ROS_HPP
#define TF2_GEOMETRY__ROS_HPP


#include "tf2_geometry/transform2d.hpp"
#include "tf2/transform.hpp"

namespace tf2
{
/** converts a tf2::Transform into a tf2::Transform2D
 * @param des transform2d
 * @param tf tf2::Transform
 * @return reference to des
 **/
TF2SIMD_FORCE_INLINE Transform2D &operator=(Transform2D &des, const Transform &tf) {
    Quaternion quat = tf.getRotation();
    double roll, pitch, yaw;
    tf2::Matrix3x3(q).getRPY(roll, pitch, yaw);
    des.set(tf.origin.x(), tf.origin.y(), yaw);
    return des
}

}  // namespace tf2

#endif  // TF2_GEOMETRY__ROS_HPP
