#include <cmath>
#include <iomanip>
#include <iostream>

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
  Vector vec1(a, b);
  Vector vec2(c, d);

  std::cout << vec1.Length() << ' ' << vec2.Length() << '\n';
  std::cout << vec1 + vec2 << '\n';
  std::cout << ScalarProduct(vec1, vec2) << ' ' << VectorProduct(vec1, vec2) << '\n';
  std::cout << std::abs(static_cast<double>(VectorProduct(vec1, vec2)) / 2);
}