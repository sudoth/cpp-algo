#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>
class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

class Rational {
 public:
  Rational();
  Rational(int);  // NOLINT
  Rational(int, int);

  int GetNumerator() const;
  int GetDenominator() const;

  void SetNumerator(int);
  void SetDenominator(int);

  Rational operator+(const Rational&) const;
  Rational operator-(const Rational&) const;
  Rational operator/(const Rational&) const;
  Rational operator*(const Rational&)const;

  Rational& operator+=(const Rational&);
  Rational& operator-=(const Rational&);
  Rational& operator/=(const Rational&);
  Rational& operator*=(const Rational&);

  Rational operator+() const;
  Rational operator-() const;
  Rational& operator++();
  Rational& operator--();
  Rational operator++(int);
  Rational operator--(int);

  friend bool operator<(const Rational&, const Rational&);
  friend bool operator<=(const Rational&, const Rational&);
  friend bool operator>(const Rational&, const Rational&);
  friend bool operator>=(const Rational&, const Rational&);
  friend bool operator==(const Rational&, const Rational&);
  friend bool operator!=(const Rational&, const Rational&);

  friend std::istream& operator>>(std::istream&, Rational&);
  friend std::ostream& operator<<(std::ostream&, const Rational&);

  void Reduce();

 private:
  int num_;
  int den_;
};
#endif