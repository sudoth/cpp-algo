#include <memory>
#include <iostream>
#include <vector>
#include <utility>
#include <string_view>
#include <string>
#include "cppstring.h"
#define REQUIRE std::cout<<

void CheckEqual(const String& actual, std::string expected) {
  REQUIRE(actual.Capacity() >= actual.Size());
  REQUIRE(actual.Size() == expected.size());
  REQUIRE(actual.Length() == expected.size());
  for (size_t i = 0; i < expected.size(); ++i) {
    REQUIRE(actual[i] == expected[i]);
  }
}


int main(int argc, char** argv) {

{
  const String s;
  REQUIRE(s.Capacity() == 0u);
  REQUIRE(s.Size() == 0u);
  REQUIRE(s.Data() == nullptr);
  REQUIRE(s.Empty());
  CheckEqual(String(s), "");
}

{
  {
    const String s(0, 'z');
    REQUIRE(s.Size() == 0u);
    REQUIRE(s.Capacity() == 0u);
    REQUIRE(s.Data() == nullptr);
  }

  {
    const String s(5, 'a');
    CheckEqual(s, "aaaaa");
  }
}

{
  {
    const String s = "abacaba";
    CheckEqual(s, "abacaba");
  }

  {
    const String s = "";
    REQUIRE(s.Capacity() == 0u);
    CheckEqual(s, "");
  }

  {
    const String s("abacaba", 5u);
    CheckEqual(s, "abaca");
  }

  {
    const String s("abacaba", 0u);
    REQUIRE(s.Capacity() == 0u);
    CheckEqual(s, "");
  }
}

{
  {
    const String empty;
    const auto copy = empty;
    REQUIRE(empty.Size() == 0u);
    REQUIRE(empty.Capacity() == 0u);
    REQUIRE(empty.Data() == nullptr);
    REQUIRE(copy.Size() == 0u);
    REQUIRE(copy.Capacity() == 0u);
    REQUIRE(copy.Data() == nullptr);
  }

  {
    const String s = "abacaba";
    const auto copy = s;
    CheckEqual(copy, "abacaba");
    CheckEqual(s, "abacaba");
  }
}


{
  {
    const String empty;
    String s;
    s = empty;
    REQUIRE(empty.Size() == 0u);
    REQUIRE(empty.Capacity() == 0u);
    REQUIRE(empty.Data() == nullptr);
    REQUIRE(s.Size() == 0u);
    REQUIRE(s.Capacity() == 0u);
    REQUIRE(s.Data() == nullptr);

    s = s;
    REQUIRE(s.Size() == 0u);
    REQUIRE(s.Capacity() == 0u);
    REQUIRE(s.Data() == nullptr);
  }

{
    const String empty;
    String s = "abacaba";
    s = empty;
    REQUIRE(empty.Size() == 0u);
    REQUIRE(empty.Capacity() == 0u);
    REQUIRE(empty.Data() == nullptr);
    REQUIRE(s.Size() == 0u);
  }

{
    const String init = "abacaba";
    String s;
    s = init;
    CheckEqual(s, "abacaba");
    CheckEqual(init, "abacaba");

    s = s;
    CheckEqual(s, "abacaba");
    CheckEqual(init, "abacaba");
  }

{
    const String small(10, 'a');
    String large(1000, 'b');
    large = small;
    CheckEqual(large, std::string(10, 'a'));
    CheckEqual(small, std::string(10, 'a'));
  }

{
    const String large(1000, 'b');
    String small(10, 'a');
    small = large;
    CheckEqual(large, std::string(1000, 'b'));
    CheckEqual(small, std::string(1000, 'b'));
  }
}

{
  String s = "abcdef";

  {
    REQUIRE(s.Front() == 'a');
    s.Front() = 'z';
    REQUIRE(std::as_const(s).Front() == 'z');
  }

  {
    REQUIRE(s.Back() == 'f');
    s.Back() = 'y';
    REQUIRE(std::as_const(s).Back() == 'y');
  }

  {
    REQUIRE(s[1] == 'b');
    s[1] = 'x';
    REQUIRE(std::as_const(s)[1] == 'x');
  }

  {
    REQUIRE(s.At(2) == 'c');
    s.At(2) = 'w';
    REQUIRE(std::as_const(s).At(2) == 'w');
  }

  {
    REQUIRE(s.CStr()[3] == 'd');
    REQUIRE(s.Data()[3] == 'd');
    s.CStr()[3] = 'v';
    REQUIRE(s.CStr()[3] == 'v');
    REQUIRE(s.Data()[3] == 'v');
    s.CStr()[3] = 'u';
    REQUIRE(s.CStr()[3] == 'u');
    REQUIRE(s.Data()[3] == 'u');

    REQUIRE((std::is_same_v<decltype(std::declval<const String&>().Data()), const char*>));
    REQUIRE((std::is_same_v<decltype(std::declval<const String&>().CStr()), const char*>));
  }
}

{
  auto a = String();
  auto b = String();
  a.Swap(b);
  CheckEqual(a, "");
  CheckEqual(b, "");

  b = String("abacaba");
  a.Swap(b);
  CheckEqual(a, "abacaba");
  CheckEqual(b, "");

  b = String(5, 'a');
  b.Swap(a);
  CheckEqual(a, "aaaaa");
  CheckEqual(b, "abacaba");
}

{
  {
    String s;
    std::string actual("a");
    s.PushBack('a');
    for (size_t size = 1u; size < 1'000'000; size *= 2u) {
      for (size_t i = 0u; i < size; ++i) {
        s.PushBack(static_cast<char>('a' + i % 26));
        actual.push_back(static_cast<char>('a' + i % 26));
      }
      REQUIRE(s.Capacity() >= size * 2);
      CheckEqual(s, actual);
    }
  }

{
    const String other = "abacaba";
    String s;
    (s += other) += other;
    CheckEqual(s, "abacabaabacaba");
    std::string actual("abacabaabacaba");
    for (size_t i = 0; i < 100000; ++i) {
      s += other;
      actual += "abacaba";
    }
    CheckEqual(s, actual);
  }

{
    {
      const String a;
      const String b;
      CheckEqual(a + b, "");
    }

    {
      const String a;
      const String b("caba");
      CheckEqual(a + b, "caba");
    }

    {
      const String a("aba");
      const String b;
      CheckEqual(a + b, "aba");
    }

    {
      const String a("aba");
      const String b("caba");
      CheckEqual(a + b, "abacaba");
    }

    {
      const String a("aba");
      CheckEqual(a + "caba", "abacaba");
    }

    {
      const String b("caba");
      CheckEqual("" + b, "caba");
    }
  }
}

{
  {
    String s;
    s.Clear();
    CheckEqual(s, "");

    s = "aba";
    s.Clear();
    CheckEqual(s, "");

    for (size_t size = 1u; size < 1'000'000; size *= 2u) {
      for (size_t i = 0u; i < size; ++i) {
        s.PushBack(static_cast<char>('a' + i % 26));
      }
      s.Clear();
      CheckEqual(s, "");
    }
  }

{
    String s("abacaba");
    s.PopBack();
    s.PopBack();
    CheckEqual(s, "abaca");

    for (size_t size = 1u; size < 1'000'000; size *= 2u) {
      for (size_t i = 0u; i < size; ++i) {
        s.PushBack(static_cast<char>('a' + i % 26));
      }
      for (size_t i = 0u; i < size; ++i) {
        s.PopBack();
      }
      CheckEqual(s, "abaca");
    }
  }
}

{
  {
    String a;
    a.Resize(5, 'a');
    CheckEqual(a, "aaaaa");

    a.Resize(3, 'b');
    CheckEqual(a, "aaa");

    a.Resize(7, 'c');
    CheckEqual(a, "aaacccc");

    a.Resize(0, 'a');
    CheckEqual(a, "");

    a = "aba";
    CheckEqual(a, "aba");
    REQUIRE(a.Capacity() >= 3u);
  }

{
    String a("abacaba");
    REQUIRE(a.Capacity() < 15);

    a.Reserve(20);
    REQUIRE(a.Capacity() >= 20);
    CheckEqual(a, "abacaba");

    a.Reserve(1000);
    REQUIRE(a.Capacity() >= 1000);
    CheckEqual(a, "abacaba");

    a.Reserve(1000000);
    REQUIRE(a.Capacity() >= 1000000);
    CheckEqual(a, "abacaba");

    a.Reserve(10);
    REQUIRE(a.Capacity() >= 1000000);
    CheckEqual(a, "abacaba");
  }

{
    String a("abacaba");
    a.Reserve(100);
    REQUIRE(a.Capacity() > a.Size());
    a.ShrinkToFit();
    REQUIRE(a.Capacity() == a.Size());
    CheckEqual(a, "abacaba");

    a.Resize(0, 'a');
    CheckEqual(a, "");
    REQUIRE(a.Capacity() > 0u);
    a.ShrinkToFit();
    REQUIRE(a.Size() == 0u);
    REQUIRE(a.Capacity() == 0u);

    a = "aba";
    CheckEqual(a, "aba");
    REQUIRE(a.Capacity() >= 3u);
  }
}

void CheckComparisonEqual(const String& lhs, const String& rhs) {
  REQUIRE(lhs == rhs);
  REQUIRE(lhs <= rhs);
  REQUIRE(lhs >= rhs);
  REQUIRE_FALSE(lhs != rhs);
  REQUIRE_FALSE(lhs < rhs);
  REQUIRE_FALSE(lhs > rhs);
}

void CheckComparisonLess(const String& lhs, const String& rhs) {
  REQUIRE_FALSE(lhs == rhs);
  REQUIRE(lhs <= rhs);
  REQUIRE_FALSE(lhs >= rhs);
  REQUIRE(lhs != rhs);
  REQUIRE(lhs < rhs);
  REQUIRE_FALSE(lhs > rhs);
}

void CheckComparisonGreater(const String& lhs, const String& rhs) {
  REQUIRE_FALSE(lhs == rhs);
  REQUIRE_FALSE(lhs <= rhs);
  REQUIRE(lhs >= rhs);
  REQUIRE(lhs != rhs);
  REQUIRE_FALSE(lhs < rhs);
  REQUIRE(lhs > rhs);
}

{
  {
    String a;
    String b;
    CheckComparisonEqual(a, b);
  }

  {
    String a;
    String b(1, 'a');
    CheckComparisonLess(a, b);
    CheckComparisonGreater(b, a);
  }

  {
    String a("ac");
    String b("b");
    CheckComparisonLess(a, b);
    CheckComparisonGreater(b, a);
  }

  {
    String a("abc");
    String b("aa");
    CheckComparisonLess(b, a);
    CheckComparisonGreater(a, b);
  }

  {
    String a("abcd");
    String b("abcd");
    CheckComparisonEqual(a, b);
  }

  {
    String a("abcd");
    String b("abc");
    CheckComparisonLess(b, a);
    CheckComparisonGreater(a, b);
  }

  {
    String a("adfh");
    String b("bceg");
    CheckComparisonLess(a, b);
    CheckComparisonGreater(b, a);
  }

  {
    String a("abce");
    String b("abde");
    CheckComparisonLess(a, b);
    CheckComparisonGreater(b, a);
  }
}

{
  auto oss = std::ostringstream();
  oss << String("abacaba") << ' ' << String() << ' ' << String(5, 'a');
  REQUIRE(oss.str() == "abacaba  aaaaa");
}

}