#include "s21_string.h"

// Выполняет поиск последнего вхождения символа c (беззнаковый тип)
// в строке, на которую указывает аргумент str.

char *s21_strrchr(const char *str, int c) {
  s21_size_t n = s21_strlen(str);
  const char *ch = &str[0];
  char *rez = s21_NULL;
  int check = 0;
  for (s21_size_t i = 0; i < n; i++) {
    str++;
  }
  while (*str != (char)c) {
    if (str-- == ch) {
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
//     char s[]="qewerty";
//     printf("%ld\n",(char*)s21_strrchr(s,'p')-s);

//   return 0;
// }