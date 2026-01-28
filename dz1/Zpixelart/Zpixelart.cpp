#include <cstdint>
#include <iostream>

void AddToSum(int64_t* array, int x, int n, int m, int k) {
  for (int i = x; i < m + n - 1; i += k) {
    if (i < n - 1) {
      array[x] += i + 1;
      continue;
    }
    if (i > m - 1) {
      array[x] += n - (i - m + 1);
      continue;
    }
    array[x] += n;
  }
}

int main() {
  int64_t n;
  int64_t m;
  int64_t k;
  std::cin >> n;
  std::cin >> m;
  std::cin >> k;
  auto number = new int64_t[k]{0};
  int m_lower = m % k;
  int n_lower = n % k;
  if (m_lower >= n_lower) {
    for (int x = 0; x < k; x++) {
      AddToSum(number, x, n_lower, m_lower, k);
    }
  } else {
    for (int x = 0; x < k; x++) {
      AddToSum(number, x, m_lower, n_lower, k);
    }
  }
  for (int i = 0; i < k; i++) {
    number[i] += (n / k) * (m / k) * k + (m % k) * (n / k) + (n % k) * (m / k);
  }
  for (int i = 0; i < k; i++) {
    std::cout << number[i] << " ";
  }
  delete[] number;
}