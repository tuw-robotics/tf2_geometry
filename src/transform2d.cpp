#include "tf2_geometry/transform2d.hpp"
#include "tf2_geometry/utils.hpp"
using namespace tf2;

Transform2D::Transform2D() : m_translation(), m_rotation(0) {}

Transform2D::Transform2D(const Point2D &p, tf2Scalar orientation_) : m_translation(p), m_rotation(orientation_), m_cache_uptodate(false) {}

Transform2D::Transform2D(const Transform2D &p) : m_translation(p.m_translation), m_rotation(p.m_rotation), m_cache_uptodate(false) {}

Transform2D::Transform2D(tf2Scalar x, tf2Scalar y, tf2Scalar orientation_) : m_translation(x, y), m_rotation(orientation_), m_cache_uptodate(false) {}

Transform2D::Transform2D(const Point2D &position, const Point2D &point_ahead)
    : m_translation(position), m_rotation((point_ahead - position).angle()), m_cache_uptodate(false) {}


Transform2D &Transform2D::set(tf2Scalar x, tf2Scalar y, tf2Scalar rotation) {
    m_translation.set(x, y);
    m_rotation = rotation;
    m_cache_uptodate = false;
    return *this;
}

Transform2D &Transform2D::set(const Point2D &position, tf2Scalar rotation){
    m_translation.set(position);
    m_rotation = rotation;
    m_cache_uptodate = false;
    return *this;
}

Transform2D &Transform2D::set(const Point2D &position, const Point2D &point_ahead) {
    m_translation.set(position.x(), position.y());
    m_rotation = (point_ahead - position).angle();
    m_cache_uptodate = false;
    return *this;
}
Transform2D &Transform2D::set(const Transform2D &p) {
    m_translation = p.m_translation;
    m_rotation = p.m_rotation;
    m_cache_uptodate = false;
    return *this;
}
const Point2D &Transform2D::position() const {
    return m_translation;
}

const tf2Scalar &Transform2D::x() const {
    return m_translation.m_floats[0];
}

void Transform2D::set_x(const tf2Scalar x) {
    this->m_translation.m_floats[0] = x;
    m_cache_uptodate = false;
}

const tf2Scalar &Transform2D::y() const {
    return m_translation.m_floats[1];
}

void Transform2D::set_y(const tf2Scalar y) {
    this->m_translation.m_floats[1] = y;
    m_cache_uptodate = false;
}

const tf2Scalar &Transform2D::rotation() const {
    return m_rotation;
}

void Transform2D::set_rotation(const tf2Scalar roation) {
    this->m_rotation = roation;
    m_cache_uptodate = false;
}

void Transform2D::normalize_orientation() {
    angle_normalize(m_rotation, -M_PI, +M_PI);
}

void Transform2D::recompute_cached_cos_sin() const {
    m_costheta = tf2Cos(m_rotation);
    m_sintheta = tf2Sin(m_rotation);
    Point2D t(m_translation.x() * m_costheta + m_translation.y() * m_sintheta, -m_translation.x() * m_sintheta + m_translation.y() * m_costheta);
    m_translation_inv = -t;
    m_cache_uptodate = true;
}

void Transform2D::update_cached() const {
    if (m_cache_uptodate) {
        return;
    }
    recompute_cached_cos_sin();
}

Point2D &Transform2D::transform_into_target(const Point2D &src, Point2D &des) const {
    this->update_cached();
    des.set(src.x() * m_costheta + src.y() * m_sintheta + m_translation_inv.x(), -src.x() * m_sintheta + src.y() * m_costheta + m_translation_inv.y());
    return des;
}

Point2D Transform2D::transform_into_target(const Point2D &src) const {
    Point2D des;
    return this->transform_into_target(src, des);
}

Point2D &Transform2D::transform_into_base(const Point2D &src, Point2D &des) const {
    this->update_cached();
    des.set(src.x() * m_costheta - src.y() * m_sintheta + m_translation.x(), src.x() * m_sintheta + src.y() * m_costheta + m_translation.y());
    return des;
}

Point2D Transform2D::transform_into_base(const Point2D &src) const {
    Point2D des;
    return transform_into_base(src, des);
}

Point2D Transform2D::operator*(const Point2D &src) const {
    return this->transform_into_base(src);
}

Transform2D &Transform2D::transform_into_target(const Transform2D &src, Transform2D &des) const {
    this->transform_into_target(src.m_translation, des.m_translation);
    des.m_rotation = angle_normalize(src.m_rotation - this->m_rotation);
    des.m_cache_uptodate = false;
    return des;
}

Transform2D Transform2D::transform_into_target(const Transform2D &src) const {
    Transform2D des;
    return transform_into_target(src, des);
}

Transform2D Transform2D::operator/(const Transform2D &src) const {
    return this->transform_into_target(src);
}

Transform2D &Transform2D::operator/=(const Transform2D &src) {
    update_cached();
    return src.transform_into_target(*this, *this);
}

Transform2D &Transform2D::transform_into_base(const Transform2D &src, Transform2D &des) const {
    this->transform_into_base(src.m_translation, des.m_translation);
    des.m_rotation = angle_normalize(src.m_rotation + this->m_rotation);
    des.m_cache_uptodate = false;
    return des;
}

Transform2D Transform2D::transform_into_base(const Transform2D &src) const {
    Transform2D des;
    return transform_into_base(src, des);
}

Transform2D Transform2D::operator*(const Transform2D &src) const {
    return this->transform_into_base(src);
}

Transform2D &Transform2D::operator*=(const Transform2D &src) {
    update_cached();
    return src.transform_into_base(*this, *this);
}

Transform2D &Transform2D::inverse(Transform2D &des) const {
    this->update_cached();
    des.set(this->m_translation_inv, -this->m_rotation);
    return des;
}
Transform2D Transform2D::inverse() const {
    Transform2D des;
    return inverse(des);
}