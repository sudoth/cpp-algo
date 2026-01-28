#ifndef HEAPSORT_H
#define HEAPSORT_H
template <typename T, typename U>
void SiftUp(T* begin, T* end, U i) {
  while (*(begin + (i - 1) / 2) < *(begin + i)) {
    T t = *(begin + (i - 1) / 2);
    *(begin + (i - 1) / 2) = *(begin + i);
    *(begin + i) = t;
    i = (i - 1) / 2;
  }
}

template <typename T, typename U>
void SiftDown(T* begin, T* end, U i) {
  int n = end - begin;
  while (2 * i + 1 < n) {
    U j = 2 * i + 1;
    if (2 * i + 2 < n && *(begin + 2 * i + 1) < *(begin + 2 * i + 2)) {
      j = 2 * i + 2;
    }
    if (*(begin + i) < *(begin + j)) {
      T t = *(begin + i);
      *(begin + i) = *(begin + j);
      *(begin + j) = t;
    }
    i = j;
  }
}

template <typename T>
void MakeHeap(T* begin, T* end) {
  int n = end - begin;
  for (int i = n / 2; i >= 0; i--) {
    SiftDown(begin, end, i);
  }
}

template <typename T>
void SortHeap(T* begin, T* end) {
  MakeHeap(begin, end);
  int n = end - begin;
  while (0 < n) {
    T t = *begin;
    *begin = *(begin + n - 1);
    *(begin + n - 1) = t;
    n--;
    SiftDown(begin, begin + n, 0);
  }
}
#endif