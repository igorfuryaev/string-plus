#include "s21_string.h"

// Находит первый символ в строке str1, который соответствует
// любому символу, указанному в str2.

char *s21_strpbrk(const char *str1, const char *str2) {
  s21_size_t n = s21_strlen(str2);
  s21_size_t j = s21_strlen(str1);
  s21_size_t i;
  char *rez = s21_NULL;
  int check1 = 0;
  for (i = 0; i < n; i++) {
    int check = 0;
    while (check == 0 && *str1 != str2[i]) {
      if (*str1 == '\0' && i == (n - 1)) {
        check1 = 1;
        break;
      }
      if (*str1 == '\0') {
        check = 1;
        for (s21_size_t p = 0; p < j + 1; p++) {
          str1--;
        }
      }
      str1++;
    }
    if (check == 0 && check1 == 0) {
      rez = (char *)str1;
      break;
    }
  }
  return rez;
}

// int main (){
//     char s[]="qwertey";
//     char p[]="pe";
//     printf("%ld\n",(char*)s21_strpbrk(s,p) - s);

//   return 0;
// }
