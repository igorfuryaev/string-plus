#include "s21_string.h"

// Вычисляет длину начального сегмента str1, который полностью состоит из
// символов, не входящих в str2.

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t n = 0;
  int check = 0;

  for (; *str1 && check != 1; str1++) {
    (s21_strchr(str2, *str1) == NULL) ? (n++) : (check = 1);
  }

  return n;
}
