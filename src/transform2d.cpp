#include "tf2_geometry/transform2d.hpp"
#include "tf2_geometry/utils.hpp"
using namespace tf2;

Pose2D::Pose2D() : position_(), orientation_(0) {}
Pose2D::Pose2D(const Point2D &p, tf2Scalar orientation_) : position_(p), orientation_(orientation_), cossin_uptodate_(false) {}
Pose2D::Pose2D(const Pose2D &p) : position_(p.position_), orientation_(p.orientation_), cossin_uptodate_(false) {}
Pose2D::Pose2D(tf2Scalar x, tf2Scalar y, tf2Scalar orientation_) : position_(x, y), orientation_(orientation_), cossin_uptodate_(false) {}

/** set the pose
 * @param x
 * @param y
 * @param phi (orientation_)
 * @return this reference
 **/
Pose2D &Pose2D::set(tf2Scalar x, tf2Scalar y, tf2Scalar phi) {
    angle_normalize(phi, -M_PI, +M_PI);
    position_.set(x, y);
    orientation_ = phi;
    cossin_uptodate_ = false;
    return *this;
}
/**
 * set the pose based on two points in world coordinates
 * @param position
 * @param point_ahead
 * @return this reference
 **/
Pose2D &Pose2D::set(const Point2D &position, const Point2D &point_ahead) {
    position_.set(position.x(), position.y());
    tf2Scalar dx = point_ahead.x() - position.x();
    tf2Scalar dy = point_ahead.y() - position.y();
    orientation_ = atan2(dy, dx);
    cossin_uptodate_ = false;
    return *this;
}
/** set the pose
 * @param p pose
 * @return this reference
 **/
Pose2D &Pose2D::set(const Pose2D &p) {
    position_ = p.position_;
    orientation_ = p.orientation_;
    cossin_uptodate_ = false;
    return *this;
}
/** location as vector
 * @return translational
 **/
const Point2D &Pose2D::position() const {
    return position_;
}

/** translational x component
 * @return x component
 **/
const tf2Scalar &Pose2D::x() const {
    return position_.m_floats[0];
}
/** translational y component
 * @return y component
 **/
const tf2Scalar &Pose2D::y() const {
    return position_.m_floats[1];
}
/** roational component
 * @return rotation
 **/
const tf2Scalar &Pose2D::theta() const {
    return orientation_;
}
/** location as vector
 * @return translational
 **/
Point2D &Pose2D::position() {
    return position_;
}
/** translational x component
 * @return x component
 **/
tf2Scalar &Pose2D::x() {
    return position_.m_floats[0];
}
/** translational y component
 * @return y component
 **/
tf2Scalar &Pose2D::y() {
    return position_.m_floats[1];
}
/** roational component
 * @return rotation
 **/
tf2Scalar &Pose2D::theta() {
    cossin_uptodate_ = false;
    return orientation_;
}

/** normalizes the orientation value betwenn -PI and PI
 **/
void Pose2D::normalize_orientation() {
    angle_normalize(orientation_, -M_PI, +M_PI);
}
/**
 * enforces the recompuation of the cached value of cos(theta) and sin(theta),
 * recomputing it only once when theta changes.
 */
void Pose2D::recompute_cached_cos_sin() const {
    costheta_ = cos(orientation_);
    sintheta_ = sin(orientation_);
    cossin_uptodate_ = true;
}
/**
 * Updates the cached value of cos(phi) and sin(phi),
 * recomputing it only once when phi changes.
 **/
void Pose2D::update_cached_cos_sin() const {
    if (cossin_uptodate_) {
        return;
    }
    recompute_cached_cos_sin();
}
/**
 * transforms a point from pose target space into pose base space
 * @note you have to update the cached cos and sin values in advance
 * @see Pose2D::update_cached_cos_sin
 * @param src point in pose target space, a point seen from the current pose
 * @param des point in pose base space, a point in the same frame as the  current pose
 * @return ref point in pose base space, a point in the same frame as the  current pose
 **/
Point2D &Pose2D::transform_into_base(const Point2D &src, Point2D &des) const {
    des.set(src.x() * costheta_ - src.y() * sintheta_ + 1.0 * x(), src.x() * sintheta_ + src.y() * costheta_ + 1.0 * y());
    return des;
}

/**
 * transforms a Pose2D from pose target space into pose base space
 * the orientation will be normalized between -PI and PI
 * @param src pose in pose target space, a pose seen from the current pose
 * @param des pose in pose base space, a pose in the same frame as the  current pose
 * @return pose in target frame, a pose in the same frame as the  current pose
 **/
Pose2D Pose2D::transform_into_base(const Pose2D &src, Pose2D &des) const {
    transform_into_base(src.position(), des.position());
    des.theta() = angle_normalize(src.theta() + this->theta());
    return des;
}

/**
 * transforms a point from pose target space into pose base space
 * @note you have to update the cached cos and sin values in advance
 * @see Pose2D::update_cached_cos_sin
 * @param src point in pose target space, a point seen from the current pose
 * @return point in pose base space, a point in the same frame as the  current pose
 **/
Point2D Pose2D::transform_into_base(const Point2D &src) const {
    Point2D des;
    return transform_into_base(src, des);
}
/**
 * transforms a Pose2D from pose target space into pose base space
 * the orientation will be normalized between -PI and PI
 * @param src pose in pose target space, a pose seen from the current pose
 * @return pose in target frame, a pose in the same frame as the  current pose
 **/
Point2D Pose2D::operator*(const Point2D &src) const {
    return this->transform_into_base(src);
}

/**
 * transforms a Pose2D from pose target space into pose base space
 * the orientation will be normalized between -PI and PI
 * @param src pose in pose target space, a pose seen from the current pose
 * @return pose in target frame, a pose in the same frame as the  current pose
 **/
Pose2D Pose2D::transform_into_base(const Pose2D &src) const {
    Pose2D des;
    transform_into_base(src.position(), des.position());
    des.theta() = angle_normalize(src.theta() + this->theta());
    return des;
}

/**
 * transforms a Pose2D from pose target space into pose base space
 * the orientation will be normalized between -PI and PI
 * @param src pose in pose target space, a pose seen from the current pose
 * @return pose in target frame, a pose in the same frame as the  current pose
 **/
Pose2D Pose2D::operator*(const Pose2D &src) const {
    return this->transform_into_base(src);
}

/**
 * invert pose
 * @return inverted pose
 **/
Pose2D &Pose2D::inverse(Pose2D &des) const {
    des.set(0, 0, -this->theta());
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
Pose2D Pose2D::inverse() const {
    Pose2D des;
    return inverse(des);
}