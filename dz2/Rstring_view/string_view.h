#ifndef STRING_VIEW_H
#define STRING_VIEW_H
#include <stdexcept>
class StringViewOutOfRange : public std::out_of_range {
 public:
  StringViewOutOfRange() : std::out_of_range("StringViewOutOfRange"){};
};
class StringView {
 private:
  const char* begin_;
  size_t size_;

 public:
  StringView();
  StringView(const char*, size_t);
  StringView(const char*);  // NOLINT
  const char& operator[](size_t);
  const char& operator[](size_t) const;
  const char& At(size_t) const;
  const char& Front() const;
  const char& Back() const;
  size_t Size() const;
  size_t Length() const;
  bool Empty() const;
  const char* Data() const;
  void SetData(const char*);
  size_t GetSize();
  void SetSize(size_t);
  void Swap(StringView&);
  void RemovePrefix(size_t);
  void RemoveSuffix(size_t);
  StringView Substr(size_t, size_t) const;
};
#endif