#ifndef KTHELEMENT_H
#define KTHELEMENT_H
template <typename T>
T* PartitionLomuto(T* begin, T* end) {
  int n = end - begin;
  // select pivot | low < high < mid
  if (*(end - 1) < *(begin)) {
    T t = *(end - 1);
    *(end - 1) = *(begin);
    *(begin) = t;
  }
  if (*(begin + n / 2) < *(begin)) {
    T t = *(begin + n / 2);
    *(begin + n / 2) = *(begin);
    *(begin) = t;
  }
  if (*(begin + n / 2) < *(end - 1)) {
    T t = *(begin + n / 2);
    *(begin + n / 2) = *(end - 1);
    *(end - 1) = t;
  }
  T pivot = *(end - 1);
  // select pivot
  int wall = 0;
  for (int j = 0; j < n - 1; j++) {
    if (pivot < *(begin + j)) {
      continue;
    }
    T t = *(begin + wall);
    *(begin + wall) = *(begin + j);
    *(begin + j) = t;
    wall++;
  }
  T t = *(begin + wall);
  *(begin + wall) = *(end - 1);
  *(end - 1) = t;
  return begin + wall;
}

template <typename U>
void KthElement(U* begin, U* kth, U* end) {
  U* partition = PartitionLomuto(begin, end);
  if (partition - begin < kth - begin) {
    KthElement(partition, kth, end);
  }
  if (kth - begin < partition - begin) {
    KthElement(begin, kth, partition);
  }
}
#endif