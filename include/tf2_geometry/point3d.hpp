#ifndef TF2_GEOMETRY__POINT3D_HPP
#define TF2_GEOMETRY__POINT3D_HPP

#include "tf2/LinearMath/Vector3.hpp"

namespace tf2 {

/**
 * class to represent a point [x, y, z]
 **/
class Point3D : public Vector3 {
  public:
    // This is the type of the base class
    using Base = Vector3;

    using Base::Base;

    Point3D(const tf2Scalar &x, const tf2Scalar &y, const tf2Scalar &z);

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
     * y component
     * @return rotation
     **/
    const tf2Scalar &y() const;
    /**
     * y component
     * @return rotation
     **/
    tf2Scalar &y();

    /**
     * z component
     * @return rotation
     **/
    const tf2Scalar &z() const;
    /**
     * z component
     * @return rotation
     **/
    tf2Scalar &z();

    /**
     * returns the distance to an other point
     * @return disance
     **/
    tf2Scalar distanceTo(const Point3D &p0) const;

    /**
     * returns the distance to an other point
     * @return disance
     **/
    tf2Scalar distanceTo(const tf2Scalar &x0, const tf2Scalar &y0, const tf2Scalar &z0) const;

    /**
     * assignment operator from Vector3
     * @param v vector to assign from
     * @return reference to this
     **/
    Point3D& operator=(const Vector3 &v);

};
}; // namespace tf2

#endif // TF2_GEOMETRY__POINT2D_HPP