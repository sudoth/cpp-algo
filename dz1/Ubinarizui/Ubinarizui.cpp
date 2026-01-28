#include <cstdint>
#include <cstring>
#include <iostream>

int Strlen(const char* str) {
  if (*str == '\0') {
    return 0;
  }
  return Strlen(++str) + 1;
}

void DevideByTwo(char* str) {
  auto value = new char[1000007];
  for (int i = 0; i < Strlen(str); i++) {
    value[i] = str[Strlen(str) - i - 1];
  }
  value[Strlen(str)] = '\0';
  int ammandment = 0;
  for (int i = Strlen(value) - 1; i >= 0; i--) {
    int cur = (value[i] - '0') + ammandment * 10;
    value[i] = cur / 2 + '0';
    ammandment = cur % 2;
  }
  while (Strlen(value) > 0 && value[Strlen(value) - 1] == '0') {
    value[Strlen(value) - 1] = '\0';
  }
  for (int i = 0; i < Strlen(value); i++) {
    str[Strlen(value) - i - 1] = value[i];
  }
  str[Strlen(value)] = '\0';
  delete[] value;
}

void ToBinaryString(char* value, char* binary_number) {
  auto inverted_number = new char[1000007];
  int i = 0;
  do {
    int length = Strlen(value);
    inverted_number[i] = static_cast<char>('0' + (value[length - 1] - '0') % 2);
    DevideByTwo(value);
    i++;
  } while (Strlen(value) > 0);
  for (int j = 0; j < i; j++) {
    binary_number[j] = inverted_number[i - j - 1];
  }
  binary_number[i] = '\0';
  delete[] inverted_number;
}

int main() {
  auto prev_str = new char[1337];
  auto new_str = new char[1000007];
  auto inter_str = new char[1000007];
  auto binary_inter_str = new char[1000007];
  std::cin.getline(prev_str, 1e6);
  int n = Strlen(prev_str);
  int new_str_it = 0;
  for (int i = 0; i < n; i++) {
    if (prev_str[i] >= '0' && prev_str[i] <= '9') {
      // input int begin
      int j = 0;
      while (prev_str[i + j] >= '0' && prev_str[i + j] <= '9' && i + j < n) {
        inter_str[j] = prev_str[i + j];
        j++;
      }
      inter_str[j] = '\0';
      // input int end
      ToBinaryString(inter_str, binary_inter_str);
      for (int m = 0; m < Strlen(binary_inter_str); m++) {
        new_str[new_str_it] = binary_inter_str[m];
        new_str_it++;
      }
      // binarysation
      i += j - 1;
    } else {
      new_str[new_str_it] = prev_str[i];
      new_str_it++;
    }
  }
  for (int i = 0; i < new_str_it; i++) {
    std::cout << new_str[i];
  }
  delete[] prev_str;
  delete[] new_str;
  delete[] inter_str;
  delete[] binary_inter_str;
}