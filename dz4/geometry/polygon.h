#ifndef POLYGON_H
#define POLYGON_H
#include <string>
#include <vector>

#include "ishape.h"
namespace geometry {
class Point;
class Polygon : public IShape {
 public:
  Polygon() = default;
  Polygon(const std::vector<Point>&);  //  NOLINT
  Polygon& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  IShape* Clone() const override;
  std::string ToString() const override;
  std::vector<Point> vertices;
  std::size_t n;
};
bool IsInside(const Polygon&, const Point&);
std::istream& operator>>(std::istream& is, Polygon& p);
}
#endif