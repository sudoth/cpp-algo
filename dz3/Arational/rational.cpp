#include "rational.h"
#include <cstring>
#include <iostream>
#include <numeric>
#include <stdexcept>

void Rational::Reduce() {
  if (den_ == 0) {
    throw RationalDivisionByZero{};
  }
  int gcd = std::gcd(num_, den_);
  num_ /= gcd;
  den_ /= gcd;
  if (den_ < 0) {
    num_ *= (-1);
    den_ *= (-1);
  }
}

Rational::Rational() {
  num_ = 0;
  den_ = 1;
}

Rational::Rational(int num) {
  num_ = num;
  den_ = 1;
}

Rational::Rational(int num, int den) {
  if (den == 0) {
    throw RationalDivisionByZero{};
  }
  num_ = num;
  den_ = den;
  Reduce();
}

int Rational::GetNumerator() const {
  return num_;
}

int Rational::GetDenominator() const {
  return den_;
}

void Rational::SetNumerator(int num) {
  num_ = num;
  Reduce();
}

void Rational::SetDenominator(int den) {
  den_ = den;
  Reduce();
}

Rational Rational::operator+(const Rational& other) const {
  Rational ans(num_ * other.den_ + den_ * other.num_, den_ * other.den_);
  return ans;
}

Rational Rational::operator-(const Rational& other) const {
  Rational ans(num_ * other.GetDenominator() - den_ * other.GetNumerator(), den_ * other.GetDenominator());
  return ans;
}

Rational Rational::operator/(const Rational& other) const {
  Rational ans(num_ * other.GetDenominator(), den_ * other.GetNumerator());
  return ans;
}

Rational Rational::operator*(const Rational& other) const {
  Rational ans(num_ * other.GetNumerator(), den_ * other.GetDenominator());
  return ans;
}

Rational Rational::operator+() const {
  return Rational(num_, den_);
}

Rational Rational::operator-() const {
  return Rational(-num_, den_);
}

Rational& Rational::operator+=(const Rational& other) {
  *this = *this + other;
  return *this;
}

Rational& Rational::operator-=(const Rational& other) {
  *this = *this - other;
  return *this;
}

Rational& Rational::operator*=(const Rational& other) {
  *this = *this * other;
  return *this;
}

Rational& Rational::operator/=(const Rational& other) {
  *this = *this / other;
  return *this;
}

Rational& Rational::operator++() {
  *this = *this + 1;
  return *this;
}

Rational& Rational::operator--() {
  *this = *this - 1;
  return *this;
}

Rational Rational::operator++(int) {
  Rational copy = *this;
  *this += 1;
  return copy;
}

Rational Rational::operator--(int) {
  Rational copy = *this;
  *this -= 1;
  return copy;
}

bool operator<(const Rational& first, const Rational& second) {
  return static_cast<double>(first.GetNumerator()) / first.GetDenominator() <
         static_cast<double>(second.GetNumerator()) / second.GetDenominator();
}

bool operator>(const Rational& first, const Rational& second) {
  return static_cast<double>(first.GetNumerator()) / first.GetDenominator() >
         static_cast<double>(second.GetNumerator()) / second.GetDenominator();
}

bool operator<=(const Rational& first, const Rational& second) {
  return !(first > second);
}

bool operator>=(const Rational& first, const Rational& second) {
  return !(first < second);
}

bool operator==(const Rational& first, const Rational& second) {
  return !(first > second) && !(first < second);
}

bool operator!=(const Rational& first, const Rational& second) {
  return !(first == second);
}

std::ostream& operator<<(std::ostream& os, const Rational& other) {
  if (other.GetDenominator() == 1) {
    os << other.GetNumerator();
    return os;
  }
  os << other.GetNumerator() << '/' << other.GetDenominator();
  return os;
}

std::istream& operator>>(std::istream& is, Rational& other) {
  int num;
  int den;
  char pol;
  is >> num;
  if (is.peek() == '/') {
    is >> pol;
    is >> den;
  } else {
    den = 1;
  }
  other.SetNumerator(num);
  other.SetDenominator(den);
  return is;
}
int main(int argc, char** argv) {
  Rational a(4, 9);
  std::cout << a + 1;
}