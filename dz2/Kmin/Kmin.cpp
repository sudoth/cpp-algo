#include <cstring>
#include <iostream>

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
      delete minqueue->head;
      minqueue->head = nullptr;
      minqueue->tail = nullptr;
      Node::n--;
      return;
    }
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
    std::cout << -1 << '\n';
    return -1;
  }
  return dequeue->head->value;
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n;
  std::cin >> n;
  int k;
  std::cin >> k;
  Minqueue minqueue;
  Dequeue dequeue;
  auto answer = new int[n - k + 1];
  for (int i = 0; i < k; i++) {
    int t;
    std::cin >> t;
    EnqueueMin(&minqueue, &dequeue, t);
  }
  for (int i = k; i < n; i++) {
    int t;
    std::cin >> t;
    answer[i - k] = MinMin(&dequeue);
    DequeueMin(&minqueue, &dequeue);
    EnqueueMin(&minqueue, &dequeue, t);
  }
  answer[n - k] = MinMin(&dequeue);
  for (int i = 0; i < n - k + 1; i++) {
    std::cout << answer[i] << '\n';
  }
  ClearMin(&minqueue, &dequeue);
  delete[] answer;
}