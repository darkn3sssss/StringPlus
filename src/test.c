#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

#define BUFFER_SIZE 1024

START_TEST(test_s21_memchr) {
  char str[] = "Hello, World!";
  ck_assert_ptr_eq(s21_memchr(str, 'H', 0), memchr(str, 'H', 0));
  ck_assert_ptr_eq(s21_memchr(str, 'H', 3), memchr(str, 'H', 3));
  ck_assert_ptr_eq(s21_memchr(str, 'W', 12), memchr(str, 'W', 12));
  ck_assert_ptr_eq(s21_memchr(str, '\0', 13), memchr(str, '\0', 13));
}
END_TEST

START_TEST(test_s21_memcmp) {
  char str1[] = "World";
  char str2[] = "World";
  char str3[] = "Worl!";
  ck_assert_int_eq(s21_memcmp(str1, str2, 5), memcmp(str1, str2, 5));
  ck_assert_int_eq(s21_memcmp(str1, str3, 4), memcmp(str1, str3, 4));

  int s21_res = s21_memcmp(str1, str3, 5);
  int std_res = memcmp(str1, str3, 5);
  ck_assert((s21_res < 0 && std_res < 0) || (s21_res > 0 && std_res > 0));
}
END_TEST

START_TEST(test_s21_memcpy) {
  char src[] = "Hello, World!";
  char dest_s21[30] = {0};
  char dest_std[30] = {0};

  s21_memcpy(dest_s21, src, 0);
  memcpy(dest_std, src, 0);
  ck_assert_mem_eq(dest_s21, dest_std, 30);

  s21_memcpy(dest_s21, src, 6);
  memcpy(dest_std, src, 6);
  ck_assert_str_eq(dest_s21, dest_std);

  s21_memcpy(dest_s21, src, 13);
  memcpy(dest_std, src, 13);
  ck_assert_str_eq(dest_s21, dest_std);
}
END_TEST

START_TEST(test_s21_memset) {
  char str_s21[50] = "Hello, World!";
  char str_std[50] = "Hello, World!";

  s21_memset(str_s21, 'a', 5);
  memset(str_std, 'a', 5);
  ck_assert_str_eq(str_s21, str_std);
}
END_TEST

START_TEST(test_s21_strncat) {
  char src[] = " World!";
  char dest_s21[50] = "Hello,";
  char dest_std[50] = "Hello,";

  s21_strncat(dest_s21, src, 0);
  strncat(dest_std, src, 0);
  ck_assert_str_eq(dest_s21, dest_std);

  s21_strncat(dest_s21, src, 3);
  strncat(dest_std, src, 3);
  ck_assert_str_eq(dest_s21, dest_std);

  strcpy(dest_s21, "Hello,");
  strcpy(dest_std, "Hello,");
  s21_strncat(dest_s21, src, 7);
  strncat(dest_std, src, 7);
  ck_assert_str_eq(dest_s21, dest_std);
}
END_TEST

START_TEST(test_s21_strchr) {
  char str[] = "Hello, World!";

  ck_assert_ptr_eq(s21_strchr(str, 'z'), strchr(str, 'z'));
  ck_assert_ptr_eq(s21_strchr(str, 'H'), strchr(str, 'H'));
  ck_assert_ptr_eq(s21_strchr(str, ','), strchr(str, ','));
  ck_assert_ptr_eq(s21_strchr(str, '\0'), strchr(str, '\0'));
}
END_TEST

START_TEST(test_s21_strncmp) {
  char str1[] = "World";
  char str2[] = "World";
  char str3[] = "Worl!";
  char str4[] = "World!";

  ck_assert_int_eq(s21_strncmp(str1, str2, 5), strncmp(str1, str2, 5));
  ck_assert_int_eq(s21_strncmp(str1, str3, 4), strncmp(str1, str3, 4));
  ck_assert_int_eq(s21_strncmp(str1, str4, 3), strncmp(str1, str4, 3));

  int s21_res = s21_strncmp(str1, str3, 5);
  int std_res = strncmp(str1, str3, 5);
  ck_assert((s21_res < 0 && std_res < 0) || (s21_res > 0 && std_res > 0));
}
END_TEST

START_TEST(test_s21_strncpy) {
  char src[] = "Hello, World!";
  char dest_s21[30] = "xxxxx";
  char dest_std[30] = "xxxxx";

  s21_strncpy(dest_s21, src, 13);
  strncpy(dest_std, src, 13);
  ck_assert_str_eq(dest_s21, dest_std);
}
END_TEST

START_TEST(test_s21_strcspn) {
  char str1[] = "Hello, World!";
  char str2[] = ",!";

  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
  ck_assert_int_eq(s21_strcspn("abcde", "xyz"), strcspn("abcde", "xyz"));
  ck_assert_int_eq(s21_strcspn("", "abc"), strcspn("", "abc"));
}
END_TEST

START_TEST(test_s21_strerror) {
  ck_assert_str_eq(s21_strerror(0), strerror(0));
  ck_assert_str_eq(s21_strerror(1), strerror(1));
  ck_assert_str_eq(s21_strerror(5), strerror(5));

  char* s21_res = s21_strerror(1000);
  char* std_res = strerror(1000);
  ck_assert(strstr(s21_res, "Unknown error") != NULL);
  ck_assert(strstr(std_res, "Unknown error") != NULL);
}
END_TEST

START_TEST(test_s21_strlen) {
  ck_assert_int_eq(s21_strlen(""), strlen(""));
  ck_assert_int_eq(s21_strlen("Hello, World!"), strlen("Hello, World!"));
  ck_assert_int_eq(s21_strlen("a"), strlen("a"));
  ck_assert_int_eq(s21_strlen(NULL), 0);
}
END_TEST

START_TEST(test_s21_strpbrk) {
  char str1[] = "Hello, World!";
  char str2[] = ",W!";

  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
  ck_assert_ptr_eq(s21_strpbrk(str1, "xyz"), strpbrk(str1, "xyz"));
  ck_assert_ptr_eq(s21_strpbrk("", str2), strpbrk("", str2));
}
END_TEST

START_TEST(test_s21_strrchr) {
  char str[] = "Hello, World!";
  ck_assert_ptr_eq(s21_strrchr(str, ','), strrchr(str, ','));
  ck_assert_ptr_eq(s21_strrchr(str, '8'), strrchr(str, '8'));
  ck_assert_ptr_eq(s21_strrchr(str, 'l'), strrchr(str, 'l'));
}
END_TEST

START_TEST(test_s21_strstr) {
  char haystack[] = "Hello, World!";
  ck_assert_ptr_eq(s21_strstr(haystack, "lo, Wo"), strstr(haystack, "lo, Wo"));
  ck_assert_ptr_eq(s21_strstr(haystack, "9"), strstr(haystack, "9"));
  ck_assert_ptr_eq(s21_strstr(haystack, ""), strstr(haystack, ""));
  ck_assert_ptr_eq(s21_strstr(haystack, "Hello"), strstr(haystack, "Hello"));
}
END_TEST

START_TEST(test_s21_strtok) {
  char str_s21[] = "Hello, World!";
  char str_std[] = "Hello, World!";
  char* delim = " ,!";

  char* token_s21 = s21_strtok(str_s21, delim);
  char* token_std = strtok(str_std, delim);
  ck_assert_str_eq(token_s21, token_std);

  token_s21 = s21_strtok(NULL, delim);
  token_std = strtok(NULL, delim);
  ck_assert_str_eq(token_s21, token_std);
}
END_TEST

START_TEST(test_s21_to_upper) {
  char* ptr1 = s21_to_upper("world");
  ck_assert_str_eq(ptr1, "WORLD");
  free(ptr1);

  char* ptr2 = s21_to_upper("HELLO");
  ck_assert_str_eq(ptr2, "HELLO");
  free(ptr2);

  char* ptr3 = s21_to_upper("1a2b3c4d");
  ck_assert_str_eq(ptr3, "1A2B3C4D");
  free(ptr3);

  char* ptr5 = s21_to_upper(NULL);
  ck_assert_ptr_eq(ptr5, NULL);
}
END_TEST

START_TEST(test_s21_to_lower) {
  char* ptr1 = s21_to_lower("WORLD");
  ck_assert_str_eq(ptr1, "world");
  free(ptr1);

  char* ptr2 = s21_to_lower("hello");
  ck_assert_str_eq(ptr2, "hello");
  free(ptr2);

  char* ptr3 = s21_to_lower("1A2B3C4D");
  ck_assert_str_eq(ptr3, "1a2b3c4d");
  free(ptr3);

  char* ptr5 = s21_to_lower(NULL);
  ck_assert_ptr_eq(ptr5, NULL);
}
END_TEST

START_TEST(test_s21_insert) {
  char* ptr1 = s21_insert("Hello,", " World!", 6);
  ck_assert_str_eq(ptr1, "Hello, World!");
  free(ptr1);

  char* ptr2 = s21_insert("Hello,", " World!", 0);
  ck_assert_str_eq(ptr2, " World!Hello,");
  free(ptr2);

  char* ptr3 = s21_insert("", "Hello", 0);
  ck_assert_str_eq(ptr3, "Hello");
  free(ptr3);

  char* ptr4 = s21_insert("Hello", NULL, 2);
  ck_assert_str_eq(ptr4, "Hello");
  free(ptr4);

  char* ptr5 = s21_insert(NULL, "World", 0);
  ck_assert_ptr_eq(ptr5, NULL);
}
END_TEST

START_TEST(test_s21_trim) {
  char* ptr1 = s21_trim("   world  ", " ");
  ck_assert_str_eq(ptr1, "world");
  free(ptr1);

  char* ptr2 = s21_trim("333HELLO333", "3");
  ck_assert_str_eq(ptr2, "HELLO");
  free(ptr2);

  char* ptr3 = s21_trim("World", " ");
  ck_assert_str_eq(ptr3, "World");
  free(ptr3);

  char* ptr4 = s21_trim("  Hello World  ", NULL);
  ck_assert_str_eq(ptr4, "Hello World");
  free(ptr4);

  char* ptr5 = s21_trim(NULL, " ");
  ck_assert_ptr_eq(ptr5, NULL);
}
END_TEST

START_TEST(test_s21_sprintf_c) {
  char s21_buf[BUFFER_SIZE] = {0};
  char std_buf[BUFFER_SIZE] = {0};

  int res1 = s21_sprintf(s21_buf, "%c", 'A');
  int res2 = sprintf(std_buf, "%c", 'A');
  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_d) {
  char s21_buf[BUFFER_SIZE] = {0};
  char std_buf[BUFFER_SIZE] = {0};

  int res1 = s21_sprintf(s21_buf, "%d", -12345);
  int res2 = sprintf(std_buf, "%d", -12345);
  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(res1, res2);
  res1 = s21_sprintf(s21_buf, "%+d", 12345);
  res2 = sprintf(std_buf, "%+d", 12345);
  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(res1, res2);
  res1 = s21_sprintf(s21_buf, "% d", 2147483647);
  res2 = sprintf(std_buf, "% d", 2147483647);
  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(res1, res2);
  res1 = s21_sprintf(s21_buf, "%*d", 4, 12);
  res2 = sprintf(std_buf, "%*d", 4, 12);
  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_f) {
  char s21_buf[BUFFER_SIZE] = {0};
  char std_buf[BUFFER_SIZE] = {0};

  double nums[] = {123.456, -123.456, 0.000001, 1000000.0};

  for (int i = 0; i < 7; i++) {
    int res1 = s21_sprintf(s21_buf, "%f", nums[i]);
    int res2 = sprintf(std_buf, "%f", nums[i]);
    ck_assert_str_eq(s21_buf, std_buf);
    ck_assert_int_eq(res1, res2);

    res1 = s21_sprintf(s21_buf, "%+f", nums[i]);
    res2 = sprintf(std_buf, "%+f", nums[i]);
    ck_assert_str_eq(s21_buf, std_buf);
    ck_assert_int_eq(res1, res2);

    res1 = s21_sprintf(s21_buf, "% f", nums[i]);
    res2 = sprintf(std_buf, "% f", nums[i]);
    ck_assert_str_eq(s21_buf, std_buf);
    ck_assert_int_eq(res1, res2);
  }
}
END_TEST

START_TEST(test_s21_sprintf_u) {
  char s21_buf[BUFFER_SIZE] = {0};
  char std_buf[BUFFER_SIZE] = {0};

  unsigned int nums[] = {0, 123, 4294967295U, 42};

  for (int i = 0; i < 4; i++) {
    int res1 = s21_sprintf(s21_buf, "%u", nums[i]);
    int res2 = sprintf(std_buf, "%u", nums[i]);
    ck_assert_str_eq(s21_buf, std_buf);
    ck_assert_int_eq(res1, res2);

    res1 = s21_sprintf(s21_buf, "%10u", nums[i]);
    res2 = sprintf(std_buf, "%10u", nums[i]);
    ck_assert_str_eq(s21_buf, std_buf);
    ck_assert_int_eq(res1, res2);

    res1 = s21_sprintf(s21_buf, "%-10u", nums[i]);
    res2 = sprintf(std_buf, "%-10u", nums[i]);
    ck_assert_str_eq(s21_buf, std_buf);
    ck_assert_int_eq(res1, res2);
  }
}
END_TEST

START_TEST(test_s21_sprintf_s) {
  char s21_buf[BUFFER_SIZE] = {0};
  char std_buf[BUFFER_SIZE] = {0};

  int res1 = s21_sprintf(s21_buf, "%s", "Hello");
  int res2 = sprintf(std_buf, "%s", "Hello");
  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(res1, res2);
  res1 = s21_sprintf(s21_buf, "%10s", "World!");
  res2 = sprintf(std_buf, "%10s", "World!");
  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(res1, res2);
  res1 = s21_sprintf(s21_buf, "%-10s", "World");
  res2 = sprintf(std_buf, "%-10s", "World");
  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(res1, res2);
  res1 = s21_sprintf(s21_buf, "%.5s", "erfrfrfr");
  res2 = sprintf(std_buf, "%.5s", "erfrfrfr");
  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_x) {
  char s21_buf[BUFFER_SIZE] = {0};
  char std_buf[BUFFER_SIZE] = {0};

  int res1 = s21_sprintf(s21_buf, "%x", 255);
  int res2 = sprintf(std_buf, "%x", 255);
  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(res1, res2);
  res1 = s21_sprintf(s21_buf, "%X", 12345);
  res2 = sprintf(std_buf, "%X", 12345);
  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(res1, res2);
  res1 = s21_sprintf(s21_buf, "%#x", 12567);
  res2 = sprintf(std_buf, "%#x", 12567);
  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(res1, res2);
  res1 = s21_sprintf(s21_buf, "%10x", 255);
  res2 = sprintf(std_buf, "%10x", 255);
  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_o) {
  char s21_buf[BUFFER_SIZE] = {0};
  char std_buf[BUFFER_SIZE] = {0};

  int res1 = s21_sprintf(s21_buf, "%o", 64);
  int res2 = sprintf(std_buf, "%o", 64);
  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(res1, res2);
  res1 = s21_sprintf(s21_buf, "%#o", 123456);
  res2 = sprintf(std_buf, "%#o", 123456);
  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_p) {
  char s21_buf[BUFFER_SIZE] = {0};
  char std_buf[BUFFER_SIZE] = {0};

  int x = 42;
  void* ptr = &x;

  int res1 = s21_sprintf(s21_buf, "%p", ptr);
  int res2 = sprintf(std_buf, "%p", ptr);
  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(res1, res2);

  res1 = s21_sprintf(s21_buf, "%20p", ptr);
  res2 = sprintf(std_buf, "%20p", ptr);
  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_percent) {
  char s21_buf[BUFFER_SIZE] = {0};
  char std_buf[BUFFER_SIZE] = {0};

  int res1 = s21_sprintf(s21_buf, "%%");
  int res2 = sprintf(std_buf, "%%");
  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_width_and_precision) {
  char s21_buf[BUFFER_SIZE] = {0};
  char std_buf[BUFFER_SIZE] = {0};

  int num = 123;

  int res1 = s21_sprintf(s21_buf, "%10d", num);
  int res2 = sprintf(std_buf, "%10d", num);
  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(res1, res2);

  res1 = s21_sprintf(s21_buf, "%.5d", num);
  res2 = sprintf(std_buf, "%.5d", num);
  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(res1, res2);

  res1 = s21_sprintf(s21_buf, "%*.*d", 10, 5, num);
  res2 = sprintf(std_buf, "%*.*d", 10, 5, num);
  ck_assert_str_eq(s21_buf, std_buf);
  ck_assert_int_eq(res1, res2);
}
END_TEST

Suite* create_test() {
  Suite* s = suite_create("s21_string");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_memchr);
  tcase_add_test(tc_core, test_s21_memcmp);
  tcase_add_test(tc_core, test_s21_memcpy);
  tcase_add_test(tc_core, test_s21_memset);
  tcase_add_test(tc_core, test_s21_strncat);
  tcase_add_test(tc_core, test_s21_strchr);
  tcase_add_test(tc_core, test_s21_strncmp);
  tcase_add_test(tc_core, test_s21_strncpy);
  tcase_add_test(tc_core, test_s21_strcspn);
  tcase_add_test(tc_core, test_s21_strerror);
  tcase_add_test(tc_core, test_s21_strlen);
  tcase_add_test(tc_core, test_s21_strpbrk);
  tcase_add_test(tc_core, test_s21_strrchr);
  tcase_add_test(tc_core, test_s21_strstr);
  tcase_add_test(tc_core, test_s21_strtok);

  tcase_add_test(tc_core, test_s21_to_upper);
  tcase_add_test(tc_core, test_s21_to_lower);
  tcase_add_test(tc_core, test_s21_insert);
  tcase_add_test(tc_core, test_s21_trim);

  tcase_add_test(tc_core, test_s21_sprintf_c);
  tcase_add_test(tc_core, test_s21_sprintf_d);
  tcase_add_test(tc_core, test_s21_sprintf_f);
  tcase_add_test(tc_core, test_s21_sprintf_u);
  tcase_add_test(tc_core, test_s21_sprintf_s);
  tcase_add_test(tc_core, test_s21_sprintf_x);
  tcase_add_test(tc_core, test_s21_sprintf_o);
  tcase_add_test(tc_core, test_s21_sprintf_p);
  tcase_add_test(tc_core, test_s21_sprintf_percent);
  tcase_add_test(tc_core, test_s21_sprintf_width_and_precision);

  suite_add_tcase(s, tc_core);
  return s;
}

int main(void) {
  Suite* s = create_test();
  SRunner* sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  srunner_set_log(sr, "report.log");
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : 1;
}