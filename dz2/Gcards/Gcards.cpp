#include <iostream>

struct Node {
  inline static int n = 0;
  int value;
  struct Node* next = nullptr;
  struct Node* previous = nullptr;
};

struct Dequeue {
  Node* head = nullptr;
  Node* tail = nullptr;
  int n = 0;
};

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

int PopFront(Dequeue* dequeue) {
  if (dequeue->n == 1) {
    int x = dequeue->head->value;
    delete dequeue->head;
    dequeue->head = nullptr;
    dequeue->tail = nullptr;
    dequeue->n--;
    return x;
  }
  int x = dequeue->head->value;
  Node* deleted_node = dequeue->head;
  dequeue->head = dequeue->head->previous;
  dequeue->head->next = nullptr;
  delete deleted_node;
  dequeue->n--;
  return x;
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

bool IsNotEmpty(Dequeue* dequeue) {
  return dequeue->n != 0;
}

int main() {
  Dequeue dequeue1;
  Dequeue dequeue2;
  for (int i = 0; i < 5; i++) {
    int t;
    std::cin >> t;
    PushBack(&dequeue1, t);
  }
  for (int i = 0; i < 5; i++) {
    int t;
    std::cin >> t;
    PushBack(&dequeue2, t);
  }
  int n = 0;
  while (IsNotEmpty(&dequeue1) && IsNotEmpty(&dequeue2)) {
    if (n == 1000000) {
      Clear(&dequeue1);
      Clear(&dequeue2);
      std::cout << "botva";
      return 0;
    }
    int x = PopFront(&dequeue1);
    int y = PopFront(&dequeue2);
    if (x == 0 && y == 9) {
      PushBack(&dequeue1, x);
      PushBack(&dequeue1, y);
      n++;
      continue;
    }
    if (y == 0 && x == 9) {
      PushBack(&dequeue2, x);
      PushBack(&dequeue2, y);
      n++;
      continue;
    }
    if (x > y) {
      PushBack(&dequeue1, x);
      PushBack(&dequeue1, y);
      n++;
      continue;
    }
    if (x < y) {
      PushBack(&dequeue2, x);
      PushBack(&dequeue2, y);
      n++;
      continue;
    }
    PushBack(&dequeue1, x);
    PushBack(&dequeue2, y);
    n++;
  }
  if (IsNotEmpty(&dequeue1)) {
    std::cout << "first " << n;
  } else {
    std::cout << "second " << n;
  }
  Clear(&dequeue1);
  Clear(&dequeue2);
}