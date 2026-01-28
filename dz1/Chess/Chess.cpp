#include <iostream>

void Search(int y, int n, int& counter, int* collumns, int* diagonal_1, int* diagonal_2) {
  if (y == n) {
    counter++;
    return;
  }
  for (int x = 0; x < n; x++) {
    if (collumns[x] || diagonal_1[x + y] || diagonal_2[n - x + y - 1]) {
      continue;
    }
    collumns[x] = 1;
    diagonal_1[x + y] = 1;
    diagonal_2[n - x + y - 1] = 1;
    Search(y + 1, n, counter, collumns, diagonal_1, diagonal_2);
    collumns[x] = 0;
    diagonal_1[x + y] = 0;
    diagonal_2[n - x + y - 1] = 0;
  }
}

int main() {
  int counter = 0;
  int collumns[100] = {0};
  int diagonal_1[100] = {0};
  int diagonal_2[100] = {0};
  int n;
  std::cin >> n;
  Search(0, n, counter, collumns, diagonal_1, diagonal_2);
  std::cout << counter;
}