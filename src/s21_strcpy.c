#include "s21_string.h"

// Копирует строку, на которую указывает src, в dest.

char *s21_strcpy(char *dest, const char *src) {
  char *ptr = dest;
  for (; *src != '\0'; ++src) {
    *ptr++ = *src;
  }
  *ptr = '\0';
  return dest;
}

// int main() {
//   char test_cpy[10] = "1k";
//   char test_out[5] = "8888";
//   printf("%s\n", s21_strcpy(test_out, test_cpy));
//   for (int i = 0; i < 5; ++i) {
//     if (test_out[i] == '\0') printf("\\0");
//     printf("%c", test_out[i]);
//   }
//   return 0;
// }