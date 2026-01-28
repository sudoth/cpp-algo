#include <iostream>

void FillingArray(int (*prev_gen)[12], int (*next_gen)[12], int n) {
  for (int i = 1; i < n + 1; i++) {
    for (int j = 1; j < n + 1; j++) {
      int power = 0;
      power += prev_gen[i - 1][j - 1] + prev_gen[i - 1][j] + prev_gen[i - 1][j + 1] + prev_gen[i][j - 1] +
               prev_gen[i][j + 1] + prev_gen[i + 1][j - 1] + prev_gen[i + 1][j] + prev_gen[i + 1][j + 1];
      // if 1
      if (prev_gen[i][j] == 1) {
        if ((power == 2) || (power == 3)) {
          next_gen[i][j] = 1;
        } else {
          next_gen[i][j] = 0;
        }
      }
      // if 0
      if (prev_gen[i][j] == 0) {
        if (power == 3) {
          next_gen[i][j] = 1;
        } else {
          next_gen[i][j] = 0;
        }
      }
    }
  }
  for (int i = 1; i < n + 1; i++) {
    for (int j = 1; j < n + 1; j++) {
      prev_gen[i][j] = next_gen[i][j];
    }
  }
}

int main() {
  int n;
  int t;
  std::cin >> n;
  std::cin >> t;
  int prev_gen[12][12] = {0};
  for (int i = 1; i < n + 1; i++) {
    for (int j = 1; j < n + 1; j++) {
      std::cin >> prev_gen[i][j];
    }
  }
  int next_gen[12][12] = {0};
  for (int k = 0; k < t; k++) {
    FillingArray(prev_gen, next_gen, n);
  }
  for (int i = 1; i < n + 1; i++) {
    for (int j = 1; j < n + 1; j++) {
      std::cout << next_gen[i][j] << " ";
    }
    std::cout << "\n";
  }
}