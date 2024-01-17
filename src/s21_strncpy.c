#include "s21_string.h"

// Копирует до n символов из строки, на которую указывает src, в dest.

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *ptr = dest;
  s21_size_t i = 0;
  for (; i < n && *src != '\0'; ++src, ++i) {
    *ptr++ = *src;
  }
  if (s21_strlen(src) < n) {
    for (; i < n; ++i) {
      *ptr++ = '\0';
    }
  }
  return dest;
}

// int main() {
//   char test_cpy[3] = "1k";
//   char test_out[5] = "8887";
//   printf("%s\n", s21_strncpy(test_out, test_cpy, 4));
//   for (int i = 0; i < 9; ++i) {
//     if (test_out[i] == '\0') printf("\\0");
//     printf("%c", test_out[i]);
//   }
//   return 0;
// }