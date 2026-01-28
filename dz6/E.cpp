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

struct Graph {
  std::vector<Edge> edges;
};

int64_t BoruvkaMST(const Graph& graph, const int& n) {
  DSU dsu(n);
  int64_t weight = 0;
  int size = n;
  while (size > 1) {
    std::vector<Edge> min_edge;
    for (int i = 0; i < n; ++i) {
      min_edge.emplace_back(i, i, INT32_MAX);
    }
    for (const auto& edge : graph.edges) {
      int comp_v = dsu.FindSet(edge.u_);
      int comp_u = dsu.FindSet(edge.v_);
      if (comp_u != comp_v) {
        if (edge.w_ < min_edge[comp_v].w_) {
          min_edge[comp_v] = edge;
        }
        if (edge.w_ < min_edge[comp_u].w_) {
          min_edge[comp_u] = edge;
        }
      }
    }
    for (auto& edge : min_edge) {
      if (edge.w_ == INT32_MAX) {
        continue;
      }
      if (dsu.FindSet(edge.u_) != dsu.FindSet(edge.v_)) {
        weight += edge.w_;
        dsu.Union(edge.u_, edge.v_);
        --size;
      }
    }
  }
  return weight;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Graph graph;
  for (int i = 0; i < m; ++i) {
    int u = 0;
    int v = 0;
    int w = 0;
    std::cin >> u >> v >> w;
    --u;
    --v;
    graph.edges.emplace_back(u, v, w);
  }

  std::cout << BoruvkaMST(graph, n);
}