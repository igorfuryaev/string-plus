#include "s21_string.h"

// Выполняет поиск первого вхождения символа c (беззнаковый тип)
// в строке, на которую указывает аргумент str.

char *s21_strchr(const char *str, int c) {
  char *rez = s21_NULL;
  int check = 0;
  while (*str != (char)c) {
    if (*str++ == '\0') {
      check = 1;
      break;
    }
  }
  if (check != 1) {
    rez = (char *)str;
  }
  return rez;
}

// int main (){
//     char s[]="qwerty";
//     printf("%ld\n",(char*)s21_strchr(s,'r')-s);

//   return 0;
// }
