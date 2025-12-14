#ifndef TF2_GEOMETRY__LINE2D_HPP
#define TF2_GEOMETRY__LINE2D_HPP

#include <memory>
#include <tf2_geometry/point2d.hpp>
#include <tf2/LinearMath/Vector3.hpp>

namespace tf2 {


/**
 * class to represent a line equation
 **/
class Line2D : public Vector3 {
  public:
    // This is the type of the base class
    using Base = Vector3;

    // Inherit constructors (C++11/14 feature)
    using Base::Base;
    /**
     * constructor
     **/
    Line2D();
    /**
     * constructor with optional normalization
     * @param l equation
     * @param normalize normalizes equation on true
     **/
    Line2D(Vector3 &l, bool normalize = true);
    /**
     * constructor to create a line from points
     * @param p0
     * @param p1
     * @param normalize normalizes equation on true
     **/
    Line2D(const Point2D &p0, const Point2D &p1, bool normalize = true);
    /**
     * constructor to create a line from points
     * @param x0
     * @param y0
     * @param x1
     * @param y1
     * @param normalize normalizes equation on true
     * @return ref to this
     **/
    Line2D(const tf2Scalar &x0, const tf2Scalar &y0, const tf2Scalar &x1, const tf2Scalar &y1, bool normalize = true);
    /**
     * creates a line from points
     * @param x0
     * @param y0
     * @param x1
     * @param y1
     * @param normalize normalizes equation on true
     * @return ref to this
     **/
    Line2D &create(const tf2Scalar &x0, const tf2Scalar &y0, const tf2Scalar &x1, const tf2Scalar &y1, bool normalize = true);
    
    
    /**
     * creates a line from points
     * @param p1
     * @param p2
     * @param normalize normalizes equation on true
     * @return ref to this
     **/
    Line2D &create(const Point2D &p0, const Point2D &p1, bool normalize = true);

    /**
     * convert to string
     * @param with width of each element
     * @param precision precision of each element
     * @return string representation
     **/
    std::string to_str(int with = 0, int precision = 6) const ;
    
    /**
     * computes the distance to a point
     * @param x
     * @param y
     * @returns the minimal distance to a point
     * @pre normalize
     **/
    tf2Scalar distance_to(const tf2Scalar &x, const tf2Scalar &y) const;
    /**
     * computes the distance to a point
     * @param p
     * @returns the minimal distance to a point
     * @pre normalize
     **/
    tf2Scalar distance_to(const Point2D &p) const;
    /**
     * computes a point on the line with the shortest distance to the point given
     * @param x
     * @param y
     * @returns point on line
     * @pre normalize
     **/
    Point2D point_on_line(const tf2Scalar &x, const tf2Scalar &y) const;
    /**
     * computes a point on the line with the shortest distance to the point given
     * @param p
     * @returns point on line
     * @pre normalize
     **/
    Point2D point_on_line(const Point2D &p) const;

    /**
     * computes the intersection point of two lines
     * @param l
     * @returns point on line
     * @pre normalize
     **/
    Point2D intersection(const Line2D &l) const;

    /**
     * restuns the normal vector to a line
     * @return vector
     **/
    Vector2 normal() const;
    /**
     * restuns the direction vector to a line
     * @return vector
     **/
    Vector2 direction() const;
    /**
     * normalizes the equation to a*a + b*b = 1
     **/
    void normalize();
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
};
}; // namespace tuw2

#endif // TF2_GEOMETRY__LINE2D_HPP