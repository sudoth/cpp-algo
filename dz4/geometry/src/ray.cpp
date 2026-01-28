#include "../ray.h"

#include "../line.h"
#include "../segment.h"
namespace geometry {
bool RaySegmentInt(const Ray& ray, const Segment& segment) {
  if (!LineSegmentInt(Line(ray.a, ray.a + ray.direction), segment)) {
    return false;
  }
  if (IsOnRay(ray, segment.a) || IsOnRay(ray, segment.b)) {
    return true;
  }
  if (VectorProduct(Vector(segment.a, ray.a), Vector(segment.a, segment.b)) >
          0 &&
      VectorProduct(Vector(ray.a, ray.a + ray.direction),
                    Vector(segment.a, segment.b)) < 0) {
    return true;
  }
  if (VectorProduct(Vector(segment.a, ray.a), Vector(segment.a, segment.b)) <
          0 &&
      VectorProduct(Vector(ray.a, ray.a + ray.direction),
                    Vector(segment.a, segment.b)) > 0) {
    return true;
  }
  return false;
}

Ray::Ray(const Point& a, const Point& b) {
  this->a = a;
  this->direction = b - a;
}

std::istream& operator>>(std::istream& is, Ray& r) {
  is >> r.a >> r.direction;
  return is;
}

Ray& Ray::Move(const Vector& move) {
  a = a + move;
  return *this;
}

bool Ray::ContainsPoint(const Point& point) const {
  return IsOnRay(*this, point);
}

bool Ray::CrossesSegment(const Segment& segment) const {
  return RaySegmentInt(*this, segment);
}

IShape* Ray::Clone() const {
  return new Ray(this->a, this->a + this->direction);
}

std::string Ray::ToString() const {
  return std::string("Ray(" + a.ToString() + ", " + "Vector(" +
                     std::to_string(direction.x) + ", " +
                     std::to_string(direction.y) + "))");
}
}  // namespace geometry