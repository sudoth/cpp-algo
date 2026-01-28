#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H
#include <memory>
#include <utility>
template <typename T>
class UniquePtr {
 public:
  T* ptr;
  ~UniquePtr() {
    delete ptr;
  };
  UniquePtr() : ptr(nullptr){};
  explicit UniquePtr<T>(const T* other) : ptr(other){};
  UniquePtr(const UniquePtr<T>&) = delete;
  UniquePtr(UniquePtr<T>&& other) noexcept : ptr(other.ptr) {
    other.ptr = nullptr;
  }
  UniquePtr<T>& operator=(const UniquePtr<T>&) = delete;
  UniquePtr<T>& operator=(UniquePtr<T>&&) noexcept;
  T* Release();
  void Reset(T* other = nullptr);
  void Swap(UniquePtr<T>&);
  T& operator*() const;
  T* Get() const;
  T* operator->() const;
  explicit operator bool() const;
};

template <typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& other) noexcept {
  if (this != &other) {
    delete ptr;
    ptr = other.ptr;
    other.ptr = nullptr;
  }
  return *this;
}

template <typename T>
T* UniquePtr<T>::Release() {
  T* prev_ptr = ptr;
  ptr = nullptr;
  return prev_ptr;
}

template <typename T>
void UniquePtr<T>::Reset(T* other) {
  delete ptr;
  ptr = other;
}

template <typename T>
void UniquePtr<T>::Swap(UniquePtr<T>& other) {
  std::swap(*this, other);
}

template <typename T>
T* UniquePtr<T>::Get() const {
  return ptr;
}

template <typename T>
T& UniquePtr<T>::operator*() const {
  return *ptr;
}

template <typename T>
T* UniquePtr<T>::operator->() const {
  return ptr;
}

template <typename T>
UniquePtr<T>::operator bool() const {
  return ptr != nullptr;
}

#endif

// #include <memory>

// // ...

// std::unique_ptr<int> ptr(new int(10));

// std::cout << *ptr << '\n';  // 10

// // std::unique_ptr<int> copy = ptr; копирование запрещено

// std::unique_ptr<int> moved = std::move(ptr);  // теперь ptr пуст

// std::cout << *moved << '\n';  // 10

// auto rational = std::make_unique<Rational>(1, 2);

// // эквивалентно std::unique_ptr<Rational> rational(new Rational(1, 2));

// std::cout << rational->Numerator() << ' ' << rational->Denominator() << '\n';  // 1 2

// // delete вызовутся автоматически в деструкторах!