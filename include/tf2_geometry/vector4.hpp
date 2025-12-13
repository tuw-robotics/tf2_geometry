#ifndef TF2_GEOMETRY__VECTOR2_HPP
#define TF2_GEOMETRY__VECTOR2_HPP

#include "tf2/LinearMath/Scalar.hpp"
#include "tf2/LinearMath/Vector3.hpp"

namespace tf2 {

/**
 * class to represent a vector4 based on the tf2::Vector3 which holds 4 components
 **/
class Vector4 : protected Vector3 {
  public:
    // This is the type of the base class
    using Base = Vector3;

    /**
     * constructor
     **/
    Vector4();
    /**
     * constructor
     * @param v0
     * @param v1
     * @param v2
     * @param v3
     **/
    Vector4(const tf2Scalar &v0, const tf2Scalar &v1, const tf2Scalar &v2, const tf2Scalar &v3);

    Vector4 &operator+=(const Vector4 &v);

    Vector4 &operator-=(const Vector4 &v);

    Vector4 &operator*=(const tf2Scalar &s);

    Vector4 &operator/=(const tf2Scalar &s);

    Vector4 operator+(const Vector4 &v) const;

    Vector4 operator-(const Vector4 &v) const;

    Vector4 operator-() const;

    Vector4 operator*(const tf2Scalar &s) const;

    Vector4 operator/(const tf2Scalar &s) const;

	  tf2Scalar dot(const Vector4& v) const;
    /**
     * access to the underlying data Point2D::m_floats
     * @return Point2D::m_floats[index]
     **/
    tf2Scalar &operator[](int index);

    /**
     * access to the underlying data Point2D::m_floats
     * @return Point2D::m_floats[index]
     **/
    const tf2Scalar &operator[](int index) const;

    /**
     * vector length squared
     * @return length
     **/
    tf2Scalar length2() const;

    /**
     * vector length
     * @return length
     **/
    tf2Scalar length() const;

    /**
     * equality operator
     * @param p point to compare with
     * @return true if points are equal
     **/
    bool operator==(const Vector4 &p) const;

    /**
     * inequality operator
     * @param p point to compare with
     * @return true if points are not equal
     **/
    bool operator!=(const Vector4 &p) const;

    /**
     * returns a reference to the first three elements as Vector3
     * @return reference to the first three elements as Vector3
     **/
    const Vector3 &head() const;

    /**
     * returns a reference to the first three elements as Vector3
     * @return reference to the first three elements as Vector3
     **/
    Vector3 &head();

};
}; // namespace tf2

#endif // TF2_GEOMETRY__VECTOR2_HPP