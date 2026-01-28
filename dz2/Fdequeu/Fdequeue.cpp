#include <cstring>
#include <iostream>

struct Node {
  inline static int n = 0;
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

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int m;
  std::cin >> m;
  Dequeue dequeue;
  for (int i = 0; i < m; i++) {
    char request[11];
    std::cin >> request;
    if (strcmp(request, "push_front") == 0) {
      int value;
      std::cin >> value;
      PushFront(&dequeue, value);
      std::cout << "ok" << '\n';
    }
    if (strcmp(request, "push_back") == 0) {
      int value;
      std::cin >> value;
      PushBack(&dequeue, value);
      std::cout << "ok" << '\n';
    }
    if (strcmp(request, "pop_front") == 0) {
      if (dequeue.n == 0) {
        std::cout << "error" << '\n';
      } else {
        std::cout << dequeue.head->value << '\n';
        PopFront(&dequeue);
      }
    }
    if (strcmp(request, "pop_back") == 0) {
      if (dequeue.n == 0) {
        std::cout << "error" << '\n';
      } else {
        std::cout << dequeue.tail->value << '\n';
        PopBack(&dequeue);
      }
    }
    if (strcmp(request, "front") == 0) {
      if (dequeue.n == 0) {
        std::cout << "error" << '\n';
      } else {
        std::cout << dequeue.head->value << '\n';
      }
    }
    if (strcmp(request, "back") == 0) {
      if (dequeue.n == 0) {
        std::cout << "error" << '\n';
      } else {
        std::cout << dequeue.tail->value << '\n';
      }
    }
    if (strcmp(request, "size") == 0) {
      std::cout << dequeue.n << '\n';
    }
    if (strcmp(request, "clear") == 0) {
      Clear(&dequeue);
      std::cout << "ok" << '\n';
    }
    if (strcmp(request, "exit") == 0) {
      Clear(&dequeue);
      std::cout << "bye" << '\n';
      return 0;
    }
  }
  Clear(&dequeue);
}