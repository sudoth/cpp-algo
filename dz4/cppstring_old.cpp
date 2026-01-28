#include "cppstring.h"

#include <algorithm>
#include <cstring>

String::String() {
  size = 0;
  capacity = 0;
  ptr = new char[1]{};
}

String::String(const size_t& new_size, const char& new_char) {
  size = new_size;
  capacity = new_size;
  ptr = new char[capacity + 1]{};
  for (size_t i = 0; i < size; ++i) {
    ptr[i] = new_char;
  }
}

String::String(const char* new_ptr) {  // NOLINT
  size = (new_ptr == nullptr ? 0 : std::strlen(new_ptr));
  capacity = size;
  ptr = new char[capacity + 1]{};
  for (size_t i = 0; i < size; ++i) {
    ptr[i] = new_ptr[i];
  }
}

String::String(const char* new_ptr, const size_t& count) {
  size = (new_ptr == nullptr ? 0 : count);
  capacity = size;
  ptr = new char[capacity + 1]{};
  for (size_t i = 0; i < size; ++i) {
    ptr[i] = new_ptr[i];
  }
}

String::String(const String& other) {
  size = other.size;
  capacity = other.capacity;
  ptr = new char[capacity + 1]{};
  for (size_t i = 0; i < size; ++i) {
    ptr[i] = other.ptr[i];
  }
}

String& String::operator=(const String& other) {
  if (this != &other) {
    delete[] ptr;
    size = other.size;
    capacity = other.capacity;
    ptr = new char[capacity + 1]{};
    for (size_t i = 0; i < size; ++i) {
      ptr[i] = other.ptr[i];
    }
  }
  return *this;
}

String::~String() {
  delete[] ptr;
}

const char& String::operator[](const size_t& i) const {
  return ptr[i];
}

char& String::operator[](const size_t& i) {
  return ptr[i];
}

const char& String::At(const size_t& i) const {
  if (i >= size) {
    throw StringOutOfRange{};
  }
  return ptr[i];
}

char& String::At(const size_t& i) {
  if (i >= size) {
    throw StringOutOfRange{};
  }
  return ptr[i];
}

const char& String::Front() const {
  return ptr[0];
}

char& String::Front() {
  return ptr[0];
}

const char& String::Back() const {
  return ptr[size - 1];
}

char& String::Back() {
  return ptr[size - 1];
}

char* String::CStr() const {
  return ((size == 0) ? nullptr : ptr);
}

char* String::Data() const {
  return ((size == 0) ? nullptr : ptr);
}

bool String::Empty() const {
  return (ptr[0] == '\0');
}

size_t String::Size() const {
  return size;
}

size_t String::Length() const {
  return size;
}

size_t String::Capacity() const {
  return capacity;
}

void String::Clear() {
  size = 0;
}

void String::Swap(String& other) {
  std::swap(size, other.size);
  std::swap(capacity, other.capacity);
  std::swap(ptr, other.ptr);
}

void String::PopBack() {
  --size;
}

void String::PushBack(const char& other) {
  if (capacity == 0) {
    delete[] ptr;
    ptr = new char[2]{};
    ptr[0] = other;
    size = 1;
    capacity = 1;
    return;
  }
  if (size == capacity) {
    auto new_ptr = new char[2 * capacity + 1]{};
    for (size_t i = 0; i < size; ++i) {
      new_ptr[i] = ptr[i];
    }
    delete[] ptr;
    ptr = new_ptr;
    capacity *= 2;
  }
  ptr[size++] = other;
}

String& String::operator+=(const String& other) {
  for (size_t i = 0; i < other.size; ++i) {
    this->PushBack(other.ptr[i]);
  }
  return *this;
}

void String::Resize(const size_t& new_size, const char& other) {
  if (new_size > capacity) {
    auto new_ptr = new char[new_size + 1]{};
    for (size_t i = 0; i < size; ++i) {
      new_ptr[i] = ptr[i];
    }
    delete[] ptr;
    ptr = new_ptr;
    capacity = new_size;
  }
  for (size_t i = size; i < new_size; ++i) {
    ptr[i] = other;
  }
  size = new_size;
}

void String::Reserve(const size_t& new_capacity) {
  if (new_capacity > capacity) {
    auto new_ptr = new char[new_capacity + 1]{};
    for (size_t i = 0; i < size; ++i) {
      new_ptr[i] = ptr[i];
    }
    delete[] ptr;
    ptr = new_ptr;
    capacity = new_capacity;
  }
}

void String::ShrinkToFit() {
  auto new_ptr = new char[size + 1]{};
  for (size_t i = 0; i < size; ++i) {
    new_ptr[i] = ptr[i];
  }
  delete[] ptr;
  ptr = new_ptr;
  capacity = size;
}

String operator+(const String& lhs, const String& rhs) {
  String s(lhs);
  s += rhs;
  return s;
}

bool String::operator<(const String& other) const {
  return (std::strcmp(this->ptr, other.ptr) < 0);
}

bool String::operator>(const String& other) const {
  return (std::strcmp(this->ptr, other.ptr) > 0);
}

bool String::operator<=(const String& other) const {
  return (std::strcmp(this->ptr, other.ptr) <= 0);
}

bool String::operator>=(const String& other) const {
  return (std::strcmp(this->ptr, other.ptr) >= 0);
}

bool String::operator!=(const String& other) const {
  return (std::strcmp(this->ptr, other.ptr) != 0);
}

bool String::operator==(const String& other) const {
  return (std::strcmp(this->ptr, other.ptr) == 0);
}

std::ostream& operator<<(std::ostream& os, const String& str) {
  for (size_t i = 0; i < str.Size(); ++i) {
    os << str[i];
  }
  return os;
}