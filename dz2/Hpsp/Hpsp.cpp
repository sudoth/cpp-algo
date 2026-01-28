#include <cstring>
#include <iostream>

struct Node {
  inline static int n = 0;
  char value;
  Node* prev = nullptr;
};

struct Stack {
  Node* head;
};

void PushBack(Stack* stack, char value) {
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

int main() {
  auto brackets = new char[100007];
  std::cin >> brackets;
  int n = strlen(brackets);
  Stack stack;
  for (int i = 0; i < n; i++) {
    char t = brackets[i];
    if (Node::n == 0) {
      PushBack(&stack, t);
      continue;
    }
    if ((stack.head->value == '(' && t == ')') || (stack.head->value == '[' && t == ']') ||
        (stack.head->value == '{' && t == '}')) {
      PopBack(&stack);
    } else {
      PushBack(&stack, t);
    }
  }
  if (Node::n == 0) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
  Clear(&stack);
  delete[] brackets;
}