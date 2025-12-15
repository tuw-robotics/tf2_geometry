#ifndef TF2_GEOMETRY__LINESEGMENT2D_HPP
#define TF2_GEOMETRY__LINESEGMENT2D_HPP

#include "tf2_geometry/line2d.hpp"

namespace tf2
{

/**
 * class to represent a 2D line with its endpoints and as equation a*x + b*y + c = 0
 **/
class LineSegment2D : public Line2D
{
protected:
  Point2D p0_, p1_;  /// the lines endpoints

public:
    // This is the type of the base class
    using Base = Line2D;
  /// constructor
  LineSegment2D();
  /**
     * copy constructor
     * @param l LineSegment2D
     **/
  LineSegment2D(const LineSegment2D & l);
  /**
     * constructor to create a line from points
     * @param p0
     * @param p1
     **/
  LineSegment2D(const Point2D & p0, const Point2D & p1);
  /**
     * constructor to create a line from points
     * @param x0
     * @param y0
     * @param x1
     * @param y1
     **/
  LineSegment2D(const tf2Scalar & x0, const tf2Scalar & y0, const tf2Scalar & x1, const tf2Scalar & y1);
  /**
     * @return startpoint x
     **/
  const tf2Scalar & x0() const;
  /**
     * @return startpoint y
     **/
  const tf2Scalar & y0() const;
  /**
     * @return endpoint x
     **/
  const tf2Scalar & x1() const;
  /**
     * @return endpoint y
     **/
  const tf2Scalar & y1() const;
  /**
     * orientation of the line in space
     * @retun angle between -PI and PI
     **/
  tf2Scalar angle() const;
  /**
     * @return startpoint
     **/
  const Point2D & p0() const;
  /**
     * @return endpoint
     **/
  const Point2D & p1() const;
  /**
     * @return center point between p0 and p1
     **/
  Point2D pc() const;
  /**
     * @return the line function of the base class
     **/
  const Line2D & line() const;
  /**
     * @return length of the line
     **/
  tf2Scalar length() const;
  /**
     * comparison operator
     * @return true on equal
     **/
  bool operator==(const LineSegment2D & o) const;
  /**
     * sets a line from points
     * @param x0
     * @param y0
     * @param x1
     * @param y1
     **/
  LineSegment2D & set(const tf2Scalar & x0, const tf2Scalar & y0, const tf2Scalar & x1, const tf2Scalar & y1);
  /**
     * sets a line from points
     * @param p0
     * @param p1
     **/
  LineSegment2D & set(const Point2D & p0, const Point2D & p1);
  /** computes distance to line segment
     * @see http://stackoverflow.com/questions/849211/shortest-distance-between-a-point-and-a-line-segment
     * @param p point
     * @param dx vector to point x
     * @param dx vector to point y
     * @return distance to line between the segment endpoints or the distance to the nearest endpoints
     **/
  tf2Scalar distance_to(const Point2D & p, tf2Scalar & dx, tf2Scalar & dy) const;
  /** computes distance to line segment
     * @see http://stackoverflow.com/questions/849211/shortest-distance-between-a-point-and-a-line-segment
     * @param p point
     * @param dx vector to point x
     * @param dx vector to point y
     * @return distance to line between the segment endpoints or the distance to the nearest endpoints
     **/
  tf2Scalar distanceSqrTo(const Point2D & p, tf2Scalar & dx, tf2Scalar & dy) const;

  tf2Scalar closestPointLineSegmentRatio(const Point2D & p) const;
  /** computes closest point along segment
     * @param p point
     * @return closest point along segment to the given point
     **/
  Point2D closestPointTo(const Point2D & p) const;
  /** computes distance to line segment
     * @see http://stackoverflow.com/questions/849211/shortest-distance-between-a-point-and-a-line-segment
     * @return distance to line between the segment endpoints or the distance to the nearest endpoints
     **/
  tf2Scalar distance_to(const Point2D & p) const;
};

}  // namespace tf2
#endif  // TF2_GEOMETRY__LINESEGMENT2D_HPP
