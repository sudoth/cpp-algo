#include <iostream>
#include <vector>
#include <queue>

class Graph {
 public:
  int size_;
  std::vector<std::vector<int>> adj_;
  struct BFSResult {
    std::vector<int> dist;
    std::vector<int> parent;
  };

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
  int a, b;
  std::cin >> a >> b;
  Graph graph(10000);
  for (int i = 1000; i < 10000; ++i) {
    if (i / 1000 != 9) {
      graph.AddEdge(i, i + 1000);
    }
    if (i % 10 != 1) {
      graph.AddEdge(i, i - 1);
    }
    graph.AddEdge(i, (i % 10) * 1000 + i / 10);
    graph.AddEdge(i, (i % 1000) * 10 + i / 1000);
  }
  auto[dist, parent] = graph.BFS(a);
  std::cout << dist[b] + 1 << '\n';
  std::vector<int> path = std::move(Recover(parent, a, b));
  for (auto it = path.rbegin(); it != path.rend(); ++it) {
    std::cout << *it << ' ';
  }
}