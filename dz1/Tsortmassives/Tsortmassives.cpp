#include <iostream>

template <typename T>
void Merge(T* left, T* middle, T* right) {
  int n = right - left;
  auto out = new T[n];
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

template <typename T>
void MergeSort(T* pos_begin, T* next_pos_begin, int k, int* arr_begin) {
  if (k == 2) {
    return;
  }
  int m = 1;
  if (k % 2) {
    for (int i = 1; i < k; i += 2) {
      Merge(arr_begin + pos_begin[i - 1], arr_begin + pos_begin[i], arr_begin + pos_begin[i + 1]);
      next_pos_begin[m] = pos_begin[i + 1];
      m++;
    }
  } else {
    for (int i = 1; i < k - 1; i += 2) {
      Merge(arr_begin + pos_begin[i - 1], arr_begin + pos_begin[i], arr_begin + pos_begin[i + 1]);
      next_pos_begin[m] = pos_begin[i + 1];
      m++;
    }
    next_pos_begin[m] = pos_begin[k - 1];
  }
  for (int i = 0; i < k / 2 + 1; i++) {
    pos_begin[i] = next_pos_begin[i];
  }
  MergeSort(pos_begin, next_pos_begin, k / 2 + 1, arr_begin);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int k;
  int n = 0;
  std::cin >> k;
  auto position = new int[1000007];
  auto next_position = new int[1000007];
  position[0] = 0;
  next_position[0] = 0;
  auto array = new int[1000007];
  for (int i = 0; i < k; i++) {
    int m;
    std::cin >> m;
    position[i + 1] = position[i] + m;
    for (int j = 0; j < m; j++) {
      std::cin >> array[n + j];
    }
    n += m;
  }
  MergeSort(position, next_position, k + 1, array);
  for (int i = 0; i < n; i++) {
    std::cout << array[i] << " ";
  }
  delete[] array;
  delete[] position;
  delete[] next_position;
}