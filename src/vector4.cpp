#include "tf2_geometry/vector4.hpp"
#include <cmath>
#include <stdexcept>

using namespace tf2;

Vector4::Vector4() : Base() {
    ;
}

Vector4::Vector4(const tf2Scalar &v0, const tf2Scalar &v1, const tf2Scalar &v2, const tf2Scalar &v3) {
    m_floats[0] = v0, m_floats[1] = v1, m_floats[2] = v2, m_floats[3] = v3;
}

tf2Scalar &Vector4::operator[](int index) {
    if (index < 0 || index >= 4) {
        throw std::out_of_range("Index out of bounds in Vector4::operator[]");
    }
    return m_floats[index];
}

const tf2Scalar &Vector4::operator[](int index) const {
    if (index < 0 || index >= 4) {
        throw std::out_of_range("Index out of bounds in Vector4::operator[] const");
    }
    return m_floats[index];
}

tf2Scalar Vector4::length2() const {
    return this->dot(*this);
}

tf2Scalar Vector4::length() const {
    return tf2Sqrt(this->length2());
}

const Vector3 &Vector4::head() const {
    return static_cast<const Vector3 &>(*this);
}

Vector3 &Vector4::head() {
    return static_cast<Vector3 &>(*this);
}

Vector4 &Vector4::operator+=(const Vector4 &v) {
    m_floats[0] += v.m_floats[0], m_floats[1] += v.m_floats[1], m_floats[2] += v.m_floats[2], m_floats[3] += v.m_floats[3];
    return *this;
}

Vector4 &Vector4::operator-=(const Vector4 &v) {
    m_floats[0] -= v.m_floats[0], m_floats[1] -= v.m_floats[1], m_floats[2] -= v.m_floats[2], m_floats[3] -= v.m_floats[3];
    return *this;
}
Vector4 &Vector4::operator*=(const tf2Scalar &s) {
    m_floats[0] *= s, m_floats[1] *= s, m_floats[2] *= s, m_floats[3] *= s;
    return *this;
}
Vector4 &Vector4::operator/=(const tf2Scalar &s) {
    tf2FullAssert(s != tf2Scalar(0.0));
    m_floats[0] /= s, m_floats[1] /= s, m_floats[2] /= s, m_floats[3] /= s;
    return *this;
}

Vector4 Vector4::operator+(const Vector4 &v) const {
    return Vector4(m_floats[0] + v.m_floats[0], m_floats[1] + v.m_floats[1], m_floats[2] + v.m_floats[2], m_floats[3] + v.m_floats[3]);
}

Vector4 Vector4::operator-(const Vector4 &v) const {
    return Vector4(m_floats[0] - v.m_floats[0], m_floats[1] - v.m_floats[1], m_floats[2] - v.m_floats[2], m_floats[3] - v.m_floats[3]);
}

Vector4 Vector4::operator-() const {
    return Vector4(-m_floats[0], -m_floats[1], -m_floats[2], -m_floats[3]);
}

Vector4 Vector4::operator*(const tf2Scalar &s) const {
    return Vector4(m_floats[0] * s, m_floats[1] * s, m_floats[2] * s, m_floats[3] * s);
}

Vector4 Vector4::operator/(const tf2Scalar &s) const {
    tf2FullAssert(s != tf2Scalar(0.0));
    return Vector4(m_floats[0] / s, m_floats[1] / s, m_floats[2] / s, m_floats[3] / s);
}

tf2Scalar Vector4::dot(const Vector4 &v) const {
    return m_floats[0] * v.m_floats[0] + m_floats[1] * v.m_floats[1] + m_floats[2] * v.m_floats[2] + m_floats[3] * v.m_floats[3];
}

bool Vector4::operator==(const Vector4 &p) const {
    const tf2Scalar epsilon = 1e-9;
    return (std::fabs(m_floats[0] - p.m_floats[0]) < epsilon) && (std::fabs(m_floats[1] - p.m_floats[1]) < epsilon) &&
           (std::fabs(m_floats[2] - p.m_floats[2]) < epsilon) && (std::fabs(m_floats[3] - p.m_floats[3]) < epsilon);
}

bool Vector4::operator!=(const Vector4 &p) const {
    return !(*this == p);
}