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
  Point(int64_t a, int64_t b) : x(a), y(b) {
  }
  int64_t x;
  int64_t y;
};

class Vector {
 public:
  Vector() = default;
  Vector(Point a, Point b) {
    x = b.x - a.x;
    y = b.y - a.y;
  }
  double Length() const;
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
  Vector Vec(const int64_t&, const int64_t&) const;
  int64_t n;
  Point* vertices;
  bool IsConvex() const;
};

std::istream& operator>>(std::istream& is, Polygon& polygon) {
  for (int64_t i = 0; i < polygon.n; ++i) {
    Point point;
    is >> point.x >> point.y;
    polygon.vertices[i] = point;
  }
  return is;
}

Vector Polygon::Vec(const int64_t& i, const int64_t& j) const {
  return Vector(this->vertices[i], this->vertices[j]);
}

double Vector::Length() const {
  return std::sqrt(this->x * this->x + this->y * this->y);
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

double Distant(const Point& a, const Point& b) {
  return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool Polygon::IsConvex() const {
  int64_t n = this->n;
  int signum = 0;
  for (int64_t i = 0; i < n; ++i) {
    int64_t three_points =
        VectorProduct(this->Vec(i % this->n, (i + 1) % this->n), this->Vec(i % this->n, (i + 2) % this->n));
    if (three_points == 0) {
      continue;
    }
    if (signum == 0) {
      signum = Sgn(three_points);
      continue;
    }
    if (signum != Sgn(three_points)) {
      return false;
    }
  }
  return true;
}

int main() {
  std::cout << std::fixed << std::setprecision(9);
  int64_t n;
  std::cin >> n;
  Polygon polygon(n);
  std::cin >> polygon;
  std::cout << (polygon.IsConvex() ? "YES" : "NO");
}