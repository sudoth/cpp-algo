#ifndef VECTOR_H
#define VECTOR_H
#define VECTOR_MEMORY_IMPLEMENTED

#include <iostream>
#include <numeric>
#include <exception>
#include <type_traits>
#include <memory>
#include <algorithm>
#pragma once

template <class A>
struct Vector {
  void* a_;
  size_t s_;
  size_t cap_;
  using ValueType = A;
  using Pointer = ValueType*;
  using ConstPointer = const ValueType*;
  using Reference = ValueType&;
  using ConstReference = const ValueType&;
  using SizeType = size_t;
  using Iterator = A*;
  using ConstIterator = const A*;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
  template <typename B>
  friend bool operator<=(const Vector<B>& start, const Vector<B>& finish);
  template <typename B>
  friend bool operator<(const Vector<B>& start, const Vector<B>& finish);
  template <typename B>
  friend bool operator>(const Vector<B>& start, const Vector<B>& finish);
  template <typename B>
  friend bool operator==(const Vector<B>& start, const Vector<B>& finish);
  template <typename B>
  friend bool operator>=(const Vector<B>& start, const Vector<B>& finish);

  void* Ex() {
    if (cap_ == 0) {
      auto new_a = operator new(sizeof(ValueType));
      return new_a;
    }
    auto new_a = operator new(cap_ * 2 * sizeof(ValueType));
    std::uninitialized_move_n(static_cast<Pointer>(a_), s_, static_cast<Pointer>(new_a));
    return new_a;
  }
  Vector() : a_(nullptr), s_(0), cap_(0) {
  }
  explicit Vector(size_t s) : Vector() {
    if (s == 0) {
      return;
    }
    auto new_a = operator new(sizeof(ValueType) * s);
    try {
      std::uninitialized_default_construct_n(static_cast<Pointer>(new_a), s);
    } catch (...) {
      operator delete(new_a);
      throw;
    }
    a_ = new_a;
    s_ = s;
    cap_ = s;
  }

  Vector(size_t s, ConstReference data) : Vector() {
    if (s == 0) {
      return;
    }
    auto new_a = operator new(sizeof(ValueType) * s);
    try {
      std::uninitialized_fill_n(static_cast<Pointer>(new_a), s, data);
    } catch (...) {
      operator delete(new_a);
      throw;
    }
    cap_ = s_ = s;
    a_ = new_a;
  }

  template <class Iterator, class = std::enable_if_t<std::is_base_of_v<
                                std::forward_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>>>
  Vector(Iterator start, Iterator finish) : Vector() {
    if (start == finish) {
      return;
    }
    size_t s = finish - start;
    auto new_a = operator new(s * sizeof(A));
    try {
      std::uninitialized_copy(start, finish, static_cast<Pointer>(new_a));
    } catch (...) {
      operator delete(new_a);
      throw;
    }
    s_ = s;
    cap_ = s;
    a_ = new_a;
  }

  Vector(const std::initializer_list<A>& l) : Vector() {
    if (l.size() == 0) {
      return;
    }
    size_t s = l.size();
    auto new_a = operator new(s * sizeof(ValueType));
    try {
      std::uninitialized_copy(l.begin(), l.end(), static_cast<Pointer>(new_a));
    } catch (...) {
      operator delete(new_a);
      throw;
    }
    s_ = s;
    cap_ = s;
    a_ = new_a;
  }

  Vector(const Vector<A>& elem) : Vector() {
    if (elem.s_ == 0) {
      return;
    }
    auto new_a = operator new(elem.s_ * sizeof(ValueType));
    try {
      std::uninitialized_copy(elem.begin(), elem.end(), static_cast<Pointer>(new_a));
    } catch (...) {
      operator delete(new_a);
      throw;
    }
    a_ = new_a;
    s_ = elem.s_;
    cap_ = elem.s_;
  }

  Vector(Vector<A>&& elem) : a_(elem.a_), s_(elem.s_), cap_(elem.s_) {
    elem.s_ = 0;
    elem.cap_ = 0;
    elem.a_ = nullptr;
  }

  Vector& operator=(const Vector<A>& elem) {
    if (this == &elem) {
      return *this;
    }
    if (cap_ < elem.s_) {
      auto new_a = operator new(elem.s_ * sizeof(ValueType));
      try {
        std::uninitialized_copy(elem.begin(), elem.end(), static_cast<Pointer>(new_a));
      } catch (...) {
        operator delete(new_a);
        throw;
      }
      std::destroy(begin(), end());
      operator delete(a_);
      a_ = new_a;
      s_ = elem.s_;
      cap_ = elem.s_;
    } else if (s_ > elem.s_) {
      std::copy(elem.begin(), elem.end(), static_cast<Pointer>(a_));
      std::destroy(begin() + elem.s_, begin() + s_);
      s_ = elem.s_;
    } else {
      std::copy(elem.begin(), elem.begin() + s_, static_cast<Pointer>(a_));
      std::uninitialized_copy(elem.begin() + s_, elem.end(), static_cast<Pointer>(a_) + s_);
      s_ = elem.s_;
    }
    return *this;
  }

  Vector& operator=(Vector<A>&& elem) noexcept {
    std::destroy(begin(), end());
    operator delete(a_);
    a_ = elem.a_;
    s_ = elem.s_;
    cap_ = elem.cap_;
    elem.a_ = nullptr;
    elem.s_ = 0;
    elem.cap_ = 0;
    return *this;
  }

  Vector& operator=(const std::initializer_list<A>& l) {
    if (cap_ < l.size()) {
      auto new_a = operator new(l.size());
      try {
        std::uninitialized_move(l.begin(), l.end(), static_cast<Pointer>(new_a));
      } catch (...) {
        operator delete(new_a);
        throw;
      }
      a_ = new_a;
      s_ = cap_ = l.size();
    } else if (s_ > l.size()) {
      std::copy(l.begin(), l.end(), static_cast<Pointer>(a_));
      std::destroy(begin() + l.size(), begin() + s_);
    } else {
      std::move(l.begin(), l.begin() + s_, static_cast<Pointer>(a_));
      std::uninitialized_move(l.begin() + s_, l.end(), static_cast<Pointer>(a_) + s_);
    }
    return *this;
  }

  ~Vector() noexcept {
    if (a_ != nullptr) {
      std::destroy(begin(), end());
      operator delete(a_);
      s_ = 0;
      cap_ = 0;
    }
  }

  size_t Size() const noexcept {
    return s_;
  }
  bool Empty() const noexcept {
    return s_ == 0;
  }
  size_t Capacity() const noexcept {
    return cap_;
  }

  Reference operator[](size_t id) noexcept {
    return *(static_cast<Pointer>(a_) + id);
  }

  ConstReference operator[](size_t id) const noexcept {
    return *(static_cast<Pointer>(a_) + id);
  }
  void Out(size_t id, size_t s) {
    if (id >= s) {
      throw std::out_of_range{"Vector out of range"};
    }
  }
  Reference At(size_t id) {
    Out(id, s_);
    return static_cast<Pointer>(a_)[id];
  }

  ConstReference At(size_t id) const {
    if (id >= s_) {
      throw std::out_of_range{"Vector out of range"};
    }
    return static_cast<Pointer>(a_)[id];
  }
  ConstReference Front() const noexcept {
    return static_cast<Pointer>(a_)[0];
  }
  Reference Front() noexcept {
    return static_cast<Pointer>(a_)[0];
  }
  ConstReference Back() const noexcept {
    return static_cast<Pointer>(a_)[s_ - 1];
  }
  Reference Back() noexcept {
    return static_cast<Pointer>(a_)[s_ - 1];
  }
  ConstPointer Data() const noexcept {
    return static_cast<Pointer>(a_);
  }
  Pointer Data() noexcept {
    return static_cast<Pointer>(a_);
  }

  void Swap(Vector<A>& elem) noexcept {
    std::swap(cap_, elem.cap_);
    std::swap(a_, elem.a_);
    std::swap(s_, elem.s_);
  }
  void Resizetry(void* a, size_t s, size_t new_s, void* new_a) {
    try {
      std::uninitialized_move(static_cast<Pointer>(a), static_cast<Pointer>(a) + s, static_cast<Pointer>(new_a));
    } catch (...) {
      operator delete(new_a);
    }
    try {
      std::uninitialized_default_construct(static_cast<Pointer>(new_a) + s, static_cast<Pointer>(new_a) + new_s);
    } catch (...) {
      std::move(static_cast<Pointer>(new_a), static_cast<Pointer>(new_a) + s, static_cast<Pointer>(a));
      operator delete(new_a);
      throw;
    }
  }
  void Resize(size_t new_s) {
    if (new_s <= cap_) {
      if (new_s < s_) {
        std::destroy(static_cast<Pointer>(a_) + new_s, static_cast<Pointer>(a_) + s_);
      } else {
        std::uninitialized_default_construct(static_cast<Pointer>(a_) + s_, static_cast<Pointer>(a_) + new_s);
      }
      s_ = new_s;
      return;
    }

    auto new_a = operator new(new_s * sizeof(ValueType));
    Resizetry(a_, s_, new_s, new_a);
    std::destroy(begin(), end());
    operator delete(a_);
    a_ = new_a;
    s_ = new_s;
    cap_ = new_s;
  }

  void Resize(size_t new_s, const A& data) {
    if (new_s <= cap_) {
      if (new_s < s_) {
        std::destroy(static_cast<Pointer>(a_) + new_s, static_cast<Pointer>(a_) + s_);
      } else {
        std::uninitialized_fill(static_cast<Pointer>(a_) + s_, static_cast<Pointer>(a_) + new_s, data);
      }
      s_ = new_s;
      return;
    }
    auto new_a = operator new(new_s * sizeof(ValueType));
    try {
      std::uninitialized_move(static_cast<Pointer>(a_), static_cast<Pointer>(a_) + s_, static_cast<Pointer>(new_a));
    } catch (...) {
      operator delete(new_a);
    }
    try {
      std::uninitialized_fill(static_cast<Pointer>(new_a) + s_, static_cast<Pointer>(new_a) + new_s, data);
    } catch (...) {
      std::move(static_cast<Pointer>(new_a), static_cast<Pointer>(new_a) + s_, static_cast<Pointer>(a_));
      operator delete(new_a);
      throw;
    }
    std::destroy(begin(), end());
    operator delete(a_);
    a_ = new_a;
    s_ = new_s;
    cap_ = new_s;
  }
  void Reservetry(void* new_a) {
    try {
      std::uninitialized_move(begin(), end(), static_cast<Pointer>(new_a));
    } catch (...) {
      operator delete(new_a);
      throw;
    }
  }
  void Reserve(size_t new_cap) {
    if (new_cap <= cap_) {
      return;
    }
    auto new_a = operator new(sizeof(ValueType) * new_cap);
    Reservetry(new_a);
    std::destroy(begin(), end());
    operator delete(a_);
    a_ = new_a;
    cap_ = new_cap;
  }

  void ShrinkToFit() {
    if (s_ == cap_) {
      return;
    }

    if (s_ == 0) {
      std::destroy(begin(), end());
      operator delete(a_);
      a_ = nullptr;
      s_ = 0;
      cap_ = 0;
      return;
    }

    auto new_a = operator new(sizeof(A) * s_);
    try {
      std::uninitialized_move(begin(), end(), static_cast<Pointer>(new_a));
    } catch (...) {
      operator delete(new_a);
      throw;
    }
    std::destroy(begin(), end());
    operator delete(a_);
    cap_ = s_;
    a_ = new_a;
  }

  void Clear() noexcept {
    if (s_ > 0) {
      std::destroy(begin(), end());
      s_ = 0;
    }
  }
  void PushBack(const A& data) {
    if (s_ < cap_) {
      new (static_cast<Pointer>(a_) + s_) A(data);
      s_++;
      return;
    }

    void* new_a = nullptr;
    try {
      new_a = Ex();
      new (static_cast<Pointer>(new_a) + s_) A(data);
    } catch (...) {
      std::destroy_n(static_cast<Pointer>(new_a), s_);
      operator delete(new_a);
      throw;
    }
    cap_ = (cap_ == 0) ? 1 : cap_ * 2;
    std::destroy(begin(), end());
    operator delete(a_);
    a_ = new_a;
    s_++;
  }

  void PushBack(A&& data) {
    if (s_ < cap_) {
      new (static_cast<Pointer>(a_) + s_) A(std::move(data));
      s_++;
      return;
    }

    void* new_a = nullptr;
    try {
      new_a = Ex();
      new (static_cast<Pointer>(new_a) + s_) A(std::move(data));
    } catch (...) {
      std::destroy_n(static_cast<Pointer>(new_a), s_);
      operator delete(new_a);
      throw;
    }
    cap_ = (cap_ == 0) ? 1 : cap_ * 2;
    std::destroy(begin(), end());
    operator delete(a_);
    a_ = new_a;
    s_++;
  }
  template <class... Args>
  void EmplaceBack(Args&&... ar) {
    if (s_ < cap_) {
      new (static_cast<Pointer>(a_) + s_) A(std::forward<Args>(ar)...);
      s_++;
      return;
    }

    void* new_a = nullptr;
    try {
      new_a = Ex();
      new (static_cast<Pointer>(new_a) + s_) A(std::forward<Args>(ar)...);
    } catch (...) {
      std::uninitialized_move(static_cast<Pointer>(new_a), static_cast<Pointer>(new_a) + s_, static_cast<Pointer>(a_));
      operator delete(new_a);
      throw;
    }
    cap_ = (cap_ == 0) ? 1 : cap_ * 2;
    std::destroy(begin(), end());
    operator delete(a_);
    a_ = new_a;
    s_++;
  }

  void PopBack() {
    if (s_ > 0) {
      std::destroy_at(static_cast<Pointer>(a_) + s_ - 1);
      s_--;
    }
  }
  ConstIterator begin() const noexcept {  // NOLINT
    return static_cast<Pointer>(a_);
  }
  Iterator begin() noexcept {  // NOLINT
    return static_cast<Pointer>(a_);
  }
  ConstIterator end() const noexcept {  // NOLINT
    return static_cast<Pointer>(a_) + s_;
  }
  Iterator end() noexcept {  // NOLINT
    return static_cast<Pointer>(a_) + s_;
  }

  ConstIterator cbegin() const noexcept {  // NOLINT
    return static_cast<Pointer>(a_);
  }
  ReverseIterator rbegin() noexcept {  // NOLINT
    return std::reverse_iterator(end());
  }
  ConstIterator cend() const noexcept {  // NOLINT
    return static_cast<Pointer>(a_) + s_;
  }
  ConstReverseIterator rbegin() const noexcept {  // NOLINT
    return std::reverse_iterator(cend());
  }
  ReverseIterator rend() noexcept {  // NOLINT
    return std::reverse_iterator(begin());
  }
  ConstReverseIterator crbegin() const noexcept {  // NOLINT
    return std::reverse_iterator(cend());
  }
  ConstReverseIterator rend() const noexcept {  // NOLINT
    return std::reverse_iterator(cbegin());
  }
  ConstReverseIterator crend() const noexcept {  // NOLINT
    return std::reverse_iterator(cbegin());
  }
};
template <typename A>
bool operator>=(const Vector<A>& start, const Vector<A>& finish) {
  bool ans = !(start < finish);
  return ans;
}
template <class A>
bool operator<(const Vector<A>& start, const Vector<A>& finish) {
  size_t last = std::min(start.s_, finish.s_), id = 0;
  for (id = 0; id < last; ++id) {
    if (start[id] < finish[id]) {
      return true;
    }
    if (start[id] > finish[id]) {
      return false;
    }
  }
  return static_cast<bool>(start.s_ < finish.s_);
}
template <typename A>
bool operator>(const Vector<A>& start, const Vector<A>& finish) {
  bool ans = (!(start < finish) && !(start == finish));
  return ans;
}
template <typename A>
bool operator!=(const Vector<A>& start, const Vector<A>& finish) {
  bool ans = !(start == finish);
  return ans;
}
template <typename A>
bool operator<=(const Vector<A>& start, const Vector<A>& finish) {
  bool ans = (start < finish || start == finish);
  return ans;
}
template <typename A>
bool operator==(const Vector<A>& start, const Vector<A>& finish) {
  size_t id = 0;
  if (start.s_ != finish.s_) {
    return false;
  }
  for (id = 0; id < start.s_; ++id) {
    if (start[id] != finish[id]) {
      return false;
    }
  }
  return true;
}

#endif