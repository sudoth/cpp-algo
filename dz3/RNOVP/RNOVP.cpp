#include <iostream>
#include <vector>

struct Node {
  inline static int n = 0;
  int value;
  Node* previous = nullptr;
};

struct Stack {
  Node* head;
};

void PushBack(Stack* stack, int value) {
  auto node = new Node;
  node->value = value;
  if (Node::n == 0) {
    stack->head = node;
  } else {
    node->previous = stack->head;
    stack->head = node;
  }
  Node::n++;
}

void PopBack(Stack* stack) {
  Node* delted = stack->head;
  stack->head = stack->head->previous;
  delete delted;
  Node::n--;
}

int Size() {
  return Node::n;
}

void Clear(Stack* stack) {
  while (Node::n > 0) {
    std::cout << stack->head->value << ' ';
    if (Node::n == 1) {
      delete stack->head;
      Node::n--;
    } else {
      Node* delted = stack->head;
      stack->head = stack->head->previous;
      delete delted;
      Node::n--;
    }
  }
}

int main() {
  int n;
  std::cin >> n;
  int first_arr[501];
  for (int i = 1; i <= n; i++) {
    std::cin >> first_arr[i];
  }
  int m;
  std::cin >> m;
  int second_arr[501];
  for (int i = 1; i <= m; i++) {
    std::cin >> second_arr[i];
  }
  int dp[501][501]{};
  int previous[501]{};

  for (int i = 1; i <= n; i++) {
    int ind = 0;
    int best = 0;
    for (int j = 1; j <= m; j++) {
      dp[i][j] = dp[i - 1][j];
      if (first_arr[i] == second_arr[j] && dp[i - 1][j] < best + 1) {
        dp[i][j] = best + 1;
        previous[j] = ind;
      }
      if (first_arr[i] > second_arr[j] && dp[i - 1][j] > best) {
        best = dp[i - 1][j];
        ind = j;
      }
    }
  }

  int current = 0;
  for (int i = 1; i <= m; i++) {
    if (dp[n][current] < dp[n][i]) {
      current = i;
    }
  }
  Stack ans;
  while (current != 0) {
    PushBack(&ans, second_arr[current]);
    current = previous[current];
  }
  std::cout << Size() << '\n';
  Clear(&ans);
}