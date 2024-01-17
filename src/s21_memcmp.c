#include "s21_string.h"

// Сравнивает первые n байтов str1 и str2.

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int res = 0;
  while (n != 0) {
    if (*(char *)str1 == *(char *)str2) {
      n--;
      str1++;
      str2++;
    } else {
      res = *(char *)str1 - *(char *)str2;
      break;
    }
  }
  return res;
}
