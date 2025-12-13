#ifndef TF2_GEOMETRY__VECTOR2_HPP
#define TF2_GEOMETRY__VECTOR2_HPP

#include "tf2/LinearMath/Scalar.hpp"
#include "tf2/LinearMath/Vector3.hpp"

namespace tf2 {
  
/**
 * class to represent a vector2 based on the tf2::Vector3 which holds 4 components two are unsed
 **/
class Vector2 : protected Vector3 {
  public:
    /**
     * constructor
     **/
    Vector2();

    /**
     * constructor
     * @param x
     * @param y
     **/
    Vector2(const tf2Scalar &v0, const tf2Scalar &v1);

    /**
     * constructor
     * @param x
     * @param y
     **/
    Vector2& set(const tf2Scalar &v0, const tf2Scalar &v1);
    Vector2 &operator+=(const Vector2 &v);

    Vector2 &operator-=(const Vector2 &v);

    Vector2 &operator*=(const tf2Scalar &s);

    Vector2 &operator/=(const tf2Scalar &s);

    Vector2 operator+(const Vector2 &v) const;

    Vector2 operator-(const Vector2 &v) const;

    Vector2 operator-() const;

    Vector2 operator*(const tf2Scalar &s) const;

    Vector2 operator/(const tf2Scalar &s) const;

	  tf2Scalar dot(const Vector2& v) const;
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
     * angle between -PI and +PI
     * @return angle between -PI and +PI
     **/

    tf2Scalar angle() const;
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
    bool operator==(const Vector2 &p) const;

    /**
     * inequality operator
     * @param p point to compare with
     * @return true if points are not equal
     **/
    bool operator!=(const Vector2 &p) const;
};
}; // namespace tf2

#endif // TF2_GEOMETRY__VECTOR2_HPP