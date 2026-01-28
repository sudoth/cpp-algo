#ifndef LINE_H
#define LINE_H
#include <string>

#include "ishape.h"
#include "point.h"
namespace geometry {
class Segment;
class Point;
class Vector;
class Line : public IShape {
 public:
  Line() = default;
  Line(const Point&, const Point&);
  Line& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  IShape* Clone() const override;
  std::string ToString() const override;
  Point a;
  Point b;
};
bool LineSegmentInt(const Line&, const Segment&);
std::istream& operator>>(std::istream&, Line&);
}
#endif