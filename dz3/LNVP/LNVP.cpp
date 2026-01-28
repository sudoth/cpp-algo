#include <iostream>

int main() {
  int n;
  std::cin >> n;
  auto sequence = new int[n];
  auto previous = new int[n];
  auto dp = new int[n];
  for (int i = 0; i < n; i++) {
    std::cin >> sequence[i];
  }
  for (int i = 0; i < n; i++) {
    dp[i] = 1;
    previous[i] = -1;
    for (int j = 0; j < i; j++) {
      if ((sequence[j] < sequence[i]) && (dp[j] + 1 > dp[i])) {
        dp[i] = dp[j] + 1;
        previous[i] = j;
      }
    }
  }
  int position = 0;
  int length = dp[0];
  for (int i = 0; i < n; i++) {
    if (dp[i] > length) {
      position = i;
      length = dp[i];
    }
  }
  int k = 0;
  auto answer = new int[n];
  while (position >= 0) {
    answer[k] = sequence[position];
    position = previous[position];
    k++;
  }
  for (int i = 1; i < k + 1; i++) {
    std::cout << answer[k - i] << ' ';
  }
  delete[] sequence;
  delete[] previous;
  delete[] answer;
  delete[] dp;
}