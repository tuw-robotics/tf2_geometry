#include "tf2_geometry/pose2d.hpp"
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