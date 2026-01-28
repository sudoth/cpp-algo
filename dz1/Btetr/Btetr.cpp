#include <iostream>
#include <cstdint>

int main() {
  int64_t n;
  int64_t m;
  std::cin >> n >> m;
  auto field = new char*[n];
  for (int i = 0; i < n; i++) {
    field[i] = new char[m];
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      std::cin >> field[i][j];
    }
  }

  if (m == 1 || n == 1) {
    std::cout << "?";
    for (int i = 0; i < n; i++) {
      delete[] field[i];
    }
    delete[] field;
    return 0;
  }

  int64_t prev = 0;
  int64_t rows_counter = 0;
  int64_t rows_dist = 0;
  auto rows = new int64_t[n];
  for (int k = 0; k < n; k++) {
    if (field[k][0] == '1' && field[k][1] == '1') {
      rows[k] = 1;
      rows_dist = k - prev;
      prev = k;
      rows_counter++;
    } else {
      rows[k] = 0;
    }
  }

  prev = 0;
  int64_t columns_counter = 0;
  int64_t columns_dist = 0;
  auto columns = new int64_t[m];
  for (int k = 0; k < m; k++) {
    if (field[0][k] == '1' && field[1][k] == '1') {
      columns[k] = 1;
      columns_dist = k - prev;
      prev = k;
      columns_counter++;
    } else {
      columns[k] = 0;
    }
  }

  if (columns_counter > 0 && rows_counter > 0) {
    std::cout << "Square";
  } else {
    if (columns_counter == 1 || rows_counter == 1) {
      std::cout << "?";
    } else {
      if (rows_counter > 0) {
        if (m >= rows_dist) {
          std::cout << "Line";
        } else {
          std::cout << "?";
        }
      }
      if (columns_counter > 0) {
        if (n >= columns_dist) {
          std::cout << "Vertical line";
        } else {
          std::cout << "?";
        }
      }
    }
  }

  for (int i = 0; i < n; i++) {
    delete[] field[i];
  }
  delete[] rows;
  delete[] field;
  delete[] columns;
}