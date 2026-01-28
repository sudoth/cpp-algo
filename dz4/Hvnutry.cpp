#include <iostream>
#include <cmath>
#include <iomanip>

class Point {
 public:
  Point() = default;
  Point(const int& a, const int& b) : x(a), y(b) {
  }
  int x;
  int y;
};

class Vector {
 public:
  Vector() = default;
  Vector(const Point& a, const Point& b) {
    x = b.x - a.x;
    y = b.y - a.y;
  }
  double Length() const;
  int x;
  int y;
};

class Line {
 public:
  Line() = default;
  Line(const Point& p1, const Point& p2) {
    a = p1;
    b = p2;
  }
  Point a;
  Point b;
};

class Ray {
 public:
  Ray() = default;
  Ray(const Point& p1, const Point& p2) {
    begin = p1;
    b = p2;
  }
  Ray(const Point& p, const Vector& v) {
    begin = p;
    b.x = p.x + v.x;
    b.y = p.y + v.y;
  }
  Point begin;
  Point b;
};

class Segment {
 public:
  Segment() = default;
  Segment(const Point& p1, const Point& p2) {
    a = p1;
    b = p2;
  }
  Point a;
  Point b;
};

class Polygon {
 public:
  Polygon() = default;
  explicit Polygon(int64_t a) : n(a) {
    vertices = new Point[n];
  }
  ~Polygon() {
    delete[] vertices;
  }
  Vector Vec(const int&, const int&) const;
  Point* vertices;
  int n;
};

std::istream& operator>>(std::istream& is, Polygon& polygon) {
  for (int i = 0; i < polygon.n; ++i) {
    Point point;
    is >> point.x >> point.y;
    polygon.vertices[i] = point;
  }
  return is;
}

std::istream& operator>>(std::istream& is, Point& point) {
  is >> point.x >> point.y;
  return is;
}

double Vector::Length() const {
  return std::sqrt(this->x * this->x + this->y * this->y);
}

Vector Polygon::Vec(const int& i, const int& j) const {
  return Vector(this->vertices[i], this->vertices[j]);
}

int ScalarProduct(const Vector& vec1, const Vector& vec2) {
  return vec1.x * vec2.x + vec1.y * vec2.y;
}

int VectorProduct(const Vector& vec1, const Vector& vec2) {
  return vec1.x * vec2.y - vec2.x * vec1.y;
}

bool IsOnLine(const Line& line, const Point& c) {
  return VectorProduct(Vector(line.a, line.b), Vector(line.a, c)) == 0;
}

bool IsOnRay(const Ray& ray, const Point& c) {
  return IsOnLine(Line(ray.begin, ray.b), c) && ScalarProduct(Vector(ray.begin, ray.b), Vector(ray.begin, c)) >= 0;
}

bool IsOnSegment(const Segment& segment, const Point& c) {
  return IsOnRay(Ray(segment.a, segment.b), c) && IsOnRay(Ray(segment.b, segment.a), c);
}

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

bool RaySegmentInt(const Ray& ray, const Segment& segment) {
  if (!LineSegmentInt(Line(ray.begin, ray.b), segment)) {
    return false;
  }
  if (IsOnRay(ray, segment.a) || IsOnRay(ray, segment.b)) {
    return false;
  }
  if (VectorProduct(Vector(segment.a, ray.begin), Vector(segment.a, segment.b)) > 0 &&
      VectorProduct(Vector(ray.begin, ray.b), Vector(segment.a, segment.b)) < 0) {
    return true;
  }
  if (VectorProduct(Vector(segment.a, ray.begin), Vector(segment.a, segment.b)) < 0 &&
      VectorProduct(Vector(ray.begin, ray.b), Vector(segment.a, segment.b)) > 0) {
    return true;
  }
  return false;
}

bool SegmentOnRay(const Ray& ray, const Segment& segment) {
  return (VectorProduct(Vector(ray.begin, ray.b), Vector(ray.begin, segment.a)) == 0 &&
          VectorProduct(Vector(ray.begin, ray.b), Vector(ray.begin, segment.b)) == 0);
}

bool IsInside(const Polygon& polygon, const Point& point) {
  int n = polygon.n;
  int counter = 0;
  Ray ray(point, Point(point.x + 1, point.y));
  for (int i = 0; i < n; ++i) {
    Segment segment(polygon.vertices[i % n], polygon.vertices[(i + 1) % n]);
    if (IsOnSegment(segment, point)) {
      return true;
    }
    if (SegmentOnRay(ray, segment)) {
      continue;
    }
    if (IsOnRay(ray, segment.b)) {
      if ((VectorProduct(Vector(ray.begin, ray.b), Vector(ray.begin, polygon.vertices[i])) > 0 &&
           VectorProduct(Vector(ray.begin, ray.b), Vector(ray.begin, polygon.vertices[(i + 2) % n])) < 0) ||
          (VectorProduct(Vector(ray.begin, ray.b), Vector(ray.begin, polygon.vertices[i])) < 0 &&
           VectorProduct(Vector(ray.begin, ray.b), Vector(ray.begin, polygon.vertices[(i + 2) % n])) > 0) ||
          SegmentOnRay(ray, Segment(polygon.vertices[(i + 1) % n], polygon.vertices[(i + 2) % n]))) {
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

int main() {
  std::cout << std::fixed << std::setprecision(9);
  int n;
  std::cin >> n;
  Point point;
  std::cin >> point;
  Polygon polygon(n);
  std::cin >> polygon;
  std::cout << (IsInside(polygon, point) ? "YES" : "NO");
}