#include <iostream>
#include <vector>

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<int64_t> sculptures(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> sculptures[i];
  }

  std::vector<int64_t> prefix_sum(n + 1, 0);
  for (int i = 1; i <= n; ++i) {
    prefix_sum[i] = prefix_sum[i - 1] + sculptures[i - 1];
  }

  int k = 0;
  std::cin >> k;
  for (int i = 0; i < k; ++i) {
    int right = 0;
    int left = 0;
    std::cin >> left >> right;
    std::cout << prefix_sum[right] - prefix_sum[left - 1] << " ";
  }
}