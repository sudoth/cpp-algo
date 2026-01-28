#include <iostream>

void FindMax(int** field, const int& x_prev, const int& y_prev, const int& x_local_max, const int& y_local_max,
             int& x_next, int& y_next, int& max) {
  for (int x = x_prev; x < x_local_max; x++) {
    for (int y = y_prev; y < y_local_max; y++) {
      if (max < field[x][y]) {
        max = field[x][y];
        x_next = x;
        y_next = y;
      }
    }
  }
}

int main() {
  int x_max;
  std::cin >> x_max;
  int y_max;
  std::cin >> y_max;
  int h;
  std::cin >> h;
  int w;
  std::cin >> w;
  auto field = new int*[x_max];
  for (int x = 0; x < x_max; x++) {
    field[x] = new int[y_max];
  }
  for (int x = 0; x < x_max; x++) {
    for (int y = 0; y < y_max; y++) {
      std::cin >> field[x][y];
    }
  }
  int x_next = 0;
  int y_next = 0;
  int x_prev = -1;
  int y_prev = -1;
  int max = -1;
  while (x_next != x_prev || y_next != y_prev) {
    x_prev = x_next;
    y_prev = y_next;
    int x_local_max = h + x_prev > x_max ? x_max : h + x_prev;
    int y_local_max = w + y_prev > y_max ? y_max : w + y_prev;
    FindMax(field, x_prev, y_prev, x_local_max, y_local_max, x_next, y_next, max);
  }
  std::cout << x_next << ' ' << y_next;
  for (int x = 0; x < x_max; x++) {
    delete[] field[x];
  }
  delete[] field;
}