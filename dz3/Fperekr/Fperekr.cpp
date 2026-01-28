#include <iostream>
#include <cstdint>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n;
  int m;
  std::cin >> n;
  std::cin >> m;
  auto dp = new int64_t*[n];
  for (int i = 0; i < n; i++) {
    auto arr = new int64_t[m]{};
    dp[i] = arr;
  }
  dp[0][0] = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (i != n - 1) {
        dp[i + 1][j] += dp[i][j];
      }
      if ((i != n - 1) && (j != m - 1)) {
        dp[i + 1][j + 1] += dp[i][j];
      }
      if (j != m - 1) {
        dp[i][j + 1] += dp[i][j];
      }
    }
  }
  std::cout << dp[n - 1][m - 1];
  for (int i = 0; i < n; i++) {
    delete[] dp[i];
  }
  delete[] dp;
}