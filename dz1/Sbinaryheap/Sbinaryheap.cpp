#include <iostream>

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
    // left_son = begin + 2 * i + 1;
    // right_son = begin + 2 * i + 2;
    // root = begin + i;
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

int main() {
  int heap[7]{9, 4, 5, 1, 2, 3, 1};  // (последний элемент не вставлен)*
  PopHeap(heap, heap + 7); // heap == {6, 5, 4, 1, 2, 3, 9} (извлекли 9)
  for (int i = 0; i < 7; i++) {
    std::cout << heap[i] << " ";
  }
  std::cout << "\n";
  // PushHeap(heap, heap + 7);  // heap == {9, 5, 6, 1, 2, 3, 4} (вставили 6)
  // for (int i = 0; i < 7; i++) {
  //   std::cout << heap[i] << " ";
  // }
  // std::cout << "\n";
}