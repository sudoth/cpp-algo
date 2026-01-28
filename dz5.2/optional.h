#ifndef OPTIONAL_H
#define OPTIONAL_H
#include <cstddef>
#include <new>
#include <stdexcept>

class BadOptionalAccess : public std::runtime_error {
 public:
  BadOptionalAccess() : std::runtime_error("BadOptionalAccess") {
  }
};

template <typename T>
class Optional {
 public:
  Optional() = default;

  Optional(const Optional<T>& other) : empty_(other.empty_) {
    if (other.empty_) {
      return;
    }
    new (data_) T(*reinterpret_cast<const T*>(other.data_));
  }

  Optional(Optional<T>&& other) : empty_(other.empty_) {
    if (other.empty_) {
      return;
    }
    new (data_) T(std::move(*other));
  }

  Optional(const T& value) : empty_(false) {  // NOLINT
    new (data_) T(std::forward<const T>(value));
  }

  Optional(T&& value) : empty_(false) {  // NOLINT
    new (data_) T(std::move(value));
  }

  ~Optional() {
    Clear();
  }

  Optional<T>& operator=(const Optional<T>& other) {
    if (this != &other) {
      Clear();
      if (!other.empty_) {
        empty_ = false;
        new (data_) T(*reinterpret_cast<const T*>(other.data_));
      }
    }
    return *this;
  }

  Optional<T>& operator=(Optional<T>&& other) {
    if (this != &other) {
      Clear();
      if (!other.empty_) {
        empty_ = other.empty_;
        new (data_) T(std::move(*other));
      }
    }
    return *this;
  }

  Optional<T>& operator=(const T& value) {
    Clear();
    empty_ = false;
    new (data_) T(std::forward<const T>(value));
    return *this;
  }

  Optional<T>& operator=(T&& value) {
    Clear();
    empty_ = false;
    new (data_) T(std::forward<T>(value));
    return *this;
  }

  bool HasValue() const {
    return !empty_;
  }

  explicit operator bool() const {
    return !empty_;
  }
  const T& Value() const {
    if (empty_) {
      throw BadOptionalAccess();
    }
    return *reinterpret_cast<const T*>(data_);
  }

  T& Value() {
    if (empty_) {
      throw BadOptionalAccess();
    }
    return *reinterpret_cast<T*>(data_);
  }

  const T& operator*() const {
    return *reinterpret_cast<const T*>(data_);
  }

  T& operator*() {
    return *reinterpret_cast<T*>(data_);
  }

  void Swap(Optional<T>& other) {
    if (!empty_ && !other.empty_) {
      std::swap(this->Value(), other.Value());
    } else {
      std::swap(data_, other.data_);
    }
    std::swap(empty_, other.empty_);
  }

  template <typename... Args>
  void Emplace(Args&&... args) {
    Clear();
    new (data_) T(std::forward<Args>(args)...);
    empty_ = false;
  }

  void Reset() {
    Clear();
  }

 private:
  void Clear() {
    if (!empty_) {
      empty_ = true;
      reinterpret_cast<T*>(data_)->~T();
    }
  }

 private:
  alignas(T) std::byte data_[sizeof(T)];
  bool empty_ = true;
};
#endif