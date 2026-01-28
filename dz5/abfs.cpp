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
  auto BFS(const int&);
};

void Graph::AddEdge(const int& v, const int& u) {
  adj_[v].push_back(u);
}

auto Graph::BFS(const int& s) {
  std::vector<int> parent(size_, -1);
  std::vector<int> dist(size_, -1);
  std::queue<int> q;
  q.push(s);
  dist[s] = 0;
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (const auto& u : adj_[v]) {
      if (dist[u] == -1) {
        dist[u] = dist[v] + 1;
        parent[u] = v;
        q.push(u);
      }
    }
  }
  return BFSResult{dist, parent};
}

auto Recover(const std::vector<int> parent, const int& begin, const int& end) {
  std::vector<int> path;
  int tmp = end;
  while (tmp != begin) {
    path.push_back(tmp);
    tmp = parent[tmp];
  }
  path.push_back(tmp);
  return path;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  int a, b;
  std::cin >> a >> b;
  --a, --b;
  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    graph.AddEdge(u, v);
    graph.AddEdge(v, u);
  }
  auto[dist, parent] = graph.BFS(a);
  if (dist[b] == -1) {
    std::cout << -1;
  } else {
    std::cout << dist[b] << '\n';
    std::vector<int> path = std::move(Recover(parent, a, b));
    for (auto it = path.rbegin(); it != path.rend(); ++it) {
      std::cout << *it + 1 << ' ';
    }
  }
}