#include <iostream>
#include <vector>

class DSU {
 public:
  DSU() = default;
  explicit DSU(const int& n) {
    parent_.resize(n);
    rank_.resize(n);
    weight.resize(n);
    for (int i = 0; i < n; ++i) {
      parent_[i] = i;
    }
  }
  int FindSet(const int& x);
  void Union(int& x, int& y);
  std::vector<int> weight;

 private:
  std::vector<int> parent_;
  std::vector<int> rank_;
};

int DSU::FindSet(const int& x) {
  if (x == parent_[x]) {
    return x;
  }
  return parent_[x] = FindSet(parent_[x]);
}

void DSU::Union(int& x, int& y) {
  x = FindSet(x);
  y = FindSet(y);
  if (x != y) {
    if (rank_[x] < rank_[y]) {
      parent_[x] = y;
      weight[y] += weight[x];
    } else if (rank_[x] > rank_[y]) {
      parent_[y] = x;
      weight[x] += weight[y];
    } else {
      parent_[x] = y;
      weight[y] += weight[x];
      ++rank_[y];
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  DSU dsu(n);
  for (int i = 0; i < m; ++i) {
    int command = 0;
    std::cin >> command;
    if (command == 1) {
      int u = 0;
      int v = 0;
      int w = 0;
      std::cin >> u >> v >> w;
      --u;
      --v;
      dsu.Union(u, v);
      dsu.weight[dsu.FindSet(v)] += w;
    } else {
      int v = 0;
      std::cin >> v;
      --v;
      std::cout << dsu.weight[dsu.FindSet(v)] << '\n';
    }
  }
}