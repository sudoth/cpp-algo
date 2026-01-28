#include <iostream>

template <typename T, typename U>
bool BinarySearch(T* begin, T* end, const U& value) {
  while (begin + 1 < end) {
    T* middle = begin + (end - begin) / 2;
    if (value < *middle) {
      end = middle;
    } else {
      begin = middle;
    }
  }
  return !(*begin < value) && !(value < *begin);
}

template <typename V, typename W>
V* LowerBound(V* begin, V* end, const W& value) {
  if (value < *begin || (!(*begin < value) && !(value < *begin))) {
    return begin;
  }
  while (begin + 1 < end) {
    V* middle = begin + (end - begin) / 2;
    if (*middle < value) {
      begin = middle;
    } else {
      end = middle;
    }
  }
  return end;
}

template <typename W, typename X>
W* UpperBound(W* begin, W* end, const X& value) {
  if (value < *begin) {
    return begin;
  }
  while (begin + 1 < end) {
    W* middle = begin + (end - begin) / 2;
    if (value < *middle) {
      end = middle;
    } else {
      begin = middle;
    }
  }
  return end;
}

int main() {
  int matrix[] = {1, 3, 5, 6, 8, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 14, 14, 14, 14, 14, 14, 16, 19, 22};
  std::cout << std::lower_bound(matrix, matrix + 24, 1) << " " << *(std::lower_bound(matrix, matrix + 24, 1)) << "\n";
  std::cout << LowerBound(matrix, matrix + 24, 1) << " " << *(LowerBound(matrix, matrix + 24, 1)) << "\n";
  std::cout << std::upper_bound(matrix, matrix + 24, 1) << " " << *(std::upper_bound(matrix, matrix + 24, 1)) << "\n";
  std::cout << UpperBound(matrix, matrix + 24, 1) << " " << *(UpperBound(matrix, matrix + 24, 1)) << "\n";
  std::cout << BinarySearch(matrix, matrix + 24, 1) << "\n";
}