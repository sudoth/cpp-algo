#include <iostream>
#include <stdexcept>
#include <array>

class ArrayOutOfRange : public std::out_of_range {
 public:
  ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
  }
};

template <typename T, size_t N>
class Array {
 public:
  size_t Size() const;
  bool Empty() const;
  const T& At(size_t) const;
  T& At(size_t);
  const T Front() const;
  T& Front();
  const T Back() const;
  T& Back();
  const T* Data() const;
  T* Data();
  void Fill(const T&);
  void Swap(Array<T, N>&);
  T arr[N];
  T& operator[](size_t idx) {
    if (idx >= N || idx < 0) {
      throw ArrayOutOfRange();
    }
    return arr[idx];
  }
  const T& operator[](size_t idx) const {
    if (idx >= N || idx < 0) {
      throw ArrayOutOfRange();
    }
    return arr[idx];
  }
};

template <typename T, size_t N>
size_t Array<T, N>::Size() const {
  return N;
}

template <typename T, size_t N>
bool Array<T, N>::Empty() const {
  return N == 0;
}

template <typename T, size_t N>
T& Array<T, N>::At(size_t idx) {
  if (idx >= N || idx < 0) {
    throw ArrayOutOfRange{};
  }
  return arr[idx];
}

template <typename T, size_t N>
const T& Array<T, N>::At(size_t idx) const {
  if (idx >= N || idx < 0) {
    throw ArrayOutOfRange();
  }
  return arr[idx];
}

template <typename T, size_t N>
T& Array<T, N>::Front() {
  return arr[0];
}

template <typename T, size_t N>
const T Array<T, N>::Front() const {
  return arr[0];
}

template <typename T, size_t N>
T& Array<T, N>::Back() {
  return arr[N - 1];
}

template <typename T, size_t N>
const T Array<T, N>::Back() const {
  return arr[N - 1];
}

template <typename T, size_t N>
T* Array<T, N>::Data() {
  return arr;
}

template <typename T, size_t N>
const T* Array<T, N>::Data() const {
  return arr;
}

template <typename T, size_t N>
void Array<T, N>::Fill(const T& value) {
  for (size_t i = 0; i < N; ++i) {
    arr[i] = value;
  }
}

template <typename T, size_t N>
void Array<T, N>::Swap(Array<T, N>& other) {
  for (size_t i = 0; i < N; ++i) {
    T tmp = other.arr[i];
    other.arr[i] = this->arr[i];
    this->arr[i] = tmp;
  }
}

template <typename T, size_t N>
size_t GetSize(T (&array)[N]) {
  return sizeof(array) / sizeof(T);
}

template <typename T>
size_t GetSize(T) {
  return 0;
}

template <typename T>
size_t GetRank(T) {
  return 0;
}

template <typename T, size_t N>
size_t GetRank(T (&array)[N]) {
  if (GetSize(array) > 0) {
    return GetRank(array[0]) + 1;
  }
  return 0;
}

template <typename T>
size_t GetNumElements(T) {
  return 1;
}

template <typename T, size_t N>
size_t GetNumElements(T (&array)[N]) {
  if (GetSize(array) > 0) {
    return GetNumElements(array[0]) * GetSize(array);
  }
  return 0;
}

int main() {
  int single[1][1][1];
  int x = 8;
  std::cout << GetNumElements(single);
}
