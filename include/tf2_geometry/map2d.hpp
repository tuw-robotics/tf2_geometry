#ifndef TUW2_GEOMETRY__MAP2D_HPP
#define TUW2_GEOMETRY__MAP2D_HPP

#include <Eigen/Dense>
#include <memory>
#include <tuw2_geometry/core.hpp>

namespace tuw2 {

class Map2D; /// Prototype
using Map2DPtr = std::shared_ptr<Map2D>;
using Map2DConstPtr = std::shared_ptr<Map2D const>;

/**
 * class to represent a Map 2D in a 3D space
 **/
class Map2D {
    Plane2D plane_; // plane of the map
    t origin_; // origin on the plane
  public:

    Map2D();

    /**
     * creates the map plane from a point which is also the origin and a normal
     * @param p point on the plane and origin of the map
     * @param n normal of the plane
     **/
    void create(const Vector3 &p, const Vector3 &n);
    
};
}; // namespace tuw2

#endif // TUW2_GEOMETRY__MAP2D_HPP