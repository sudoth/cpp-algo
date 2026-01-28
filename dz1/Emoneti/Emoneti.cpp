#include <iostream>

void IfTrue(int* coins, int n, int m, int* number, int* ans_array, int& ans) {
  int sum = 0;
  int k = 0;
  for (int i = 0; i < m; i++) {
    k += number[i];
    for (int j = 0; j < number[i]; j++) {
      sum += coins[i];
    }
  }
  if (n == sum && k < ans) {
    ans = k;
    for (int i = 0; i < m; i++) {
      ans_array[i] = number[i];
    }
  }
}

void Search(int* coins, int n, int m, int* number, int* ans_array, int& ans, int y = 0) {
  if (y == m) {
    return;
  }
  for (int i = 0; i < 3; i++) {
    number[y] = i;
    Search(coins, n, m, number, ans_array, ans, y + 1);
    if (i == 2) {
      continue;
    }
    IfTrue(coins, n, m, number, ans_array, ans);
  }
}

int main() {
  int ans = 2147483647;
  int ans_array[15] = {0};
  int number[15] = {0};
  int n;
  std::cin >> n;
  int m;
  std::cin >> m;
  int coins[15];
  for (int i = 0; i < m; i++) {
    std::cin >> coins[i];
  }
  int summ = 0;
  for (int i = 0; i < m; i++) {
    summ += coins[i] * 2;
  }
  if (summ < n) {
    std::cout << "-1";
    return 0;
  }

  for (int i = 0; i < m; i++) {
    if (coins[i] > n) {
      coins[i] = coins[m - 1];
      m--;
    }
  }

  Search(coins, n, m, number, ans_array, ans);
  IfTrue(coins, n, m, number, ans_array, ans);

  if (ans == 2147483647) {
    std::cout << "0";
    return 0;
  }

  std::cout << ans << "\n";
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < ans_array[i]; j++) {
      std::cout << coins[i] << " ";
    }
  }
}