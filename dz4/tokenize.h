#ifndef TOKENIZE_H
#define TOKENIZE_H
#include <string>
#include <vector>
#include <variant>
struct PlusToken {};

struct MinusToken {};

struct MultiplyToken {};

struct DivideToken {};

struct ResidualToken {};

struct OpeningBracketToken {};

struct ClosingBracketToken {};

struct SqrToken {};

struct MaxToken {};

struct MinToken {};

struct AbsToken {};

struct NumberToken {
  int value;
};

struct UnknownToken {
  std::string value;
};

bool operator==(PlusToken, PlusToken);

bool operator==(MinusToken, MinusToken);

bool operator==(MultiplyToken, MultiplyToken);

bool operator==(DivideToken, DivideToken);

bool operator==(ResidualToken, ResidualToken);

bool operator==(OpeningBracketToken, OpeningBracketToken);

bool operator==(ClosingBracketToken, ClosingBracketToken);

bool operator==(SqrToken, SqrToken);

bool operator==(MaxToken, MaxToken);

bool operator==(MinToken, MinToken);

bool operator==(AbsToken, AbsToken);

bool operator==(NumberToken, NumberToken);

bool operator==(UnknownToken, UnknownToken);

using Token = std::variant<PlusToken, MinusToken, MultiplyToken, DivideToken, ResidualToken, OpeningBracketToken,
                           ClosingBracketToken, SqrToken, MaxToken, MinToken, AbsToken, NumberToken, UnknownToken>;
std::vector<Token> Tokenize(const std::string&);

bool IsNumber(const char&);

#endif