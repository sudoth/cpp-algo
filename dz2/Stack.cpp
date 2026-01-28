#include <cstring>
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

int main() {
  int n;
  std::cin >> n;
  Stack stack;
  for (int i = 0; i < n; i++) {
    char request[6];
    std::cin >> request;
    if (strcmp(request, "push") == 0) {
      int value;
      std::cin >> value;
      PushBack(&stack, value);
      std::cout << "ok" << '\n';
    }
    if (strcmp(request, "pop") == 0) {
      std::cout << stack.head->value << '\n';
      PopBack(&stack);
    }
    if (strcmp(request, "back") == 0) {
      std::cout << stack.head->value << '\n';
    }
    if (strcmp(request, "size") == 0) {
      std::cout << Size() << '\n';
    }
    if (strcmp(request, "clear") == 0) {
      Clear(&stack);
      std::cout << "ok" << '\n';
    }
    if (strcmp(request, "exit") == 0) {
      while (Node::n > 0) {
        if (Node::n == 1) {
          delete stack.head;
          Node::n--;
        } else {
          auto delted = stack.head;
          stack.head = stack.head->prev;
          delete delted;
          Node::n--;
        }
      }
      std::cout << "bye" << '\n';
      return 0;
    }
  }
  while (Node::n > 0) {
    if (Node::n == 1) {
      delete stack.head;
      Node::n--;
    } else {
      auto delted = stack.head;
      stack.head = stack.head->prev;
      delete delted;
      Node::n--;
    }
  }
}