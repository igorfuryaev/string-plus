// #include <stdio.h>
// #include <stdlib.h>

// typedef long unsigned s21_size_t;
// char *s21_strcat(char *dest, const char *src);
// s21_size_t s21_strlen(const char *str);

#include "s21_string.h"

// Добавляет строку, на которую указывает src, в конец строки, на которую
// указывает dest.

char *s21_strcat(char *dest, const char *src) {
  int dest_len = s21_strlen(dest);
  int i = 0;
  for (i = 0; src[i]; i++) {
    dest[dest_len + i] = src[i];
  }
  dest[dest_len + i] = '\0';
  return dest;
}

// s21_size_t s21_strlen(const char *str) {
//   s21_size_t len = 0;
//   for (; *(str + len); len++)
//     ;
//   return len;
// }

// int main() {
//   char s[] = "qwerty";
//   char ss[] = "q1w2e3r4t5y";
//   s21_strcat(s, ss);
//   for (int i = 0; i < 20; i = i + 1) {
//     printf("%c", ss[i]);
//   }
//   return 0;
// }
