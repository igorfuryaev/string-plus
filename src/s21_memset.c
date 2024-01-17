// #include <string.h>

#include "s21_string.h"

// Копирует символ c (беззнаковый тип) в первые n символов
// строки, на которую указывает аргумент str.

void *s21_memset(void *str, int c, s21_size_t n) {
  char *ptr = str;
  for (s21_size_t i = 0; i < n; ++i) {
    *ptr++ = c;
  }
  return str;
}

// int main() {
//   char test[] = "1111111";
//   printf("%s\n", (char *)s21_memset(test, '6', 3));
//   return 0;
// }