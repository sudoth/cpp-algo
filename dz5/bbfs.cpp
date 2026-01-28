#include <iostream>
#include <vector>
#include <queue>

class Graph {
  int size_;
  std::vector<std::vector<int>> adj_;
  struct BFSResult {
    std::vector<int> dist;
    std::vector<int> parent;
  };

 public:
  Graph() = default;
  explicit Graph(const int& n) : size_(n) {
    adj_.resize(size_);
  }
  void AddEdge(const int&, const int&);
  bool BFS(const int&, std::vector<int>&) const;
  bool IsBipartite() const;
};

void Graph::AddEdge(const int& v, const int& u) {
  adj_[v].push_back(u);
}

bool Graph::BFS(const int& s, std::vector<int>& color) const {
  std::queue<int> q;
  q.push(s);
  if (color[s] == -1) {
    color[s] = 0;
  }
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (const auto& u : adj_[v]) {
      if (color[u] == color[v]) {
        return false;
      }
      if (color[u] == -1) {
        color[u] = (color[v] + 1) % 2;
        q.push(u);
      }
    }
  }
  return true;
}

bool Graph::IsBipartite() const {
  std::vector<int> color(size_, -1);
  for (int i = 0; i < size_; ++i) {
    if (!this->BFS(i, color)) {
      return false;
    }
  }
  return true;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    graph.AddEdge(u, v);
    graph.AddEdge(v, u);
  }
  std::cout << (graph.IsBipartite() ? "YES" : "NO");
}