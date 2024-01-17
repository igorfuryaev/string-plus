#include <math.h>
#include <stdarg.h>
#include <stdint.h>
// #include <stdio.h>
// #include <string.h>

#include "s21_string.h"

struct FLAGS {
  int minus;
  int plus;
  int space;
  int width;
  int precision;
  int precision_point;
  char length;
  char specifier;
};

const char *get_flags(const char *format, struct FLAGS *flags);
const char *get_width(const char *format, struct FLAGS *flags);
const char *get_precision(const char *format, struct FLAGS *flags);
const char *get_length(const char *format, struct FLAGS *flags);

void specifier_value(struct FLAGS flags, char *buffer, va_list args);
void parse_int(struct FLAGS flags, char *buffer, va_list args);
void parse_unsigned(struct FLAGS flags, char *buffer, va_list args);
void parse_char(struct FLAGS flags, char *buffer, va_list args);
void parse_string(struct FLAGS flags, char *buffer, va_list args);
void parse_float(struct FLAGS flags, char *buffer, va_list args);

void format_string(struct FLAGS flags, char *buffer, char *str);
void format_wide_string(struct FLAGS flags, char *buffer, wchar_t *wstr);
void format_precision(char *buffer, struct FLAGS flags);
void format_flags(char *bufer, struct FLAGS flags);

int digits(const char *format);
void double_to_string(long double value, char *buffer, struct FLAGS flags);
void unsigned_num_to_string(uint64_t val, char *ret);

// int main() {
//   char str1[128] = {0};
//   char str2[128] = {0};
//   char format[] = "Hello world";
//   char arg1 = 'm';
//   // strcat(str1, format);
//   // printf("%s\n", str1);
//   sprintf(str1, format, arg1);
//   printf("%s\n", str1);
//   printf("%d\n", sprintf);
//   s21_sprintf(str2, format, arg1);
//   printf("%s\n", str2);
//   printf("%d\n", s21_sprintf);

//   return 0;
// }

// Отправляет форматированный вывод в строку, на которую указывает str.

int s21_sprintf(char *str, const char *format, ...) {
  struct FLAGS flags = {0};
  va_list args;
  va_start(args, format);
  while (*format) {
    if (*format != '%') {
      *str++ = *format++;
      continue;
    } else {
      format++;
      // struct FLAGS flags = {0};
      s21_memset(&flags, 0, sizeof(flags));
    }

    get_flags(format, &flags);
    get_width(format, &flags);
    get_precision(format, &flags);
    get_length(format, &flags);

    flags.specifier = *format;
    format++;

    char buffer[BUFF_SIZE] = {'\0'};
    specifier_value(flags, buffer, args);
    for (int i = 0; buffer[i]; i++, str++) *str = buffer[i];
  }

  *str = '\0';
  va_end(args);

  return s21_strlen(str);
}

const char *get_flags(const char *format, struct FLAGS *flags) {
  while (*format == '-' || *format == '+' || *format == ' ') {
    switch (*format) {
      case '-':
        flags->minus = 1;
        break;
      case '+':
        flags->plus = 1;
        break;
      case ' ':
        flags->space = 1;
        break;
    }
    format++;
  }
  return format;
}

const char *get_width(const char *format, struct FLAGS *flags) {
  flags->width = digits(format);
  return format;
}

const char *get_precision(const char *format, struct FLAGS *flags) {
  if (*format == '.') {
    flags->precision_point = 1;
    format++;
  }

  flags->precision = digits(format);
  return format;
}

const char *get_length(const char *format, struct FLAGS *flags) {
  switch (*format) {
    case 'h':
      flags->length = 'h';
      format++;
      break;
    case 'l':
      flags->length = 'l';
      format++;
      break;
  }
  return format;
}

int digits(const char *format) {
  int tmp = 0;
  while (*format >= '0' && *format <= '9') {
    tmp = tmp * 10 + (*format - '0');
    format++;
  }
  return tmp;
}

void specifier_value(struct FLAGS flags, char *buffer, va_list args) {
  if (flags.specifier == 'd' || flags.specifier == 'i')
    parse_int(flags, buffer, args);
  else if (flags.specifier == 'u')
    parse_unsigned(flags, buffer, args);
  else if (flags.specifier == '%')
    buffer[0] = '%';
  else if (flags.specifier == 'c')
    parse_char(flags, buffer, args);
  else if (flags.specifier == 's')
    parse_string(flags, buffer, args);
  else if (flags.specifier == 'f')
    parse_float(flags, buffer, args);
}

void parse_unsigned(struct FLAGS flags, char *buffer, va_list args) {
  uint64_t val = va_arg(args, uint64_t);
  switch (flags.length) {
    case 'h':
      val = (uint16_t)val;
      break;
    case 'l':
      val = (uint64_t)val;
      break;
  }
  unsigned_num_to_string(val, buffer);
  format_precision(buffer, flags);
  format_flags(buffer, flags);
}

void unsigned_num_to_string(uint64_t val, char *ret) {
  char buf[BUFF_SIZE + 1] = {'\0'};
  int idx = BUFF_SIZE - 1;
  if (val == 0) {
    buf[idx] = '0';
    idx--;
  }

  for (; val && idx; --idx, val /= 10) buf[idx] = "0123456789"[val % 10];
  for (int j = 0; buf[idx + 1]; idx++, j++) ret[j] = buf[idx + 1];
}

void parse_string(struct FLAGS flags, char *buffer, va_list args) {
  if (flags.length == 'l') {
    wchar_t *wstr = va_arg(args, wchar_t *);
    format_wide_string(flags, buffer, wstr);
  } else {
    char *str = va_arg(args, char *);
    format_string(flags, buffer, str);
  }
}

void format_string(struct FLAGS flags, char *buffer, char *str) {
  char tmp[BUFF_SIZE] = {'\0'};
  s21_strcpy(tmp, str);
  if (flags.precision_point) tmp[flags.precision] = '\0';

  int shift = flags.width - s21_strlen(tmp);
  int len = s21_strlen(tmp);

  if (flags.minus && shift > 0) {
    s21_strcpy(buffer, tmp);
    s21_memset(buffer + len, ' ', shift);
  } else if (shift > 0) {
    s21_memset(buffer, ' ', shift);
    s21_strcpy(buffer + shift, tmp);
  } else {
    s21_strcpy(buffer, tmp);
  }
}

void format_wide_string(struct FLAGS flags, char *buffer, wchar_t *wstr) {
  char tmp[BUFF_SIZE] = {'\0'};
  char str[BUFF_SIZE] = {'\0'};

  wcstombs(str, wstr, BUFF_SIZE);
  s21_strcpy(tmp, str);
  if (flags.precision_point) tmp[flags.precision] = '\0';

  int shift = flags.width - s21_strlen(tmp);
  int len = s21_strlen(tmp);

  if (flags.minus && shift > 0) {
    s21_strcpy(buffer, tmp);
    s21_memset(buffer + len, ' ', shift);
  } else if (shift > 0) {
    s21_memset(buffer, ' ', shift);
    s21_strcpy(buffer + shift, tmp);
  } else {
    s21_strcpy(buffer, tmp);
  }
}

void parse_float(struct FLAGS flags, char *buffer, va_list args) {
  long double value = 0;
  (flags.length == 'L') ? (value = va_arg(args, long double))
                        : (value = va_arg(args, double));

  if (!flags.precision_point) {
    flags.precision = 6;
  }

  double_to_string(value, buffer, flags);
  format_flags(buffer, flags);
}

void double_to_string(long double value, char *buffer, struct FLAGS flags) {
  char temp[BUFF_SIZE] = {'\0'};
  int idx = BUFF_SIZE - 2;
  long double l = 0, r = modfl(fabsl(value), &l);
  if (flags.precision == 0) {
    l = roundl(fabsl(value));
    r = 0;
  }
  char fractions[BUFF_SIZE] = {'\0'};
  for (int i = 0; i < flags.precision; i++) {
    r = r * 10;
    fractions[i] = (int)r + '0';
  }
  long long right = roundl(r), left = l;
  if (!right) {
    for (int i = 0; i < flags.precision; idx--, i++) temp[idx] = '0';
  } else {
    for (int i = s21_strlen(fractions); right || i > 0; right /= 10, idx--, i--)
      temp[idx] = (int)(right % 10 + 0.05) + '0';
  }
  if ((flags.precision_point && flags.precision != 0) || (int)r ||
      (!flags.precision_point && value == 0) || s21_strlen(fractions))
    temp[idx--] = '.';
  if (!left) {
    temp[idx] = '0';
    idx--;
  } else {
    for (; left; left /= 10, idx--) temp[idx] = (int)(left % 10) + '0';
  }
  for (int i = 0; temp[idx + 1]; idx++, i++) {
    if (value < 0 && i == 0) {
      buffer[i] = '-';
      i++;
    }
    buffer[i] = temp[idx + 1];
  }
}

void parse_int(struct FLAGS flags, char *buffer, va_list args) {
  int64_t val = va_arg(args, int64_t);

  switch (flags.length) {
    case 0:
      val = (int32_t)val;
      break;
    case 'h':
      val = (int16_t)val;
  }

  char tmp[BUFF_SIZE] = {'\0'};
  int idx = BUFF_SIZE - 2;  // почему -2?

  int neg = val < 0 ? 1 : 0;
  val = neg ? -val : val;

  if (val == 0) tmp[idx] = '0';  // получается это 510 ячейка?

  while (val > 0) {
    idx--;
    tmp[idx] = "0123456789abcdef"[val % 10];  // не понял такую запись
    val /= 10;
  }
  for (int j = 0; tmp[idx]; idx++, j++) {
    if (neg && j == 0) {
      buffer[j++] = '-';  // не понял почему плюсуется в скобках, мы же должны
                          // задать '-' для нулевой ячейки массива
    }

    buffer[j] = tmp[idx];
  }
  format_precision(buffer, flags);
  format_flags(buffer, flags);
}

void format_precision(char *buffer, struct FLAGS flags) {
  char tmp[BUFF_SIZE] = {'\0'};

  int sign = 0;
  int len = s21_strlen(buffer);

  if (buffer[0] == '-') {
    tmp[0] = '-';
    len--;
    sign = 1;
  }

  if (flags.precision > len) {
    int idx;
    for (idx = sign; idx < flags.precision - len + sign; idx++) tmp[idx] = '0';

    for (int i = sign; buffer[i]; i++, idx++) tmp[idx] = buffer[i];

    s21_strcpy(buffer, tmp);
  }

  char specs[] = {'d', 'i', 'u'};
  int res = 0;
  for (s21_size_t i = 0; i < sizeof(specs); i++) {
    if (specs[i] == flags.specifier) {
      res = 1;
      break;
    }
  }

  if (flags.precision_point && flags.precision == 0 && res && buffer[0] == '0')
    buffer[0] = '\0';
}

void format_flags(char *buffer, struct FLAGS flags) {
  char tmp[BUFF_SIZE + 1] = {'\0'};
  if (flags.plus && flags.specifier != 'u') {
    tmp[0] = buffer[0] == '-' ? buffer[0] : '+';
    s21_strcpy(tmp + 1, buffer[0] == '-' ? buffer + 1 : buffer);
    s21_strcpy(buffer, tmp);
  } else if (flags.space && buffer[0] != '-' && flags.specifier != 'u') {
    tmp[0] = ' ';
    s21_strcpy(tmp + 1, buffer);
    s21_strcpy(buffer, tmp);
  }
  if (flags.width > (int)s21_strlen(buffer)) {
    int idx = flags.width - s21_strlen(buffer);
    if (!flags.minus) {
      s21_strcpy(tmp + idx, buffer);
    } else {
      s21_strcpy(tmp, buffer);
      s21_memset(tmp + s21_strlen(tmp), ' ', idx);
    }
    s21_strcpy(buffer, tmp);
  }
}

void parse_char(struct FLAGS flags, char *buffer, va_list args) {
  if (flags.length == 'l') {
    wchar_t w_c = va_arg(args, wchar_t);
    if (flags.minus && flags.width) {
      wcstombs(buffer, &w_c, BUFF_SIZE);
      for (int i = s21_strlen(buffer); i < flags.width; i++) buffer[i] = ' ';
    } else if (flags.width) {
      char tmp[BUFF_SIZE] = {'\0'};
      wcstombs(tmp, &w_c, BUFF_SIZE);
      for (s21_size_t i = 0; i < flags.width - s21_strlen(tmp); i++)
        buffer[i] = ' ';
      s21_strcat(buffer, tmp);
    } else {
      wcstombs(buffer, &w_c, BUFF_SIZE);
    }
  } else {
    char c = va_arg(args, int);  // возможно там нужен char, а не int
    if (!flags.minus && flags.width) {
      for (int i = 0; i < flags.width; i++) {
        buffer[i] = ' ';
        if (i == flags.width - 1) buffer[i] = c;
      }
    } else if (flags.width) {
      buffer[0] = c;
      for (int i = 1; i < flags.width; i++) buffer[i] = ' ';
    } else {
      buffer[0] = c;
    }
  }
}
