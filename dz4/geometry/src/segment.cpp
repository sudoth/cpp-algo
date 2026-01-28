#include "../segment.h"

#include <string>

#include "../vector.h"
namespace geometry {
template <typename T>
int64_t Sgn(const T& val) {
  return val >= T(0) ? 1 : -1;
}

bool IsPointOnLine(const Segment& segment1, const Segment& segment2) {
  return (
      IsOnSegment(segment1, segment2.a) || IsOnSegment(segment1, segment2.b) ||
      IsOnSegment(segment2, segment1.a) || IsOnSegment(segment2, segment1.b));
}

bool IsCollinear(const Segment& segment1, const Segment& segment2) {
  return (VectorProduct(Vector(segment1.a, segment1.b),
                        Vector(segment1.a, segment2.a)) == 0 &&
          VectorProduct(Vector(segment1.a, segment1.b),
                        Vector(segment1.a, segment2.b)) == 0 &&
          VectorProduct(Vector(segment2.a, segment2.b),
                        Vector(segment2.a, segment1.a)) == 0 &&
          VectorProduct(Vector(segment2.a, segment2.b),
                        Vector(segment2.a, segment1.b)) == 0);
}

bool IsIntersection(const Segment& segment1, const Segment& segment2) {
  return (Sgn(VectorProduct(Vector(segment1.a, segment1.b),
                            Vector(segment1.a, segment2.a))) *
              Sgn(VectorProduct(Vector(segment1.a, segment1.b),
                                Vector(segment1.a, segment2.b))) <
          0) &&
         ((Sgn(VectorProduct(Vector(segment2.a, segment2.b),
                             Vector(segment2.a, segment1.a))) *
               Sgn(VectorProduct(Vector(segment2.a, segment2.b),
                                 Vector(segment2.a, segment1.b))) <
           0));
}

bool Intersection(const Segment& segment1, const Segment& segment2) {
  if (IsPointOnLine(segment1, segment2)) {
    return true;
  }
  if (IsCollinear(segment1, segment2)) {
    return VectorProduct(Vector(segment1.a, segment2.a),
                         Vector(segment2.a, segment1.b)) ||
           VectorProduct(Vector(segment1.a, segment2.b),
                         Vector(segment2.b, segment1.b)) ||
           VectorProduct(Vector(segment2.a, segment1.a),
                         Vector(segment1.a, segment2.b)) ||
           VectorProduct(Vector(segment2.a, segment1.b),
                         Vector(segment1.b, segment2.b));
  }
  if (IsIntersection(segment1, segment2)) {
    return true;
  }
  return false;
}

Segment::Segment(const Point& p1, const Point& p2) {
  a = p1;
  b = p2;
}

std::istream& operator>>(std::istream& is, Segment& s) {
  is >> s.a >> s.b;
  return is;
}

Segment& Segment::Move(const Vector& move) {
  a = a + move;
  b = b + move;
  return *this;
}

bool Segment::ContainsPoint(const Point& point) const {
  if (this->a.ContainsPoint(this->b)) {
    return a.ContainsPoint(point);
  }
  return IsOnSegment(*this, point);
}

bool Segment::CrossesSegment(const Segment& segment) const {
  if (this->a.ContainsPoint(this->b)) {
    return IsOnSegment(segment, this->a);
  }
  return Intersection(*this, segment);
}

IShape* Segment::Clone() const { return new Segment(this->a, this->b); }

std::string Segment::ToString() const {
  return std::string("Segment(" + a.ToString() + ", " + b.ToString() + ")");
}
}  // namespace geometry