#include <iostream>

template <typename T>
T* PartitionLomuto(T* begin, T* end) {
  end--;
  T pivot = *end;
  int n = end - begin;
  int i = 0;
  for (int j = 0; j < n; j++) {
    if (*(begin + j) <= pivot) {
      T t = *(begin + i);
      *(begin + i) = *(begin + j);
      *(begin + j) = t;
      i++;
    }
  }
  T t = *(begin + i);
  *(begin + i) = *(end);
  *(end) = t;
  return begin + i;
}

template <typename U>
void QuickSort(U* begin, U* end) {
  if (begin + 1 < end) {
    U* partition = PartitionLomuto(begin, end);
    QuickSort(begin, partition);
    QuickSort(partition, end);
  }
}

int main() {
  int n;
  std::cin >> n;
  int arr1[100001];
  for (int i = 0; i < n; i++) {
    std::cin >> arr1[i];
  }
  int m;
  std::cin >> m;
  int arr2[100001];
  for (int i = 0; i < m; i++) {
    std::cin >> arr2[i];
  }
  QuickSort(arr1, arr1 + n);
  QuickSort(arr2, arr2 + m);
  int it1 = 0;
  int it2 = 0;
  while (it1 < n && it2 < m) {
    // skip arr1
    while (it1 + 1 < n) {
      while (arr1[it1] == arr1[it1 + 1]) {
        it1++;
        if (it1 + 1 > n) {
          break;
        }
      }
      break;
    }
    // skip arr2
    while (it2 + 1 < m) {
      while (arr2[it2] == arr2[it2 + 1]) {
        it2++;
        if (it2 + 1 > m) {
          break;
        }
      }
      break;
    }
    // 1 7 9 | n = 3
    // 0 1 2
    // 1 7 7 9 9 9| m = 6
    // 0 1 2 3 4 5
    if (arr1[it1] == arr2[it2]) {
      if (it1 == n - 1 && it2 == m - 1) {
        std::cout << "YES";
        return 0;
      }
      if (it1 + 1 < n) {
        it1++;
      }
      if (it2 + 1 < m) {
        it2++;
      }
      continue;
    }
    std::cout << "NO";
    return 0;
  }
}