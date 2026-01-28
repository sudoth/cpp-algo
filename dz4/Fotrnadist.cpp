#include <iostream>
#include <cmath>
#include <iomanip>

template <typename T>
int Sgn(const T& val) {
  return val >= T(0) ? 1 : -1;
}

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
  Vector() = default;
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

double Distant(const Point& a, const Point& b) {
  return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool IsOnRay(const Ray& ray, const Point& c) {
  return ScalarProduct(Vector(ray.begin, ray.b), Vector(ray.begin, c)) >= 0;
}

bool IsOnSegment(const Segment& segment, const Point& c) {
  return IsOnRay(Ray(segment.a, segment.b), c) && IsOnRay(Ray(segment.b, segment.a), c);
}

bool OnLine(const Line& line, const Point& c) {
  return VectorProduct(Vector(line.a, line.b), Vector(line.a, c)) == 0;
}

bool OnRay(const Ray& ray, const Point& c) {
  return OnLine(Line(ray.begin, ray.b), c) && ScalarProduct(Vector(ray.begin, ray.b), Vector(ray.begin, c)) >= 0;
}

bool OnSegment(const Segment& segment, const Point& c) {
  return OnRay(Ray(segment.a, segment.b), c) && IsOnRay(Ray(segment.b, segment.a), c);
}

double DefaultDistance(const Segment& segment, const Point& point) {
  return (std::abs(VectorProduct(Vector(segment.a, segment.b), Vector(segment.a, point))) /
          Vector(segment.a, segment.b).Length());
}

double SegmentDistance(const Segment& segment, const Point& c) {
  return IsOnSegment(segment, c) ? DefaultDistance(Segment(segment.a, segment.b), c)
                                 : std::min(Distant(segment.a, c), Distant(segment.b, c));
}

double CalculateDistance(const Segment& segment1, const Segment& segment2) {
  double distance3 = SegmentDistance(segment2, segment1.a);
  double distance4 = SegmentDistance(segment2, segment1.b);
  double distance1 = SegmentDistance(segment1, segment2.a);
  double distance2 = SegmentDistance(segment1, segment2.b);
  return std::min(std::min(distance1, distance2), std::min(distance3, distance4));
}

bool IsPointOnLine(const Segment& segment1, const Segment& segment2) {
  return (OnSegment(segment1, segment2.a) || OnSegment(segment1, segment2.b) || OnSegment(segment2, segment1.a) ||
          OnSegment(segment2, segment1.b));
}

bool IsCollinear(const Segment& segment1, const Segment& segment2) {
  return (VectorProduct(Vector(segment1.a, segment1.b), Vector(segment1.a, segment2.a)) == 0 &&
          VectorProduct(Vector(segment1.a, segment1.b), Vector(segment1.a, segment2.b)) == 0 &&
          VectorProduct(Vector(segment2.a, segment2.b), Vector(segment2.a, segment1.a)) == 0 &&
          VectorProduct(Vector(segment2.a, segment2.b), Vector(segment2.a, segment1.b)) == 0);
}

bool IsIntersection(const Segment& segment1, const Segment& segment2) {
  return (Sgn(VectorProduct(Vector(segment1.a, segment1.b), Vector(segment1.a, segment2.a))) *
              Sgn(VectorProduct(Vector(segment1.a, segment1.b), Vector(segment1.a, segment2.b))) <
          0) &&
         ((Sgn(VectorProduct(Vector(segment2.a, segment2.b), Vector(segment2.a, segment1.a))) *
               Sgn(VectorProduct(Vector(segment2.a, segment2.b), Vector(segment2.a, segment1.b))) <
           0));
}

bool Intersection(const Segment& segment1, const Segment& segment2) {
  if (IsPointOnLine(segment1, segment2)) {
    return true;
  }
  if (IsCollinear(segment1, segment2)) {
    if (VectorProduct(Vector(segment1.a, segment2.a), Vector(segment2.a, segment1.b)) ||
        VectorProduct(Vector(segment1.a, segment2.b), Vector(segment2.b, segment1.b)) ||
        VectorProduct(Vector(segment2.a, segment1.a), Vector(segment1.a, segment2.b)) ||
        VectorProduct(Vector(segment2.a, segment1.b), Vector(segment1.b, segment2.b))) {
      return true;
    }
  }
  if (IsIntersection(segment1, segment2)) {
    return true;
  }
  return false;
}

int main() {
  std::cout << std::fixed << std::setprecision(9);
  Point a;
  Point b;
  Point c;
  Point d;
  std::cin >> a;
  std::cin >> b;
  std::cin >> c;
  std::cin >> d;
  std::cout << (Intersection(Segment(a, b), Segment(c, d)) ? 0 : CalculateDistance(Segment(a, b), Segment(c, d)));
}