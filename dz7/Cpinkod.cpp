#include <iostream>
#include <vector>

class SparseTable {
  std::vector<std::vector<int>> sparse_table_;

 public:
  explicit SparseTable(const std::vector<int>& values) {
    int n = static_cast<int>(values.size());
    sparse_table_ = std::vector<std::vector<int>>(n, std::vector<int>(20));
    for (int i = 0; i < n; ++i) {
      sparse_table_[i][0] = values[i];
    }

    for (int j = 1; (1 << j) <= n; ++j) {
      for (int i = 0; i + (1 << j) - 1 < n; ++i) {
        sparse_table_[i][j] = std::min(sparse_table_[i][j - 1], sparse_table_[i + (1 << (j - 1))][j - 1]);
      }
    }
  }

  int Query(const int l, const int r) {
    int k = 0;
    while ((1 << (k + 1)) <= r - l + 1) {
      ++k;
    }
    return std::min(sparse_table_[l][k], sparse_table_[r - (1 << k) + 1][k]);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int q = 0;
  std::cin >> n >> q;
  std::vector<int> values(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> values[i];
  }

  SparseTable st(values);

  for (int i = 0; i < q; ++i) {
    int l = 0;
    int r = 0;
    std::cin >> l >> r;
    std::cout << st.Query(l - 1, r - 1) << '\n';
  }
}
