#include "s21_string.h"

void* s21_memchr(const void* str, int c, s21_size n) {
  void* ptr = S21_NULL;
  for (s21_size i = 0; i < n; ++i) {
    if (*((const unsigned char*)str + i) == (unsigned char)c) {
      ptr = (void*)(str + i);
      break;
    }
  }
  return ptr;
}

char* s21_strchr(const char* str, int c) {
  char* ptr = S21_NULL;
  if (str == S21_NULL) {
    return ptr;
  }
  for (s21_size i = 0;; ++i) {
    if (*(str + i) == '\0') {
      if (c == '\0') {
        ptr = (char*)(str + i);
      }
      break;
    }
    if (*(str + i) == c) {
      ptr = (char*)(str + i);
      break;
    }
  }
  return ptr;
}

char* s21_strrchr(const char* str, int c) {
  if (str == S21_NULL) {
    return S21_NULL;
  }
  char* ptr = S21_NULL;
  long long len = s21_strlen(str);
  for (long long i = len; i >= 0; --i) {
    if (str[i] == c) {
      ptr = (char*)(str + i);
      break;
    }
  }
  return ptr;
}

char* s21_strpbrk(const char* str1, const char* str2) {
  for (int i = 0; str1[i] != '\0'; ++i) {
    for (int j = 0; str2[j] != '\0'; ++j) {
      if (str1[i] == str2[j]) {
        return (char*)(str1 + i);
      }
    }
  }
  return S21_NULL;
}

char* s21_strstr(const char* haystack, const char* needle) {
  if (haystack == S21_NULL || needle == S21_NULL) {
    return S21_NULL;
  }
  if (!*needle) {
    return (char*)haystack;
  }
  for (s21_size i = 0; haystack[i]; ++i) {
    s21_size j;
    for (j = 0; needle[j] && haystack[i + j]; j++) {
      if (haystack[i + j] != needle[j]) {
        break;
      }
    }
    if (!needle[j]) {
      return (char*)(haystack + i);
    }
  }
  return S21_NULL;
}

char* s21_strtok(char* str, const char* delim) {
  if (delim == S21_NULL) {
    return S21_NULL;
  }
  static char* next_token = S21_NULL;
  char* current_token;
  if (str != S21_NULL) {
    current_token = str;
  } else {
    if (next_token == S21_NULL) return S21_NULL;
    current_token = next_token;
  }
  while (*current_token != '\0' &&
         s21_strchr(delim, *current_token) != S21_NULL) {
    current_token++;
  }
  if (*current_token == '\0') {
    next_token = S21_NULL;
    return S21_NULL;
  }
  char* result = current_token;
  while (*current_token != '\0' &&
         s21_strchr(delim, *current_token) == S21_NULL) {
    current_token++;
  }
  if (*current_token != '\0') {
    *current_token = '\0';
    next_token = ++current_token;
  } else {
    next_token = S21_NULL;
  }
  return result;
}

int s21_memcmp(const void* str1, const void* str2, s21_size n) {
  const unsigned char* pointer1 = (const unsigned char*)str1;
  const unsigned char* pointer2 = (const unsigned char*)str2;
  for (s21_size i = 0; i < n; ++i) {
    if (*(pointer1 + i) != *(pointer2 + i)) {
      return (int)(*(pointer1 + i) - *(pointer2 + i));
    }
  }
  return 0;
}

int s21_strncmp(const char* str1, const char* str2, s21_size n) {
  int flag = 0;
  if (str1 != S21_NULL && str2 != S21_NULL) {
    for (s21_size i = 0; i < n; ++i) {
      if (str1[i] != str2[i] || str1[i] == '\0' || str2[i] == '\0') {
        flag = (int)((unsigned char)str1[i] - (unsigned char)str2[i]);
        break;
      }
    }
  }
  return flag;
}

void* s21_memcpy(void* dest, const void* src, s21_size n) {
  if (dest == S21_NULL || src == S21_NULL) {
    return S21_NULL;
  }
  unsigned char* dest_pointer = (unsigned char*)dest;
  const unsigned char* src_pointer = (const unsigned char*)src;
  for (s21_size i = 0; i < n; ++i) {
    *(dest_pointer++) = *(src_pointer++);
  }
  return dest;
}

char* s21_strncpy(char* dest, const char* src, s21_size n) {
  if (dest == S21_NULL || src == S21_NULL) {
    return S21_NULL;
  }
  char* dest_start = dest;
  s21_size i;
  for (i = 0; i < n && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }
  for (; i < n; i++) {
    dest[i] = '\0';
  }
  return dest_start;
}

char* s21_strncat(char* dest, const char* src, s21_size n) {
  if (dest == S21_NULL || src == S21_NULL) {
    return S21_NULL;
  }
  char* dest_ptr = dest;
  const char* src_ptr = src;
  dest_ptr = s21_strchr(dest_ptr, '\0');
  while (n > 0 && *src_ptr != '\0') {
    *(dest_ptr++) = *(src_ptr++);
    n--;
  }
  *dest_ptr = '\0';
  return dest;
}

void* s21_memset(void* src, int c, s21_size n) {
  if (src == S21_NULL) {
    return S21_NULL;
  }
  unsigned char* ptr = (unsigned char*)src;
  c = (unsigned char)c;
  for (s21_size i = 0; i < n; ++i) {
    *(ptr++) = c;
  }
  return src;
}

s21_size s21_strlen(const char* str) {
  if (str == S21_NULL) {
    return 0;
  }
  const char* start = str;
  while (*str) str++;
  return str - start;
}

s21_size s21_strcspn(const char* s, const char* reject) {
  if (s == S21_NULL || reject == S21_NULL) {
    return 0;
  }
  s21_size len = 0;
  const char* src = s;
  const char* rej = reject;
  while (*src != '\0') {
    const char* ptr = s21_strchr(rej, *src);
    if (ptr != S21_NULL) {
      break;
    }
    len++;
    src++;
  }
  return len;
}

char* s21_strerror(int errnum) {
#ifdef __linux__
  static const char** errors = errors_linux;
  int count = MAX_SIZE_LINUX;
#elif __APPLE__
  static const char** errors = errors_apple;
  int count = MAX_SIZE_APPLE;
#else
#error "Unsupported operating system"
#endif
  static char result[100];
  if (0 <= errnum && errnum < count) {
    sprintf(result, "%s", errors[errnum]);
  } else {
    sprintf(result, "Unknown error %d", errnum);
  }
  return result;
}

void* s21_to_upper(const char* str) {
  if (str == S21_NULL) {
    return S21_NULL;
  }
  s21_size len = 0;
  while (*(str + len) != '\0') {
    len++;
  }
  char* pointer = malloc(len + 1);
  if (pointer == S21_NULL) {
    return S21_NULL;
  }
  for (s21_size i = 0; i <= len; ++i) {
    if ('a' <= str[i] && str[i] <= 'z') {
      pointer[i] = str[i] - 32;
      continue;
    }
    pointer[i] = str[i];
  }
  return pointer;
}

void* s21_to_lower(const char* str) {
  if (str == S21_NULL) {
    return S21_NULL;
  }
  s21_size len = 0;
  while (*(str + len) != '\0') {
    len++;
  }
  char* pointer = malloc(len + 1);
  if (pointer == S21_NULL) {
    return S21_NULL;
  }
  for (s21_size i = 0; i <= len; ++i) {
    if ('A' <= str[i] && str[i] <= 'Z') {
      pointer[i] = str[i] + 32;
      continue;
    }
    pointer[i] = str[i];
  }
  return pointer;
}

void* s21_insert(const char* src, const char* str, size_t start_index) {
  if (src == S21_NULL || s21_strlen(src) < start_index) {
    return S21_NULL;
  }
  s21_size src_len = s21_strlen(src);
  s21_size str_len = (str == S21_NULL) ? 0 : s21_strlen(str);
  s21_size len = src_len + str_len + 1;
  char* pointer = malloc(len);
  if (pointer != S21_NULL) {
    for (s21_size i = 0; i < start_index; ++i) {
      pointer[i] = src[i];
    }
    for (s21_size j = 0; j < str_len; ++j) {
      pointer[start_index + j] = str[j];
    }
    for (s21_size k = start_index; k < src_len; ++k) {
      pointer[str_len + k] = src[k];
    }
    pointer[len - 1] = '\0';
  }
  return pointer;
}

void* s21_trim(const char* src, const char* trim_chars) {
  if (!src) return S21_NULL;
  if (!trim_chars) {
    trim_chars = " \t\n\r\f\v";
  }
  s21_size len = s21_strlen(src);
  if (len == 0) {
    char* new_src = malloc(1);
    if (new_src) {
      new_src[0] = '\0';
    }
    return new_src;
  }
  const char* r_ptr = &src[len - 1];
  const char* l_ptr = src;
  while (l_ptr <= r_ptr && s21_strchr(trim_chars, *l_ptr) != S21_NULL) {
    l_ptr++;
  }
  if (l_ptr > r_ptr) {
    char* new_src = malloc(1);
    if (new_src) new_src[0] = '\0';
    return new_src;
  }
  while (r_ptr > l_ptr && s21_strchr(trim_chars, *r_ptr) != S21_NULL) {
    r_ptr--;
  }
  len = r_ptr - l_ptr + 1;
  char* new_src = malloc(len + 1);
  if (new_src == S21_NULL) {
    return S21_NULL;
  }
  for (s21_size i = 0; i < len; ++i) {
    new_src[i] = l_ptr[i];
  }
  new_src[len] = '\0';
  return new_src;
}

int s21_atoi(const char** str) {
  int num = 0;
  while (**str >= '0' && **str <= '9') {
    num = num * 10 + (**str - '0');
    (*str)++;
  }
  return num;
}

int s21_sprintf(char* str, const char* format, ...) {
  va_list args;
  va_start(args, format);
  char* start = str;
  while (*format) {
    options opt = {0};
    if (*format != '%') {
      *str++ = *format++;
      continue;
    }
    format++;
    parsing(&format, &args, &opt);
    switch (opt.specifier) {
      case 'c':
        format_c(&str, &args, &opt);
        break;
      case 'd':
      case 'i':
        format_d(&str, &args, &opt);
        break;
      case 'u':
        format_u(&str, &args, &opt);
        break;
      case 'f':
        format_f(&str, &args, &opt);
        break;
      case 's':
        format_s(&str, &args, &opt);
        break;
      case 'x':
        format_x(&str, &args, &opt, 0);
        break;
      case 'X':
        format_x(&str, &args, &opt, 1);
        break;
      case 'o':
        format_o(&str, &args, &opt);
        break;
      case 'p':
        format_p(&str, &args, &opt);
        break;
      case '%':
        format_percent(&str);
        break;
    }
  }
  *str = '\0';
  va_end(args);
  return str - start;
}

void parsing(const char** format, va_list* args, options* opt) {
  opt->width = 0;
  opt->precision = 0;
  opt->precision_specified = 0;

  while (**format == '+' || **format == '-' || **format == ' ' ||
         **format == '#' || **format == '0') {
    if (**format == '+') opt->plus = 1;
    if (**format == '-') opt->minus = 1;
    if (**format == ' ') opt->space = 1;
    if (**format == '#') opt->hash = 1;
    if (**format == '0') opt->zero = 1;
    (*format)++;
  }
  if (**format == '*') {
    opt->width = va_arg(*args, int);
    (*format)++;
  } else if ('0' <= **format && **format <= '9') {
    opt->width = s21_atoi(format);
  }
  if (**format == '.') {
    (*format)++;
    opt->precision_specified = 1;
    if (**format == '*') {
      opt->precision = va_arg(*args, int);
      (*format)++;
    } else if ('0' <= **format && **format <= '9') {
      opt->precision = s21_atoi(format);
    }
  }
  if (**format == 'h') {
    opt->h = 1;
    (*format)++;
  } else if (**format == 'l') {
    opt->l = 1;
    (*format)++;
  } else if (**format == 'L') {
    opt->L = 1;
    (*format)++;
  }
  opt->specifier = **format;
  (*format)++;
}

void format_c(char** str, va_list* args, options* opt) {
  char* ptr = *str;
  char c = (char)va_arg(*args, int);
  if (!opt->minus) {
    if (opt->width > 1) {
      add_padding(&ptr, ' ', opt->width - 1);
    }
    add_padding(&ptr, c, 1);
  } else {
    add_padding(&ptr, c, 1);
    if (opt->width > 1) {
      add_padding(&ptr, ' ', opt->width - 1);
    }
  }
  *str = ptr;
}

void format_d(char** str, va_list* args, options* opt) {
  char* ptr = *str;
  long long number;
  if (opt->l) {
    number = va_arg(*args, long);
  } else if (opt->h) {
    number = (short)va_arg(*args, int);
  } else {
    number = va_arg(*args, int);
  }
  int is_negative = number < 0 ? 1 : 0;
  number = number < 0 ? -number : number;
  int len = count_figures(number);
  opt->space = (opt->plus) ? 0 : opt->space;
  int size = len;
  if (opt->precision > len) {
    size = opt->precision;
  }
  if (opt->plus || is_negative) {
    size++;
  } else if (opt->space) {
    size++;
  }
  int pad = (opt->width > size) ? (opt->width - size) : 0;
  if (!opt->minus) {
    if (opt->zero && !opt->precision_specified) {
      if (is_negative) {
        *ptr++ = '-';
      } else if (opt->plus) {
        *ptr++ = '+';
      } else if (opt->space) {
        *ptr++ = ' ';
      }
      add_padding(&ptr, '0', pad);
    } else {
      add_padding(&ptr, ' ', pad);
      if (is_negative) {
        *ptr++ = '-';
      } else if (opt->plus) {
        *ptr++ = '+';
      } else if (opt->space) {
        *ptr++ = ' ';
      }
    }
    if (opt->precision_specified && opt->precision > len) {
      add_padding(&ptr, '0', opt->precision - len);
    }
    put_number(&ptr, number);
  } else {
    if (is_negative) {
      add_padding(&ptr, '-', 1);
    } else if (opt->plus) {
      add_padding(&ptr, '+', 1);
    } else if (opt->space) {
      add_padding(&ptr, ' ', 1);
    }
    if (opt->precision_specified && opt->precision > len) {
      add_padding(&ptr, '0', opt->precision - len);
    }
    put_number(&ptr, number);
    if (opt->width > size) {
      add_padding(&ptr, ' ', pad);
    }
  }
  *str = ptr;
}

void format_u(char** str, va_list* args, options* opt) {
  char* ptr = *str;
  unsigned long long number;
  int len;
  if (opt->l)
    number = va_arg(*args, unsigned long);
  else if (opt->h)
    number = (unsigned short)va_arg(*args, unsigned int);
  else
    number = va_arg(*args, unsigned int);

  len = count_figures_unsigned(number);

  opt->plus = 0;
  opt->space = 0;

  int size = len;
  if (opt->precision > len) size = opt->precision;

  if (!opt->minus) {
    if (opt->width > size) {
      char pad = opt->zero ? '0' : ' ';
      add_padding(&ptr, pad, opt->width - size);
    }

    if (opt->precision > len) add_padding(&ptr, '0', opt->precision - len);

    put_unsigned(&ptr, number);
  } else {
    if (opt->precision > len) add_padding(&ptr, '0', opt->precision - len);

    put_unsigned(&ptr, number);

    if (opt->width > size) add_padding(&ptr, ' ', opt->width - size);
  }

  *str = ptr;
}

void format_f(char** str, va_list* args, options* opt) {
  char* ptr = *str;
  long double number;
  if (opt->L)
    number = va_arg(*args, long double);
  else
    number = va_arg(*args, double);
  int is_negative = number < 0;
  if (is_negative) number = -number;
  int precision = opt->precision_specified ? opt->precision : 6;
  long double rounder = 0.5;
  for (int i = 0; i < precision; i++) rounder /= 10.0;
  number += rounder;
  long long int_part = (long long)number;
  long double frac = number - int_part;
  long long pow10 = 1;
  for (int i = 0; i < precision; i++) pow10 *= 10;
  long long frac_part = (long long)(frac * pow10);
  int int_len = count_figures(int_part);
  int size = int_len;
  if (precision > 0) size += 1 + precision;
  if (is_negative || opt->plus || opt->space) size++;
  opt->space = opt->plus ? 0 : opt->space;
  int pad = (opt->width > size) ? (opt->width - size) : 0;
  if (!opt->minus) {
    if (opt->zero) {
      if (is_negative)
        *ptr++ = '-';
      else if (opt->plus)
        *ptr++ = '+';
      else if (opt->space)
        *ptr++ = ' ';
      add_padding(&ptr, '0', pad);
    } else {
      add_padding(&ptr, ' ', pad);
      if (is_negative)
        *ptr++ = '-';
      else if (opt->plus)
        *ptr++ = '+';
      else if (opt->space)
        *ptr++ = ' ';
    }
  } else {
    if (is_negative)
      *ptr++ = '-';
    else if (opt->plus)
      *ptr++ = '+';
    else if (opt->space)
      *ptr++ = ' ';
  }
  put_number(&ptr, int_part);
  if (precision > 0) {
    *ptr++ = '.';
    int frac_len = count_figures(frac_part);
    for (int i = 0; i < precision - frac_len; i++) *ptr++ = '0';
    put_number(&ptr, frac_part);
  }
  if (opt->minus) add_padding(&ptr, ' ', pad);
  *str = ptr;
}

void format_s(char** str, va_list* args, options* opt) {
  char* ptr = *str;
  char* s = va_arg(*args, char*);
  if (s == NULL) s = "(null)";
  int len = s21_strlen(s);
  if (opt->precision_specified && opt->precision < len && opt->precision >= 0)
    len = opt->precision;
  int width = opt->width;
  if (width < 0) {
    width = -width;
    opt->minus = 1;
  }
  if (!opt->minus) {
    if (opt->width > len) add_padding(&ptr, ' ', opt->width - len);

    for (int i = 0; i < len; i++) add_padding(&ptr, s[i], 1);
  } else {
    for (int i = 0; i < len; i++) add_padding(&ptr, s[i], 1);

    if (opt->width > len) add_padding(&ptr, ' ', opt->width - len);
  }
  *str = ptr;
}

void format_x(char** str, va_list* args, options* opt, int uppercase) {
  char* ptr = *str;
  unsigned long long number;
  if (opt->l) {
    number = va_arg(*args, unsigned long);
  } else if (opt->h) {
    number = (unsigned short)va_arg(*args, unsigned int);
  } else {
    number = va_arg(*args, unsigned int);
  }
  int len = 0;
  unsigned long long temp = number;
  if (temp == 0) {
    len = 1;
  } else {
    while (temp > 0) {
      len++;
      temp /= 16;
    }
  }
  if (opt->precision_specified && opt->precision == 0 && number == 0) {
    len = 0;
  }
  int hash_size = 0;
  if (opt->hash && number != 0) {
    hash_size = 2;
  }
  int size = len;
  if (opt->precision_specified && opt->precision > len) {
    size = opt->precision;
  }
  size += hash_size;
  if (!opt->minus) {
    char pad_char = (opt->zero && !opt->precision_specified) ? '0' : ' ';
    if (opt->width > size) {
      add_padding(&ptr, pad_char, opt->width - size);
    }
    if (opt->hash && number != 0) {
      add_padding(&ptr, '0', 1);
      add_padding(&ptr, uppercase ? 'X' : 'x', 1);
    }
    if (opt->precision > len) {
      add_padding(&ptr, '0', opt->precision - len);
    }
    if (!(opt->precision_specified && opt->precision == 0 && number == 0)) {
      put_hex(&ptr, number, uppercase);
    }
  } else {
    if (opt->hash && number != 0) {
      add_padding(&ptr, '0', 1);
      add_padding(&ptr, uppercase ? 'X' : 'x', 1);
    }
    if (opt->precision > len) {
      add_padding(&ptr, '0', opt->precision - len);
    }
    if (!(opt->precision_specified && opt->precision == 0 && number == 0)) {
      put_hex(&ptr, number, uppercase);
    }
    if (opt->width > size) {
      add_padding(&ptr, ' ', opt->width - size);
    }
  }
  *str = ptr;
}

void format_o(char** str, va_list* args, options* opt) {
  char* ptr = *str;
  unsigned long long number;
  if (opt->l) {
    number = va_arg(*args, unsigned long);
  } else if (opt->h) {
    number = (unsigned short)va_arg(*args, unsigned int);
  } else {
    number = va_arg(*args, unsigned int);
  }
  int len = count_oct_digits(number);
  if (opt->precision_specified && opt->precision == 0 && number == 0) {
    len = 0;
  }

  int hash_size = 0;
  if (opt->hash && number != 0) {
    hash_size = 1;
  }
  int size = len;
  if (opt->precision_specified && opt->precision > len) {
    size = opt->precision;
  }
  size += hash_size;
  if (!opt->minus) {
    if (opt->width > size) {
      char pad_char = (opt->zero && !opt->precision_specified) ? '0' : ' ';
      add_padding(&ptr, pad_char, opt->width - size);
    }
    if (opt->hash && number != 0) {
      add_padding(&ptr, '0', 1);
    }
    if (opt->precision > len) {
      add_padding(&ptr, '0', opt->precision - len);
    }
    if (!(opt->precision_specified && opt->precision == 0 && number == 0)) {
      put_oct(&ptr, number);
    }
  } else {
    if (opt->hash && number != 0) {
      add_padding(&ptr, '0', 1);
    }
    if (opt->precision > len) {
      add_padding(&ptr, '0', opt->precision - len);
    }
    if (!(opt->precision_specified && opt->precision == 0 && number == 0)) {
      put_oct(&ptr, number);
    }
    if (opt->width > size) {
      add_padding(&ptr, ' ', opt->width - size);
    }
  }
  *str = ptr;
}

void format_p(char** str, va_list* args, options* opt) {
  char* ptr = *str;
  unsigned long long address = (unsigned long long)va_arg(*args, void*);
  int len = count_hex_digits(address) + 2;
  if (!opt->minus) {
    if (opt->width > len) {
      add_padding(&ptr, ' ', opt->width - len);
    }
    add_padding(&ptr, '0', 1);
    add_padding(&ptr, 'x', 1);
    put_hex(&ptr, address, 0);
  } else {
    add_padding(&ptr, '0', 1);
    add_padding(&ptr, 'x', 1);
    put_hex(&ptr, address, 0);
    if (opt->width > len) {
      add_padding(&ptr, ' ', opt->width - len);
    }
  }
  *str = ptr;
}

void format_percent(char** str) {
  char* ptr = *str;
  add_padding(&ptr, '%', 1);
  *str = ptr;
}

void put_number(char** str, long long num) {
  if (num >= 10) {
    put_number(str, num / 10);
  }
  **str = '0' + (num % 10);
  (*str)++;
}

void put_unsigned(char** str, unsigned long long num) {
  if (num >= 10) {
    put_unsigned(str, num / 10);
  }
  **str = '0' + (num % 10);
  (*str)++;
}

void put_hex(char** str, unsigned long long number, int uppercase) {
  char buffer[32];
  int i = 0;
  char* digits;
  if (uppercase) {
    digits = "0123456789ABCDEF";
  } else {
    digits = "0123456789abcdef";
  }
  if (number == 0) {
    **str = '0';
    (*str)++;
    return;
  }
  while (number > 0) {
    buffer[i++] = digits[number % 16];
    number /= 16;
  }
  while (i > 0) {
    **str = buffer[--i];
    (*str)++;
  }
}

void put_oct(char** str, unsigned long long number) {
  char buffer[32];
  int i = 0;
  if (number == 0) {
    **str = '0';
    (*str)++;
    return;
  }
  while (number > 0) {
    buffer[i++] = '0' + (number % 8);
    number /= 8;
  }
  while (i > 0) {
    **str = buffer[--i];
    (*str)++;
  }
}

void add_padding(char** str, char pad_char, int count) {
  for (int i = 0; i < count; ++i) {
    **str = pad_char;
    (*str)++;
  }
}

int count_figures(long long number) {
  int count = 1;
  unsigned long long abs_num;
  if (number < 0) {
    abs_num = -(unsigned long long)number;
  } else {
    abs_num = (unsigned long long)number;
  }
  while (abs_num >= 10) {
    abs_num /= 10;
    count++;
  }
  return count;
}

int count_figures_unsigned(unsigned long long number) {
  int count = 1;
  while (number >= 10) {
    number /= 10;
    count++;
  }
  return count;
}

int count_hex_digits(unsigned long long number) {
  int count = 0;
  if (number == 0) {
    count++;
  }
  while (number > 0) {
    count++;
    number /= 16;
  }
  return count;
}

int count_oct_digits(unsigned long long number) {
  int count = 0;
  if (number == 0) {
    count++;
  }
  while (number > 0) {
    count++;
    number /= 8;
  }
  return count;
}