#include <iostream>

void BlockTransfer(int, int);

void BlockTransfer(int i, int j, int n) {
  if (n == 0) {
    return;
  }
  BlockTransfer(i, 6 - i - j, n - 1);
  std::cout << n << " " << i << " " << j << "\n";
  BlockTransfer(6 - i - j, j, n - 1);
}

int main() {
  int n;
  std::cin >> n;
  BlockTransfer(1, 3, n);
}