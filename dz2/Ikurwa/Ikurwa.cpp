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

bool IsDigit(char a) {
  return a <= '9' && a >= '0';
}

int main() {
  freopen("input.txt", "r", stdin);
  Stack stack;
  char c;
  while (std::cin >> c) {
    if (c == ' ') {
      continue;
    }
    if (IsDigit(c)) {
      PushBack(&stack, c - '0');
    } else {
      int a;
      int b;
      b = stack.head->value;
      PopBack(&stack);
      a = stack.head->value;
      PopBack(&stack);
      if (c == '*') {
        PushBack(&stack, a * b);
      }
      if (c == '+') {
        PushBack(&stack, a + b);
      }
      if (c == '-') {
        PushBack(&stack, a - b);
      }
    }
  }
  std::cout << stack.head->value;
  Clear(&stack);
}