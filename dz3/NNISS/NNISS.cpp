#include <iostream>
#include <cstdint>

int main() {
  int n;
  std::cin >> n;
  auto numbers = new int[n];
  for (int i = 0; i < n; i++) {
    std::cin >> numbers[i];
  }
  auto dp = new int64_t[5000]{};
  for (int i = 0; i < n; i++) {
    for (int j = numbers[i] - 1; j >= 0; j--) {
      dp[numbers[i]] += dp[j];
      dp[numbers[i]] %= 1000000;
    }
    dp[numbers[i]]++;
  }

  int64_t answer = 0;
  for (int i = 0; i < 5000; i++) {
    answer += dp[i];
  }
  std::cout << answer % 1000000;
  delete[] numbers;
  delete[] dp;
}
