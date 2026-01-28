#include <iostream>

template <typename T>
void Merge(T* left, T* middle, T* right) {
  int n = right - left;
  T* out = new T[n];
  int it1 = 0;
  int it2 = 0;
  while (left + it1 < middle && middle + it2 < right) {
    if (*(left + it1) < *(middle + it2)) {
      out[it1 + it2] = *(left + it1);
      it1++;
    } else {
      out[it1 + it2] = *(middle + it2);
      it2++;
    }
  }
  while (left + it1 < middle) {
    out[it1 + it2] = *(left + it1);
    it1++;
  }
  while (middle + it2 < right) {
    out[it1 + it2] = *(middle + it2);
    it2++;
  }
  for (int i = 0; i < n; i++) {
    left[i] = out[i];
  }
  delete[] out;
}

template <typename U>
void Sort(U* begin, U* end) {
  if (begin + 1 < end) {
    U* middle = begin + (end - begin) / 2;
    Sort(begin, middle);
    Sort(middle, end);
    Merge(begin, middle, end);
  }
}

int main() {
  int n;
  std::cin >> n;
  int* arr = new int[n];
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i];
  }
  Sort(arr, arr + n);
  for (int i = 0; i < n; i++) {
    std::cout << arr[i] << " ";
  }
  delete[] arr;
}