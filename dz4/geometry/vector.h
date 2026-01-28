#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
namespace geometry {
class Point;
class Vector {
 public:
  Vector() = default;
  Vector(const int64_t& a, const int64_t& b);
  Vector(const Point& a, const Point& b);
  Vector operator+() const;
  Vector operator+(const Vector&) const;
  Vector operator-() const;
  Vector operator-(const Vector&) const;
  Vector operator*(const int64_t&) const;
  Vector operator/(const int64_t&) const;
  Vector& operator+=(const Vector&);
  Vector& operator-=(const Vector&);
  Vector& operator*=(const int64_t&);
  Vector& operator/=(const int64_t&);
  bool operator==(const Vector&) const;
  int64_t x;
  int64_t y;
};
int64_t ScalarProduct(const Vector&, const Vector&);
int64_t VectorProduct(const Vector&, const Vector&);
std::istream& operator>>(std::istream&, Vector&);
}
#endif
