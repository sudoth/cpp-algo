#include <iostream>

template <typename T, typename U>
int SiftUp(T* begin, U i) {
  while (*(begin + (i - 1) / 2) < *(begin + i)) {
    T t = *(begin + (i - 1) / 2);
    *(begin + (i - 1) / 2) = *(begin + i);
    *(begin + i) = t;
    i = (i - 1) / 2;
  }
  return i;
}

template <typename T, typename U>
int SiftDown(T* begin, T* end, U i) {
  int n = end - begin;
  while (2 * i + 1 < n) {
    U j = 2 * i + 1;
    if (2 * i + 2 < n && *(begin + 2 * i + 1) < *(begin + 2 * i + 2)) {
      j = 2 * i + 2;
    }
    if (*(begin + i) >= *(begin + j)) {
      break;
    }
    T t = *(begin + i);
    *(begin + i) = *(begin + j);
    *(begin + j) = t;
    i = j;
  }
  return i;
}

int main() {
  int n;
  std::cin >> n;
  int m;
  std::cin >> m;
  auto queue = new int[n + 1];
  int length = 0;
  for (int i = 0; i < m; i++) {
    int request;
    std::cin >> request;

    if (request == 1) {
      if (length == 0) {
        std::cout << -1 << '\n';
        continue;
      }
      if (length == 1) {
        std::cout << 0 << ' ';
        std::cout << queue[0] << '\n';
        length--;
        continue;
      }
      int value = queue[0];
      queue[0] = queue[length - 1];
      length--;
      std::cout << SiftDown(queue, queue + length, 0) + 1 << ' ';
      std::cout << value << '\n';
    }

    if (request == 2) {
      int value;
      std::cin >> value;
      if (length >= n) {
        std::cout << -1 << '\n';
        continue;
      }
      length++;
      queue[length - 1] = value;
      std::cout << SiftUp(queue, length - 1) + 1 << '\n';
    }

    if (request == 3) {
      int index;
      std::cin >> index;
      index--;
      if (index >= length || index < 0) {
        std::cout << -1 << '\n';
        continue;
      }
      int value = queue[index];
      queue[index] = queue[length - 1];
      length--;
      int new_index = SiftUp(queue, index);
      SiftDown(queue, queue + length, new_index);
      std::cout << value << '\n';
    }
  }
  for (int i = 0; i < length; i++) {
    std::cout << queue[i] << ' ';
  }
  delete[] queue;
}