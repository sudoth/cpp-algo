#include <iostream>
#include <cstring>

void DelChar(char* str, int k) {
  int n = strlen(str);
  for (int i = 0; i < k; i++) {
    std::cout << str[i];
  }
  for (int i = k + 1; i < n; i++) {
    std::cout << str[i];
  }
}

bool IsPolyndrom(char* str, int na, int kn) {
  for (int i = 0; i <= (kn - na + 1) / 2; i++) {
    if (str[na + i] != str[kn - i]) {
      return false;
    }
  }
  return true;
}

void DelPunkt(char* str, char* newstr) {
  int j = 0;
  int n = strlen(str);
  for (int i = 0; i < n; i++) {
    if ((str[i] >= 'a') && (str[i] <= 'z')) {
      newstr[j] = str[i] - 'a' + 'A';
      j++;
      continue;
    }
    if ((str[i] >= 'A') && (str[i] <= 'Z')) {
      newstr[j] = str[i];
      j++;
      continue;
    }
  }
}

int main() {
  char str[200000];
  char newstr[200000];
  std::cin.getline(str, 1e6);
  DelPunkt(str, newstr);
  int n = strlen(newstr);
  for (int i = 0; i < n - 1; i++) { // (n - 1) / 2
    if (newstr[i] != newstr[n - i - 1]) {
      if (IsPolyndrom(newstr, i + 1, n - i - 1)) {
        std::cout << "YES\n";
        DelChar(newstr, i);
        return 0;
      }
      if (IsPolyndrom(newstr, i, n - i - 2)) {
        std::cout << "YES\n";
        DelChar(newstr, n - i - 1);
        return 0;
      }
      if (IsPolyndrom(newstr, i + 1, n - i - 2)) {
        std::cout << "YES\n";
        newstr[i] = newstr[n - i - 1];
        std::cout << newstr;
        return 0;
      }
      std::cout << "NO\n";
      return 0;
    }
  }
  std::cout << "YES\n";
  std::cout << newstr;
}