#ifndef TF2_GEOMETRY__POSE2D_HPP
#define TF2_GEOMETRY__POSE2D_HPP

#include <tf2_geometry/point2d.hpp>
namespace tf2 {

/**
 * class to represent a transform in in 2D space
 * the class caches the cos(theta), sin(theta) values and the inverse translation
 **/
class Transform2D {
  protected:
    Point2D m_translation;                  /// translation t
    double m_rotation;                      /// rotation in rad
    mutable bool m_cache_uptodate;          /// cache uptodate flag, on true the cached values are valid
    mutable double m_costheta, m_sintheta;  /// cached precomputed cos() & sin() of theta.
    mutable Point2D m_translation_inv;      /// cached inverse translation - (Rinv * t)

    /**
     * Updates the cached value of cos(phi), sin(phi) and the inverse translation,
     * recomputing it only once when phi changes.
     **/
    void update_cached() const;

  public:
    /**
     * constructors
     **/
    Transform2D();
    /**
     * constructors
     * @param point
     * @param orientation
     **/
    Transform2D(const Point2D &p, double orientation);
    /**
     * copy constructor
     * @param p transfrom
     **/
    Transform2D(const Transform2D &p);
    /**
     * copy constructor
     * @param x
     * @param y
     * @param orientation
     **/
    Transform2D(double x, double y, double orientation);
    /**
     * copy constructor
     * @param position
     * @param point_ahead
     **/
    Transform2D(const Point2D &position, const Point2D &point_ahead);
    /**
     * defines the transform
     * @param x
     * @param y
     * @param orientation
     * @return this reference
     **/
    Transform2D &set(double x, const double y, double orientation);
    /**
     * set the pose based on two points in world coordinates
     * @param position
     * @param point_ahead
     * @return this reference
     **/
    Transform2D &set(const Point2D &position, const Point2D &point_ahead);

    /**
     * set the pose
     * @param p pose
     * @return this reference
     **/
    Transform2D &set(const Transform2D &p);

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
    const double &rotation() const;

    /**
     * position
     * @return rotation
     **/
    double &rotation();

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
     * @return pose in target frame, a pose in the same frame as the  current pose
     * @see Pose2D::transform_into_base
     * @see Pose2D::transform_into_base
     **/
    Point2D operator*(const Point2D &src) const;

    /**
     * transforms a Pose2D from pose target space into pose base space
     * the orientation will be normalized between -PI and PI
     * @param src pose in pose target space, a pose seen from the current pose
     * @param des pose in pose base space, a pose in the same frame as the  current pose
     * @return pose in target frame, a pose in the same frame as the  current pose
     **/
    Transform2D &transform_into_base(const Transform2D &src, Transform2D &des) const;
    /**
     * transforms a Transform2D from pose target space into pose base space
     * the orientation will be normalized between -PI and PI
     * @param src pose in pose target space, a pose seen from the current pose
     * @return pose in target frame, a pose in the same frame as the  current pose
     **/
    Transform2D transform_into_base(const Transform2D &src) const;

    /**
     * transforms a Transform2D from pose target space into pose base space
     * the orientation will be normalized between -PI and PI
     * @param src pose in pose target space, a pose seen from the current pose
     * @return pose in target frame, a pose in the same frame as the  current pose
     * @see Pose2D::transform_into_base
     **/
    Transform2D operator*(const Transform2D &src) const;

    /**
     * transforms a Transform2D from pose target space into pose base space
     * the orientation will be normalized between -PI and PI
     * @param src pose in pose target space, a pose seen from the current pose
     * @return pose in target frame, updated this
     * @see Pose2D::transform_into_base
     **/
    Transform2D &operator*=(const Transform2D &src);

    /**
     * invert pose
     * @param des inverted pose
     * @return inverted pose
     **/
    Transform2D &inverse(Transform2D &des) const;

    /**
     * invert pose
     * @return inverted pose
     **/
    Transform2D inverse() const;
};
} // namespace tf2
#endif // TF2_GEOMETRY__POSE2D_HPP
