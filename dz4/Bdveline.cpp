#include <cmath>
#include <iostream>
#include <iomanip>

class Line {
 public:
  Line() = default;
  Line(int x, int y, int z) : a(x), b(y), c(z) {
  }
  int a;
  int b;
  int c;
};

class Vector {
 public:
  Vector() = default;
  Vector(int a, int b) : x(a), y(b) {
  }
  int x;
  int y;
};

class FloatPoint {
 public:
  FloatPoint() = default;
  FloatPoint(double a, double b) : x(a), y(b) {
  }
  double x;
  double y;
};

std::ostream& operator<<(std::ostream& os, const Vector& vec) {
  os << vec.x << ' ' << vec.y;
  return os;
}

std::ostream& operator<<(std::ostream& os, const FloatPoint& dvec) {
  os << dvec.x << ' ' << dvec.y;
  return os;
}

std::istream& operator>>(std::istream& is, Line& line) {
  is >> line.a >> line.b >> line.c;
  return is;
}

int ScalarProduct(const Vector& vec1, const Vector& vec2) {
  return vec1.x * vec2.x + vec1.y * vec2.y;
}

int VectorProduct(const Vector& vec1, const Vector& vec2) {
  return vec1.x * vec2.y - vec2.x * vec1.y;
}

bool IsParalell(const Vector& vec1, const Vector& vec2) {
  return !VectorProduct(vec1, vec2);
}

double Distance(const Line& line1, const Line& line2) {
  return std::abs(line1.c * line2.b - line2.c * line1.b) /
         std::sqrt(line1.b * line1.b * line2.a * line2.a + line1.b * line1.b * line2.b * line2.b);
}

FloatPoint Intersection(const Line& line1, const Line& line2) {
  return FloatPoint{
      (static_cast<double>(-line1.c * line2.b + line1.b * line2.c)) / (line1.a * line2.b - line1.b * line2.a),
      (static_cast<double>(-line1.a * line2.c + line1.c * line2.a)) / (line1.a * line2.b - line1.b * line2.a)};
}

int main() {
  std::cout << std::fixed << std::setprecision(9);
  Line line1;
  Line line2;
  std::cin >> line1 >> line2;
  Vector vec1(-line1.b, line1.a);
  Vector vec2(-line2.b, line2.a);
  std::cout << vec1 << '\n';
  std::cout << vec2 << '\n';
  if (IsParalell(vec1, vec2)) {
    if (line1.b == 0) {
      std::cout << std::abs(static_cast<double>(line1.c) / line1.a - line2.c / line2.a);
      return 0;
    }
    std::cout << Distance(line1, line2);
  } else {
    std::cout << Intersection(line1, line2);
  }
}