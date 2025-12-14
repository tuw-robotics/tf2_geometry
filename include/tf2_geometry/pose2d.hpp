#ifndef TF2_GEOMETRY__POSE2D_HPP
#define TF2_GEOMETRY__POSE2D_HPP

#include <tf2_geometry/point2d.hpp>
namespace tf2 {

/**
 * class to represent a pose in 2D space
 * the class caches the cos(theta) and sin(theta) values
 **/
class Pose2D {
  protected:
    Point2D position_;                   /// position
    double orientation_;                 /// rotation in rad
    mutable double costheta_, sintheta_; // precomputed cos() & sin() of theta.
    mutable bool cossin_uptodate_;

    /**
     * Updates the cached value of cos(phi) and sin(phi),
     * recomputing it only once when phi changes.
     **/
    void update_cached_cos_sin() const;

  public:
    Pose2D();
    Pose2D(const Point2D &p, double orientation);
    Pose2D(const Pose2D &p);
    Pose2D(double x, double y, double orientation);
    /**
     * set the pose
     * @param x
     * @param y
     * @param phi (orientation)
     * @return this reference
     **/
    Pose2D &set(double x, const double y, double phi);
    /**
     * set the pose based on two points in world coordinates
     * @param position
     * @param point_ahead
     * @return this reference
     **/
    Pose2D &set(const Point2D &position, const Point2D &point_ahead);

    /**
     * set the pose
     * @param p pose
     * @return this reference
     **/
    Pose2D &set(const Pose2D &p);

    /**
     * position
     * @return translational
     **/
    const Point2D &position() const;

    /**
     * location as vector
     * @return translational
     **/
    Point2D &position();

    /**
     * point in front of the pose
     * @param d distance ahead
     * @return point
     **/
    const double &x() const;

    /**
     * translational y component
     * @return y component
     **/
    double &x();

    /**
     * translational y component
     * @return y component
     **/
    const double &y() const;

    /**
     * rotational component
     * @return rotation
     **/
    double &y();

    /**
     * rotational component
     * @return rotation
     **/
    const double &theta() const;

    /**
     * position
     * @return rotation
     **/
    double &theta();

    /**
     * normalizes the orientation value betwenn -PI and PI
     **/
    void normalize_orientation();
};
} // namespace tf2
#endif // TF2_GEOMETRY__POSE2D_HPP
