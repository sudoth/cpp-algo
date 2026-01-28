#ifndef RAY_H
#define RAY_H
#include <string>

#include "ishape.h"
#include "point.h"
#include "vector.h"
namespace geometry {
class Point;
class Vector;
class Segment;
class Ray : public IShape {
 public:
  Ray() = default;
  Ray(const Point&, const Point&);
  Ray& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  IShape* Clone() const override;
  std::string ToString() const override;
  Point a;
  Vector direction;
};
bool RaySegmentInt(const Ray&, const Segment&);
std::istream& operator>>(std::istream& is, Ray& r);
}
#endif