#ifndef TF2_GEOMETRY__POSE2D_HPP
#define TF2_GEOMETRY__POSE2D_HPP

#include <tf2_geometry/point2d.hpp>
namespace tf2 {

/**
 * class to represent a transform in in 2D space from a parent frame to a child frame
 * the class caches the cos(theta), sin(theta) values and the inverse translation
 **/
class Transform2D {
  protected:
    Point2D m_translation;                    /// translation t
    tf2Scalar m_rotation;                     /// rotation in rad
    mutable bool m_cache_uptodate;            /// cache uptodate flag, on true the cached values are valid
    mutable tf2Scalar m_costheta, m_sintheta; /// cached precomputed cos() & sin() of theta.
    mutable Point2D m_translation_inv;        /// cached inverse translation - (Rinv * t)

    /**
     * Updates the cached value of cos(rotation), sin(rotation) and the inverse translation,
     * recomputing it only once when rotation or translation changes.
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
     * @param roation
     **/
    Transform2D(const Point2D &p, tf2Scalar roation);
    /**
     * copy constructor
     * @param p transfrom
     **/
    Transform2D(const Transform2D &p);
    /**
     * constructor
     * @param x
     * @param y
     * @param roation
     **/
    Transform2D(tf2Scalar x, tf2Scalar y, tf2Scalar roation);
    /**
     * constructor
     * @param position
     * @param point_ahead
     **/
    Transform2D(const Point2D &position, const Point2D &point_ahead);
    /**
     * sets the transform
     * @param x
     * @param y
     * @param roation
     * @return this reference
     **/
    Transform2D &set(tf2Scalar x, const tf2Scalar y, tf2Scalar roation);
    /**
     * sets the transform
     * @param position
     * @param roation
     * @return this reference
     **/
    Transform2D &set(const Point2D &position, tf2Scalar roation);
    /**
     * sets the transform
     * @param position
     * @param point_ahead
     * @return this reference
     **/
    Transform2D &set(const Point2D &position, const Point2D &point_ahead);

    /**
     * sets the transform
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
     * point in front of the pose
     * @param d distance ahead
     * @return point
     **/
    const tf2Scalar &x() const;

    /**
     * sets the x component
     * @param x
     **/
    void set_x(const tf2Scalar x);

    /**
     * translational y component
     * @return y component
     **/
    const tf2Scalar &y() const;

    /**
     * sets the y component
     * @param y
     **/
    void set_y(const tf2Scalar y);

    /**
     * rotational component
     * @return rotation
     **/
    const tf2Scalar &rotation() const;

    /**
     * sets the rotational component
     * @param rotation
     **/
    void set_rotation(const tf2Scalar roation);

    /**
     * normalizes the roation value betwenn -PI and PI
     **/
    void normalize_roation();

    /**
     * enforces the recompuation of the cached value of cos(theta) and sin(theta),
     * recomputing it only once when theta changes.
     */
    void recompute_cached_cos_sin() const;

    /**
     * transforms a point from transform parent frame into the child frame
     * it uses the cached inverse transform internally
     * @param src point in transform parent frame
     * @param des point in transform child frame
     * @return ref point in transform child frame
     **/
    Point2D &transform_into_child(const Point2D &src, Point2D &des) const;
    /**
     * transforms a point from transform parent frame into the child frame
     * it uses the cached inverse transform internally
     * @param src point in transform parent frame
     * @return ref point in transform child frame
     **/
    Point2D transform_into_child(const Point2D &src) const;

    /**
     * transforms a point from transfrom child frame space into the parent frame
     * @param src point in transform child frame
     * @param des point in transform parent frame
     * @return ref point in transform parent frame
     **/
    Point2D &transform_into_parent(const Point2D &src, Point2D &des) const;

    /**
     * transforms a point from transfrom child frame space into the parent frame
     * @param src point in transform child frame
     * @return ref point in transform parent frame
     **/
    Point2D transform_into_parent(const Point2D &src) const;

    /**
     * transforms a point from transfrom child frame space into the parent frame
     * @param src point in transform child frame
     * @return ref point in point parent frame
     **/
    Point2D operator*(const Point2D &src) const;

    /**
     * transforms a transform/pose from parent frame space into the child frame
     * it uses the cached inverse transform internally
     * e.g this = base_link -> scan, src = base_link -> object, des = scan -> object
     * @param src transform with child same as current parent frame
     * @param des transform in parent frame
     * @return pose in parent frame
     **/
    Transform2D &transform_into_child(const Transform2D &src, Transform2D &des) const;

    /**
     * transforms a transform/pose from parent frame space into the child frame
     * it uses the cached inverse transform internally
     * e.g this = base_link -> scan, src = base_link -> object, des = scan -> object
     * @param src transform with child same as current parent frame
     * @return pose in parent frame
     **/
    Transform2D transform_into_child(const Transform2D &src) const;

    /**
     * transforms a transform/pose from parent frame space into the child frame
     * it uses the cached inverse transform internally
     * e.g this = base_link -> scan, src = base_link -> object, des = scan -> object
     * @param src transform with child same as current parent frame
     * @return pose in parent frame
     **/
    Transform2D operator/(const Transform2D &src) const;

    /**
     * transforms a transform/pose from parent frame space into the child frame
     * it uses the cached inverse transform internally
     * e.g this = base_link -> scan, src = base_link -> object, des = scan -> object
     * @param src transform with child same as current parent frame
     * @return pose in parent frame
     **/
    Transform2D &operator/=(const Transform2D &src);

    /**
     * transforms a transform/pose from child frame space into the parent frame
     * e.g this = base_link -> scan, src = scan -> object, des = base_link -> object
     * @param src transform with parent same as current child frame
     * @param des transform in child frame
     * @return pose in child frame
     **/
    Transform2D &transform_into_parent(const Transform2D &src, Transform2D &des) const;
    /**
     * transforms a transform/pose from child frame space into the parent frame
     * e.g this = base_link -> scan, src = scan -> object, des = base_link -> object
     * @param src transform with parent same as current child frame
     * @return pose in child frame
     **/
    Transform2D transform_into_parent(const Transform2D &src) const;

    /**
     * transforms a transform/pose from child frame space into the parent frame
     * e.g this = base_link -> scan, src = scan -> object, des = base_link -> object
     * @param src transform with parent same as current child frame
     * @return pose in child frame
     **/
    Transform2D operator*(const Transform2D &src) const;

    /**
     * transforms a transform/pose from child frame space into the parent frame
     * e.g this = base_link -> scan, src = scan -> object, des = base_link -> object
     * @param src transform with parent same as current child frame
     * @return pose in child frame
     **/
    Transform2D &operator*=(const Transform2D &src);

    /**
     * invert transform
     * @param des inverted transform
     * @return inverted transform
     **/
    Transform2D &inverse(Transform2D &des) const;

    /**
     * invert transform
     * @return inverted transform
     **/
    Transform2D inverse() const;
};

TF2SIMD_FORCE_INLINE Point2D &operator*=(Point2D &des, const Transform2D &tf) {
    return tf.transform_into_parent(des, des);
}
TF2SIMD_FORCE_INLINE Point2D &operator/=(Point2D &des, const Transform2D &tf) {
    return tf.transform_into_child(des, des);
}

} // namespace tf2
#endif // TF2_GEOMETRY__POSE2D_HPP
