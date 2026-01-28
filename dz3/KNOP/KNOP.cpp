#include <iostream>

void Print(int i, int j, int** previ, int** prevj, int* arrx) {
  if (i == 0 || j == 0) {
    return;
  }
  if (previ[i][j] == i - 1 && prevj[i][j] == j - 1) {
    Print(i - 1, j - 1, previ, prevj, arrx);
    std::cout << arrx[i] << ' ';
  } else {
    if (previ[i][j] == i - 1 && prevj[i][j] == j) {
      Print(i - 1, j, previ, prevj, arrx);
    } else {
      Print(i, j - 1, previ, prevj, arrx);
    }
  }
}

int main() {
  int m;
  std::cin >> m;
  int arrx[1007];
  for (int i = 1; i <= m; i++) {
    std::cin >> arrx[i];
  }
  int n;
  std::cin >> n;
  int arry[1007];
  for (int i = 1; i <= n; i++) {
    std::cin >> arry[i];
  }
  auto dp = new int*[1007];
  for (int i = 0; i < 1007; i++) {
    auto arr = new int[1007];
    dp[i] = arr;
  }
  for (int i = 1; i <= m; i++) {
    dp[i][0] = 0;
  }
  for (int i = 0; i <= n; i++) {
    dp[0][i] = 0;
  }
  auto previ = new int*[1007];
  for (int i = 0; i < 1007; i++) {
    auto arr = new int[1007];
    previ[i] = arr;
  }
  auto prevj = new int*[1007];
  for (int i = 0; i < 1007; i++) {
    auto arr = new int[1007];
    prevj[i] = arr;
  }
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      if (arrx[i] == arry[j]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
        previ[i][j] = i - 1;
        prevj[i][j] = j - 1;
      } else {
        if (dp[i - 1][j] >= dp[i][j - 1]) {
          dp[i][j] = dp[i - 1][j];
          previ[i][j] = i - 1;
          prevj[i][j] = j;
        } else {
          dp[i][j] = dp[i][j - 1];
          previ[i][j] = i;
          prevj[i][j] = j - 1;
        }
      }
    }
  }
  Print(m, n, previ, prevj, arrx);

  for (int i = 0; i < 1007; i++) {
    delete[] dp[i];
  }
  for (int i = 0; i < 1007; i++) {
    delete[] previ[i];
  }
  for (int i = 0; i < 1007; i++) {
    delete[] prevj[i];
  }
  delete[] dp;
  delete[] previ;
  delete[] prevj;
}