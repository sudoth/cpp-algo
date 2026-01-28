#include <iostream>

struct Node {
  inline static int64_t n = 0;
  int64_t value;
  Node* previous = nullptr;
};

struct Stack {
  Node* head;
};

void PushBack(Stack* stack, int64_t value) {
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

int64_t Size() {
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

int main(int argc, char** argv) {
  int64_t n;
  std::cin >> n;
  auto first_arr = new int64_t[n + 1];
  for (int64_t i = 1; i <= n; i++) {
    std::cin >> first_arr[i];
  }
  int64_t m;
  std::cin >> m;
  auto second_arr = new int64_t[m + 1];
  for (int64_t i = 1; i <= m; i++) {
    std::cin >> second_arr[i];
  }
  auto dp = new int64_t*[n + 1];
  for (int64_t i = 0; i <= n; i++) {
    auto arr = new int64_t[m + 1]{};
    dp[i] = arr;
  }
  auto previous = new int64_t[n + 1]{};

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (first_arr[i] == second_arr[j]) {
        dp[i][j] = 1;
        for (int k = 1; k < i; k++) {
          if (first_arr[k] < first_arr[i] && dp[i][j] < dp[k][j] + 1) {
            dp[i][j] = dp[k][j] + 1;
            previous[i] = k;
          }
        }
      } else {
        dp[i][j] = dp[i][j - 1];
      }
    }
  }

  int64_t current = 1;
  for (int64_t i = 1; i <= n; i++) {
    if (dp[current][m] < dp[i][m]) {
      current = i;
    }
  }
  Stack ans;
  while (current != 0) {
    PushBack(&ans, first_arr[current]);
    current = previous[current];
  }
  std::cout << Size() << '\n';
  Clear(&ans);
  delete[] first_arr;
  delete[] second_arr;
  for (int64_t i = 0; i < n + 1; i++) {
    delete[] dp[i];
  }
  delete[] dp;
  delete[] previous;
}