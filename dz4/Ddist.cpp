#include <iostream>
#include <cmath>
#include <iomanip>

class Point {
 public:
  Point() = default;
  Point(int a, int b) : x(a), y(b) {
  }
  int x;
  int y;
};

class Vector {
 public:
  Vector(int x1, int x2, int y1, int y2) {
    x = x2 - x1;
    y = y2 - y1;
  }
  Vector(int a, int b) : x(a), y(b) {
  }
  Vector(Point a, Point b) {
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

double Vector::Length() const {
  return std::sqrt(this->x * this->x + this->y * this->y);
}

std::istream& operator>>(std::istream& is, Point& point) {
  is >> point.x >> point.y;
  return is;
}

int ScalarProduct(const Vector& vec1, const Vector& vec2) {
  return vec1.x * vec2.x + vec1.y * vec2.y;
}

int VectorProduct(const Vector& vec1, const Vector& vec2) {
  return vec1.x * vec2.y - vec2.x * vec1.y;
}

bool IsOnRay(const Ray& ray, const Point& c) {
  return ScalarProduct(Vector(ray.begin, ray.b), Vector(ray.begin, c)) >= 0;
}

bool IsOnSegment(const Segment& segment, const Point& c) {
  return IsOnRay(Ray(segment.a, segment.b), c) && IsOnRay(Ray(segment.b, segment.a), c);
}

double Distant(const Point& a, const Point& b) {
  return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double LineDistant(const Line& line, const Point& c) {
  return (std::abs(VectorProduct(Vector(line.a, line.b), Vector(line.a, c))) / Vector(line.a, line.b).Length());
}

double RayDistant(const Ray& ray, const Point& c) {
  return IsOnRay(ray, c) ? LineDistant(Line(ray.begin, ray.b), c) : Distant(ray.begin, c);
}

double SegmentDistant(const Segment& segment, const Point& c) {
  return IsOnSegment(segment, c) ? LineDistant(Line(segment.a, segment.b), c)
                                 : std::min(Distant(segment.a, c), Distant(segment.b, c));
}

int main() {
  std::cout << std::fixed << std::setprecision(9);
  Point a;
  Point b;
  Point c;
  std::cin >> c;
  std::cin >> a;
  std::cin >> b;
  std::cout << LineDistant(Line(a, b), c) << '\n';
  std::cout << RayDistant(Ray(a, b), c) << '\n';
  std::cout << SegmentDistant(Segment(a, b), c);
}