#include "s21_string.h"

// Выполняет поиск первого вхождения символа c (беззнаковый тип)
// в первых n байтах строки, на который указывает аргумент str.

void *s21_memchr(const void *str, int c, s21_size_t n) {
  s21_size_t i;
  char *rez = s21_NULL;
  for (i = 0; i < n; i++)
    if (*((char *)str + i) == c) {
      rez = (char *)str + i;
      break;
    }
  return rez;
}

// int main (){
//     char s[]="qwerty";
//     printf("%ld\n",(char*)s21_memchr(s, 'r', s21_strlen(s))-s);

//   return 0;
// }
