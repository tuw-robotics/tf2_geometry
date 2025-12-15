#include "tf2_geometry/linesegment2d.hpp"

using namespace tf2;
LineSegment2D::LineSegment2D() {}
LineSegment2D::LineSegment2D(const LineSegment2D & l)
: Line2D(l.line()), p0_(l.p0()), p1_(l.p1())
{
}
LineSegment2D::LineSegment2D(const Point2D & p0, const Point2D & p1)
: Line2D(p0, p1, true), p0_(p0), p1_(p1)
{
}
LineSegment2D::LineSegment2D(
  const tf2Scalar & x0, const tf2Scalar & y0, const tf2Scalar & x1, const tf2Scalar & y1)
: Line2D(x0, y0, x1, y1, true), p0_(x0, y0), p1_(x1, y1)
{
}
const tf2Scalar & LineSegment2D::x0() const {return p0_.x();}
const tf2Scalar & LineSegment2D::y0() const {return p0_.y();}
const tf2Scalar & LineSegment2D::x1() const {return p1_.x();}
const tf2Scalar & LineSegment2D::y1() const {return p1_.y();}
tf2Scalar LineSegment2D::angle() const
{
  tf2Scalar dx = p1_.x() - p0_.x();
  tf2Scalar dy = p1_.y() - p0_.y();
  return tf2Atan2(dy, dx);
}
Point2D LineSegment2D::pc() const
{
  tf2Scalar dx = p1_.x() - p0_.x();
  tf2Scalar dy = p1_.y() - p0_.y();
  return Point2D(p0_.x() + dx / 2., p0_.y() + dy / 2.);
}
const Point2D & LineSegment2D::p0() const {return p0_;}
const Point2D & LineSegment2D::p1() const {return p1_;}
const Line2D & LineSegment2D::line() const {return *this;}

tf2Scalar LineSegment2D::length() const {return p0_.distance_to(p1_);}
/// comparison operator @return true on equal
bool LineSegment2D::operator==(const LineSegment2D & o) const
{
  return p0() == o.p0() && p1() == o.p1();
}
LineSegment2D & LineSegment2D::set(
  const tf2Scalar & x0, const tf2Scalar & y0, const tf2Scalar & x1, const tf2Scalar & y1)
{
  Line2D::create(x0, y0, x1, y1, true);
  p0_.set(x0, y0), p1_.set(x1, y1);
  return *this;
}
LineSegment2D & LineSegment2D::set(const Point2D & p0, const Point2D & p1)
{
  set(p0.x(), p0.y(), p1.x(), p1.y());
  return *this;
}
/** computes distance to line segment
 * @see http://stackoverflow.com/questions/849211/shortest-distance-between-a-point-and-a-line-segment
 * @param p point
 * @param dx vector to point x
 * @param dx vector to point y
 * @return distance to line between the segment endpoints or the distance to the nearest endpoints **/
tf2Scalar LineSegment2D::distance_to(const Point2D & p, tf2Scalar & dx, tf2Scalar & dy) const
{
  return tf2Sqrt(distanceSqrTo(p, dx, dy));
}
/** computes squared distance to line segment
 * @see http://stackoverflow.com/questions/849211/shortest-distance-between-a-point-and-a-line-segment
 * @param p point
 * @param dx vector to point x
 * @param dx vector to point y
 * @return distance to line between the segment endpoints or the distance to the nearest endpoints **/
tf2Scalar LineSegment2D::distanceSqrTo(const Point2D & p, tf2Scalar & dx, tf2Scalar & dy) const
{
  const tf2Scalar px = x1() - x0();
  const tf2Scalar py = y1() - y0();
  const tf2Scalar l2 = px * px + py * py;
  tf2Scalar u = ((p.x() - x0()) * px + (p.y() - y0()) * py) / l2;
  if (u > 1) {
    u = 1;
  } else if (u < 0) {
    u = 0;
  }
  const tf2Scalar xk = x0() + u * px;
  const tf2Scalar yk = y0() + u * py;
  dx = xk - p.x();
  dy = yk - p.y();
  return dx * dx + dy * dy;
}

tf2Scalar LineSegment2D::closestPointLineSegmentRatio(const Point2D & p) const
{
  tf2Scalar px = x1() - x0();
  tf2Scalar py = y1() - y0();
  tf2Scalar l2 = px * px + py * py;
  tf2Scalar u = ((p.x() - x0()) * px + (p.y() - y0()) * py) / l2;
  if (u > 1) {
    u = 1;
  } else if (u < 0) {
    u = 0;
  }
  return u;
}
Point2D LineSegment2D::closestPointTo(const Point2D & p) const
{
  tf2Scalar px = x1() - x0();
  tf2Scalar py = y1() - y0();
  const tf2Scalar u = closestPointLineSegmentRatio(p);
  return Point2D(x0() + u * px, y0() + u * py);
}

/** computes distance to line segment
 * @see http://stackoverflow.com/questions/849211/shortest-distance-between-a-point-and-a-line-segment
 * @param p point
 * @return distance to line between the segment endpoints or the distance to the nearest endpoints **/
tf2Scalar LineSegment2D::distance_to(const Point2D & p) const
{
  tf2Scalar dx, dy;
  return distance_to(p, dx, dy);
}
