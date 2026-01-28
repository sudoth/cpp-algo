#ifndef CIRCLE_H
#define CIRCLE_H
#include <string>

#include "ishape.h"
#include "point.h"
namespace geometry {
class Vector;
class Segment;
class Circle : public IShape {
 public:
  Circle() = default;
  Circle(const Point&, const int64_t&);
  Circle& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  IShape* Clone() const override;
  std::string ToString() const override;
  Point a;
  int64_t radius;
};
std::istream& operator>>(std::istream&, Circle&);
double Distant(const Point&, const Point&);
double LineDistant(const Line&, const Point&);
bool IsInSector(const Segment&, const Point&);
bool IsIntersection(const Segment&, const Circle&);
}
#endif