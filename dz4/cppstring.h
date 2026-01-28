#ifndef CPPSTREING_H
#define CPPSTREING_H
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cstring>

class StringOutOfRange : public std::out_of_range {
 public:
  StringOutOfRange() : std::out_of_range("StringOutOfRange") {
  }
};

class String {
 public:
  size_t size;
  size_t capacity;
  char* ptr;
  String();
  String(const size_t&, const char&);
  String(const char*);  // NOLINT
  String(const char*, const size_t&);
  String(const String&);
  String& operator=(const String&);
  ~String();
  const char& operator[](const size_t&) const;
  char& operator[](const size_t&);
  const char& At(const size_t&) const;
  char& At(const size_t&);
  const char& Front() const;
  char& Front();
  const char& Back() const;
  char& Back();
  char* CStr();
  const char* CStr() const;
  char* Data();
  const char* Data() const;
  bool Empty() const;
  size_t Size() const;
  size_t Length() const;
  size_t Capacity() const;
  void Clear();
  void Swap(String&);
  void PopBack();
  void PushBack(const char&);
  String& operator+=(const String&);
  void Resize(const size_t&, const char&);
  void Reserve(const size_t&);
  void ShrinkToFit();
  bool operator<(const String&) const;
  bool operator>(const String&) const;
  bool operator<=(const String&) const;
  bool operator>=(const String&) const;
  bool operator==(const String&) const;
  bool operator!=(const String&) const;
  friend std::ostream& operator<<(std::ostream&, const String&);
  friend String operator+(const String&, const String&);
};

#endif