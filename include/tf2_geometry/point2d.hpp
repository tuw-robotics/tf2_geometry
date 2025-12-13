#ifndef TF2_GEOMETRY__POINT2D_HPP
#define TF2_GEOMETRY__POINT2D_HPP

#include "tf2_geometry/vector2.hpp"

namespace tf2 {

/**
 * class to represent a point [x, y]
 **/
class Point2D : public Vector2 {
  public:
    // This is the type of the base class
    using Base = Vector2;

    using Base::Base;

    Point2D(const tf2Scalar &x, const tf2Scalar &y);

    /**
     * x component
     * @return rotation
     **/
    const tf2Scalar &x() const;
    /**
     * x component
     * @return rotation
     **/
    tf2Scalar &x();

    /**
     * x component
     * @return rotation
     **/
    const tf2Scalar &y() const;
    /**
     * x component
     * @return rotation
     **/
    tf2Scalar &y();

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
     * returns the distance to an other point
     * @return disance
     **/
    tf2Scalar distanceTo(const Point2D &p0) const;
    /**
     * returns the distance to an other point
     * @return disance
     **/
    tf2Scalar distanceTo(const tf2Scalar &x0, const tf2Scalar &y0) const;

    /**
     * assignment operator from Vector3
     * @param v vector to assign from
     * @return reference to this
     **/
    Point2D& operator=(const Vector2 &v);

    /**
     * angle form origin to point (alpha in polar space)
     * @see radius
     * @see Polar2D
     * @return angle between -PI and +PI
     **/
    tf2Scalar angle() const;
    /**
     * distance to origin (rho in polar space)
     * @see angle
     * @see Polar2D
     * @return distance
     **/
    tf2Scalar radius() const;

};
}; // namespace tf2

#endif // TF2_GEOMETRY__POINT2D_HPP