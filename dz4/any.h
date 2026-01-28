#ifndef ANY_H
#define ANY_H
#include <stdexcept>
#include <memory>
class BadAnyCast : public std::bad_cast {
 public:
  [[nodiscard]] const char* what() const noexcept override {
    return "BadAnyCast error";
  }
};

class IHolder {
 public:
  virtual std::shared_ptr<IHolder> Clone() const = 0;
  virtual ~IHolder() = default;
};

template <typename T>
class AnyHolder : public IHolder {
 public:
  T any;
  AnyHolder(const T& other) : any(other) {  // NOLINT
  }
  std::shared_ptr<IHolder> Clone() const override;
};

class Any {
 public:
  std::shared_ptr<IHolder> ptr;
  Any();
  Any(const Any&);  // NOLINT
  Any(Any&&);
  Any& operator=(const Any&);
  Any& operator=(Any&&);
  template <typename T>
  Any(const T&);  // NOLINT
  template <typename T>
  Any& operator=(const T&);
  void Swap(Any& other);
  void Reset();
  bool HasValue() const;
};

template <typename T>
inline std::shared_ptr<IHolder> AnyHolder<T>::Clone() const {
  std::shared_ptr<IHolder> new_ptr(new AnyHolder(any));
  return new_ptr;
}

inline Any::Any() {
  ptr = nullptr;
}

inline Any::Any(const Any& other) {
  if (this != &other) {
    ptr = other.ptr->Clone();
  }
}

inline Any::Any(Any&& other) {
  if (this != &other) {
    ptr = other.ptr->Clone();
    other.ptr.reset();
  }
}

inline Any& Any::operator=(const Any& other) {
  if (this != &other) {
    ptr = other.ptr->Clone();
  }
  return *this;
}

inline Any& Any::operator=(Any&& other) {
  if (this != &other) {
    ptr = other.ptr->Clone();
    other.ptr.reset();
  }
  return *this;
}

template <typename T>
inline Any::Any(const T& other) {
  IHolder* new_ptr = new AnyHolder<T>(other);
  std::shared_ptr<IHolder> new_sptr(new_ptr);
  ptr = new_sptr;
}

template <typename T>
inline Any& Any::operator=(const T& other) {
  IHolder* new_ptr = new AnyHolder<T>(other);
  ptr.reset(new_ptr);
  return *this;
}

inline void Any::Swap(Any& other) {
  ptr.swap(other.ptr);
}

inline void Any::Reset() {
  ptr.reset();
}

inline bool Any::HasValue() const {
  return (ptr != nullptr);
}

template <typename T>
inline T AnyCast(const Any& value) {
  if ((value.ptr) == nullptr || dynamic_cast<AnyHolder<T>*>(value.ptr.get()) == nullptr) {
    throw BadAnyCast{};
  } else {
    return (dynamic_cast<AnyHolder<T>*>(value.ptr.get())->any);
  }
}
#endif