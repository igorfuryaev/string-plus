#include "s21_string.h"
// #include <stdio.h>
// #include <stdlib.h>

// typedef long unsigned s21_size_t;
// char *s21_strcat(char *dest, const char *src);
// s21_size_t s21_strlen(const char *str);

// Добавляет строку, на которую указывает src, в конец строки,
// на которую указывает dest, длиной до n символов.

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t dest_len = s21_strlen(dest);
  s21_size_t i = 0;

  for (i = 0; i < n && src[i]; i++) {
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
//   char dest[] = "qw";
//   char src[] = "12345";
//   s21_strncat(dest, src, 2);
//   //   for (int i = 0; i < 7; i++) {
//   //     printf("%c", dest[i]);
//   //   }
//   return 0;
// }
