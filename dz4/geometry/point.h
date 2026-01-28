#ifndef POINT_H
#define POINT_H
#include <iostream>
#include <memory>
#include <string>

#include "ishape.h"
namespace geometry {
class Line;
class Ray;
class Segment;
class Point : public IShape {
 public:
  Point() = default;
  Point(const int64_t&, const int64_t&);
  Vector operator-(const Point&) const;
  Point operator+(const Vector&) const;
  Point& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  IShape* Clone() const override;
  std::string ToString() const override;
  int64_t x;
  int64_t y;
};
std::istream& operator>>(std::istream&, Point&);
bool IsOnLine(const Line&, const Point&);
bool IsOnRay(const Ray&, const Point&);
bool IsOnSegment(const Segment&, const Point&);
}
#endif