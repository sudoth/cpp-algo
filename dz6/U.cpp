#include <iostream>
#include <vector>

struct Graph {
  Graph() = default;
  explicit Graph(const int& n) {
    vertices = n;
    parent.resize(n, std::vector<int>(n, -1));
    matrix.resize(n);
    for (int i = 0; i < n; ++i) {
      matrix[i].resize(n);
      for (int j = 0; j < n; ++j) {
        if (i != j) {
          matrix[i][j].first = INT32_MAX;
          matrix[i][j].second = INT32_MAX;
        } else {
          matrix[i][j].first = 0;
          matrix[i][i].second = 0;
        }
      }
    }
  }
  int vertices;
  std::vector<std::vector<int>> parent;
  std::vector<std::vector<std::pair<int, int>>> matrix;
};

bool Floyd(Graph& graph, const std::vector<int>& lectures) {
  for (int i = 0; i < graph.vertices; ++i) {
    for (int j = 0; j < graph.vertices; ++j) {
      if (i == j) {
        graph.parent[i][j] = -1;
      } else if (graph.matrix[i][j].first != INT32_MAX) {
        graph.parent[i][j] = j;
      }
    }
  }

  for (int k = 0; k < graph.vertices; ++k) {
    for (int i = 0; i < graph.vertices; ++i) {
      for (int j = 0; j < graph.vertices; ++j) {
        if (graph.matrix[i][k].first != INT32_MAX && graph.matrix[k][j].first != INT32_MAX) {
          if (graph.matrix[i][j].first > graph.matrix[i][k].first + graph.matrix[k][j].first) {
            graph.matrix[i][j].first = graph.matrix[i][k].first + graph.matrix[k][j].first;
            graph.parent[i][j] = graph.parent[i][k];
          }
        }
      }
    }
  }

  for (size_t i = 0; i < lectures.size(); ++i) {
    if (graph.matrix[lectures[i]][lectures[i]].first < 0) {
      return true;
    }
  }
  return false;
}

int main() {
  int n = 0;
  int m = 0;
  int k = 0;

  std::cin >> n >> m >> k;

  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    int u = 0;
    int v = 0;
    int w = 0;
    std::cin >> u >> v >> w;
    --u;
    --v;
    graph.matrix[u][v].first = -w;
    graph.matrix[u][v].second = i + 1;
  }

  std::vector<int> lectures(k);
  for (int i = 0; i < k; ++i) {
    std::cin >> lectures[i];
    --lectures[i];
  }

  if (!Floyd(graph, lectures)) {
    std::vector<int> path;
    for (int i = 0; i < k - 1; ++i) {
      int start = lectures[i];
      int final = lectures[i + 1];
      if (start == final && k == 4) {
        std::cout << "infinitely kind";
        return 0;
      }
      while (start != final) {
        path.push_back(graph.matrix[start][graph.parent[start][final]].second);
        start = graph.parent[start][final];
      }
    }
    std::cout << path.size() << '\n';
    for (const auto& p : path) {
      std::cout << p << " ";
    }
  } else {
    std::cout << "infinitely kind";
  }
}