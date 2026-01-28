#include <iostream>
#include <vector>
#include <cmath>

class SparseTable {
  std::vector<std::vector<std::vector<std::vector<int>>>> sparse_table_;

 public:
  SparseTable(const std::vector<std::vector<int>>& values, const int& m, const int& n) {
    sparse_table_ = std::vector<std::vector<std::vector<std::vector<int>>>>(
        10, std::vector<std::vector<std::vector<int>>>(10, std::vector<std::vector<int>>(500, std::vector<int>(500))));
    for (int i = 0; (1 << i) - 1 < m; ++i) {
      for (int j = 0; (1 << j) - 1 < n; ++j) {
        for (int x = 0; x + (1 << i) - 1 < m; ++x) {
          for (int y = 0; y + (1 << j) - 1 < n; ++y) {
            if (i == 0 && j == 0) {
              sparse_table_[i][j][x][y] = values[x][y];
            } else if (i == 0 && j != 0) {
              sparse_table_[i][j][x][y] =
                  std::min(sparse_table_[i][j - 1][x][y], sparse_table_[i][j - 1][x][y + (1 << (j - 1))]);
            } else if (j == 0 && i != 0) {
              sparse_table_[i][j][x][y] =
                  std::min(sparse_table_[i - 1][j][x][y], sparse_table_[i - 1][j][x + (1 << (i - 1))][y]);
            } else {
              sparse_table_[i][j][x][y] = std::min(
                  std::min(sparse_table_[i - 1][j - 1][x][y], sparse_table_[i - 1][j - 1][x + (1 << (i - 1))][y]),
                  std::min(sparse_table_[i - 1][j - 1][x][y + (1 << (j - 1))],
                           sparse_table_[i - 1][j - 1][x + (1 << (i - 1))][y + (1 << (j - 1))]));
            }
          }
        }
      }
    }
  }

  int Query(const int& x1, const int& y1, const int& x2, const int& y2) {
    int i = static_cast<int>(log2(x2 - x1 + 1));
    int j = static_cast<int>(log2(y2 - y1 + 1));
    int min1 = sparse_table_[i][j][x1][y1];
    int min2 = sparse_table_[i][j][x2 - (1 << i) + 1][y1];
    int min3 = sparse_table_[i][j][x1][y2 - (1 << j) + 1];
    int min4 = sparse_table_[i][j][x2 - (1 << i) + 1][y2 - (1 << j) + 1];
    return std::min(std::min(min1, min2), std::min(min3, min4));
  }
};

int main() {
  freopen("input.txt", "r", stdin);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int m = 0;
  int n = 0;
  std::cin >> m >> n;
  std::vector<std::vector<int>> values(m, std::vector<int>(n));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> values[i][j];
    }
  }

  int q = 0;
  std::cin >> q;
  SparseTable st(values, m, n);
  for (int i = 0; i < q; ++i) {
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    std::cin >> x1 >> y1 >> x2 >> y2;
    std::cout << st.Query(x1 - 1, y1 - 1, x2 - 1, y2 - 1) << '\n';
  }
}