#include "../circle.h"

#include <cmath>

#include "../line.h"
#include "../segment.h"
#include "../vector.h"
namespace geometry {

double Distant(const Point& a, const Point& b) {
  return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool IsInSector(const Segment& segment, const Point& point) {
  return ScalarProduct(Vector(segment.a, segment.b),
                       Vector(segment.a, point)) >= 0 &&
         ScalarProduct(Vector(segment.b, segment.a),
                       Vector(segment.b, point)) >= 0;
}

double LineDistant(const Line& line, const Point& c) {
  return (std::abs(VectorProduct(Vector(line.a, line.b), Vector(line.a, c))) /
          std::sqrt((line.a.x - line.b.x) * (line.a.x - line.b.x) +
                    (line.a.y - line.b.y) * (line.a.y - line.b.y)));
}

bool IsIntersection(const Segment& segment, const Circle& circle) {
  return ((IsInSector(segment, circle.a)
               ? LineDistant(Line(segment.a, segment.b), circle.a)
               : std::min(Distant(segment.a, circle.a),
                          Distant(segment.b, circle.a))) <= circle.radius);
}

Circle::Circle(const Point& a, const int64_t& radius) {
  this->a = a;
  this->radius = radius;
}

std::istream& operator>>(std::istream& is, Circle& c) {
  is >> c.a >> c.radius;
  return is;
}

Circle& Circle::Move(const Vector& move) {
  a = a + move;
  return *this;
}

bool Circle::ContainsPoint(const Point& point) const {
  return ((this->a.x - point.x) * (this->a.x - point.x) +
              (this->a.y - point.y) * (this->a.y - point.y) <=
          radius * radius);
}

bool Circle::CrossesSegment(const Segment& segment) const {
  if ((Distant(segment.a, this->a) >= this->radius &&
       Distant(segment.b, this->a) <= this->radius) ||
      (Distant(segment.a, this->a) <= this->radius &&
       Distant(segment.b, this->a) >= this->radius)) {
    return true;
  }
  if (Distant(segment.a, this->a) >= this->radius &&
      (Distant(segment.b, this->a) >= this->radius)) {
    return IsIntersection(segment, *this);
  }
  return false;
}

IShape* Circle::Clone() const { return new Circle(this->a, this->radius); }

std::string Circle::ToString() const {
  return std::string("Circle(" + a.ToString() + ", " + std::to_string(radius) +
                     ")");
}
}  // namespace geometry