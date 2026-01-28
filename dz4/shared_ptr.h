#ifndef SHARED_PTR_H
#define SHARED_PTR_H
template <typename T>
class SharedPtr {
 public:
  T* ptr;
  int* strong_counter;
  ~SharedPtr() {
    this->Delete();
  }
  SharedPtr() : ptr(nullptr), strong_counter(nullptr){};
  SharedPtr(T* other) : ptr(other) {  // NOLINT
    strong_counter = (other ? new int(1) : nullptr);
  }
  void Delete();

  SharedPtr(const SharedPtr&);
  SharedPtr<T>& operator=(const SharedPtr<T>&);
  SharedPtr(SharedPtr<T>&&) noexcept;
  SharedPtr<T>& operator=(SharedPtr<T>&&) noexcept;

  void Reset(T* other = nullptr);
  void Swap(SharedPtr&);
  T* Get() const;
  int UseCount() const;
  T& operator*() const;
  T* operator->() const;
  operator bool() const;  // NOLINT
};

template <typename T>
void SharedPtr<T>::Delete() {
  if (this->ptr) {
    (*(this->strong_counter))--;
    if ((*(this->strong_counter)) == 0) {
      delete ptr;
      delete strong_counter;
      ptr = nullptr;
      strong_counter = nullptr;
    }
  }
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other) {
  this->ptr = other.ptr;
  this->strong_counter = other.strong_counter;
  if (other.ptr) {
    (*(this->strong_counter))++;
  }
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other) {
  if (this != &other) {  // xz zachem
    this->Delete();
    this->ptr = other.ptr;
    this->strong_counter = other.strong_counter;
    if (other.ptr) {
      (*(this->strong_counter))++;
    }
  }
  return *this;
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T>&& other) noexcept {
  this->ptr = other.ptr;
  this->strong_counter = other.strong_counter;
  other.ptr = nullptr;
  other.strong_counter = nullptr;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& other) noexcept {
  if (this != &other) {  // xz zachem
    this->Delete();
    this->ptr = other.ptr;
    this->strong_counter = other.strong_counter;
    other.ptr = nullptr;
    other.strong_counter = nullptr;
  }
  return *this;
}

template <typename T>
void SharedPtr<T>::Reset(T* other) {
  this->Delete();
  this->ptr = other;
  this->strong_counter = (other ? new int(1) : nullptr);
}

template <typename T>
void SharedPtr<T>::Swap(SharedPtr& other) {
  std::swap(this->ptr, other.ptr);
  std::swap(this->strong_counter, other.strong_counter);
}

template <typename T>
T* SharedPtr<T>::Get() const {
  return ptr;
}

template <typename T>
int SharedPtr<T>::UseCount() const {
  return (strong_counter ? *(strong_counter) : 0);
}

template <typename T>
T& SharedPtr<T>::operator*() const {
  return *ptr;
}

template <typename T>
T* SharedPtr<T>::operator->() const {
  return ptr;
}

template <typename T>
SharedPtr<T>::operator bool() const {
  return ptr != nullptr;
}
#endif