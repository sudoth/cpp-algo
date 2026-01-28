#include <iostream>
#include <cstring>

int StringToInt(char* str, int begin, int difference = 5) {
  int end = begin + difference;
  int dec = 1;
  int ans = 0;
  for (int i = end - 1; i >= begin; i--) {
    if (str[i] == '\0') {
      continue;
    }
    ans += (str[i] - '0') * dec;
    dec *= 10;
  }
  return ans;
}

int main() {
  int m;
  std::cin >> m;
  char str[207];
  std::cin >> str;
  int n = strlen(str);
  int limit = 10000;
  auto dp = new int*[n];
  for (int i = 0; i < n; i++) {
    dp[i] = new int[2 * limit + 1]{};
  }
  for (int i = 0; i < n; i++) {
    if (i < 4) {
      dp[i][StringToInt(str, 0, i + 1) + limit] = 1;
    }
    for (int k = 1; k < 5; k++) {
      for (int j = 0; j < 2 * limit + 1; j++) {
        if (dp[i][j] == 1 && i + 1 < n) {
          int sti = StringToInt(str, i + 1, k);
          int plus = j + sti;
          int minus = j - sti;
          if (plus <= 2 * limit + 1 && plus >= 0 && i + k < n) {
            dp[i + k][plus] = 1;
          }
          if (minus <= 2 * limit + 1 && minus >= 0 && i + k < n) {
            dp[i + k][minus] = 1;
          }
        }
      }
    }
  }
  if (dp[n - 1][m + limit]) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
  for (int i = 0; i < n; i++) {
    delete[] dp[i];
  }
  delete[] dp;
}
