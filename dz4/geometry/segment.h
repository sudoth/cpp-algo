#ifndef SEGMENT_H
#define SEGMENT_H
#include <string>

#include "ishape.h"
#include "point.h"
namespace geometry {
class Segment;
class Segment : public IShape {
 public:
  Segment() = default;
  Segment(const Point&, const Point&);
  Segment& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  IShape* Clone() const override;
  std::string ToString() const override;
  Point a;
  Point b;
};
std::istream& operator>>(std::istream&, Segment&);
bool IsCollinear(const geometry::Segment&, const geometry::Segment&);
bool IsPointOnLine(const Segment&, const Segment&);
bool IsIntersection(const Segment&, const Segment&);
bool Intersection(const Segment&, const Segment&);
}

#endif