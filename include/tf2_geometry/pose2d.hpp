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

    /**
     * enforces the recompuation of the cached value of cos(theta) and sin(theta),
     * recomputing it only once when theta changes.
     */
    void recompute_cached_cos_sin() const;

    /**
     * transforms a point from pose target space into pose base space
     * @note you have to update the cached cos and sin values in advance
     * @see Pose2D::update_cached_cos_sin
     * @param src point in pose target space, a point seen from the current pose
     * @param des point in pose base space, a point in the same frame as the  current pose
     * @return ref point in pose base space, a point in the same frame as the  current pose
     **/
    Point2D &transform_into_base(const Point2D &src, Point2D &des) const;

    /**
     * transforms a point from pose target space into pose base space
     * @note you have to update the cached cos and sin values in advance
     * @see Pose2D::update_cached_cos_sin
     * @param src point in pose target space, a point seen from the current pose
     * @return ref point in pose base space, a point in the same frame as the  current pose
     **/
    Point2D transform_into_base(const Point2D &src) const;
    /**
     * transforms a Pose2D from pose target space into pose base space
     * the orientation will be normalized between -PI and PI
     * @param src pose in pose target space, a pose seen from the current pose
     * @param des pose in pose base space, a pose in the same frame as the  current pose
     * @return pose in target frame, a pose in the same frame as the  current pose
     **/
    Pose2D transform_into_base(const Pose2D &src, Pose2D &des) const;
    /**
     * transforms a Pose2D from pose target space into pose base space
     * the orientation will be normalized between -PI and PI
     * @param src pose in pose target space, a pose seen from the current pose
     * @return pose in target frame, a pose in the same frame as the  current pose
     **/
    Pose2D transform_into_base(const Pose2D &src) const;

    /**
     * invert pose
     * @param des inverted pose
     * @return inverted pose
     **/
    Pose2D &inverse(Pose2D &des) const;
    /**
     * invert pose
     * @return inverted pose
     **/
    Pose2D inverse() const;
};
} // namespace tf2
#endif // TF2_GEOMETRY__POSE2D_HPP
