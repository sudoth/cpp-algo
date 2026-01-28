#include "../point.h"

#include <iostream>
#include <string>

#include "../line.h"
#include "../ray.h"
#include "../segment.h"
#include "../vector.h"

namespace geometry {

bool IsOnLine(const Line& line, const Point& c) {
  return VectorProduct(Vector(line.a, line.b), Vector(line.a, c)) == 0;
}

bool IsOnRay(const Ray& ray, const Point& c) {
  return IsOnLine(Line(ray.a, ray.a + ray.direction), c) &&
         ScalarProduct(ray.direction, Vector(ray.a, c)) >= 0;
}

bool IsOnSegment(const Segment& segment, const Point& c) {
  return IsOnRay(Ray(segment.a, segment.b), c) &&
         IsOnRay(Ray(segment.b, segment.a), c);
}

Point::Point(const int64_t& a, const int64_t& b) {
  this->x = a;
  this->y = b;
}

std::istream& operator>>(std::istream& is, Point& p) {
  is >> p.x >> p.y;
  return is;
}

Vector Point::operator-(const Point& other) const {
  const Vector v{this->x - other.x, this->y - other.y};
  return v;
}

Point Point::operator+(const Vector& other) const {
  return Point(this->x + other.x, this->y + other.y);
}

Point& Point::Move(const Vector& move) {
  *this = *this + move;
  return *this;
}

bool Point::ContainsPoint(const Point& other) const {
  return this->x == other.x && this->y == other.y;
}

bool Point::CrossesSegment(const Segment& other) const {
  return IsOnSegment(other, *this);
}

IShape* Point::Clone() const { return new Point(this->x, this->y); }

std::string Point::ToString() const {
  return std::string("Point(" + std::to_string(this->x) + ", " +
                     std::to_string(this->y) + ")");
}
}  // namespace geometry