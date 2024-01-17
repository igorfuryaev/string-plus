#include "s21_string.h"

// Разбивает строку str на ряд токенов, разделенных delim.

char *s21_strtok(char *str, const char *delim) {
  static char *save;
  int ch, flag = 1;

  if (str == s21_NULL) str = save;
  do {
    if ((ch = *str++) == '\0') flag = 0;
  } while (s21_strchr(delim, ch) && flag);
  if (flag) {
    --str;
    save = str + s21_strcspn(str, delim);
    if (*save != '\0') *save++ = '\0';
  }
  return flag ? str : s21_NULL;
}