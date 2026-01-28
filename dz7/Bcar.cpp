#include <iostream>
#include <vector>

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<int> suspicion(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> suspicion[i];
  }

  int64_t maximum = suspicion[0];
  int left = 0;
  int right = 0;
  int64_t sum = 0;
  int64_t min_sum = 0;
  int min_position = -1;

  for (int i = 0; i < n; ++i) {
    sum += suspicion[i];
    int64_t current_sum = sum - min_sum;
    if (current_sum > maximum) {
      maximum = current_sum;
      left = min_position + 1;
      right = i;
    }
    if (min_sum > sum) {
      min_sum = sum;
      min_position = i;
    }
  }

  std::cout << left + 1 << " " << right + 1 << " " << maximum;
}
