#include <iostream>

template <typename T>
T* PartitionLomuto(T* begin, T* end) {
  int n = end - begin;
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
void QuickSort(U* begin, U* end) {
  if (begin + 1 < end) {
    U* partition = PartitionLomuto(begin, end);
    QuickSort(begin, partition);
    QuickSort(partition, end);
  }
}

bool CheckDist(int* score, int middle, int n, int m, int k) {
  int counter = 0;
  for (int i = 0; i < n - k + 1; i++) {
    if (score[i + k - 1] - score[i] < middle) {
      counter++;
      i += k - 1;
    }
  }
  return counter >= m;
}

int main() {
  int n;
  int m;
  int k;
  std::cin >> n;
  std::cin >> m;
  std::cin >> k;
  auto score = new int[1000007];
  for (int i = 0; i < n; i++) {
    std::cin >> score[i];
  }
  QuickSort(score, score + n);
  int left = 0;
  int right = score[n - 1] + 1;
  while (right - left > 1) {
    int middle = left + (right - left) / 2;
    if (CheckDist(score, middle, n, m, k)) {
      right = middle;
    } else {
      left = middle;
    }
  }
  std::cout << left;
  delete[] score;
}