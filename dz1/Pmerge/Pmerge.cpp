#include <iostream>
#include <cstdint>
#include "Pmerge.h"

int main() {
  int16_t first[100]{1, 3, 3, 5, 8, 12};
  int32_t second[100]{2, 3, 5};
  int64_t out[100];
  Merge(first, first + 6, second, second + 3, out);
  for (int i = 0; i < 9; i++) {
    std::cout << out[i] << " ";
  }
}