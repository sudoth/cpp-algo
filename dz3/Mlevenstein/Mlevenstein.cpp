#include <cstring>
#include <iostream>

int main() {
  char str1[5007];
  char str2[5007];
  std::cin.getline(str1, 5007);
  std::cin.getline(str2, 5007);
  int m = strlen(str1);
  int n = strlen(str2);
  auto dp = new int64_t*[m + 1];
  for (int i = 0; i <= m; i++) {
    auto arr = new int64_t[n + 1];
    dp[i] = arr;
  }
  dp[0][0] = 0;
  for (int i = 0; i <= n; i++) {
    dp[0][i] = i;
  }
  for (int i = 0; i <= m; i++) {
    dp[i][0] = i;
  }
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      int64_t minn = std::min(dp[i - 1][j] + 1, dp[i - 1][j - 1] + (str1[i - 1] != str2[j - 1]));
      dp[i][j] = std::min(dp[i][j - 1] + 1, minn);
    }
  }
  std::cout << dp[m][n];
  for (int i = 0; i <= m; i++) {
    delete[] dp[i];
  }
  delete[] dp;
}