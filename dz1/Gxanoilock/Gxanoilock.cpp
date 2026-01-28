#include <iostream>

void BlockTransfer(int, int);

void BlockTransfer(int i, int j, int n) {
  if (n == 0) {
    return;
  }
  if (n == 1) {
    std::cout << n << " " << i << " " << j << "\n";
  } else {
    BlockTransfer(i, j, n - 1);
    std::cout << n << " " << i << " " << 6 - i - j << "\n";
    BlockTransfer(j, i, n - 1);
    std::cout << n << " " << 6 - i - j << " " << j << "\n";
    BlockTransfer(i, j, n - 1);
  }
}

int main() {
  int n;
  std::cin >> n;
  BlockTransfer(1, 3, n);
}