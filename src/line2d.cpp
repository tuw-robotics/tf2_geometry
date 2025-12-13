#include "tf2_geometry/line2d.hpp"
#include <cmath>

using namespace tf2;

Line2D::Line2D() : Base(0.0, 0.0, 0.0) {}

Line2D::Line2D(Vector3 &l, bool normalize) : Base(l) {
    if (normalize) {
        this->normalize();
    }
}
Line2D::Line2D(const tf2Scalar &x0, const tf2Scalar &y0, const tf2Scalar &x1, const tf2Scalar &y1, bool normalize) {
    create(x0, y0, x1, y1, normalize);
}

Line2D &Line2D::create(const tf2Scalar &x0, const tf2Scalar &y0, const tf2Scalar &x1, const tf2Scalar &y1, bool normalize) {
    this->a() = y0 - y1, this->b() = x1 - x0, this->c() = x0 * y1 - y0 * x1; /// cross product with homogenios vectors
    if (normalize) {
        this->normalize();
    }
    return *this;
}

Line2D &Line2D::create(const Point2D &p0, const Point2D &p1, bool normalize) {
    return create(p0.x(), p0.y(), p1.x(), p1.y(), normalize);
}

tf2Scalar Line2D::distanceTo(const tf2Scalar &x, const tf2Scalar &y) const {
    return this->a() * x + this->b() * y + this->c();
}

tf2Scalar Line2D::distanceTo(const Point2D &p) const {
    return distanceTo(p.x(), p.y());
}

Point2D Line2D::pointOnLine(const tf2Scalar &x, const tf2Scalar &y) const {
    tf2Scalar d = distanceTo(x, y);
    return Point2D(x - d * a(), y - d * b());
}

Point2D Line2D::pointOnLine(const Point2D &p) const {
    return pointOnLine(p.x(), p.y());
}

Point2D Line2D::intersection(const Line2D &l) const {
    Vector3 h = this->cross(l);
    return Point2D(h[0] / h[2], h[1] / h[2]);
}

Vector2 Line2D::normal() const {
    return Vector2(this->a(), this->b());
}

Vector2 Line2D::direction() const {
    return Vector2(this->b(), -this->a());
}

void Line2D::normalize() {
    tf2Scalar r = std::sqrt(this->a() * this->a() + this->b() * this->b());
    this->a() /= r, this->b() /= r, this->c() /= r;
}

const tf2Scalar &Line2D::a() const {
    return this->m_floats[0];
}
tf2Scalar &Line2D::a() {
    return this->m_floats[0];
}
const tf2Scalar &Line2D::b() const {
    return this->m_floats[1];
}
tf2Scalar &Line2D::b() {
    return this->m_floats[1];
}
const tf2Scalar &Line2D::c() const {
    return this->m_floats[2];
}
tf2Scalar &Line2D::c() {
    return this->m_floats[2];
}