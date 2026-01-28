#include <stdexcept>
#include <memory>
#include <iostream>
#include <vector>

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
  T any;  // constructor
  AnyHolder(const T& other) : any(other) {
  }
  std::shared_ptr<IHolder> Clone() const override;
};

class Any {
 public:
  std::shared_ptr<IHolder> ptr;
  Any();
  Any(const Any&);
  Any(Any&&);
  Any& operator=(const Any&);
  Any& operator=(Any&&);
  template <typename T>
  Any(const T&);
  template <typename T>
  Any& operator=(const T&);
  void Swap(Any& other);
  void Reset();
  bool HasValue() const;
};

template <typename T>
std::shared_ptr<IHolder> AnyHolder<T>::Clone() const {
  std::shared_ptr<IHolder> new_ptr(new AnyHolder(any));
  return new_ptr;
}

Any::Any() {
  ptr = nullptr;
}

Any::Any(const Any& other) {
  if (this != &other) {
    ptr = other.ptr->Clone();
  }
}

Any::Any(Any&& other) {
  if (this != &other) {
    ptr = other.ptr->Clone();
    other.ptr.reset();
  }
}

Any& Any::operator=(const Any& other) {
  if (this != &other) {
    ptr = other.ptr->Clone();
  }
  return *this;
}

Any& Any::operator=(Any&& other) {
  if (this != &other) {
    ptr = other.ptr->Clone();
    other.ptr.reset();
  }
  return *this;
}

template <typename T>
Any::Any(const T& other) {
  IHolder* new_ptr = new AnyHolder<T>(other);
  std::shared_ptr<IHolder> new_sptr(new_ptr);
  ptr = new_sptr;
}

template <typename T>
Any& Any::operator=(const T& other) {
  IHolder* new_ptr = new AnyHolder<T>(other);
  ptr.reset(new_ptr);
  return *this;
}

void Any::Swap(Any& other) {
  ptr.swap(other.ptr);
}

void Any::Reset() {
  ptr.reset();
}

bool Any::HasValue() const {
  return (ptr != nullptr);
}

template <typename T>
T AnyCast(const Any& value) {
  if ((value.ptr) == nullptr || dynamic_cast<AnyHolder<T>*>(value.ptr.get()) == nullptr) {
    throw BadAnyCast{};
  } else {
    return (dynamic_cast<AnyHolder<T>*>(value.ptr.get())->any);
  }
}

#define REQUIRE std::cout<<
int main() {

{
  Any a;
  a = 11;
  AnyCast<char*>(a);
}




}