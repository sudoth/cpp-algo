#include "tokenize.h"

#include <iostream>
#include <string>
#include <vector>
#include <variant>
bool operator==(PlusToken, PlusToken) {
  return true;
}

bool operator==(MinusToken, MinusToken) {
  return true;
}

bool operator==(MultiplyToken, MultiplyToken) {
  return true;
}

bool operator==(DivideToken, DivideToken) {
  return true;
}

bool operator==(ResidualToken, ResidualToken) {
  return true;
}

bool operator==(OpeningBracketToken, OpeningBracketToken) {
  return true;
}

bool operator==(ClosingBracketToken, ClosingBracketToken) {
  return true;
}

bool operator==(SqrToken, SqrToken) {
  return true;
}

bool operator==(MaxToken, MaxToken) {
  return true;
}

bool operator==(MinToken, MinToken) {
  return true;
}

bool operator==(AbsToken, AbsToken) {
  return true;
}

bool operator==(NumberToken lhs, NumberToken rhs) {
  return lhs.value == rhs.value;
}

bool operator==(UnknownToken lhs, UnknownToken rhs) {
  return lhs.value == rhs.value;
}

bool IsNumber(const char& symbol) {
  return ('0' <= symbol && symbol <= '9');
}

void AddUnknownToken(std::vector<Token>& tokens, const int& i, const std::string& tokenize_string, int& unknown) {
  if (unknown) {
    UnknownToken token;
    token.value = tokenize_string.substr(i - unknown, unknown);
    tokens.emplace_back(token);
    unknown = 0;
  }
}

std::vector<Token> Tokenize(const std::string& string) {
  std::string tokenize_string = (' ' + string + ' ');
  std::vector<Token> tokens;
  int unknown = 0;
  for (size_t i = 0; i < tokenize_string.size(); ++i) {
    if (tokenize_string[i] == ' ') {
      AddUnknownToken(tokens, i, tokenize_string, unknown);
      continue;
    }
    if (tokenize_string[i] == '+' && tokenize_string[i - 1] == ' ' &&
        (tokenize_string[i + 1] == ' ' || IsNumber(tokenize_string[i + 1]))) {
      if (IsNumber(tokenize_string[i + 1])) {
        continue;
      }
      PlusToken token;
      AddUnknownToken(tokens, i, tokenize_string, unknown);
      tokens.emplace_back(token);
      continue;
    }
    if (tokenize_string[i] == '-' && tokenize_string[i - 1] == ' ' &&
        (tokenize_string[i + 1] == ' ' || IsNumber(tokenize_string[i + 1]))) {
      if (IsNumber(tokenize_string[i + 1])) {
        continue;
      }
      MinusToken token;
      AddUnknownToken(tokens, i, tokenize_string, unknown);
      tokens.emplace_back(token);
      continue;
    }
    if (tokenize_string[i] == '*' && tokenize_string[i - 1] == ' ' && tokenize_string[i + 1] == ' ') {
      MultiplyToken token;
      AddUnknownToken(tokens, i, tokenize_string, unknown);
      tokens.emplace_back(token);
      continue;
    }
    if (tokenize_string[i] == '/' && tokenize_string[i - 1] == ' ' && tokenize_string[i + 1] == ' ') {
      DivideToken token;
      AddUnknownToken(tokens, i, tokenize_string, unknown);
      tokens.emplace_back(token);
      continue;
    }
    if (tokenize_string[i] == '%' && tokenize_string[i - 1] == ' ' && tokenize_string[i + 1] == ' ') {
      ResidualToken token;
      AddUnknownToken(tokens, i, tokenize_string, unknown);
      tokens.emplace_back(token);
      continue;
    }
    if (tokenize_string[i] == '(' && tokenize_string[i - 1] == ' ' && tokenize_string[i + 1] == ' ') {
      OpeningBracketToken token;
      AddUnknownToken(tokens, i, tokenize_string, unknown);
      tokens.emplace_back(token);
      continue;
    }
    if (tokenize_string[i] == ')' && tokenize_string[i - 1] == ' ' && tokenize_string[i + 1] == ' ') {
      ClosingBracketToken token;
      AddUnknownToken(tokens, i, tokenize_string, unknown);
      tokens.emplace_back(token);
      continue;
    }
    if (i < tokenize_string.size() - 3) {
      if (tokenize_string.substr(i, 3) == "sqr" && tokenize_string[i - 1] == ' ' && tokenize_string[i + 3] == ' ') {
        SqrToken token;
        AddUnknownToken(tokens, i, tokenize_string, unknown);
        tokens.emplace_back(token);
        i += 3;
        continue;
      }
      if (tokenize_string.substr(i, 3) == "max" && tokenize_string[i - 1] == ' ' && tokenize_string[i + 3] == ' ') {
        MaxToken token;
        AddUnknownToken(tokens, i, tokenize_string, unknown);
        tokens.emplace_back(token);
        i += 3;
        continue;
      }
      if (tokenize_string.substr(i, 3) == "min" && tokenize_string[i - 1] == ' ' && tokenize_string[i + 3] == ' ') {
        MinToken token;
        AddUnknownToken(tokens, i, tokenize_string, unknown);
        tokens.emplace_back(token);
        i += 3;
        continue;
      }
      if (tokenize_string.substr(i, 3) == "abs" && tokenize_string[i - 1] == ' ' && tokenize_string[i + 3] == ' ') {
        AbsToken token;
        AddUnknownToken(tokens, i, tokenize_string, unknown);
        tokens.emplace_back(token);
        i += 3;
        continue;
      }
    }
    int k = 0;
    while (i + k < tokenize_string.size() && IsNumber(tokenize_string[i + k])) {
      k++;
    }
    if (k != 0 &&
        (tokenize_string[i - 1] == ' ' ||
         ((tokenize_string[i - 1] == '-' || tokenize_string[i - 1] == '+') && tokenize_string[i - 2] == ' ')) &&
        tokenize_string[i + k] == ' ') {
      NumberToken token;
      AddUnknownToken(tokens, i, tokenize_string, unknown);
      token.value = std::stoi(tokenize_string.substr(i, k));
      if (tokenize_string[i - 1] == '-') {
        token.value *= (-1);
      }
      tokens.emplace_back(token);
      i += k;
      continue;
    }
    unknown += 1;
  }
  return tokens;
}