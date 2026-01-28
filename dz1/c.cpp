#include <iostream>

void elem(int x, int y, int** arr) {
  std::cout << arr[x - 1][y - 1];
}

void delstl(int x, int** arr, int n, int m) {
  x--;
  for (int i = x; i < n - 1; i++) {
    for (int j = 0; j < m; j++) {
      arr[i][j] = arr[i + 1][j];
    }
  }
}

int main() {
  int n, m;
  std:: cout << "Введите размер матрица (а - ширина; и - длина): ";
  std::cin >> n >> m;
  int** arr = new int*[n];
  for (int i = 0; i < n; i++) {
    int* a = new int[m];
    arr[i] = a;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      std::cin >> arr[i][j];
    }
  }
  
  int x, y;
  std::cin >> x >> y;
  elem(x, y, arr);



  for (int i = 0; i < n; i++) {
    delete[] arr[i];
  }
  delete[] arr;
}