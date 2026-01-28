#ifndef STACK_H
#define STACK_H
#include <deque>
#include <iostream>
#include <vector>
#include <list>
#include <memory>
template <typename T, typename Container = std::deque<T>>
class Stack {
 public:
  Container container;
  Stack() = default;
  ~Stack() = default;
  Stack(const Stack&);
  Stack(Stack&&);
  explicit Stack(const Container&);
  template <typename InputIterator>
  Stack(InputIterator, InputIterator);
  Stack& operator=(const Stack&);
  Stack& operator=(Stack&&);
  T& Top();
  const T& Top() const;
  bool Empty() const;
  size_t Size() const;
  template <typename U>
  void Push(U&&);
  void Push(const T&);
  template <typename... Args>
  void Emplace(Args&&...);
  void Pop();
  void Swap(Stack&);
};

template <typename T, typename Container>
Stack<T, Container>::Stack(const Stack& other) {
  container = other.container;
}

template <typename T, typename Container>
Stack<T, Container>::Stack(Stack&& other) {
  container = std::move(other.container);
}

template <typename T, typename Container>
Stack<T, Container>::Stack(const Container& other) {
  container = other;
}

template <typename T, typename Container>
template <typename InputIterator>
Stack<T, Container>::Stack(InputIterator begin, InputIterator end) {
  container = Container(begin, end);
}

template <typename T, typename Container>
Stack<T, Container>& Stack<T, Container>::operator=(const Stack& other) {
  container = other.container;
  return *this;
}

template <typename T, typename Container>
Stack<T, Container>& Stack<T, Container>::operator=(Stack&& other) {
  container = std::move(other.container);
  return *this;
}

template <typename T, typename Container>
T& Stack<T, Container>::Top() {
  return container.back();
}

template <typename T, typename Container>
const T& Stack<T, Container>::Top() const {
  return container.back();
}

template <typename T, typename Container>
bool Stack<T, Container>::Empty() const {
  return container.empty();
}

template <typename T, typename Container>
size_t Stack<T, Container>::Size() const {
  return container.size();
}

template <typename T, typename Container>
template <typename U>
void Stack<T, Container>::Push(U&& other) {
  container.push_back(std::forward<T>(other));
}

template <typename T, typename Container>
void Stack<T, Container>::Push(const T& other) {
  container.push_back(other);
}

template <typename T, typename Container>
template <typename... Args>
void Stack<T, Container>::Emplace(Args&&... args) {
  container.emplace_back(std::forward<Args>(args)...);
}

template <typename T, typename Container>
void Stack<T, Container>::Pop() {
  return container.pop_back();
}

template <typename T, typename Container>
void Stack<T, Container>::Swap(Stack& other) {
  std::swap(container, other.container);
}

#endif