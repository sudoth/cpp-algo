#include <iostream>
#include <vector>
#include <queue>

struct Graph {
  Graph() = default;
  explicit Graph(const int& n) {
    vertices = n;
    capacity.resize(n, std::vector<int>(n));
    flow.resize(n, std::vector<int>(n));
  }
  int vertices;
  std::vector<std::vector<int>> capacity;
  std::vector<std::vector<int>> flow;
};

auto BFS(Graph& graph) {
  std::vector<int> dist(graph.vertices, INT32_MAX);
  std::queue<int> queue;
  dist[0] = 0;
  queue.push(0);
  while (!queue.empty()) {
    int v = queue.front();
    queue.pop();
    for (int i = 0; i < graph.vertices; ++i) {
      if (dist[i] == INT32_MAX && graph.flow[v][i] < graph.capacity[v][i]) {
        dist[i] = dist[v] + 1;
        queue.push(i);
      }
    }
  }
  return dist;
}

int DFS(Graph& graph, const int& v, const std::vector<int>& dist, int min_delta_flow) {
  if (v == graph.vertices - 1 || min_delta_flow == 0) {
    return min_delta_flow;
  }
  for (int i = 0; i < graph.vertices; ++i) {
    if (dist[i] == dist[v] + 1) {
      int delta_flow = DFS(graph, i, dist, std::min(min_delta_flow, graph.capacity[v][i] - graph.flow[v][i]));
      if (delta_flow > 0) {
        graph.flow[v][i] += delta_flow;
        graph.flow[i][v] -= delta_flow;
        return delta_flow;
      }
    }
  }
  return 0;
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    int u = 0;
    int v = 0;
    int capacity = 0;
    std::cin >> u >> v >> capacity;
    --u;
    --v;
    graph.capacity[u][v] = capacity;
  }

  int delta_flow = 0;
  auto dist = BFS(graph);
  while (dist[n - 1] != INT32_MAX) {
    delta_flow = DFS(graph, 0, dist, INT32_MAX);
    while (delta_flow > 0) {
      delta_flow = DFS(graph, 0, dist, INT32_MAX);
    }
    dist = BFS(graph);
  }
  int64_t max_flow = 0;
  for (int i = 0; i < n; ++i) {
    max_flow += graph.flow[0][i];
  }
  std::cout << max_flow;
}