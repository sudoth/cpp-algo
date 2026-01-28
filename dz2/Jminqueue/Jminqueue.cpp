#include <iostream>
#include <cstring>

struct Node {
  inline static int n = 0;
  int value;
  struct Node* next = nullptr;
  struct Node* previous = nullptr;
};

struct Minqueue {
  Node* head = nullptr;
  Node* tail = nullptr;
};

struct DeqNode {
  inline static int n = 0;
  int value;
  struct DeqNode* next = nullptr;
  struct DeqNode* previous = nullptr;
};

struct Dequeue {
  DeqNode* head = nullptr;
  DeqNode* tail = nullptr;
};

void PushFront(Dequeue* dequeue, int value) {
  if (DeqNode::n == 0) {
    auto node = new DeqNode;
    node->value = value;
    dequeue->tail = node;
    dequeue->head = node;
  } else {
    auto node = new DeqNode;
    node->value = value;
    node->previous = dequeue->head;
    dequeue->head->next = node;
    dequeue->head = node;
  }
  DeqNode::n++;
}
void PushBack(Dequeue* dequeue, int value) {
  if (DeqNode::n == 0) {
    auto node = new DeqNode;
    node->value = value;
    dequeue->tail = node;
    dequeue->head = node;
  } else {
    auto node = new DeqNode;
    node->value = value;
    node->next = dequeue->tail;
    dequeue->tail->previous = node;
    dequeue->tail = node;
  }
  DeqNode::n++;
}
void PopFront(Dequeue* dequeue) {
  if (DeqNode::n == 1) {
    delete dequeue->head;
    dequeue->head = nullptr;
    dequeue->tail = nullptr;
    DeqNode::n--;
    return;
  }
  DeqNode* deleted_node = dequeue->head;
  dequeue->head = dequeue->head->previous;
  dequeue->head->next = nullptr;
  delete deleted_node;
  DeqNode::n--;
}

void PopBack(Dequeue* dequeue) {
  if (DeqNode::n == 1) {
    delete dequeue->tail;
    dequeue->head = nullptr;
    dequeue->tail = nullptr;
    DeqNode::n--;
    return;
  }
  DeqNode* deleted_node = dequeue->tail;
  dequeue->tail = dequeue->tail->next;
  dequeue->tail->previous = nullptr;
  delete deleted_node;
  DeqNode::n--;
}

void Clear(Dequeue* dequeue) {
  while (DeqNode::n > 0) {
    if (DeqNode::n == 1) {
      delete dequeue->tail;
      dequeue->head = nullptr;
      dequeue->tail = nullptr;
      DeqNode::n--;
      continue;
    }
    DeqNode* deleted_node = dequeue->tail;
    dequeue->tail = dequeue->tail->next;
    dequeue->tail->previous = nullptr;
    delete deleted_node;
    DeqNode::n--;
  }
}

void EnqueueMin(Minqueue* minqueue, Dequeue* dequeue, int value) {
  if (Node::n == 0) {
    auto node = new Node;
    node->value = value;
    minqueue->tail = node;
    minqueue->head = node;
    PushFront(dequeue, value);
  } else {
    auto node = new Node;
    node->value = value;
    node->next = minqueue->tail;
    minqueue->tail->previous = node;
    minqueue->tail = node;
    while (DeqNode::n > 0) {
      if (dequeue->tail->value > value) {
        PopBack(dequeue);
      } else {
        break;
      }
    }
    PushBack(dequeue, value);
  }
  Node::n++;
}

void DequeueMin(Minqueue* minqueue, Dequeue* dequeue) {
  if (Node::n == 0) {
    std::cout << "error" << '\n';
  } else {
    if (dequeue->head->value == minqueue->head->value) {
      PopFront(dequeue);
    }
    if (Node::n == 1) {
      std::cout << minqueue->head->value << '\n';
      delete minqueue->head;
      minqueue->head = nullptr;
      minqueue->tail = nullptr;
      Node::n--;
      return;
    }
    std::cout << minqueue->head->value << '\n';
    Node* deleted_node = minqueue->head;
    minqueue->head = minqueue->head->previous;
    minqueue->head->next = nullptr;
    deleted_node->previous = nullptr;
    delete deleted_node;
    Node::n--;
  }
}

void ClearMin(Minqueue* minqueue, Dequeue* dequeue) {
  while (Node::n > 0) {
    if (Node::n == 1) {
      delete minqueue->tail;
      minqueue->head = nullptr;
      minqueue->tail = nullptr;
      Node::n--;
      continue;
    }
    Node* deleted_node = minqueue->tail;
    minqueue->tail = minqueue->tail->next;
    minqueue->tail->previous = nullptr;
    deleted_node->next = nullptr;
    delete deleted_node;
    Node::n--;
  }
  Clear(dequeue);
}

int MinMin(Dequeue* dequeue) {
  if (Node::n == 0) {
    return -1;
  }
  return dequeue->head->value;
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int m;
  std::cin >> m;
  Minqueue minqueue;
  Dequeue dequeue;
  for (int i = 0; i < m; i++) {
    char request[69];
    std::cin >> request;
    if (strcmp(request, "enqueue") == 0) {
      int value;
      std::cin >> value;
      std::cout << "ok" << '\n';
      EnqueueMin(&minqueue, &dequeue, value);
    }
    if (strcmp(request, "dequeue") == 0) {
      DequeueMin(&minqueue, &dequeue);
    }
    if (strcmp(request, "front") == 0) {
      if (Node::n == 0) {
        std::cout << "error" << '\n';
      } else {
        std::cout << minqueue.head->value << '\n';
      }
    }
    if (strcmp(request, "size") == 0) {
      std::cout << Node::n << '\n';
    }
    if (strcmp(request, "clear") == 0) {
      ClearMin(&minqueue, &dequeue);
      std::cout << "ok" << '\n';
    }
    if (strcmp(request, "min") == 0) {
      int t = MinMin(&dequeue);
      if (t == -1) {
        std::cout << "error" << '\n';
      } else {
        std::cout << t << '\n';
      }
    }
  }
  ClearMin(&minqueue, &dequeue);
}