#include "string_view.h"
const char& StringView::operator[](size_t idx) {
  return begin_[idx];
}
const char& StringView::operator[](size_t idx) const {
  return begin_[idx];
}
StringView::StringView(const char* str, size_t n) : begin_(str), size_(n) {
}
StringView::StringView() : begin_(nullptr), size_(0ull) {
}
StringView::StringView(const char* str) {
  begin_ = str;
  size_t n = 0;
  while (str[n] != '\0') {
    n++;
  }
  size_ = n;
}
size_t StringView::Size() const {
  return size_;
}
size_t StringView::Length() const {
  return size_;
}
bool StringView::Empty() const {
  return size_ == 0ull;
}
const char& StringView::At(size_t idx) const {
  if (idx >= size_) {
    throw StringViewOutOfRange();
  }
  return begin_[idx];
}
const char& StringView::Front() const {
  return begin_[0];
}
const char& StringView::Back() const {
  return begin_[size_ - 1];
}
const char* StringView::Data() const {
  return begin_;
}
void StringView::SetData(const char* new_ptr) {
  this->begin_ = new_ptr;
}
size_t StringView::GetSize() {
  return size_;
}
void StringView::SetSize(size_t value) {
  size_ = value;
}
void StringView::Swap(StringView& other) {
  size_t n = other.GetSize();
  const char* tmp = other.Data();
  other.SetData(this->Data());
  other.SetSize(this->GetSize());
  this->SetData(tmp);
  this->SetSize(n);
}
void StringView::RemovePrefix(size_t prefix_size) {
  this->begin_ += prefix_size;
  this->size_ -= prefix_size;
}
void StringView::RemoveSuffix(size_t suffix_size) {
  this->size_ -= suffix_size;
}
StringView StringView::Substr(size_t pos = 0, size_t count = 9e18) const {
  count = std::min(count, this->Size() - pos);
  StringView ans(this->begin_ + pos, count);
  return ans;
}