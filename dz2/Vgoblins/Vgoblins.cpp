#include <iostream>
#include <cstring>

struct Node {
  int value;
  struct Node* next = nullptr;
  struct Node* previous = nullptr;
};

struct Dequeue {
  int n = 0;
  Node* head = nullptr;
  Node* tail = nullptr;
};

void PushFront(Dequeue* dequeue, int value) {
  if (dequeue->n == 0) {
    auto node = new Node;
    node->value = value;
    dequeue->tail = node;
    dequeue->head = node;
  } else {
    auto node = new Node;
    node->value = value;
    node->previous = dequeue->head;
    dequeue->head->next = node;
    dequeue->head = node;
  }
  dequeue->n++;
}
void PushBack(Dequeue* dequeue, int value) {
  if (dequeue->n == 0) {
    auto node = new Node;
    node->value = value;
    dequeue->tail = node;
    dequeue->head = node;
  } else {
    auto node = new Node;
    node->value = value;
    node->next = dequeue->tail;
    dequeue->tail->previous = node;
    dequeue->tail = node;
  }
  dequeue->n++;
}
void PopFront(Dequeue* dequeue) {
  if (dequeue->n == 1) {
    delete dequeue->head;
    dequeue->head = nullptr;
    dequeue->tail = nullptr;
    dequeue->n--;
    return;
  }
  Node* deleted_node = dequeue->head;
  dequeue->head = dequeue->head->previous;
  dequeue->head->next = nullptr;
  delete deleted_node;
  dequeue->n--;
}

void PopBack(Dequeue* dequeue) {
  if (dequeue->n == 1) {
    delete dequeue->tail;
    dequeue->head = nullptr;
    dequeue->tail = nullptr;
    dequeue->n--;
    return;
  }
  Node* deleted_node = dequeue->tail;
  dequeue->tail = dequeue->tail->next;
  dequeue->tail->previous = nullptr;
  delete deleted_node;
  dequeue->n--;
}

void Clear(Dequeue* dequeue) {
  while (dequeue->n > 0) {
    if (dequeue->n == 1) {
      delete dequeue->tail;
      dequeue->head = nullptr;
      dequeue->tail = nullptr;
      dequeue->n--;
      continue;
    }
    Node* deleted_node = dequeue->tail;
    dequeue->tail = dequeue->tail->next;
    dequeue->tail->previous = nullptr;
    delete deleted_node;
    dequeue->n--;
  }
}

// left - begin right - end

int main() {
  int n;
  std::cin >> n;
  char request;
  int value;
  Dequeue left;
  Dequeue right;
  for (int i = 0; i < n; i++) {
    std::cin >> request;
    if (request == '+') {
      std::cin >> value;
      PushBack(&right, value);
    }
    if (request == '*') {
      std::cin >> value;
      PushFront(&right, value);
    }
    if (request == '-') {
      std::cout << left.head->value << '\n';
      PopFront(&left);
    }
    if (left.n < right.n) {
      PushBack(&left, right.head->value);
      PopFront(&right);
    }
  }
  Clear(&left);
  Clear(&right);
}