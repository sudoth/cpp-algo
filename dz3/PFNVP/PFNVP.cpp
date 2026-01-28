#include <algorithm>
#include <iostream>

int main() {
  int n;
  std::cin >> n;
  auto values = new int[n];
  for (int i = 0; i < n; i++) {
    int t = 0;
    std::cin >> t;
    values[i] = t + 100000;
  }
  auto dp = new int[200001];
  dp[0] = -1e9;
  for (int i = 1; i <= 200000; i++) {
    dp[i] = 1e9;
  }
  for (int i = 0; i < n; i++) {
    int j = std::upper_bound(dp, dp + 200000, values[i]) - dp;
    if (dp[j - 1] < values[i] && values[i] < dp[j]) {
      dp[j] = values[i];
    }
  }
  int ans = 1;
  for (int i = 0; i < 200000; i++) {
    if (dp[i] == 1e9) {
      continue;
    }
    ans = i;
  }
  std::cout << ans;
  delete[] values;
  delete[] dp;
}