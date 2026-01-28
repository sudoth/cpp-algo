#include <iostream>
#include <cmath>

class Point {
 public:
  Point() = default;
  Point(int a, int b) : x(a), y(b) {
  }
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

double Vector::Length() const {
  return std::sqrt(this->x * this->x + this->y * this->y);
}

Vector operator+(const Vector& vec1, const Vector& vec2) {
  Vector ans(vec1.x + vec2.x, vec1.y + vec2.y);
  return ans;
}

std::ostream& operator<<(std::ostream& os, const Vector& vec) {
  os << vec.x << ' ' << vec.y;
  return os;
}

int ScalarProduct(const Vector& vec1, const Vector& vec2) {
  return vec1.x * vec2.x + vec1.y * vec2.y;
}

int VectorProduct(const Vector& vec1, const Vector& vec2) {
  return vec1.x * vec2.y - vec2.x * vec1.y;
}

std::istream& operator>>(std::istream& is, Point& point) {
  is >> point.x >> point.y;
  return is;
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

int main() {
  Point a;
  Point b;
  Point c;
  std::cin >> c;
  std::cin >> a;
  std::cin >> b;
  std::cout << (IsOnLine(Line(a, b), c) ? "YES\n" : "NO\n");
  std::cout << (IsOnRay(Ray(a, b), c) ? "YES\n" : "NO\n");
  std::cout << (IsOnSegment(Segment(a, b), c) ? "YES" : "NO");
}