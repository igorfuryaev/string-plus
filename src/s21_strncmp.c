#include "s21_string.h"

// Сравнивает не более первых n байтов str1 и str2.

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int res = 0;
  while (n != 0) {
    if (*str1 == *str2) {
      n--;
      str1++;
      str2++;
    } else {
      res = *str1 - *str2;
      break;
    }
  }
  return res;
}
