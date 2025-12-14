#include "tf2_geometry/plane3d.hpp"
#include <cmath>

using namespace tf2;

Plane3D::Plane3D(const Point3D &p1, const Point3D &p2, const Point3D &p3, bool normalize) {
    create(p1, p2, p3, normalize);
}

Plane3D &Plane3D::create(const Point3D &p1, const Point3D &p2, const Point3D &p3, bool normalize) {
    Vector3 d2 = p2 - p1;
    Vector3 d3 = p3 - p1;
    if (normalize)
        this->head() = d2.cross(d3).normalized();
    else
        this->head() = d2.cross(d3);
    (*this)[3] = -((*this)[0] * p1[0] + (*this)[1] * p1[1] + (*this)[2] * p1[2]);
    return *this;
}

Plane3D &Plane3D::create(const Point3D &p, const Vector3 &normal) {
    this->head() = normal.normalized();
    (*this)[3] = -(this->head().dot(p));
    return *this;
}

Plane3D &Plane3D::nomalize() {
    tf2Scalar n = this->head().length();
    (*this)/= n;
    return *this;
}

bool Plane3D::intersection(const Vector3 &p1, const Vector3 &p2, Vector3 &intersection, tf2Scalar epsilon) const {

    auto &n = this->head();
    Vector3 v = p2 - p1;
    tf2Scalar denominator = v[0] * n[0] + v[1] * n[1] + v[2] * n[2];
    if (fabs(denominator) < epsilon) {
        return false;
    }
    tf2Scalar d = (*this)[0] * p1[0] + (*this)[1] * p1[1] + (*this)[2] * p1[2] + (*this)[3];
    tf2Scalar u = d / (-v[0] * n[0] - v[1] * n[1] - v[2] * n[2]);
    intersection = p1 + v * u;
    return true;
}

const tf2Scalar &Plane3D::a() const {
    return this->m_floats[0];
}

tf2Scalar &Plane3D::a() {
    return this->m_floats[0];
}

const tf2Scalar &Plane3D::b() const {
    return this->m_floats[1];
}

tf2Scalar &Plane3D::b() {
    return this->m_floats[1];
}

const tf2Scalar &Plane3D::c() const {
    return this->m_floats[2];
}

tf2Scalar &Plane3D::c() {
    return this->m_floats[2];
}

const tf2Scalar &Plane3D::d() const {
    return this->m_floats[3];
}

tf2Scalar &Plane3D::d() {
    return this->m_floats[3];
}

tf2Scalar Plane3D::distance_to(const Point3D &p) const {
    tf2Scalar distance = this->head().dot(p) + (*this)[3];
    return distance;
}

Point3D &Plane3D::closest_point_on_plane(const Point3D &src, Point3D &des) const {
    des = src - this->head() * this->distance_to(src);
    return des;
}