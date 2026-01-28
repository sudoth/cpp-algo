#include <iostream>
#include <iomanip>

class Point {
 public:
  Point() = default;
  Point(const int64_t& a, const int64_t& b) : x(a), y(b) {
  }
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

class Polygon {
 public:
  Polygon() = default;
  explicit Polygon(int64_t a) : n(a) {
    vertices = new Point[n];
  }
  ~Polygon() {
    delete[] vertices;
  }
  int64_t Area() const;
  Point* vertices;
  int64_t n;
};

std::istream& operator>>(std::istream& is, Polygon& polygon) {
  for (int64_t i = 0; i < polygon.n; ++i) {
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

int64_t ScalarProduct(const Vector& vec1, const Vector& vec2) {
  return vec1.x * vec2.x + vec1.y * vec2.y;
}

int64_t VectorProduct(const Vector& vec1, const Vector& vec2) {
  return vec1.x * vec2.y - vec2.x * vec1.y;
}

int64_t Polygon::Area() const {
  int64_t n = this->n;
  int64_t area = 0;
  for (int64_t i = 0; i < n - 1; i++) {
    area +=
        VectorProduct(Vector(this->vertices[0], this->vertices[i]), Vector(this->vertices[0], this->vertices[i + 1]));
  }
  return std::abs(area);
}

int main() {
  int64_t n;
  std::cin >> n;
  Polygon polygon(n);
  std::cin >> polygon;
  int64_t area = polygon.Area();
  std::cout << area / 2;
  if (area % 2 == 0) {
    std::cout << ".0";
  } else {
    std::cout << ".5";
  }
}