#include "tf2_geometry/vector2.hpp"
#include <cmath>
#include <iomanip>
#include <sstream>

using namespace tf2;

Vector2::Vector2() {
    m_floats[0] = 0.0, m_floats[1] = 0.0, m_floats[2] = 0.0, m_floats[3] = 0.0;
}

Vector2::Vector2(const tf2Scalar &v0, const tf2Scalar &v1) {
    m_floats[0] = v0, m_floats[1] = v1, m_floats[2] = 0.0, m_floats[3] = 0.0;
}

std::string Vector2::to_str(int with, int precision) const {
    std::ostringstream ss;
    ss << std::setw(with) << std::setprecision(precision) << std::fixed << this->m_floats[0] << ", ";
    ss << std::setw(with) << std::setprecision(precision) << std::fixed << this->m_floats[1] << "]";
    return ss.str();
}

Vector2 &Vector2::set(const tf2Scalar &v0, const tf2Scalar &v1) {
    m_floats[0] = v0;
    m_floats[1] = v1;
    return *this;
}
Vector2 &Vector2::set(const Vector2 &v) {
    m_floats[0] = v.m_floats[0];
    m_floats[1] = v.m_floats[1];
    return *this;
}

Vector2 &Vector2::operator+=(const Vector2 &v) {
    m_floats[0] += v.m_floats[0], m_floats[1] += v.m_floats[1];
    return *this;
}

Vector2 &Vector2::operator-=(const Vector2 &v) {
    m_floats[0] -= v.m_floats[0], m_floats[1] -= v.m_floats[1];
    return *this;
}
Vector2 &Vector2::operator*=(const tf2Scalar &s) {
    m_floats[0] *= s, m_floats[1] *= s;
    return *this;
}
Vector2 &Vector2::operator/=(const tf2Scalar &s) {
    tf2FullAssert(s != tf2Scalar(0.0));
    m_floats[0] /= s, m_floats[1] /= s;
    return *this;
}

Vector2 Vector2::operator+(const Vector2 &v) const {
    return Vector2(m_floats[0] + v.m_floats[0], m_floats[1] + v.m_floats[1]);
}

Vector2 Vector2::operator-(const Vector2 &v) const {
    return Vector2(m_floats[0] - v.m_floats[0], m_floats[1] - v.m_floats[1]);
}

Vector2 Vector2::operator-() const {
    return Vector2(-m_floats[0], -m_floats[1]);
}

Vector2 Vector2::operator*(const tf2Scalar &s) const {
    return Vector2(m_floats[0] * s, m_floats[1] * s);
}

Vector2 Vector2::operator/(const tf2Scalar &s) const {
    tf2FullAssert(s != tf2Scalar(0.0));
    return Vector2(m_floats[0] / s, m_floats[1] / s);
}

tf2Scalar Vector2::dot(const Vector2 &v) const {
    return m_floats[0] * v.m_floats[0] + m_floats[1] * v.m_floats[1];
}

tf2Scalar &Vector2::operator[](int index) {

	tf2FullAssert(index >= 0 && index < 2);
    return m_floats[index];
}

const tf2Scalar &Vector2::operator[](int index) const {    
	tf2FullAssert(index >= 0 && index < 2);
    return m_floats[index];
}

tf2Scalar Vector2::angle() const {
    return tf2Atan2(m_floats[1], m_floats[0]);
}

tf2Scalar Vector2::length2() const {
    return m_floats[0] * m_floats[0] + m_floats[1] * m_floats[1];
}

tf2Scalar Vector2::length() const {
    return std::sqrt(this->length2());
}
/**
 * equality operator
 * @param p point to compare with
 * @return true if points are equal
 **/
bool Vector2::operator==(const Vector2 &p) const {
    return (std::fabs(m_floats[0] - p.m_floats[0]) < TF2SIMD_EPSILON) && (std::fabs(m_floats[1] - p.m_floats[1]) < TF2SIMD_EPSILON);
}

/**
 * inequality operator
 * @param p point to compare with
 * @return true if points are not equal
 **/
bool Vector2::operator!=(const Vector2 &p) const {
    return !(*this == p);
}