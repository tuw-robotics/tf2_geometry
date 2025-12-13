#include "tuw2_geometry/map2d.hpp"
#include <cmath>

using namespace tuw2;

Map2D::Map2D() : plane_(), origin_(Matrix3S::Identity()) {}

void Map2D::create(const Vector3 &p, const Vector3 &n) {
    plane_.create(p, n);
    origin_ << 1.0, 0.0, p[0], 0.0, 1.0, p[1], 0.0, 0.0, 1.0;
}

Point2D tuw2::toMap(const Vector3 &p) {
    Vector3 ph = map.origin_ * p;
    return Point2D(ph[0] / ph[2], ph[1] / ph[2]);
}