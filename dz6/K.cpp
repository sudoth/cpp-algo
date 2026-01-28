#include <iostream>
#include <vector>
#include <algorithm>

struct Graph {
  Graph() = default;
  explicit Graph(const int& n) {
    vertices = n;
    matrix.resize(n, std::vector<int>(n));
    parent.resize(n, -1);
  }
  int vertices;
  std::vector<std::vector<int>> matrix;
  std::vector<int> parent;
};

int HasCycle(Graph& graph) {
  std::vector<int> dist(graph.vertices);
  int cycle = -1;

  for (int k = 0; k < graph.vertices; ++k) {
    cycle = -1;
    for (int i = 0; i < graph.vertices; ++i) {
      for (int j = 0; j < graph.vertices; ++j) {
        if (graph.matrix[i][j] != 100000) {
          if (dist[i] + graph.matrix[i][j] < dist[j]) {
            dist[j] = dist[i] + graph.matrix[i][j];
            graph.parent[j] = i;
            cycle = j;
          }
        }
      }
    }
  }

  if (cycle != -1) {
    for (int i = 0; i < graph.vertices; ++i) {
      cycle = graph.parent[cycle];
    }
  }

  return cycle;
}

int main() {
  int n = 0;
  std::cin >> n;
  Graph graph(n);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> graph.matrix[i][j];
    }
  }

  int cycle = HasCycle(graph);

  if (cycle == -1) {
    std::cout << "NO";
  } else {
    std::cout << "YES\n";
    std::vector<int> path;
    int i = cycle;

    do {
      path.push_back(i);
      i = graph.parent[i];
    } while (i != cycle);
    path.push_back(path.front());

    std::reverse(path.begin(), path.end());

    std::cout << path.size() << '\n';
    for (const auto& p : path) {
      std::cout << p + 1 << " ";
    }
  }
}