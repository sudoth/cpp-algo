#include <iostream>
#include <vector>

struct Graph {
  Graph() = default;
  explicit Graph(const int& n) {
    vertices = n;
    matrix.resize(n, std::vector<int>(n));
  }
  int vertices;
  std::vector<std::vector<int>> matrix;
};

void Floyd(Graph& graph) {
  for (int k = 0; k < graph.vertices; ++k) {
    for (int i = 0; i < graph.vertices; ++i) {
      for (int j = 0; j < graph.vertices; ++j) {
        graph.matrix[i][j] = std::min(graph.matrix[i][j], graph.matrix[i][k] + graph.matrix[k][j]);
      }
    }
  }
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
  Floyd(graph);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cout << graph.matrix[i][j] << " ";
    }
    std::cout << '\n';
  }
}