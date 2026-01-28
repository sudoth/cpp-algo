#include "../line.h"

#include <string>

#include "../segment.h"
#include "../vector.h"
namespace geometry {
bool LineSegmentInt(const Line& line, const Segment& segment) {
  if (IsOnLine(line, segment.a) || IsOnLine(line, segment.b)) {
    return true;
  }
  if (VectorProduct(Vector(line.a, line.b), Vector(line.a, segment.a)) > 0 &&
      VectorProduct(Vector(line.a, line.b), Vector(line.a, segment.b)) < 0) {
    return true;
  }
  if (VectorProduct(Vector(line.a, line.b), Vector(line.a, segment.a)) < 0 &&
      VectorProduct(Vector(line.a, line.b), Vector(line.a, segment.b)) > 0) {
    return true;
  }
  return false;
}

Line::Line(const Point& a, const Point& b) {
  this->a = a;
  this->b = b;
}

std::istream& operator>>(std::istream& is, Line& l) {
  is >> l.a >> l.b;
  return is;
}

Line& Line::Move(const Vector& move) {
  a = a + move;
  b = b + move;
  return *this;
}

bool Line::ContainsPoint(const Point& point) const {
  return IsOnLine(*this, point);
}

bool Line::CrossesSegment(const Segment& segment) const {
  return LineSegmentInt(*this, segment);
}

IShape* Line::Clone() const { return new Line(this->a, this->b); }

std::string Line::ToString() const {
  int64_t a_k = a.y - b.y;
  int64_t b_k = b.x - a.x;
  int64_t c_k = b.y * (a.x - b.x) - b.x * (a.y - b.y);
  return std::string("Line(" + std::to_string(a_k) + ", " +
                     std::to_string(b_k) + ", " + std::to_string(c_k) + ")");
}
}  // namespace geometry