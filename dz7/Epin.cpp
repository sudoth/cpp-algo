#include <iostream>
#include <vector>

class FenwickTree {
  std::vector<int64_t> fenwick_tree_;

 public:
  explicit FenwickTree(const int64_t& n) {
    fenwick_tree_ = std::vector<int64_t>(n);
  }

  void Update(int64_t index, const int64_t& value) {
    auto n = static_cast<int64_t>(fenwick_tree_.size());
    for (; index < n; index = (index | (index + 1))) {
      fenwick_tree_[index] += value;
    }
  }

  int64_t Query(int64_t index) {
    int64_t sum = 0;
    for (; index >= 0; index = (index & (index + 1)) - 1) {
      sum += fenwick_tree_[index];
    }
    return sum;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n = 0;
  std::cin >> n;
  std::vector<int64_t> values(n);
  FenwickTree fenwick_tree(n);
  for (int64_t i = 0; i < n; ++i) {
    std::cin >> values[i];
    fenwick_tree.Update(i, values[i]);
  }

  int64_t m = 0;
  std::cin >> m;
  for (int64_t i = 0; i < m; ++i) {
    char type = 0;
    std::cin >> type;
    if (type == 's') {
      int64_t l = 0;
      int64_t r = 0;
      std::cin >> l >> r;
      std::cout << fenwick_tree.Query(r - 1) - fenwick_tree.Query(l - 2) << ' ';
    } else if (type == 'u') {
      int64_t index = 0;
      int64_t value = 0;
      std::cin >> index >> value;
      fenwick_tree.Update(index - 1, value - values[index - 1]);
      values[index - 1] = value;
    }
  }
}
