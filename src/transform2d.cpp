#include "tf2_geometry/transform2d.hpp"
#include "tf2_geometry/utils.hpp"
using namespace tf2;

Transform2D::Transform2D() : m_translation(), m_rotation(0) {}

Transform2D::Transform2D(const Point2D &p, tf2Scalar orientation_) : m_translation(p), m_rotation(orientation_), m_cache_uptodate(false) {}

Transform2D::Transform2D(const Transform2D &p) : m_translation(p.m_translation), m_rotation(p.m_rotation), m_cache_uptodate(false) {}

Transform2D::Transform2D(tf2Scalar x, tf2Scalar y, tf2Scalar orientation_) : m_translation(x, y), m_rotation(orientation_), m_cache_uptodate(false) {}

Transform2D::Transform2D(const Point2D &position, const Point2D &point_ahead)
    : m_translation(position), m_rotation((point_ahead - position).angle()), m_cache_uptodate(false) {}

/** set the pose
 * @param x
 * @param y
 * @param phi (orientation_)
 * @return this reference
 **/
Transform2D &Transform2D::set(tf2Scalar x, tf2Scalar y, tf2Scalar phi) {
    angle_normalize(phi, -M_PI, +M_PI);
    m_translation.set(x, y);
    m_rotation = phi;
    m_cache_uptodate = false;
    return *this;
}
/**
 * set the pose based on two points in world coordinates
 * @param position
 * @param point_ahead
 * @return this reference
 **/
Transform2D &Transform2D::set(const Point2D &position, const Point2D &point_ahead) {
    m_translation.set(position.x(), position.y());
    m_rotation = (point_ahead - position).angle();
    m_cache_uptodate = false;
    return *this;
}
/** set the pose
 * @param p pose
 * @return this reference
 **/
Transform2D &Transform2D::set(const Transform2D &p) {
    m_translation = p.m_translation;
    m_rotation = p.m_rotation;
    m_cache_uptodate = false;
    return *this;
}
/** location as Point2D
 * @return translational
 **/
const Point2D &Transform2D::position() const {
    return m_translation;
}

/** translational x component
 * @return x component
 **/
const tf2Scalar &Transform2D::x() const {
    return m_translation.m_floats[0];
}
/** translational y component
 * @return y component
 **/
const tf2Scalar &Transform2D::y() const {
    return m_translation.m_floats[1];
}
/** roational component
 * @return rotation
 **/
const tf2Scalar &Transform2D::rotation() const {
    return m_rotation;
}
/** location as Point2D
 * @return translational
 **/
Point2D &Transform2D::position() {
    return m_translation;
}
/** translational x component
 * @return x component
 **/
tf2Scalar &Transform2D::x() {
    return m_translation.m_floats[0];
}
/** translational y component
 * @return y component
 **/
tf2Scalar &Transform2D::y() {
    return m_translation.m_floats[1];
}
/** roational component
 * @return rotation
 **/
tf2Scalar &Transform2D::rotation() {
    return m_rotation;
}

/** normalizes the orientation value betwenn -PI and PI
 **/
void Transform2D::normalize_orientation() {
    angle_normalize(m_rotation, -M_PI, +M_PI);
}
/**
 * enforces the recompuation of the cached value of cos(theta) and sin(theta),
 * recomputing it only once when theta changes.
 */
void Transform2D::recompute_cached_cos_sin() const {
    m_costheta = tf2Cos(m_rotation);
    m_sintheta = tf2Sin(m_rotation);
    Point2D t(m_translation.x() * m_costheta + m_translation.y() * m_sintheta, -m_translation.x() * m_sintheta + m_translation.y() * m_costheta);
    m_translation_inv = -t;
    m_cache_uptodate = true;
}
/**
 * Updates the cached value of cos(phi) and sin(phi),
 * recomputing it only once when phi changes.
 **/
void Transform2D::update_cached() const {
    if (m_cache_uptodate) {
        return;
    }
    recompute_cached_cos_sin();
}
/**
 * transforms a point from pose target space into pose base space
 * @note you have to update the cached cos and sin values in advance
 * @see Transform2D::update_cached_cos_sin
 * @param src point in pose target space, a point seen from the current pose
 * @param des point in pose base space, a point in the same frame as the  current pose
 * @return ref point in pose base space, a point in the same frame as the  current pose
 **/
Point2D &Transform2D::transform_into_base(const Point2D &src, Point2D &des) const {
    des.set(src.x() * m_costheta - src.y() * m_sintheta + 1.0 * x(), src.x() * m_sintheta + src.y() * m_costheta + 1.0 * y());
    return des;
}
/**
 * transforms a point from pose target space into pose base space
 * @note you have to update the cached cos and sin values in advance
 * @see Transform2D::update_cached_cos_sin
 * @param src point in pose target space, a point seen from the current pose
 * @return point in pose base space, a point in the same frame as the  current pose
 **/
Point2D Transform2D::transform_into_base(const Point2D &src) const {
    Point2D des;
    return transform_into_base(src, des);
}
/**
 * transforms a Transform2D from pose target space into pose base space
 * the orientation will be normalized between -PI and PI
 * @param src pose in pose target space, a pose seen from the current pose
 * @return pose in target frame, a pose in the same frame as the  current pose
 **/
Point2D Transform2D::operator*(const Point2D &src) const {
    return this->transform_into_base(src);
}

/**
 * transforms a Transform2D from pose target space into pose base space
 * the orientation will be normalized between -PI and PI
 * @param src pose in pose target space, a pose seen from the current pose
 * @param des pose in pose base space, a pose in the same frame as the  current pose
 * @return pose in target frame, a pose in the same frame as the  current pose
 **/
Transform2D& Transform2D::transform_into_base(const Transform2D &src, Transform2D &des) const {
    update_cached();
    transform_into_base(src.m_translation, des.m_translation);
    des.m_rotation = angle_normalize(src.m_rotation + this->m_rotation);
    des.m_cache_uptodate = false;
    return des;
}

/**
 * transforms a Transform2D from pose target space into pose base space
 * the orientation will be normalized between -PI and PI
 * @param src pose in pose target space, a pose seen from the current pose
 * @return pose in target frame, a pose in the same frame as the  current pose
 **/
Transform2D Transform2D::transform_into_base(const Transform2D &src) const {
    Transform2D des;
    return transform_into_base(src, des);
}

/**
 * transforms a Transform2D from pose target space into pose base space
 * the orientation will be normalized between -PI and PI
 * @param src pose in pose target space, a pose seen from the current pose
 * @return pose in target frame, a pose in the same frame as the  current pose
 **/
Transform2D Transform2D::operator*(const Transform2D &src) const {
    return this->transform_into_base(src);
}

/**
 * transforms a Transform2D from pose target space into pose base space
 * the orientation will be normalized between -PI and PI
 * @param src pose in pose target space, a pose seen from the current pose
 * @return pose in target frame, updated this
 * @see Pose2D::transform_into_base
 **/
Transform2D &Transform2D::operator*=(const Transform2D &src) {
    return this->transform_into_base(src, *this);
}

/**
 * invert pose
 * @return inverted pose
 **/
Transform2D &Transform2D::inverse(Transform2D &des) const {
    this->update_cached();
    des.set(0, 0, -this->m_rotation);
    des.recompute_cached_cos_sin();
    Point2D tmp;
    des.transform_into_base(this->position(), tmp);
    des.position() = -tmp;
    return des;
}
/**
 * invert pose
 * @return inverted pose
 **/
Transform2D Transform2D::inverse() const {
    Transform2D des;
    return inverse(des);
}