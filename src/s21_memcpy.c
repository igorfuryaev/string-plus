// #include <stdio.h>
// #include <string.h>

#include "s21_string.h"

// Копирует n символов из src в dest.

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *ptr = dest + n - 1;
  char *sr = (char *)src + n - 1;
  for (s21_size_t i = 0; i < n; ++i) {
    *ptr-- = *sr--;
  }
  return dest;
}

// int main() {
//   char a[] = "hello world";

//   char b[] = "hello world";
//   s21_memcpy(a + 1, a, 10);
//   printf("s21 %s\n", a);

//   memcpy(b + 1, b, 10);
//   printf("orig %s\n", b);
//   return 0;
// }