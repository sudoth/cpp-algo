#include <iostream>
#include <vector>

struct Edge {
  Edge() = default;
  Edge(const int& u, const int& v, const int& w) : u_(u), v_(v), w_(w) {
  }
  int u_;
  int v_;
  int w_;
};

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

int64_t KruskalMST(const std::vector<Edge>& edges, const int& n) {
  DSU dsu(n);
  int64_t count = 0;
  for (size_t i = 0; i < edges.size(); ++i) {
    int u = edges[i].u_;
    int v = edges[i].v_;
    int w = edges[i].w_;
    if (dsu.FindSet(v) != dsu.FindSet(u)) {
      dsu.Union(v, u);
      count += w;
    }
  }
  return count;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<Edge> edges;
  for (int i = 0; i < m; ++i) {
    int u = 0;
    int v = 0;
    int w = 0;
    std::cin >> u >> v >> w;
    --u;
    --v;
    edges.emplace_back(u, v, w);
  }
  std::cout << KruskalMST(edges, n);
}