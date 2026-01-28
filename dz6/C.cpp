#include <iostream>
#include <vector>
#include <queue>

struct Graph {
  Graph() = default;
  explicit Graph(const int& n) {
    adj.resize(n);
  }
  std::vector<std::vector<std::pair<int, int>>> adj;
};

int64_t PrimMST(const Graph& graph) {
  std::vector<bool> used(graph.adj.size());
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> queue;
  queue.emplace(0, 0);
  int64_t weight = 0;
  while (!queue.empty()) {
    int w = queue.top().first;
    int v = queue.top().second;
    queue.pop();
    if (!used[v]) {
      weight += w;
      used[v] = true;
    }
    for (const auto& u : graph.adj[v]) {
      if (!used[u.first]) {
        queue.emplace(u.second, u.first);
      }
    }
  }
  return weight;
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    int u = 0;
    int v = 0;
    int w = 0;
    std::cin >> u >> v >> w;
    --u;
    --v;
    graph.adj[u].emplace_back(v, w);
    graph.adj[v].emplace_back(u, w);
  }
  std::cout << PrimMST(graph);
}