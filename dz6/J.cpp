#include <iostream>
#include <vector>
#include <queue>

struct Graph {
  Graph() = default;
  explicit Graph(const int& n) {
    matrix.resize(n);
    vertices = n;
  }
  int vertices;
  std::vector<std::vector<int>> matrix;
};

std::vector<int> Dijkstra(const Graph& graph, const int& s) {
  std::vector<int> dist(graph.vertices, INT32_MAX);
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
    for (int j = 0; j < graph.vertices; ++j) {
      if (v != j && graph.matrix[v][j] != -1) {
        if (dist[v] + graph.matrix[v][j] < dist[j]) {
          dist[j] = dist[v] + graph.matrix[v][j];
          queue.emplace(dist[j], j);
        }
      }
    }
  }
  return dist;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  int s = 0;
  int f = 0;

  std::cin >> n >> s >> f;
  --s;
  --f;
  Graph graph(n);
  for (int i = 0; i < n; ++i) {
    graph.matrix[i].resize(n);
    for (int j = 0; j < n; ++j) {
      std::cin >> graph.matrix[i][j];
    }
  }
  auto dist = Dijkstra(graph, s);
  dist[f] == INT32_MAX ? std::cout << -1 : std::cout << dist[f];
}