#include "../vector.h"

#include "../point.h"
namespace geometry {

Vector::Vector(const int64_t& a, const int64_t& b) {
  x = a;
  y = b;
}

Vector::Vector(const Point& a, const Point& b) {
  x = b.x - a.x;
  y = b.y - a.y;
}

Vector Vector::operator+() const { return *this; }

Vector Vector::operator+(const Vector& other) const {
  return Vector(this->x + other.x, this->y + other.y);
}

Vector Vector::operator-() const { return Vector(-this->x, -this->y); }

Vector Vector::operator-(const Vector& other) const { return *this + (-other); }

Vector Vector::operator*(const int64_t& a) const {
  return Vector(this->x * a, this->y * a);
}

Vector Vector::operator/(const int64_t& a) const {
  return Vector(this->x / a, this->y / a);
}

Vector& Vector::operator+=(const Vector& other) {
  *this = *this + other;
  return *this;
}

Vector& Vector::operator-=(const Vector& other) {
  *this = *this + (-other);
  return *this;
}

Vector& Vector::operator*=(const int64_t& other) {
  *this = *this * other;
  return *this;
}

Vector& Vector::operator/=(const int64_t& other) {
  *this = *this / other;
  return *this;
}

bool Vector::operator==(const Vector& other) const {
  return this->x == other.x && this->y == other.y;
}

std::istream& operator>>(std::istream& is, Vector& v) {
  is >> v.x >> v.y;
  return is;
}

int64_t ScalarProduct(const Vector& vec1, const Vector& vec2) {
  return vec1.x * vec2.x + vec1.y * vec2.y;
}

int64_t VectorProduct(const Vector& vec1, const Vector& vec2) {
  return vec1.x * vec2.y - vec2.x * vec1.y;
}

}  // namespace geometry