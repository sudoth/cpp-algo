#include <iostream>
#include <vector>

class DSU {
 public:
  DSU() = default;
  explicit DSU(const int& n) {
    parent_.resize(n);
    rank_.resize(n);
    for (int i = 0; i < n; ++i) {
      parent_[i] = i;
    }
  }
  int FindSet(const int& x);
  void Union(int& x, int& y);

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
    } else if (rank_[x] > rank_[y]) {
      parent_[y] = x;
    } else {
      parent_[x] = y;
      ++rank_[y];
    }
  }
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<std::pair<int, int>> edges;

  for (int i = 0; i < m; ++i) {
    int u = 0;
    int v = 0;
    std::cin >> u >> v;
    edges.emplace_back(u, v);
  }

  DSU dsu(n);
  int count = n - 1;
  int ans = 0;
  for (int i = 0; i < m; ++i) {
    if (dsu.FindSet(edges[i].first) != dsu.FindSet(edges[i].second)) {
      dsu.Union(edges[i].first, edges[i].second);
      --count;
      if (count == 0) {
        ans = i + 1;
        break;
      }
    }
  }
  std::cout << ans;
}