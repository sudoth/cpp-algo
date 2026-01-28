#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Структура для представления ребра графа
struct Edge {
    int to;
    int capacity;
    int flow;
    int reverseEdge;
};

// Функция для добавления ребра в граф
void addEdge(vector<vector<Edge>>& graph, int v, int u, int capacity) {
    Edge forwardEdge = { u, capacity, 0, static_cast<int>(graph[u].size()) };
    Edge reverseEdge = { v, 0, 0, static_cast<int>(graph[v].size()) };
    graph[v].push_back(forwardEdge);
    graph[u].push_back(reverseEdge);
}

// Функция для нахождения максимального потока алгоритмом Эдмондса-Карпа
int edmondsKarp(vector<vector<Edge>>& graph, int source, int sink) {
    int numVertices = graph.size();
    vector<int> parent(numVertices);
    int maxFlow = 0;

    while (true) {
        fill(parent.begin(), parent.end(), -1);
        parent[source] = -2;
        queue<int> q;
        q.push(source);

        while (!q.empty()) { 
            int u = q.front();
            q.pop();

            for (auto& edge : graph[u]) {
                int next = edge.to;
                int capacity = edge.capacity;
                int flow = edge.flow;
                int reverseEdge = edge.reverseEdge;

                if (parent[next] == -1 && capacity > flow) {
                    parent[next] = u;
                    q.push(next);
                }
            }
        }

        if (parent[sink] == -1) {
            break;
        }

        int minCapacity = INT_MAX;
        int node = sink;

        while (node != source) {
            int prevNode = parent[node];
            for (auto& edge : graph[prevNode]) {
                if (edge.to == node) {
                    minCapacity = min(minCapacity, edge.capacity - edge.flow);
                    break;
                }
            }
            node = prevNode;
        }

        node = sink;

        while (node != source) {
            int prevNode = parent[node];
            for (auto& edge : graph[prevNode]) {
                if (edge.to == node) {
                    edge.flow += minCapacity;
                    graph[node][edge.reverseEdge].flow -= minCapacity;
                    break;
                }
            }
            node = prevNode;
        }

        maxFlow += minCapacity;
    }

    return maxFlow;
}

int main() {
    int n, m;
    cin >> n >> m;

    // Создание пустого графа
    vector<vector<Edge>> graph(n);

    // Заполнение графа значениями пропускных способностей из входных данных
    for (int i = 0; i < m; ++i) {
        int u, v, capacity;
        cin >> u >> v >> capacity;
        addEdge(graph, u - 1, v - 1, capacity);
    }

    int source = 0;
    int sink = n - 1;

    int maxFlow = edmondsKarp(graph, source, sink);
    cout << maxFlow << endl;

    return 0;
}