#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

class Graph {
  int size_;
  int k_;
  std::vector<std::vector<std::pair<int, int>>> adj_;
  struct BFSResult {
    std::vector<int> dist;
    std::vector<int> parent;
  };

 public:
  Graph() = default;
  explicit Graph(const int& n, const int& k) : size_(n), k_(k) {
    adj_.resize(size_);
  }
  void AddEdge(const int&, const int&, const int&);
  auto BFS(const int&, const int&);
  void AddVertices();
};

void Graph::AddEdge(const int& v, const int& u, const int& w = 1) {
  adj_[v].emplace_back(std::pair<int, int>(u, w));
}

auto Graph::BFS(const int& s, const int& finish) {
  int n = (size_ - 1) * k_;
  std::vector<int> dist(size_, -1);
  std::vector<std::queue<int>> at_dist(k_ + 1);
  at_dist[0].push(s);
  dist[s] = 0;
  for (int i = 0; i < n; ++i) {
    while (!at_dist[i % (k_ + 1)].empty()) {
      int v = at_dist[i % (k_ + 1)].front();
      at_dist[i % (k_ + 1)].pop();
      for (const auto& u : adj_[v]) {
        if (dist[u.first] > dist[v] + u.second || dist[u.first] == -1) {
          dist[u.first] = dist[v] + u.second;
          at_dist[dist[u.first] % (k_ + 1)].push(u.first);
        }
      }
    }
  }
  return dist[finish];
}

void Graph::AddVertices() {
  for (int v = 0; v < size_; ++v) {
    for (auto& u : adj_[v]) {
      if (std::find(adj_[u.first].begin(), adj_[u.first].end(), std::pair<int, int>(v, 0)) == adj_[u.first].end()) {
        AddEdge(u.first, v);
      }
    }
  }
}

int main() {
  freopen("input.txt", "r", stdin);
  int n, m;
  std::cin >> n >> m;
  Graph graph(n, 1);
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    graph.AddEdge(u, v, 0);
  }
  graph.AddVertices();
  int k;
  std::cin >> k;
  for (int i = 0; i < k; ++i) {
    int a, b;
    std::cin >> a >> b;
    --a, --b;
    std::cout << graph.BFS(a, b) << '\n';
  }
}