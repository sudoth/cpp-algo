// size_t Strlen(const char* str);. Вычисляет длину строки str (без учета
// нулевого символа).

// int Strcmp(const char* first, const char* second);. Лексикографически
// сравнивает две строки. Если first < second, то возвращает произвольное
// отрицательное число, если first > second, то - положительное. В случае
// равенства возвращает 0.

// int Strncmp(const char* first, const char* second, size_t count);. То же, что
// и предыдущая функция, но сравнивает первые count символов строк (либо пока не
// встретит нулевой символ).

// char* Strcpy(char* dest, const char* src);. Принимает строку src и копирует
// ее содержимое (вместе с нуль-терминатором) в dest. Гарантируется, что dest
// указывает на область памяти, достаточную для хранения src. Возвращает dest.

// char* Strncpy(char* dest, const char* src, size_t count);. То же, что и
// предыдущая функция, но копирует ровно count символов из src. Если count
// больше размера src, то оставшиеся символы заполняются нуль-символами.
// Возвращает dest.

// char* Strcat(char* dest, const char* src);. Приписывает строку src в конец
// строки dest (конкатенация строк). Гарантируется, что dest указывает на
// область памяти, достаточную для хранения итоговой строки. Возвращает dest.

// char* Strncat(char* dest, const char* src, size_t count);. То же, что и
// предыдущая функция, но добавляет только первые count символов из src +
// нулевой символ. Если count больше чем длина src, то работает так же как и
// Strcat(dest, src). Возвращает dest.

// const char* Strchr(const char* str, char symbol);. Возвращает указатель на
// первое появление символа symbol в строке str (с учетом нулевого символа),
// либо нулевой указатель, если такого символа нет.

// const char* Strrchr(const char* str, char symbol);. Возвращает указатель на
// последнее появление символа symbol в строке str (с учетом нулевого символа),
// либо нулевой указатель, если такого символа нет.

// size_t Strspn(const char* dest, const char* src);. Возвращает количество
// первых символов dest, которые встречаются в строке src (без учета нулевого
// символа).

// size_t Strcspn(const char* dest, const char* src);. Возвращает количество
// первых символов dest, которые не встречаются в строке src (без учета нулевого
// символа).

// const char* Strpbrk(const char* dest, const char* breakset);. Возвращает
// указатель на первый элемент dest, который лежит в breakset, либо нулевой
// указатель, если такого элемента нет.

// const char* Strstr(const char* str, const char* pattern);. Осуществляет поиск
// подстроки pattern в строке str. Возвращает указатель на начало первого
// вхождения, либо нулевой указатель, если вхождения найдено не было.

#include "cstring.h"

size_t Strlen(const char* str) {
  if (*str == '\0') {
    return 0;
  }
  return Strlen(++str) + 1;
}

int Strcmp(const char* first, const char* second) {
  if (*first == '\0' && *second == '\0') {
    return 0;
  }
  if (*first == '\0' || *first < *second) {
    return -1;
  }
  if (*second == '\0' || *first > *second) {
    return 1;
  }
  return Strcmp(++first, ++second);
}

int Strncmp(const char* first, const char* second, size_t count) {
  if ((*first == '\0' && *second == '\0') || count == 0) {
    return 0;
  }
  if (*first == '\0' || *first < *second) {
    return -1;
  }
  if (*second == '\0' || *first > *second) {
    return 1;
  }
  return Strncmp(++first, ++second, --count);
}

char* Strcpy(char* dest, const char* src) {
  int src_len = Strlen(src);
  for (int i = 0; i <= src_len; i++) {
    dest[i] = src[i];
  }
  return dest;
}

char* Strncpy(char* dest, const char* src, size_t count) {
  int src_len = Strlen(src);
  int c = count;
  if (c > src_len) {
    for (int i = 0; i < src_len; i++) {
      dest[i] = src[i];
    }
    for (int i = src_len; i <= c; i++) {
      dest[i] = '\0';
    }
    return dest;
  }
  for (int i = 0; i < c; i++) {
    dest[i] = src[i];
  }
  return dest;
}

char* Strcat(char* dest, const char* src) {
  int src_len = Strlen(src);
  int dest_len = Strlen(dest);
  for (int i = 0; i <= src_len; i++) {
    dest[dest_len + i] = src[i];
  }
  return dest;
}

char* Strncat(char* dest, const char* src, size_t count) {
  int src_len = Strlen(src);
  int dest_len = Strlen(dest);
  int c = count;
  if (c > src_len) {
    for (int i = 0; i <= src_len; i++) {
      dest[dest_len + i] = src[i];
    }
    return dest;
  }
  for (int i = 0; i < c; i++) {
    dest[dest_len + i] = src[i];
  }
  dest[dest_len + c] = '\0';
  return dest;
}

const char* Strchr(const char* str, char symbol) {
  int str_len = Strlen(str);
  for (int i = 0; i <= str_len; i++) {
    if (str[i] == symbol) {
      return str + i;
    }
  }
  return nullptr;
}

const char* Strrchr(const char* str, char symbol) {
  int str_len = Strlen(str);
  for (int i = str_len; i >= 0; i--) {
    if (str[i] == symbol) {
      return str + i;
    }
  }
  return nullptr;
}

size_t Strspn(const char* dest, const char* src) {
  int dest_len = Strlen(dest);
  size_t count = 0;
  for (int i = 0; i < dest_len; i++) {
    if (Strchr(src, dest[i]) == nullptr) {
      break;
    }
    count++;
  }
  return count;
}

size_t Strcspn(const char* dest, const char* src) {
  int dest_len = Strlen(dest);
  size_t count = 0;
  for (int i = 0; i < dest_len; i++) {
    if (Strchr(src, dest[i]) != nullptr) {
      break;
    }
    count++;
  }
  return count;
}

const char* Strpbrk(const char* dest, const char* breakset) {
  int dest_len = Strlen(dest);
  for (int i = 0; i < dest_len; i++) {
    if (Strchr(breakset, dest[i]) != nullptr) {
      return dest + i;
    }
  }
  return nullptr;
}

const char* Strstr(const char* str, const char* pattern) {
  int str_len = Strlen(str);
  int pattern_len = Strlen(pattern);
  for (int i = 0; i <= str_len - pattern_len + 1; i++) {
    int j = 0;
    while (str[i + j] == pattern[j] && j < pattern_len) {
      j++;
    }
    if (j == pattern_len) {
      return str + i;
    }
  }
  return nullptr;
}