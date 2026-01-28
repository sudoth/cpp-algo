#include <iostream>
#include <cstdint>

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

template <typename U>
void MergeSort(U* begin, U* end) {
  if (begin + 1 < end) {
    U* middle = begin + (end - begin) / 2;
    MergeSort(begin, middle);
    MergeSort(middle, end);
    Merge(begin, middle, end);
  }
}

inline bool IsTriangle(int64_t a, int64_t b, int64_t c) {
  return (a - b <= c) && (b - a <= c) && (c <= a + b);
}

void CheckMax(int64_t* array, int64_t it1, int64_t it2, int64_t& ans_it1, int64_t& ans_it2, int64_t& ans_sum) {
  int64_t sum = 0;
  for (int64_t i = it1; i < it2 + 1; i++) {
    sum += array[i];
  }
  if (sum >= ans_sum) {
    ans_sum = sum;
    ans_it1 = it1;
    ans_it2 = it2;
  }
}

int main() {
  int64_t n;
  std::cin >> n;
  auto arr = new int64_t[n];
  for (int64_t i = 0; i < n; i++) {
    std::cin >> arr[i];
  }
  if (n == 1) {
    std::cout << n << " " << arr[0];
    delete[] arr;
    return 0;
  }
  if (n == 2) {
    std::cout << n << " " << arr[0] + arr[1];
    delete[] arr;
    return 0;
  }
  MergeSort(arr, arr + n);
  // n > 2
  int64_t ans_sum = 0;
  int64_t ans_it1 = 0;
  int64_t ans_it2 = 1;
  int64_t it1 = 0;
  int64_t it2 = 1;
  int64_t new_it1 = 0;
  int64_t new_it2 = 1;
  while (new_it2 + 1 < n) {
    if (it2 == n) {
      it2--;
      break;
    }
    new_it2++;
    if (IsTriangle(arr[it1], arr[it1 + 1], arr[new_it2]) && IsTriangle(arr[it2 - 1], arr[it2], arr[new_it2])) {
      it2++;
      continue;
    }
    if (!IsTriangle(arr[it2 - 1], arr[it2], arr[new_it2])) {
      CheckMax(arr, it1, it2, ans_it1, ans_it2, ans_sum);
      it1 = it2;
      it2 = new_it2;
      new_it1 = it1;
      continue;
    }
    if (!IsTriangle(arr[it1], arr[it1 + 1], arr[new_it2])) {
      int64_t sum_fast = 0;
      while (IsTriangle(arr[it2 - 1], arr[it2], arr[new_it2]) && new_it1 < it2) {
        sum_fast += arr[new_it1];
        new_it1++;
        bool flag = false;
        int64_t sum_slow = 0;
        int64_t new_it2_slow = new_it2;
        while (IsTriangle(arr[new_it1], arr[new_it1 + 1], arr[new_it2]) && new_it2_slow < n) {
          sum_slow += arr[new_it2_slow];
          if (sum_fast <= sum_slow) {
            it1 = new_it1;
            it2 = new_it2_slow;
            new_it2 = it2;
            flag = true;
            break;
          }
          new_it2_slow++;
        }
        if (flag) {
          break;
        }
      }
      continue;
    }
  }
  CheckMax(arr, it1, it2, ans_it1, ans_it2, ans_sum);
  std::cout << ans_it2 - ans_it1 + 1 << " " << ans_sum;
  delete[] arr;
}