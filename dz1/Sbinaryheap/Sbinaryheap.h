#ifndef BINARYHEAP_H
#define BINARYHEAP_H
template <typename T>
void PushHeap(T* begin, T* end) {
  int i = end - begin - 1;
  while (*(begin + (i - 1) / 2) < *(begin + i)) {
    T t = *(begin + (i - 1) / 2);
    *(begin + (i - 1) / 2) = *(begin + i);
    *(begin + i) = t;
    i = (i - 1) / 2;
  }
}

template <typename U>
void PopHeap(U* begin, U* end) {
  int n = end - begin;
  U t = *begin;
  *begin = *(begin + n - 1);
  *(begin + n - 1) = t;
  int i = 0;
  n--;
  while (2 * i + 1 < n) {
    U* j = begin + 2 * i + 1;
    if (2 * i + 2 < n && *(begin + 2 * i + 1) < *(begin + 2 * i + 2)) {
      j = begin + 2 * i + 2;
    }
    if (*(begin + i) < *j) {
      U t = *(begin + i);
      *(begin + i) = *j;
      *j = t;
    }
    i = j - begin;
  }
}
#endif