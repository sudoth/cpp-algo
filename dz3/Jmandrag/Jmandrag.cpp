#include <algorithm>
#include <iostream>

int main() {
  int n;
  std::cin >> n;
  auto arr = new int[n];
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i];
  }
  std::sort(arr, arr + n);
  auto dp = new int[n]{};
  if (n == 2) {
    std::cout << arr[1] + arr[0];
    delete[] arr;
    delete[] dp;
    return 0;
  }
  dp[1] = arr[1] - arr[0];
  dp[2] = arr[2] - arr[0];
  for (int i = 3; i < n; i++) {
    dp[i] = std::min(dp[i - 2], dp[i - 1]) + arr[i] - arr[i - 1];
  }
  std::cout << dp[n - 1];
  delete[] arr;
  delete[] dp;
}