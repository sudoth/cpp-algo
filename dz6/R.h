#ifndef R_H
#define R_H
template <typename T>
void Swap(T& a, T& b) {
  T tmp = a;
  a = b;
  b = tmp;
}

template <typename T>
int Partition(T* left, T* right) {
  int l = right - left;
  int mid = l / 2;
  if (left[l] < left[0]) {
    Swap(left[l], left[0]);
  }
  if (left[mid] < left[l]) {
    Swap(left[mid], left[l]);
  }
  if (left[mid] < left[0]) {
    Swap(left[mid], left[0]);
  }
  T pivot = left[l];
  int i = 0;
  for (int j = 0; j < l; ++j) {
    if (pivot < left[j]) {
      continue;
    }
    Swap(left[i], left[j]);
    ++i;
  }
  Swap(left[i], left[l]);
  return i;
}

template <typename T>
void KthElement(T* begin, T* kth, T* end) {
  int left = 0;
  int right = end - begin;
  while (left < right) {
    int mid = Partition(begin + left, begin + right - 1);
    if (kth - begin < mid) {
      right = mid;
    } else if (mid < kth - begin) {
      left = mid;
    } else {
      return;
    }
  }
}
#endif