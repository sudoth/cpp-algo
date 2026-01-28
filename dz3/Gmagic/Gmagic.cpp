#include <iostream>
#include <cstring>

int CharToInt(char c) {
  return c - '0';
}

int main() {
  int m;
  std::cin >> m;
  char str[207];
  std::cin >> str;
  int n = strlen(str);
  // auto dp = new int*[n];
  // for (int i = 0; i < n; i++) {
  //   auto arr = new int[200000];
  //   dp[i] = arr;
  // }
  int dp[10][1000];
  dp[0][CharToInt(str[0]) + 500] = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 1000; j++) {
          if (dp[i - 1][j] == 1) {
            int plus = j + CharToInt(str[i]);
            int minus = j - CharToInt(str[i]);
            int nosign = (j - 500) * 10 + 500 + CharToInt(str[i]);
            if (plus <= 2001) {
              dp[i][plus] = 1;
            }
            if (minus >= 0) {
              dp[i][minus] = 1;
            }
            if (nosign <= 2001) {
              dp[i][nosign] = 1;
            }
          }
        }
    }
  std::cout << dp[n - 1][m + 500];
  // for (int i = 0; i < n; i++) {
  //   delete[] dp[i];
  // }
  // delete[] dp;
}
// dp[i][j] - можно ли составить число j из первых i символов
