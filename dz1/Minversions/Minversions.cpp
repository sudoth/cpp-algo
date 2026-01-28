#include <iostream>

template <typename T, typename W>
void Merge(T* left, T* middle, T* right, W& cnt) {
  int n = right - left;
  auto out = new T[n];
  int it1 = 0;
  int it2 = 0;
  while (left + it1 < middle && middle + it2 < right) {
    if (*(left + it1) <= *(middle + it2)) {
      out[it1 + it2] = *(left + it1);
      it1++;
      cnt += it2;
    } else {
      out[it1 + it2] = *(middle + it2);
      it2++;
    }
  }
  while (left + it1 < middle) {
    out[it1 + it2] = *(left + it1);
    it1++;
    cnt += it2;
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

template <typename U, typename V>
void MergeSort(U* begin, U* end, V& cnt) {
  if (begin + 1 < end) {
    U* middle = begin + (end - begin) / 2;
    MergeSort(begin, middle, cnt);
    MergeSort(middle, end, cnt);
    Merge(begin, middle, end, cnt);
  }
}

int main() {
  int n;
  std::cin >> n;
  auto arr = new double[n];
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i];
  }
  int64_t counter = 0;
  MergeSort(arr, arr + n, counter);
  std::cout << counter;
  delete[] arr;
}