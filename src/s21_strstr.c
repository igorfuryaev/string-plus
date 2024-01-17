#include "s21_string.h"

// Находит первое вхождение всей строки needle
// (не включая завершающий нулевой символ),
// которая появляется в строке haystack.

char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t i = 0;
  s21_size_t n = s21_strlen(needle);
  char *rez = s21_NULL;
  while (*haystack != '\0') {
    if (*haystack == *needle && i < n - 1) {
      needle++;
      haystack++;
      i++;
    }
    if (*haystack != *needle && i < n) {
      haystack++;
      for (s21_size_t p = 0; p < i; p++) {
        needle--;
      }
      i = 0;
    }
    if (*haystack == *needle && i == n - 1) {
      rez = (char *)haystack - i;
      break;
    }
  }
  return rez;
}

// int main (){
//     char s[]="qwerty";
//     char p[]="rt";
//     printf("%ld\n",(char*)s21_strstr(s,p)-s);

//   return 0;
// }
