#include <iostream>
#include <vector>
#include <queue>

struct Graph {
  Graph() = default;
  explicit Graph(const int& n) {
    adj.resize(n);
    vertices = n;
  }
  int vertices;
  std::vector<std::vector<std::pair<int, int>>> adj;
};

std::vector<int> Dijkstra(const Graph& graph, const int& s) {
  int max = 2009000999;
  std::vector<int> dist(graph.vertices, max);
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> queue;
  dist[s] = 0;
  queue.emplace(0, s);
  while (!queue.empty()) {
    auto top = queue.top();
    int w = top.first;
    int v = top.second;
    queue.pop();
    if (w > dist[v]) {
      continue;
    }
    for (const auto& u : graph.adj[v]) {
      if (dist[v] + u.second < dist[u.first]) {
        dist[u.first] = dist[v] + u.second;
        queue.emplace(dist[u.first], u.first);
      }
    }
  }
  return dist;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int k = 0;
  std::cin >> k;
  for (int i = 0; i < k; ++i) {
    int n = 0;
    int m = 0;
    std::cin >> n >> m;
    Graph graph(n);
    for (int j = 0; j < m; ++j) {
      int u = 0;
      int v = 0;
      int w = 0;
      std::cin >> u >> v >> w;
      graph.adj[u].emplace_back(v, w);
      graph.adj[v].emplace_back(u, w);
    }
    int s = 0;
    std::cin >> s;
    auto distance = Dijkstra(graph, s);
    for (const auto& dist : distance) {
      std::cout << dist << " ";
    }
    std::cout << '\n';
  }
}