#include <iostream>
#include <vector>

class FenwickTree {
  std::vector<std::vector<std::vector<int>>> fenwick_tree_;

 public:
  explicit FenwickTree(const int& n) {
    fenwick_tree_.resize(n, std::vector<std::vector<int>>(n, std::vector<int>(n, 0)));
  }

  void Update(const int& x, const int& y, const int& z, const int& val) {
    int n = static_cast<int>(fenwick_tree_.size());
    for (int i = x; i < n; i = (i | (i + 1))) {
      for (int j = y; j < n; j = (j | (j + 1))) {
        for (int k = z; k < n; k = (k | (k + 1))) {
          fenwick_tree_[i][j][k] += val;
        }
      }
    }
  }

  int Query(const int& x, const int& y, const int& z) {
    int sum = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
      for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
        for (int k = z; k >= 0; k = (k & (k + 1)) - 1) {
          sum += fenwick_tree_[i][j][k];
        }
      }
    }
    return sum;
  }

  int Query(int x1, int y1, int z1, int x2, int y2, int z2) {
    return Query(x2, y2, z2) - Query(x1 - 1, y2, z2) - Query(x2, y1 - 1, z2) - Query(x2, y2, z1 - 1) +
           Query(x1 - 1, y1 - 1, z2) + Query(x1 - 1, y2, z1 - 1) + Query(x2, y1 - 1, z1 - 1) -
           Query(x1 - 1, y1 - 1, z1 - 1);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  std::cin >> n;
  FenwickTree fenwick_tree(n);

  for (;;) {
    int type = 0;
    std::cin >> type;
    if (type == 2) {
      int x1 = 0;
      int y1 = 0;
      int z1 = 0;
      int x2 = 0;
      int y2 = 0;
      int z2 = 0;
      std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
      std::cout << fenwick_tree.Query(x1, y1, z1, x2, y2, z2) << '\n';
    } else if (type == 1) {
      int x = 0;
      int y = 0;
      int z = 0;
      int value = 0;
      std::cin >> x >> y >> z >> value;
      fenwick_tree.Update(x, y, z, value);
    } else if (type == 3) {
      break;
    }
  }
}