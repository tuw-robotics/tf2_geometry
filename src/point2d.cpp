#include "tf2_geometry/point2d.hpp"
#include <cmath>
#include <stdexcept> 

using namespace tf2;


Point2D::Point2D(const tf2Scalar &x, const tf2Scalar &y) : Base{x, y} {}

const tf2Scalar &Point2D::x() const {
    return m_floats[0];
}
tf2Scalar &Point2D::x() {
    return m_floats[0];
}
const tf2Scalar &Point2D::y() const {
    return m_floats[1];
}
tf2Scalar &Point2D::y() {
    return m_floats[1];
}

/**
 * returns the distance to an other point
 * @return disance
 **/
tf2Scalar Point2D::distanceTo(const Point2D &p0) const {
    return distanceTo(p0.x(), p0.y());
}
/**
 * returns the distance to an other point
 * @return disance
 **/
tf2Scalar Point2D::distanceTo(const tf2Scalar &x0, const tf2Scalar &y0) const {
    return  Vector2(x0 - this->x(), y0 - this->y()).length();
}

Point2D& Point2D::operator=(const Vector2 &v) {
    m_floats[0] = v[0];
    m_floats[1] = v[1];
    return *this;
}