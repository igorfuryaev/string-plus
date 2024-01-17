#include "s21_string.h"

// Еще одна функция для копирования n символов из src в dest.

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char *ptr = dest + n - 1;
  char *sr = (char *)src + n - 1;
  for (s21_size_t i = 0; i < n; ++i) {
    *ptr-- = *sr--;
  }
  return dest;
}

// int main() {
//   char a[] = "hello world";

//   char b[4] = "123\0";
//   // s21_memmove(a + 2, a, 10);
//   // printf("my %s\n", a);
//   s21_memmove(b + 1, b, 2);
//   printf("\nmove %s\n", b);
//   return 0;
// }
