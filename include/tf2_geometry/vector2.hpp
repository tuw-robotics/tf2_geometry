#ifndef TF2_GEOMETRY__VECTOR2_HPP
#define TF2_GEOMETRY__VECTOR2_HPP

#include "tf2/LinearMath/Scalar.hpp"
#include "tf2/LinearMath/Vector3.hpp"
#include <string>

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
     * convert to string
     * @param with width of each element
     * @param precision precision of each element
     * @return string representation
     **/
    std::string to_str(int with = 0, int precision = 6) const ;

    /**
     * set point coordinates
     * @param x
     * @param y
     * @return reference to this
     */
    Vector2 &set(const tf2Scalar &x, const tf2Scalar &y);

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


    // Make serialize and deserialize public
    using Vector3::serializeFloat;
    using Vector3::deSerializeFloat;
    using Vector3::serializeDouble;
    using Vector3::deSerializeDouble;
    using Vector3::serialize;
    using Vector3::deSerialize;
    using Vector3::m_floats;

};
}; // namespace tf2

#endif // TF2_GEOMETRY__VECTOR2_HPP