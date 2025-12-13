#include "tf2_geometry/point3d.hpp"
#include <cmath>
#include <stdexcept> 

using namespace tf2;


Point3D::Point3D(const tf2Scalar &x, const tf2Scalar &y, const tf2Scalar &z) : Base{x, y, z} {}

const tf2Scalar &Point3D::x() const {
    return m_floats[0];
}
tf2Scalar &Point3D::x() {
    return m_floats[0];
}
const tf2Scalar &Point3D::y() const {
    return m_floats[1];
}
tf2Scalar &Point3D::y() {
    return m_floats[1];
}

const tf2Scalar &Point3D::z() const {
    return m_floats[1];
}
tf2Scalar &Point3D::z() {
    return m_floats[1];
}
/**
 * returns the distance to an other point
 * @return disance
 **/
tf2Scalar Point3D::distanceTo(const Point3D &p0) const {
    return distanceTo(p0.x(), p0.y(), p0.z());
}
/**
 * returns the distance to an other point
 * @return disance
 **/
tf2Scalar Point3D::distanceTo(const tf2Scalar &x0, const tf2Scalar &y0, const tf2Scalar &z0) const {
    return  Vector3(x0 - this->x(), y0 - this->y(), z0 - this->z()).length();
}

/**
 * assignment operator from Vector3
 * @param v vector to assign from
 * @return reference to this
 **/
Point3D& Point3D::operator=(const Vector3 &v) {
    m_floats[0] = v.m_floats[0];
    m_floats[1] = v.m_floats[1];
    m_floats[2] = v.m_floats[2];
    m_floats[3] = v.m_floats[3];
    return *this;
}
