#include <iostream>

struct Node {
  inline static int n = 0;
  int value;
  Node* prev = nullptr;
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
    node->prev = stack->head;
    stack->head = node;
  }
  Node::n++;
}

void PopBack(Stack* stack) {
  Node* delted = stack->head;
  stack->head = stack->head->prev;
  delete delted;
  Node::n--;
}

int Size() {
  return Node::n;
}

void Clear(Stack* stack) {
  while (Node::n > 0) {
    std::cout << stack->head->value << '\n';
    if (Node::n == 1) {
      delete stack->head;
      Node::n--;
    } else {
      Node* delted = stack->head;
      stack->head = stack->head->prev;
      delete delted;
      Node::n--;
    }
  }
}

void Find(int i, int j, Stack* stack, int** dp, int* weight) {
  if (dp[i][j] == 0) {
    return;
  }
  if (dp[i - 1][j] == dp[i][j]) {
    Find(i - 1, j, stack, dp, weight);
  } else {
    Find(i - 1, j - weight[i], stack, dp, weight);
    PushBack(stack, i);
  }
}

int main() {
  Stack ans;
  int n;
  int m;
  int weight[101];
  int cost[101];
  std::cin >> n;
  std::cin >> m;
  auto dp = new int*[101];
  for (int i = 0; i < 101; i++) {
    auto arr = new int[10001];
    dp[i] = arr;
  }

  for (int i = 1; i <= n; i++) {
    std::cin >> weight[i];
  }
  for (int i = 1; i <= n; i++) {
    std::cin >> cost[i];
  }

  for (int i = 0; i <= n; i++) {
    dp[i][0] = 0;
  }
  for (int i = 0; i <= m; i++) {
    dp[0][i] = 0;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (j >= weight[i]) {
        dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - weight[i]] + cost[i]);
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }
  Find(n, m, &ans, dp, weight);
  for (int i = 0; i < 101; i++) {
    delete[] dp[i];
  }
  delete[] dp;
  Clear(&ans);
}