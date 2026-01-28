#include "../polygon.h"

#include <vector>

#include "../point.h"
#include "../ray.h"
#include "../segment.h"
#include "../vector.h"
namespace geometry {
bool SegmentOnRay(const Ray& ray, const Segment& segment) {
  return (VectorProduct(Vector(ray.a, ray.a + ray.direction),
                        Vector(ray.a, segment.a)) == 0 &&
          VectorProduct(Vector(ray.a, ray.a + ray.direction),
                        Vector(ray.a, segment.b)) == 0);
}

bool IsInside(const Polygon& polygon, const Point& point) {
  std::size_t n = polygon.vertices.size();
  int64_t counter = 0;
  Ray ray(point, Point(point.x + 3529, point.y + 1789));
  for (std::size_t i = 0; i < n; ++i) {
    Segment segment(polygon.vertices[i % n], polygon.vertices[(i + 1) % n]);
    if (IsOnSegment(segment, point)) {
      return true;
    }
    if (SegmentOnRay(ray, segment)) {
      continue;
    }
    if (IsOnRay(ray, segment.b)) {
      if ((VectorProduct(Vector(ray.a, ray.a + ray.direction),
                         Vector(ray.a, polygon.vertices[i])) > 0 &&
           VectorProduct(Vector(ray.a, ray.a + ray.direction),
                         Vector(ray.a, polygon.vertices[(i + 2) % n])) < 0) ||
          (VectorProduct(Vector(ray.a, ray.a + ray.direction),
                         Vector(ray.a, polygon.vertices[i])) < 0 &&
           VectorProduct(Vector(ray.a, ray.a + ray.direction),
                         Vector(ray.a, polygon.vertices[(i + 2) % n])) > 0) ||
          SegmentOnRay(ray, Segment(polygon.vertices[(i + 1) % n],
                                    polygon.vertices[(i + 2) % n]))) {
        ++counter;
        continue;
      }
    }
    if (RaySegmentInt(ray, segment)) {
      ++counter;
    }
  }
  return counter % 2 == 1;
}

Polygon::Polygon(const std::vector<Point>& vector) {
  this->vertices.reserve(vector.size());
  for (std::size_t i = 0; i < vector.size(); ++i) {
    this->vertices.push_back(vector[i]);
  }
}

std::istream& operator>>(std::istream& is, Polygon& p) {
  is >> p.n;
  p.vertices.reserve(p.n);
  Point point;
  for (std::size_t i = 0; i < p.vertices.capacity(); ++i) {
    is >> point;
    p.vertices.emplace_back(point);
  }
  return is;
}

Polygon& Polygon::Move(const Vector& move) {
  for (std::size_t i = 0; i < vertices.size(); ++i) {
    vertices[i] = vertices[i] + move;
  }
  return *this;
}

bool Polygon::ContainsPoint(const Point& point) const {
  return IsInside(*this, point);
}

bool Polygon::CrossesSegment(const Segment& segment) const {
  std::size_t n = this->vertices.size();
  for (std::size_t i = 0; i < n; ++i) {
    Segment side(this->vertices[i % n], this->vertices[(i + 1) % n]);
    if (side.CrossesSegment(segment) || IsOnSegment(segment, side.a)) {
      return true;
    }
  }
  return false;
}

IShape* Polygon::Clone() const { return new Polygon(this->vertices); }

std::string Polygon::ToString() const {
  std::string string;
  string += "Polygon(";
  for (std::size_t i = 0; i < this->vertices.size(); ++i) {
    string += this->vertices[i].ToString();
    if (i == this->vertices.size() - 1) {
      string += ")";
      break;
    }
    string += ", ";
  }
  return string;
}
}  // namespace geometry