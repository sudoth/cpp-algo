#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

class Point {
 public:
  Point() = default;
  Point(const int64_t& a, const int64_t& b) : x(a), y(b) {
  }
  bool operator<(const Point&) const;
  bool operator==(const Point&) const;
  bool operator!=(const Point&) const;
  int64_t x;
  int64_t y;
};

class Vector {
 public:
  Vector() = default;
  Vector(const Point& a, const Point& b) {
    x = b.x - a.x;
    y = b.y - a.y;
  }
  int64_t x;
  int64_t y;
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

class Polygon {
 public:
  Polygon() = default;
  explicit Polygon(int64_t a) : n(a) {
    vertices.reserve(n);
  }
  void Add(Point point) {
    vertices[k++] = point;
  }
  int64_t Area() const;
  std::vector<Point> vertices;
  size_t n;
  int64_t k = 0;
};

bool Point::operator<(const Point& other) const {
  return (this->x == other.x && this->y < other.y) || this->x < other.x;
}

bool Point::operator==(const Point& other) const {
  return this->x == other.x && this->y == other.y;
}

bool Point::operator!=(const Point& other) const {
  return this->x != other.x || this->y != other.y;
}

std::istream& operator>>(std::istream& is, Polygon& polygon) {
  for (size_t i = 0; i < polygon.n; ++i) {
    Point point;
    is >> point.x >> point.y;
    polygon.vertices.push_back(point);
  }
  return is;
}

std::istream& operator>>(std::istream& is, Point& point) {
  is >> point.x >> point.y;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
  os << point.x << ' ' << point.y;
  return os;
}

std::ostream& operator<<(std::ostream& os, const Polygon& polygon) {
  for (size_t i = 0; i < polygon.vertices.size(); ++i) {
    os << polygon.vertices[i] << '\n';
  }
  return os;
}

int64_t ScalarProduct(const Vector& vec1, const Vector& vec2) {
  return vec1.x * vec2.x + vec1.y * vec2.y;
}

int64_t VectorProduct(const Vector& vec1, const Vector& vec2) {
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

int64_t Polygon::Area() const {
  int64_t area = 0;
  for (size_t i = 0; i < this->vertices.size() - 1; i++) {
    area +=
        VectorProduct(Vector(this->vertices[0], this->vertices[i]), Vector(this->vertices[0], this->vertices[i + 1]));
  }
  return std::abs(area);
}

class Comparator {
 public:
  explicit Comparator(const Point& p) {
    first = p;
  }
  bool operator()(const Point& a, const Point& b) const {
    if (b == first) {
      return false;
    }
    if (VectorProduct(Vector(first, a), Vector(first, b)) == 0) {
      if (IsOnSegment(Segment(first, b), a)) {
        return true;
      }
    }
    return VectorProduct(Vector(first, a), Vector(first, b)) < 0;
  }
  Point first;
};

Polygon ConvexHull(Polygon& set) {
  Point first = set.vertices[0];
  for (size_t i = 0; i < set.vertices.size(); i++) {
    if (set.vertices[i] < first) {
      first = set.vertices[i];
    }
  }
  std::sort(set.vertices.begin(), set.vertices.end(), Comparator(first));
  Polygon hull(set.vertices.size());
  for (size_t i = 0; i < set.vertices.size(); ++i) {
    while (hull.vertices.size() > 1) {
      if (VectorProduct(Vector(hull.vertices[hull.vertices.size() - 2], hull.vertices.back()),
                        Vector(hull.vertices[hull.vertices.size() - 2], set.vertices[i])) >= 0) {
        hull.vertices.pop_back();
      } else {
        break;
      }
    }
    hull.vertices.push_back(set.vertices[i]);
  }
  return hull;
}

int main() {
  int64_t n;
  std::cin >> n;
  Polygon set(n);
  Polygon hull(n);
  std::cin >> set;
  hull = ConvexHull(set);
  std::cout << hull.vertices.size() << '\n';
  std::cout << hull;
  int64_t area = hull.Area();
  std::cout << area / 2;
  if (area % 2 == 0) {
    std::cout << ".0";
  } else {
    std::cout << ".5";
  }
}