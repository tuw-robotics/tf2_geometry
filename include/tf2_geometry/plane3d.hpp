#ifndef TF2_GEOMETRY__PLANE3D_HPP
#define TF2_GEOMETRY__PLANE3D_HPP

#include "tf2/LinearMath/Scalar.hpp"
#include "tf2_geometry/point3d.hpp"
#include "tf2_geometry/vector4.hpp"

namespace tf2 {

/**
 * class to represent a 3D plane as equation a*x + b*y + c*z + d  = 0
 **/
class Plane3D : public Vector4 {
  public:
    // This is the type of the base class
    using Base = Vector4;

    // Inherit constructors (C++11/14 feature)
    using Base::Base;

    /** computes the plane equation, based on three points
     * @param p1
     * @param p2
     * @param p3
     * @param nomalize normalizes the plane normal on true
     **/
    Plane3D(const Point3D &p1, const Point3D &p2, const Point3D &p3, bool normalize = true);

    /** computes the plane equation, based on three points
     * @param p1
     * @param p2
     * @param p3
     * @param nomalize normalizes the plane normal on true
     * @return ref to object
     **/
    Plane3D &create(const Point3D &p1, const Point3D &p2, const Point3D &p3, bool normalize = true);

    /** computes the plane equation, based a point on the plane and the plane normal
     * @param p point on the plane
     * @param n plane normal
     * @return ref to object
     **/
    Plane3D &create(const Point3D &p, const Vector3 &n);

    /** normalizes the plane equation
     * @param p point on the plane
     * @return ref to object
     **/
    Plane3D &nomalize();

    Vector3& normal() {
        return static_cast<Vector3&>(*this);
    }  
    /** Finds a line plane intersection
     * @param src point to project onto plane
     * @param des closest point on plane
     * @return ref to closestPoint des
     **/
    Point3D &closestPointOnPlane(const Point3D &point, Point3D &des) const;

    /** Finds the distance of a point to the plane
     * @param p point
     * @return distance
     **/
    tf2Scalar distanceTo(const Point3D &p) const;

    /** Finds a line plane intersection
     * @param p1 line start
     * @param p2 line end
     * @param intersection intersection point with plane
     * @param epsilon computation tolerance
     * @return true if there is an intersection
     **/
    bool intersectionLine(const Vector3 &p1,
                          const Vector3 &p2,
                          Vector3 &intersection,
                          tf2Scalar epsilon = 0.00001) const;
    

    /**
     * access to first component
     * @return rotation
     **/
    const tf2Scalar &a() const;
    /**
     * access to first component
     * @return rotation
     **/
    tf2Scalar &a();
    /**
     * access to second component
     * @return rotation
     **/
    const tf2Scalar &b() const;
    /**
     * access to second component
     * @return rotation
     **/
    tf2Scalar &b();
    /**
     * access to third component
     * @return rotation
     **/
    const tf2Scalar &c() const;
    /**
     * access to third component
     * @return rotation
     **/
    tf2Scalar &c();

    /**
     * access to forth component
     * @return rotation
     **/
    const tf2Scalar &d() const;
    /**
     * access to forth component
     * @return rotation
     **/
    tf2Scalar &d();

};
} // namespace tf2
#endif // TF2_GEOMETRY__PLANE3D_HPP
