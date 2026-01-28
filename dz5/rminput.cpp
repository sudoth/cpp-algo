#include <iostream>
#include <vector>
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
  auto BFS(const int&);
};

void Graph::AddEdge(const int& v, const int& u, const int& w) {
  adj_[v].emplace_back(std::pair<int, int>(u, w));
}

auto Graph::BFS(const int& s) {
  int pos = 0;
  int num = 1;
  std::vector<int> dist(size_, -1);
  std::vector<std::queue<int>> at_dist(k_ + 1);
  at_dist[0].push(s);
  dist[s] = 0;
  while (num > 0) {
    while (at_dist[pos % (k_ + 1)].empty()) {
      ++pos;
    }
    int u = at_dist[pos % (k_ + 1)].front();
    at_dist[pos % (k_ + 1)].pop();
    --num;
    for (const auto& v : adj_[u]) {
      if (dist[u] + v.second < dist[v.first] || dist[v.first] == -1) {
        dist[v.first] = dist[u] + v.second;
        at_dist[dist[v.first] % (k_ + 1)].push(v.first);
        ++num;
      }
    }
  }
  return dist;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int n, m;
  std::cin >> n >> m;
  int a, b;
  std::cin >> a >> b;
  --a, --b;
  Graph graph(n, 10);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    --u, --v;
    graph.AddEdge(u, v, w);
  }
  std::vector<int> dist = graph.BFS(a);
  if (dist[b] == -1) {
    std::cout << -1;
  } else {
    std::cout << dist[b];
  }
}