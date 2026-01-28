#include <iostream>
#include <vector>
#include <cstdint>

uint32_t NectRandom(const uint32_t& a, const uint32_t& b, uint32_t& current) {
  current = current * a + b;
  return current >> 8;
}

std::pair<uint32_t, uint32_t> Generate(const uint32_t& a, const uint32_t& b, uint32_t& current) {
  uint32_t l = NectRandom(a, b, current);
  uint32_t r = NectRandom(a, b, current);
  if (l > r) {
    std::swap(l, r);
  }
  return {l, r};
}

void FirstQuery(const uint32_t& a, const uint32_t& b, uint32_t& current, std::vector<uint64_t>& arr, const int& m) {
  for (int i = 0; i < m; ++i) {
    uint32_t add = NectRandom(a, b, current);
    auto [l, r] = Generate(a, b, current);
    arr[l] += add;
    arr[r + 1] -= add;
  }
}

uint32_t SecondQuery(const uint32_t& a, const uint32_t& b, uint32_t& current, std::vector<uint64_t>& arr,
                     const int& q) {
  uint64_t current_sum = 0;
  uint32_t temporary_prefix_sum = 0;
  uint32_t prefix_sum[1 << 24];
  for (int i = 0; i < 1 << 24; ++i) {
    current_sum += arr[i];
    temporary_prefix_sum += current_sum;
    prefix_sum[i] = temporary_prefix_sum;
  }
  uint32_t sum = 0;
  for (int i = 0; i < q; ++i) {
    auto [l, r] = Generate(a, b, current);
    if (l <= 0) {
      sum += prefix_sum[r];
    } else {
      sum += prefix_sum[r] - prefix_sum[l - 1];
    }
  }
  return sum;
}

int main() {
  freopen("input.txt", "r", stdin);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int m = 0;
  int q = 0;
  uint32_t a = 0;
  uint32_t b = 0;
  std::cin >> m >> q >> a >> b;
  const int n = 1 << 24;
  uint32_t current = 0;
  std::vector<uint64_t> arr(n + 1);
  FirstQuery(a, b, current, arr, m);
  std::cout << SecondQuery(a, b, current, arr, q);
  return 0;
}