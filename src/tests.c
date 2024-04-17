#include <check.h>
#include <stdlib.h>
#include <time.h>

#include "s21_decimal.h"

START_TEST(is_equal_0) {
  s21_decimal val1 = {0, 0, 0, 0};
  s21_decimal val2 = {0, 0, 0, 0};
  s21_set_sign(&val2, 1);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_n_eq_0) {
  s21_decimal val1 = {0, 0, 0, 0};
  s21_decimal val2 = {0, 0, 0, 0};
  s21_set_sign(&val2, 1);
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_1) {
  s21_decimal val1 = {0, 0, 0, 0};
  s21_decimal val2 = {0, 0, 0, 0};
  s21_set_bit_one(&val2, 33);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_2) {
  s21_decimal val1 = {0, 0, 0, 0};
  s21_decimal val2 = {0, 0, 0, 0};
  s21_set_bit_one(&val1, 33);
  s21_set_bit_one(&val2, 33);
  s21_set_bit_one(&val2, 127);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_3) {
  s21_decimal val1 = {0, 0, 0, 0};
  s21_decimal val2 = {0, 0, 0, 0};
  s21_set_bit_one(&val1, 1);
  s21_set_bit_one(&val2, 1);
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_4) {
  s21_decimal val1 = {0, 0, 0, 0};
  s21_decimal val2 = {0, 0, 0, 0};
  s21_set_bit_one(&val1, 3);
  s21_set_bit_one(&val2, 4);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_5) {
  s21_decimal val1 = {0, 0, 0, 0};
  s21_decimal val2 = {0, 0, 0, 0};
  s21_set_scale(&val1, 3);
  s21_set_scale(&val2, 3);
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_6) {
  s21_decimal val1 = {0, 0, 0, 0};
  s21_decimal val2 = {0, 0, 0, 0};
  s21_set_bit_one(&val1, 3);
  s21_set_bit_one(&val2, 4);
  s21_set_scale(&val1, 3);
  s21_set_scale(&val2, 3);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_7) {
  s21_decimal val1 = {0, 0, 0, 0};
  s21_decimal val2 = {0, 0, 0, 0};
  s21_set_scale(&val1, 3);
  s21_set_scale(&val2, 2);
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_8) {
  float a = rand() % (1000000) - 500000;
  float b = rand() % (1000000) - 500000;

  s21_decimal a1 = {0, 0, 0, 0};
  s21_decimal b1 = {0, 0, 0, 0};
  s21_from_float_to_decimal(a, &a1);
  s21_from_float_to_decimal(b, &b1);
  ck_assert_int_eq(s21_is_equal(a1, b1), a == b);
}
END_TEST

START_TEST(is_greater_or_equal_0) {
  s21_decimal val1 = {0, 0, 0, 0};
  s21_decimal val2 = {0, 0, 0, 0};
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_1) {
  s21_decimal val1 = {1, 0, 0, 0};
  s21_decimal val2 = {2, 0, 0, 0};
  ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_2) {
  s21_decimal val1 = {256, 0, 0, 0};
  s21_decimal val2 = {256, 0, 0, 0};
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_3) {
  s21_decimal val1 = {0xFFFFFFFF, 0, 0, 0};
  s21_decimal val2 = {0xFFFFFFFF - 1, 0, 0, 0};
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_4) {
  s21_decimal val1 = {0, 0, 1, 0};
  s21_decimal val2 = {0, 0, 0, 0};
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_5) {
  s21_decimal val1 = {1, 0, 0, 0};
  s21_decimal val2 = {1, 1, 0, 0};
  ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_6) {
  s21_decimal val1 = {257, 256, 0, 0};
  s21_decimal val2 = {257, 257, 0, 0};
  s21_set_scale(&val1, 10);
  s21_set_scale(&val2, 11);
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_7) {
  s21_decimal val1 = {0, 0, 0, 0};
  s21_decimal val2 = {0, 0, 0, 0};
  val2.bits[2] = 257;
  s21_set_bit_one(&val1, 127);
  s21_set_bit_one(&val2, 127);
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST
START_TEST(is_greater_or_equal_8) {
  float a, b;
  s21_decimal a1 = {0, 0, 0, 0};
  s21_decimal b1 = {0, 0, 0, 0};
  for (int i = 0; i < 10000; i++) {
    a = rand() % (1000000) - 500000;
    b = rand() % (1000000) - 500000;
    s21_from_float_to_decimal(a, &a1);
    s21_from_float_to_decimal(b, &b1);
    ck_assert_int_eq(s21_is_greater_or_equal(a1, b1), a >= b);
  }
}
END_TEST

START_TEST(is_greater_or_equal_9) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(is_greater_or_equal_10) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_set_sign(&value_1, 1);
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(is_greater_or_equal_11) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_set_sign(&value_2, 1);
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(is_greater_or_equal_12) {
  s21_decimal value_1 = {0, 0, 0, 0};
  s21_decimal value_2 = {0, 0, 0, 0};
  s21_set_sign(&value_2, 1);
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(is_greater_or_equal_13) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_set_sign(&value_1, 1);
  s21_set_sign(&value_2, 1);
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(is_greater_or_equal_14) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(is_greater_or_equal_15) {
  s21_decimal value_1 = {{12345, 0, 0, 0}};
  s21_set_scale(&value_1, 4);
  s21_decimal value_2 = {{12u, 0, 0, 0}};
  s21_set_scale(&value_1, 1);
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(is_greater_0) {
  s21_decimal val1 = {0, 0, 0, 0};
  s21_decimal val2 = {0, 0, 0, 0};
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_1) {
  s21_decimal val1 = {0, 0, 0, 0};
  s21_decimal val2 = {1, 0, 0, 0};
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_2) {
  s21_decimal val1 = {1, 0, 0, 0};
  s21_decimal val2 = {1, 0, 0, 0};
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_3) {
  s21_decimal val1 = {1, 0, 0, 0};
  s21_decimal val2 = {0, 0, 0, 0};
  ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_4) {
  s21_decimal val1 = {0, 0, 0, 0};
  s21_decimal val2 = {0, 0, 0, 0};
  s21_set_sign(&val1, 1);
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_5) {
  s21_decimal val1 = {257, 0, 256, 0};
  s21_decimal val2 = {257, 0, 257, 0};
  s21_set_scale(&val1, 11);
  s21_set_scale(&val2, 10);
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_6) {
  s21_decimal val1 = {257, 0, 256, 0};
  s21_decimal val2 = {257, 0, 257, 0};
  s21_set_scale(&val1, 10);
  s21_set_scale(&val2, 11);
  ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_7) {
  s21_decimal val1 = {0, 0, 0, 0};
  s21_decimal val2 = {0, 0, 257, 0};
  s21_set_sign(&val1, 1);
  s21_set_sign(&val2, 1);
  ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_8) {
  s21_decimal val1 = {0, 0, 0, 0};
  s21_decimal val2 = {0, 0, 257, 0};
  s21_set_sign(&val1, 1);
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_9) {
  float a;
  float b;
  s21_decimal a1 = {0, 0, 0, 0};
  s21_decimal b1 = {0, 0, 0, 0};
  for (int i = 0; i < 10000; i++) {
    a = rand() % (1000000) - 500000;
    b = rand() % (1000000) - 500000;
    s21_from_float_to_decimal(a, &a1);
    s21_from_float_to_decimal(b, &b1);
    ck_assert_int_eq(s21_is_greater(a1, b1), a > b);
  }
}
END_TEST

START_TEST(is_greater_10) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  ck_assert_int_eq(s21_is_greater(value_1, value_2), 1);
}
END_TEST

START_TEST(is_greater_11) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_set_sign(&value_1, 1);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), 0);
}
END_TEST

START_TEST(is_greater_12) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_set_sign(&value_2, 1);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), 1);
}
END_TEST

START_TEST(is_greater_13) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_set_sign(&value_1, 1);
  s21_set_sign(&value_2, 1);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), 1);
}
END_TEST

START_TEST(is_greater_14) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_set_scale(&value_2, 10);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), 1);
}
END_TEST

START_TEST(is_greater_15) {
  s21_decimal value_1 = {{234, 0, 0, 0}};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_set_scale(&value_1, 2);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), 1);
}
END_TEST

START_TEST(is_less_or_equal_0) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_1) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  val1.bits[0] = 255;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_2) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  val1.bits[0] = 256;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_3) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  val1.bits[0] = 257;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_4) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  s21_set_sign(&val1, 1);
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_5) {
  s21_decimal val1 = {101, 0, 100, 0};
  s21_decimal val2 = {101, 0, 101, 0};
  s21_set_scale(&val1, 11);
  s21_set_scale(&val2, 10);
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_6) {
  s21_decimal val1 = {100, 0, 100, 0};
  s21_decimal val2 = {100, 0, 101, 0};
  s21_set_scale(&val1, 10);
  s21_set_scale(&val2, 11);
  ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_7) {
  s21_decimal val1 = {0, 0, 0, 0};
  s21_decimal val2 = {0, 0, 101, 0};
  s21_set_sign(&val1, 1);
  s21_set_sign(&val2, 1);
  ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_8) {
  float a;
  float b;
  s21_decimal a1 = {0, 0, 0, 0};
  s21_decimal b1 = {0, 0, 0, 0};
  for (int i = 0; i < 10000; i++) {
    a = rand() % (1000000) - 500000;
    b = rand() % (1000000) - 500000;
    s21_from_float_to_decimal(a, &a1);
    s21_from_float_to_decimal(b, &b1);
    ck_assert_int_eq(s21_is_less_or_equal(a1, b1), a <= b);
  }
}
END_TEST

START_TEST(is_less_or_equal_9) {
  float a = -243.3567778;
  float b = -123.8976811123;

  s21_decimal a1 = {{0}};
  s21_decimal b1 = {{0}};
  s21_from_float_to_decimal(a, &a1);
  s21_from_float_to_decimal(b, &b1);
  ck_assert_int_eq(s21_is_less_or_equal(a1, b1), a <= b);
}
END_TEST

START_TEST(is_less_or_equal_10) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(is_less_or_equal_11) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_set_sign(&value_1, 1);
  ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), 1);
}
END_TEST

START_TEST(is_less_or_equal_12) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_set_sign(&value_2, 1);
  ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(is_less_or_equal_13) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_set_sign(&value_1, 1);
  s21_set_sign(&value_2, 1);
  ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(is_less_or_equal_14) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_set_scale(&value_2, 2);
  ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(is_less_or_equal_15) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), 1);
}
END_TEST

START_TEST(is_less_1) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_2) {
  s21_decimal val1 = {0, 0, 0, 0};
  s21_decimal val2 = {1, 0, 0, 0};
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_3) {
  s21_decimal val1 = {1, 0, 0, 0};
  s21_decimal val2 = {1, 0, 0, 0};
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_4) {
  s21_decimal val1 = {1, 0, 0, 0};
  s21_decimal val2 = {0, 0, 0, 0};
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_5) {
  s21_decimal val1 = {1, 0, 1, 0};
  s21_decimal val2 = {1, 0, 2, 0};
  s21_set_scale(&val1, 10);
  s21_set_scale(&val2, 9);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_6) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_set_scale(&val1, 10);
  s21_set_scale(&val2, 11);
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_7) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  val2.bits[2] = 257;
  s21_set_scale(&val1, 127);
  s21_set_scale(&val2, 127);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_8) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  s21_set_bit_one(&val1, 127);
  s21_set_bit_one(&val2, 127);
  s21_set_bit_one(&val1, 83);
  s21_set_scale(&val1, 12);
  s21_set_scale(&val2, 11);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_9) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  s21_set_bit_one(&val1, 127);
  s21_set_bit_one(&val2, 127);
  s21_set_bit_one(&val1, 83);
  s21_set_bit_one(&val2, 83);
  s21_set_scale(&val1, 10);
  s21_set_scale(&val2, 11);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_10) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  s21_set_bit_one(&val1, 127);
  s21_set_bit_one(&val2, 127);
  s21_set_bit_one(&val1, 83);
  s21_set_scale(&val1, 10);
  s21_set_scale(&val2, 10);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_11) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  s21_set_bit_one(&val1, 127);
  s21_set_bit_zero(&val2, 127);
  s21_set_bit_one(&val1, 83);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_12) {
  float a;
  float b;
  s21_decimal a1 = {0, 0, 0, 0};
  s21_decimal b1 = {0, 0, 0, 0};
  for (int i = 0; i < 10000; i++) {
    a = rand() % (1000000) - 500000;
    b = rand() % (1000000) - 500000;
    s21_from_float_to_decimal(a, &a1);
    s21_from_float_to_decimal(b, &b1);
    ck_assert_int_eq(s21_is_less_or_equal(a1, b1), a < b);
  }
}
END_TEST

START_TEST(is_less_13) {
  float a = -132.674244678;
  float b = -476.234435;

  s21_decimal a1 = {{0}};
  s21_decimal b1 = {{0}};
  s21_from_float_to_decimal(a, &a1);
  s21_from_float_to_decimal(b, &b1);
  ck_assert_int_eq(s21_is_less(a1, b1), a < b);
}
END_TEST

START_TEST(is_less_14) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
}
END_TEST

START_TEST(is_less_15) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_set_sign(&value_1, 1);
  ck_assert_int_eq(s21_is_less(value_1, value_2), 1);
}
END_TEST

START_TEST(is_less_16) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_set_sign(&value_2, 1);
  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
}
END_TEST

START_TEST(is_less_17) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_set_sign(&value_1, 1);
  s21_set_sign(&value_2, 1);
  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
}
END_TEST

START_TEST(is_less_18) {
  float num1 = 0.123;
  float num2 = 0.132456;
  s21_decimal dec1 = {0}, dec2 = {0};
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  ck_assert_int_eq(s21_is_less(dec1, dec2), 1);
}
END_TEST

START_TEST(is_less_19) {
  float num1 = 1.45;
  float num2 = 1.45;
  s21_decimal dec1 = {0}, dec2 = {0};
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  ck_assert_int_eq(s21_is_less(dec1, dec2), 0);
}
END_TEST

START_TEST(is_less_20) {
  float num1 = 1.567;
  float num2 = -1.567;
  s21_decimal dec1 = {0}, dec2 = {0};
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  ck_assert_int_eq(s21_is_less(dec1, dec2), 0);
}
END_TEST

START_TEST(is_less_21) {
  int num1 = -3;
  int num2 = -3;
  s21_decimal dec1 = {0}, dec2 = {0};
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  ck_assert_int_eq(s21_is_less(dec1, dec2), 0);
}
END_TEST

START_TEST(is_less_22) {
  float num1 = -34534534.232446543232446543;
  float num2 = -3.232323233232323233;
  s21_decimal dec1 = {0}, dec2 = {0};
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  ck_assert_int_eq(s21_is_less(dec1, dec2), 1);
}
END_TEST

Suite *test_comparisons(void) {
  Suite *suite = suite_create("comparisons");
  TCase *tcase = tcase_create("comparisons");
  tcase_add_test(tcase, is_equal_1);
  tcase_add_test(tcase, is_n_eq_0);
  tcase_add_test(tcase, is_equal_2);
  tcase_add_test(tcase, is_equal_3);
  tcase_add_test(tcase, is_equal_4);
  tcase_add_test(tcase, is_equal_5);
  tcase_add_test(tcase, is_equal_6);
  tcase_add_test(tcase, is_equal_7);
  tcase_add_test(tcase, is_equal_8);
  tcase_add_test(tcase, is_greater_or_equal_0);
  tcase_add_test(tcase, is_greater_or_equal_1);
  tcase_add_test(tcase, is_greater_or_equal_2);
  tcase_add_test(tcase, is_greater_or_equal_3);
  tcase_add_test(tcase, is_greater_or_equal_4);
  tcase_add_test(tcase, is_greater_or_equal_5);
  tcase_add_test(tcase, is_greater_or_equal_6);
  tcase_add_test(tcase, is_greater_or_equal_7);
  tcase_add_test(tcase, is_greater_or_equal_8);
  tcase_add_test(tcase, is_greater_or_equal_9);
  tcase_add_test(tcase, is_greater_or_equal_10);
  tcase_add_test(tcase, is_greater_or_equal_11);
  tcase_add_test(tcase, is_greater_or_equal_12);
  tcase_add_test(tcase, is_greater_or_equal_13);
  tcase_add_test(tcase, is_greater_or_equal_14);
  tcase_add_test(tcase, is_greater_or_equal_15);
  tcase_add_test(tcase, is_greater_1);
  tcase_add_test(tcase, is_greater_2);
  tcase_add_test(tcase, is_greater_3);
  tcase_add_test(tcase, is_greater_4);
  tcase_add_test(tcase, is_greater_5);
  tcase_add_test(tcase, is_greater_6);
  tcase_add_test(tcase, is_greater_7);
  tcase_add_test(tcase, is_greater_8);
  tcase_add_test(tcase, is_greater_9);
  tcase_add_test(tcase, is_greater_10);
  tcase_add_test(tcase, is_greater_11);
  tcase_add_test(tcase, is_greater_12);
  tcase_add_test(tcase, is_greater_13);
  tcase_add_test(tcase, is_greater_14);
  tcase_add_test(tcase, is_greater_15);
  tcase_add_test(tcase, is_less_or_equal_1);
  tcase_add_test(tcase, is_less_or_equal_2);
  tcase_add_test(tcase, is_less_or_equal_3);
  tcase_add_test(tcase, is_less_or_equal_4);
  tcase_add_test(tcase, is_less_or_equal_5);
  tcase_add_test(tcase, is_less_or_equal_6);
  tcase_add_test(tcase, is_less_or_equal_7);
  tcase_add_test(tcase, is_less_or_equal_8);
  tcase_add_test(tcase, is_less_or_equal_9);
  tcase_add_test(tcase, is_less_or_equal_10);
  tcase_add_test(tcase, is_less_or_equal_11);
  tcase_add_test(tcase, is_less_or_equal_12);
  tcase_add_test(tcase, is_less_or_equal_13);
  tcase_add_test(tcase, is_less_or_equal_14);
  tcase_add_test(tcase, is_less_or_equal_15);
  tcase_add_test(tcase, is_less_1);
  tcase_add_test(tcase, is_less_2);
  tcase_add_test(tcase, is_less_3);
  tcase_add_test(tcase, is_less_4);
  tcase_add_test(tcase, is_less_5);
  tcase_add_test(tcase, is_less_6);
  tcase_add_test(tcase, is_less_7);
  tcase_add_test(tcase, is_less_8);
  tcase_add_test(tcase, is_less_9);
  tcase_add_test(tcase, is_less_10);
  tcase_add_test(tcase, is_less_11);
  tcase_add_test(tcase, is_less_12);
  tcase_add_test(tcase, is_less_13);
  tcase_add_test(tcase, is_less_14);
  tcase_add_test(tcase, is_less_15);
  tcase_add_test(tcase, is_less_16);
  tcase_add_test(tcase, is_less_17);
  tcase_add_test(tcase, is_less_18);
  tcase_add_test(tcase, is_less_19);
  tcase_add_test(tcase, is_less_20);
  tcase_add_test(tcase, is_less_21);
  tcase_add_test(tcase, is_less_22);
  suite_add_tcase(suite, tcase);
  return suite;
}

START_TEST(add_1) {
  int num1;
  int num2;
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal dec_result;
  for (int i = 0; i < 5000; i++) {
    num1 = rand() % 100000;
    num2 = rand() % 100000 - 50000;
    s21_from_int_to_decimal(num1, &dec1);
    s21_from_int_to_decimal(num2, &dec2);
    ck_assert_int_eq(s21_add(dec1, dec2, &dec_result), 0);
    int num3;
    s21_from_decimal_to_int(dec_result, &num3);
    ck_assert_int_eq(num1 + num2, num3);
  }
}
END_TEST

START_TEST(add_2) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal dec_result;
  ck_assert_int_eq(s21_add(dec1, dec2, NULL), 1);
}
END_TEST

START_TEST(add_2_5) {
  s21_decimal dec1;
  s21_set_scale(&dec1, 30);
  s21_decimal dec2;
  s21_decimal dec_result;
  ck_assert_int_eq(s21_add(dec1, dec2, &dec_result), 1);
}
END_TEST

START_TEST(add_3) {
  s21_decimal dec1 = {{1000, 0, 0, 0}};
  s21_decimal dec2 = {{500, 0, 0, 0}};
  s21_set_sign(&dec1, 1);
  s21_decimal check = {{500, 0, 0, 0}};
  s21_decimal dec_result = {{0, 0, 0, 0}};
  s21_set_sign(&check, 1);

  ck_assert_int_eq(s21_add(dec1, dec2, &dec_result), 0);
  ck_assert_int_eq(s21_is_equal(dec_result, check), 1);
}
END_TEST

START_TEST(div_1) {
  s21_decimal val1 = {{10, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_decimal check = {{5, 0, 0, 0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
  ck_assert_int_eq(s21_is_equal(res, check), 1);
}
END_TEST

START_TEST(div_2) {
  s21_decimal val1 = {{2, 0, 0, MAX_INT}};
  s21_decimal val2 = {{2, 0, 0, MAX_INT}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(1, s21_div(val1, val2, NULL));
}
END_TEST

START_TEST(div_3) {
  s21_decimal val1 = {{2, 0, 0, MAX_INT}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(3, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_4) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(3, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_5) {
  s21_decimal value_1 = {{35, 0, 0, 0}};
  s21_decimal value_2 = {{5, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{70, 0, 0, 0}};
  s21_set_scale(&value_1, 1);
  s21_set_scale(&value_2, 2);
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(div_6) {
  s21_decimal value_1 = {{0x88888888, 0x88888888, 0x88888888, 0}};
  s21_decimal value_2 = {{0x2, 0, 0, 0}};
  ;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x44444444, 0x44444444, 0x44444444, 0}};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(div_7) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_set_sign(&value_1, 1);
  s21_decimal value_2 = {{8, 0, 0, 0}};
  s21_set_sign(&value_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{125, 0, 0, 0}};
  s21_set_scale(&check, 2);
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(div_8) {
  s21_decimal value_1 = {{15, 0, 0, 0}};
  s21_set_sign(&value_1, 1);
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 3);
}
END_TEST

START_TEST(div_9) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0}};
  s21_set_scale(&value_2, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{1000u, 0, 0, 0}};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(sub_0) {
  s21_decimal val1 = {{2, 0, 0, ~(MAX_BYTE / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(MAX_BYTE / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_2) {
  s21_decimal val1 = {{2, 0, 0, ~(MAX_BYTE / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(MAX_BYTE / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_3) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_6) {
  s21_decimal val1 = {{8, 0, 0, ~(MAX_BYTE / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_7) {
  s21_decimal val1 = {{2, 0, 0, ~(MAX_BYTE / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_8) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, ~(MAX_BYTE / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_9) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(MAX_BYTE / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_10) {
  s21_decimal val1 = {{8, 0, 0, ~(MAX_BYTE / 2)}};
  s21_decimal val2 = {{0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_11) {
  s21_decimal val1 = {{MAX_BYTE, MAX_BYTE, MAX_BYTE, ~(MAX_BYTE / 2)}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(2, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_12) {
  s21_decimal val1 = {{MAX_BYTE, MAX_BYTE, MAX_BYTE, 0}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_13) {
  s21_decimal val1 = {{MAX_BYTE, MAX_BYTE, MAX_BYTE, ~(MAX_BYTE / 2)}};
  s21_decimal val2 = {{4, 0, 0, ~(MAX_BYTE / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_14) {
  s21_decimal val1 = {{4, 0, 0, ~(MAX_BYTE / 2)}};
  s21_decimal val2 = {{MAX_BYTE, MAX_BYTE, MAX_BYTE, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(2, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_15) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{MAX_BYTE, MAX_BYTE, MAX_BYTE, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_16) {
  s21_decimal val1 = {{4, 0, 0, ~(MAX_BYTE / 2)}};
  s21_decimal val2 = {{MAX_BYTE, MAX_BYTE, MAX_BYTE, ~(MAX_BYTE / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_17) {
  s21_decimal val1 = {{MAX_BYTE, MAX_BYTE, MAX_BYTE, 0}};
  s21_decimal val2 = {{4, 0, 0, ~(MAX_BYTE / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(1, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_18) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{MAX_BYTE, MAX_BYTE, MAX_BYTE, ~(MAX_BYTE / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(1, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_19) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_20) {
  s21_decimal dec1 = {{0}};
  s21_decimal dec2 = {{0}};
  int tmp1 = 100;
  int tmp2 = 99999;
  int res_s21 = 0;
  int res = -99899;
  s21_decimal res1 = {{0}};
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_sub(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(sub_21) {
  s21_decimal dec1 = {{0}};
  s21_decimal dec2 = {{0}};
  int tmp1 = -100;
  int tmp2 = -99999;
  int res_s21 = 0;
  s21_decimal res1 = {{0}};
  int res = 99899;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_sub(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(sub_22) {
  s21_decimal value_1 = {{13, 0, 0, 0}};
  s21_set_scale(&value_1, 1);
  s21_set_sign(&value_1, 1);
  s21_decimal value_2 = {{286, 0, 0, 0}};
  s21_set_scale(&value_2, 2);
  s21_set_sign(&value_2, 1);
  s21_decimal result = {0};
  s21_decimal check = {{156, 0, 0, 0}};
  s21_set_scale(&check, 2);
  int return_value = s21_sub(value_1, value_2, NULL);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(sub_23) {
  s21_decimal value_1 = {{13, 0, 0, 0}};
  s21_set_scale(&value_1, 1);
  s21_set_sign(&value_1, 1);
  s21_decimal value_2 = {{286, 0, 0, 0}};
  s21_set_scale(&value_2, 2);
  s21_decimal result = {0};
  s21_decimal check = {{416, 0, 0, 0}};
  s21_set_scale(&check, 2);
  s21_set_sign(&check, 1);
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(sub_24) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_set_sign(&value_1, 1);
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 2);
}
END_TEST

START_TEST(sub_25) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_set_sign(&value_1, 1);
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_set_sign(&value_2, 1);
  s21_decimal result = {0};
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 2);
}
END_TEST

START_TEST(sub_26) {
  s21_decimal value_1 = {{64071, 0, 0, 0}};
  s21_set_scale(&value_1, 4);
  s21_decimal value_2 = {{5919, 0, 0, 0}};
  s21_set_scale(&value_2, 1);
  s21_decimal result = {0};
  s21_decimal check = {{5854929, 0, 0, 0}};
  s21_set_scale(&check, 4);
  s21_set_sign(&check, 1);
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(sub_27) {
  s21_decimal src1 = {0}, src2 = {0};
  float a = -9403;
  float b = 202.098;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = a - b;
  s21_decimal res_od = {0};
  s21_sub(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(sub_28) {
  s21_decimal src1 = {0}, src2 = {0};
  src1.bits[3] = 0b00000000000000010000000000000000;
  src1.bits[2] = 0;
  src1.bits[1] = 0;
  src1.bits[0] = 0b00000000000000000110011011110000;
  src2.bits[3] = 0b00000000000000110000000000000000;
  src2.bits[2] = 0;
  src2.bits[1] = 0;
  src2.bits[0] = 0b00000000000001000101000111010110;
  s21_decimal result_origin = {0};
  result_origin.bits[3] = 0b00000000000000110000000000000000;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0;
  result_origin.bits[0] = 0b00000000001000111110001111101010;
  s21_decimal result_our = {0};
  s21_sub(src1, src2, &result_our);
  ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST

START_TEST(s21_subTest1) {
  // 863
  s21_decimal src1, src2, origin;
  // src1 = 2;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest2) {
  // 889
  s21_decimal src1, src2, origin;
  // src1 = 3;
  // src2 = 2;

  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest3) {
  // 915
  s21_decimal src1, src2, origin;
  // src1 = 0;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000011;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest4) {
  // 941
  s21_decimal src1, src2, origin;
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest5) {
  // 967
  s21_decimal src1, src2, origin;
  // src1 = 0;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000011;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest6) {
  // 993
  s21_decimal src1, src2, origin;
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest7) {
  // 1019
  s21_decimal src1, src2, origin;
  // src1 = 6521;
  // src2 = 74121;

  src1.bits[0] = 0b00000000000000000001100101111001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000010010000110001001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000010000100000010000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest8) {
  // 1045
  s21_decimal src1, src2, origin;
  // src1 = 4;
  // src2 = 97623323;

  src1.bits[0] = 0b00000000000000000000000000000100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000101110100011001110100011011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000101110100011001110100010111;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest9) {
  // 1071
  s21_decimal src1, src2, origin;
  // src1 = 65658654;
  // src2 = 5;

  src1.bits[0] = 100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 95;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 5;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest10) {
  // 1097
  s21_decimal src1, src2, origin;
  // src1 = -364748;
  // src2 = 1;

  src1.bits[0] = 0b00000000000001011001000011001100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000001011001000011001101;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest11) {
  // 1123
  s21_decimal src1, src2, origin;
  // src1 = 1;
  // src2 = 98745654321;

  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b11111101101100110001110000110001;
  src2.bits[1] = 0b00000000000000000000000000010110;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b11111101101100110001110000110000;
  origin.bits[1] = 0b00000000000000000000000000010110;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest12) {
  // 1149
  s21_decimal src1, src2, origin;
  // src1 = -9878798789;
  // src2 = -3;

  src1.bits[0] = 0b01001100110100101000000111000101;
  src1.bits[1] = 0b00000000000000000000000000000010;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b01001100110100101000000111000010;
  origin.bits[1] = 0b00000000000000000000000000000010;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest13) {
  // 1175
  s21_decimal src1, src2, origin;
  // src1 = 9999999999999999999;
  // src2 = 1;

  src1.bits[0] = 0b10001001111001111111111111111111;
  src1.bits[1] = 0b10001010110001110010001100000100;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b10001001111001111111111111111110;
  origin.bits[1] = 0b10001010110001110010001100000100;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest14) {
  // 1201
  s21_decimal src1, src2, origin;
  // src1 = 18446744073709551615;
  // src2 = 1;

  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b11111111111111111111111111111110;
  origin.bits[1] = 0b11111111111111111111111111111111;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest15) {
  // 1227
  s21_decimal src1, src2, origin;
  // src1 = 18446744073709551615.0;
  // src2 = 965453154;

  src1.bits[0] = 0b11111111111111111111111111110110;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000001001;
  src1.bits[3] = 0b00000000000000010000000000000000;

  src2.bits[0] = 0b00111001100010111010010101100010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b11000000100010111000101000100010;
  origin.bits[1] = 0b11111111111111111111111111111101;
  origin.bits[2] = 0b00000000000000000000000000001001;
  origin.bits[3] = 0b00000000000000010000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest16) {
  // 1253
  s21_decimal src1, src2, origin;
  // src1 = -545454512454545.35265454545645;
  // src2 = 54564654;

  src1.bits[0] = 0b10000010111000100101101011101101;
  src1.bits[1] = 0b11111001111010000010010110101101;
  src1.bits[2] = 0b10110000001111101111000010010100;
  src1.bits[3] = 0b10000000000011100000000000000000;

  src2.bits[0] = 0b00000011010000001001011100101110;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b10010100100110011101101011101101;
  origin.bits[1] = 0b11000101100100110110100101100010;
  origin.bits[2] = 0b10110000001111101111000110111100;
  origin.bits[3] = 0b10000000000011100000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest18) {
  // 1305
  s21_decimal src1, src2, origin;
  // src1 = 7961327845421.879754123131254;
  // src2 = 0;

  src1.bits[0] = 0b01001110111001000011100101110110;
  src1.bits[1] = 0b01001011001101011010000111011001;
  src1.bits[2] = 0b00011001101110010111010010111111;
  src1.bits[3] = 0b00000000000011110000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b01001110111001000011100101110110;
  origin.bits[1] = 0b01001011001101011010000111011001;
  origin.bits[2] = 0b00011001101110010111010010111111;
  origin.bits[3] = 0b00000000000011110000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest23) {
  // 1435
  s21_decimal src1, src2, origin;
  // src1 = 0;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_subTest24) {
  // 1461
  s21_decimal src1, src2, origin;
  // src1 = 0;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(mul_0) {
  s21_decimal val1 = {{2, 0, 0, ~(MAX_BYTE / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(MAX_BYTE / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_2) {
  s21_decimal val1 = {{2, 0, 0, ~(MAX_BYTE / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(MAX_BYTE / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_3) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(1, s21_mul(val1, val2, NULL));
}
END_TEST

START_TEST(mul_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_6) {
  s21_decimal val1 = {{8, 0, 0, ~(MAX_BYTE / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_7) {
  s21_decimal val1 = {{2, 0, 0, ~(MAX_BYTE / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_9) {
  s21_decimal val1 = {{MAX_BYTE, MAX_BYTE, MAX_BYTE, ~(MAX_BYTE / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(2, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_10) {
  s21_decimal val1 = {{MAX_BYTE, MAX_BYTE, MAX_BYTE, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_11) {
  s21_decimal val1 = {{MAX_BYTE, MAX_BYTE, MAX_BYTE, ~(MAX_BYTE / 2)}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_12) {
  s21_decimal value_1 = {{5, 0, 0, 0}};
  s21_decimal value_2 = {{7, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{35, 0, 0, 0}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(mul_13) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0, 0, 0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{1, 0xFFFFFFFE, 0, 0}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(mul_14) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(mul_15) {
  s21_decimal value_1 = {{123456u, 123u, 0, 0}};
  s21_decimal value_2 = {{654321u, 654u, 0, 0}};
  s21_set_scale(&value_1, 2);
  s21_set_scale(&value_2, 3);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0xcedabe40, 0x99c0c5d, 0x13a3a, 0x0}};
  s21_set_scale(&check, 5);
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(mul_16) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(mul_17) {
  s21_decimal value_1 = {{17, 0, 0, 0}};
  s21_set_sign(&value_1, 1);
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_mul(value_1, value_2, &result);
  // ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(mul_19) {
  s21_decimal src1, src2;
  int a = -32768;
  int b = 32768;
  int res_our_dec = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int res_origin = -1073741824;
  s21_decimal res_od = {0};
  s21_mul(src1, src2, &res_od);
  s21_from_decimal_to_int(res_od, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(mul_test_1) {
  int num1 = -10;
  int num2 = -10;
  int prod_int = 100;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, prod_int);
}
END_TEST

START_TEST(mul_test_2) {
  int num1 = 10;
  int num2 = 20;
  int prod_int = 200;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, prod_int);
}
END_TEST

START_TEST(mul_test_3) {
  int num1 = -10;
  int num2 = 20;
  int prod_int = -200;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, prod_int);
}
END_TEST

START_TEST(mul_test_4) {
  int num1 = 9403;
  int num2 = 202;
  int res_origin = 1899406;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mul_test_5) {
  int num1 = -32768;
  int num2 = 2;
  int res_origin = -65536;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mul_test_6) {
  int num1 = -32768;
  int num2 = 32768;
  int res_origin = -1073741824;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mul_test_7) {
  float num1 = 9403.0e2;
  int num2 = 202;
  float res_origin = 189940600;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(mul_test_8) {
  float num1 = 9403.0e2;
  float num2 = 9403.0e2;
  float res_origin = 884164090000;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(truncate_0) {
  s21_decimal val = {{7, 7, 7, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 129127208515966861312.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(truncate_1) {
  s21_decimal val = {{2, 0, 0, ~(MAX_BYTE / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = -2.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(truncate_2) {
  s21_decimal val = {{2, 0, 0, ~(MAX_BYTE / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = -2.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(truncate_3) {
  s21_decimal val = {{2, 0, 0, ~(MAX_BYTE / 2)}};
  s21_decimal res = {{0}};
  s21_set_scale(&val, 5);
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = -0.0;
  ck_assert_float_eq(need, fres);
}

START_TEST(truncate_4) {
  s21_decimal val = {{128, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_set_scale(&val, 1);
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 12;
  ck_assert_float_eq(need, fres);
}

START_TEST(truncate_6) {
  s21_decimal value_1 = {{35, 0, 0, 0}};
  s21_decimal check = {{3, 0, 0, 0}};
  s21_set_scale(&value_1, 1);
  s21_truncate(value_1, &value_1);
  ck_assert_int_eq(s21_is_equal(value_1, check), 1);
}
END_TEST

START_TEST(truncate_7) {
  s21_decimal value_1 = {{123456, 0, 0, 0}};
  s21_set_scale(&value_1, 3);
  s21_set_sign(&value_1, 1);
  s21_decimal check = {{123, 0, 0, 0}};
  s21_set_sign(&check, 1);
  s21_truncate(value_1, &value_1);
  ck_assert_int_eq(s21_is_equal(value_1, check), 1);
}
END_TEST

START_TEST(truncate_8) {
  s21_decimal src1 = {0};
  src1.bits[3] = 0x000A0000;
  src1.bits[2] = 0x0;
  src1.bits[1] = 0xFFFFFFFF;
  src1.bits[0] = 0xFFFFFFFF;
  s21_decimal result = {0};
  result.bits[3] = 0x0;
  result.bits[2] = 0x0;
  result.bits[1] = 0x0;
  result.bits[0] = 0x6DF37F67;
  s21_decimal res_od = {0};
  s21_truncate(src1, &res_od);
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

START_TEST(truncate_9) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b00000000000000000000000001101101;
  src1.bits[1] = 0b00000000000011000110010101011011;
  src1.bits[2] = 0b00000000000000000011000000111001;
  src1.bits[3] = 0b00000000000011100000000000000000;
  s21_decimal result = {0};
  result.bits[0] = 0b10000111101111000001011000011110;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res_od = {0};
  s21_truncate(src1, &res_od);
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

START_TEST(negate_0) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  int sign_before = s21_get_sign(&val);
  s21_negate(val, &res);
  int sign_after = s21_get_sign(&res);

  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(negate_1) {
  s21_decimal val = {{2, 0, 0, ~(MAX_BYTE / 2)}};
  s21_decimal res;
  int sign_before = s21_get_sign(&val);
  s21_negate(val, &res);
  int sign_after = s21_get_sign(&res);
  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(negate_2) {
  s21_decimal val = {{0, 0, 0, ~(MAX_BYTE / 2)}};
  s21_decimal res = {{0}};
  int sign_before = s21_get_sign(&val);
  s21_negate(val, &res);
  int sign_after = s21_get_sign(&res);
  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(negate_3) {
  s21_decimal val = {{0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(1, s21_negate(val, NULL));
}
END_TEST

START_TEST(negate_5) {
  s21_decimal value_1 = {{5, 0xFFFFFFFF, 0, 0}};
  s21_set_sign(&value_1, 1);
  s21_decimal check = {{5, 0xFFFFFFFF, 0, 0}};
  s21_decimal result = {0};
  int return_value = s21_negate(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(negate_6) {
  s21_decimal value_1 = {{1, 1, 1, 0}};
  s21_decimal check = {{1, 1, 1, 0x80000000}};
  s21_decimal result = {0};
  int return_value = s21_negate(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(negate_7) {
  float a = 10.1234e5;
  float res_a = 0;
  s21_decimal src = {0};
  s21_from_float_to_decimal(a, &src);
  s21_decimal res = {0};
  s21_negate(src, &res);
  s21_from_decimal_to_float(res, &res_a);
  ck_assert_float_eq(-10.1234e5, res_a);
}
END_TEST

START_TEST(dec_to_fl) {
  float a = 10.1234e5;
  float res_a = 0;
  s21_decimal src = {0};
  ck_assert_float_eq(1, s21_from_float_to_decimal(a, NULL));
}
END_TEST

START_TEST(fl_to_dec) {
  float a = 10.1234e5;
  float res_a = 0;
  s21_decimal src = {0};
  ck_assert_float_eq(1, s21_from_decimal_to_float(src, NULL));
}
END_TEST

START_TEST(fl_to_dec2) {
  float a = 0;
  float res_a = 0;
  s21_decimal src = {0};
  ck_assert_int_eq(0, s21_from_float_to_decimal(a, &src));
  ck_assert_float_eq(0, res_a);
}
END_TEST

START_TEST(int_to_dec) {
  int a = 10.1234e5;
  float res_a = 0;
  s21_decimal src = {0};
  ck_assert_float_eq(1, s21_from_int_to_decimal(a, NULL));
}
END_TEST

START_TEST(dec_to_int) {
  int a = 10.1234e5;
  float res_a = 0;
  s21_decimal src = {0};
  ck_assert_int_eq(1, s21_from_decimal_to_int(src, NULL));
}
END_TEST

Suite *test_ariphmetics(void) {
  Suite *suite = suite_create("ariphmetics");
  TCase *tcase = tcase_create("ariphmetics");
  tcase_add_test(tcase, dec_to_fl);
  tcase_add_test(tcase, dec_to_int);
  tcase_add_test(tcase, fl_to_dec);
  tcase_add_test(tcase, fl_to_dec2);
  tcase_add_test(tcase, int_to_dec);
  tcase_add_test(tcase, add_1);
  tcase_add_test(tcase, add_2);
  tcase_add_test(tcase, add_2_5);
  tcase_add_test(tcase, add_3);
  suite_add_tcase(suite, tcase);
  return suite;
}

START_TEST(round_1) {
  s21_decimal val = {{3, 3, 3, ~(MAX_BYTE / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_2) {
  s21_decimal val = {{3, 3, 3, 0}};
  s21_decimal res = {{0}};
  s21_set_scale(&val, 5);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_3) {
  s21_decimal val = {{7, 7, 7, ~(MAX_BYTE / 2)}};
  s21_decimal res = {{0}};
  s21_set_scale(&val, 5);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_4) {
  s21_decimal val = {{25, 0, 0, ~(MAX_BYTE / 2)}};
  s21_decimal res = {{0}};
  s21_set_scale(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_5) {
  s21_decimal val = {{26, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_set_scale(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_6) {
  s21_decimal val = {{115, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_set_scale(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_7) {
  s21_decimal val = {{118, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_set_scale(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_8) {
  s21_decimal val = {{125, 0, 0, 0}};
  ck_assert_int_eq(1, s21_round(val, NULL));
}
END_TEST

START_TEST(round_9) {
  s21_decimal val = {{128, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_set_scale(&val, 1);
  s21_round(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 13;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(round_11) {
  s21_decimal value_1 = {{7464923, 0, 0, 0}};
  s21_set_scale(&value_1, 5);
  s21_decimal check = {{75, 0, 0, 0}};
  s21_decimal result = {0};
  int return_value = s21_round(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(round_12) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  s21_set_scale(&value_1, 5);
  s21_decimal check = {{74, 0, 0, 0}};
  s21_decimal result = {0};
  int return_value = s21_round(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(round_13) {
  s21_decimal value_1 = {{7464923, 0, 0, 0}};
  s21_set_sign(&value_1, 1);
  s21_set_scale(&value_1, 5);
  s21_decimal check = {{75, 0, 0, 0}};
  s21_set_sign(&check, 1);
  s21_decimal result = {0};
  int return_value = s21_round(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(round_14) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  s21_set_sign(&value_1, 1);
  s21_set_scale(&value_1, 5);
  s21_decimal check = {{74, 0, 0, 0}};
  s21_set_sign(&check, 1);
  s21_decimal result = {0};
  int return_value = s21_round(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(round_15) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b01010101001110101110101110110001;
  src1.bits[1] = 0b00001101101101001101101001011111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000100100000000000000000;
  s21_decimal result = {0};
  result.bits[0] = 0b00000000000000000000000000000001;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal res_od = {0};
  s21_round(src1, &res_od);
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

START_TEST(round_16) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b10010111011100111001111111111111;
  src1.bits[1] = 0b00111100000010000011000110001101;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b10000000000001110000000000000000;
  s21_decimal res_od = {0};
  s21_round(src1, &res_od);
  s21_decimal result = {0};
  result.bits[3] = 0b10000000000000000000000000000000;
  result.bits[2] = 0;
  result.bits[1] = 0b00000000000000000000001000010010;
  result.bits[0] = 0b00110110101101101000110001000000;
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

START_TEST(floor_0) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_floor(val, &res));
}
END_TEST

START_TEST(floor_1) {
  s21_decimal val = {{2, 0, 0, ~(MAX_INT / 2)}};
  s21_decimal res = {{0}};
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(-2, fres);
}
END_TEST

START_TEST(floor_2) {
  s21_decimal val = {{2, 0, 0, ~(MAX_INT / 2)}};
  s21_decimal res = {{0}};
  s21_set_scale(&val, 5);
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(-1, fres);
}
END_TEST

START_TEST(floor_3) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_set_scale(&val, 5);
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(0, fres);
}
END_TEST

START_TEST(floor_3_5) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_set_scale(&val, 5);
  ck_assert_int_eq(1, s21_floor(val, NULL));
}
END_TEST

START_TEST(floor_5) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  s21_set_scale(&value_1, 5);
  s21_decimal check = {{74, 0, 0, 0}};
  s21_decimal result = {0};
  int return_value = s21_floor(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(floor_6) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  s21_set_scale(&value_1, 5);
  s21_set_sign(&value_1, 1);
  s21_decimal check = {{75, 0, 0, 0}};
  s21_set_sign(&check, 1);
  s21_decimal result = {0};
  int return_value = s21_floor(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(floor_7) {
  s21_decimal src1;
  src1.bits[0] = 0b00001111111111111111111111111111;
  src1.bits[1] = 0b00111110001001010000001001100001;
  src1.bits[2] = 0b00100000010011111100111001011110;
  src1.bits[3] = 0b10000000000010100000000000000000;
  s21_decimal res_od = {0};
  s21_floor(src1, &res_od);
  s21_decimal result = {0};
  result.bits[0] = 0b10100111011001000000000000000000;
  result.bits[1] = 0b00001101111000001011011010110011;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

START_TEST(bank_round_t1) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal value_2 = {{500001, 0, 0, 0}};
  s21_decimal check = {{2, 0, 0, 0}};
  s21_decimal result = {0};
  result = s21_round_banking(value_1, value_2);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(bank_round_t2) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal value_2 = {{50000, 0, 0, 0}};
  s21_decimal check = {{2, 0, 0, 0}};
  s21_decimal result = {0};
  result = s21_round_banking(value_1, value_2);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(bank_round_t3) {
  s21_decimal value_1 = {{2, 0, 0, 0}};
  s21_decimal value_2 = {{5, 0, 0, 0}};
  s21_set_scale(&value_2, 1);
  s21_decimal check = {{2, 0, 0, 0}};
  s21_decimal result = {0};
  result = s21_round_banking(value_1, value_2);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

Suite *test_mul(void) {
  Suite *suite = suite_create("mul");
  TCase *tc = tcase_create("mul");

  tcase_add_test(tc, mul_0);
  tcase_add_test(tc, mul_1);
  tcase_add_test(tc, mul_2);
  tcase_add_test(tc, mul_3);
  tcase_add_test(tc, mul_4);
  tcase_add_test(tc, mul_5);
  tcase_add_test(tc, mul_6);
  tcase_add_test(tc, mul_7);
  tcase_add_test(tc, mul_9);
  tcase_add_test(tc, mul_10);
  tcase_add_test(tc, mul_11);
  tcase_add_test(tc, mul_12);
  tcase_add_test(tc, mul_13);
  tcase_add_test(tc, mul_14);
  tcase_add_test(tc, mul_15);
  tcase_add_test(tc, mul_16);
  tcase_add_test(tc, mul_17);
  tcase_add_test(tc, mul_19);

  tcase_add_test(tc, mul_test_1);
  tcase_add_test(tc, mul_test_2);
  tcase_add_test(tc, mul_test_3);
  tcase_add_test(tc, mul_test_4);
  tcase_add_test(tc, mul_test_5);
  tcase_add_test(tc, mul_test_6);
  tcase_add_test(tc, mul_test_7);
  tcase_add_test(tc, mul_test_8);
  suite_add_tcase(suite, tc);
  return suite;
}

Suite *suite_truncate(void) {
  Suite *s = suite_create("suite_truncate");
  TCase *tc = tcase_create("suite_truncate_tc");

  tcase_add_test(tc, truncate_0);
  tcase_add_test(tc, truncate_1);
  tcase_add_test(tc, truncate_2);
  tcase_add_test(tc, truncate_3);
  tcase_add_test(tc, truncate_4);
  tcase_add_test(tc, truncate_6);
  tcase_add_test(tc, truncate_7);
  tcase_add_test(tc, truncate_8);
  tcase_add_test(tc, truncate_9);

  suite_add_tcase(s, tc);
  return s;
}

Suite *suite_floor(void) {
  Suite *s = suite_create("suite_floor");
  TCase *tc = tcase_create("_tc");

  tcase_add_test(tc, floor_0);
  tcase_add_test(tc, floor_1);
  tcase_add_test(tc, floor_2);
  tcase_add_test(tc, floor_3);
  tcase_add_test(tc, floor_3_5);
  tcase_add_test(tc, floor_5);
  tcase_add_test(tc, floor_6);
  tcase_add_test(tc, floor_7);

  suite_add_tcase(s, tc);
  return s;
}

Suite *suite_negate(void) {
  Suite *s = suite_create("negate");
  TCase *tc = tcase_create("negate");

  tcase_add_test(tc, negate_0);
  tcase_add_test(tc, negate_1);
  tcase_add_test(tc, negate_2);
  tcase_add_test(tc, negate_3);
  tcase_add_test(tc, negate_5);
  tcase_add_test(tc, negate_6);
  tcase_add_test(tc, negate_7);

  suite_add_tcase(s, tc);
  return s;
}

Suite *suite_round(void) {
  Suite *s = suite_create("round");
  TCase *tc = tcase_create("round");

  tcase_add_test(tc, round_1);
  tcase_add_test(tc, round_2);
  tcase_add_test(tc, round_3);
  tcase_add_test(tc, round_4);
  tcase_add_test(tc, round_5);
  tcase_add_test(tc, round_6);
  tcase_add_test(tc, round_7);
  tcase_add_test(tc, round_8);
  tcase_add_test(tc, round_9);
  tcase_add_test(tc, round_11);
  tcase_add_test(tc, round_12);
  tcase_add_test(tc, round_13);
  tcase_add_test(tc, round_14);
  tcase_add_test(tc, round_15);
  tcase_add_test(tc, round_16);

  suite_add_tcase(s, tc);
  return s;
}

Suite *test_sub(void) {
  Suite *suite = suite_create("sub");
  TCase *tc = tcase_create("sub");
  tcase_add_test(tc, sub_0);
  tcase_add_test(tc, sub_1);
  tcase_add_test(tc, sub_2);
  tcase_add_test(tc, sub_3);
  tcase_add_test(tc, sub_4);
  tcase_add_test(tc, sub_5);
  tcase_add_test(tc, sub_6);
  tcase_add_test(tc, sub_7);
  tcase_add_test(tc, sub_8);
  tcase_add_test(tc, sub_9);
  tcase_add_test(tc, sub_10);
  tcase_add_test(tc, sub_11);
  tcase_add_test(tc, sub_12);
  tcase_add_test(tc, sub_13);
  tcase_add_test(tc, sub_14);
  tcase_add_test(tc, sub_15);
  tcase_add_test(tc, sub_16);
  tcase_add_test(tc, sub_17);
  tcase_add_test(tc, sub_18);
  tcase_add_test(tc, sub_19);
  tcase_add_test(tc, sub_20);
  tcase_add_test(tc, sub_21);
  tcase_add_test(tc, sub_22);
  tcase_add_test(tc, sub_23);
  tcase_add_test(tc, sub_24);
  tcase_add_test(tc, sub_25);
  tcase_add_test(tc, sub_26);
  tcase_add_test(tc, sub_27);
  tcase_add_test(tc, sub_28);

  tcase_add_test(tc, s21_subTest1);
  tcase_add_test(tc, s21_subTest2);
  tcase_add_test(tc, s21_subTest3);
  tcase_add_test(tc, s21_subTest4);
  tcase_add_test(tc, s21_subTest5);
  tcase_add_test(tc, s21_subTest6);
  tcase_add_test(tc, s21_subTest7);
  tcase_add_test(tc, s21_subTest8);
  tcase_add_test(tc, s21_subTest9);
  tcase_add_test(tc, s21_subTest10);
  tcase_add_test(tc, s21_subTest11);
  tcase_add_test(tc, s21_subTest12);
  tcase_add_test(tc, s21_subTest13);
  tcase_add_test(tc, s21_subTest14);
  tcase_add_test(tc, s21_subTest15);
  tcase_add_test(tc, s21_subTest16);
  tcase_add_test(tc, s21_subTest18);
  tcase_add_test(tc, s21_subTest23);
  tcase_add_test(tc, s21_subTest24);
  suite_add_tcase(suite, tc);
  return suite;
}

Suite *test_div(void) {
  Suite *suite = suite_create("div");
  TCase *tc = tcase_create("div");
  tcase_add_test(tc, div_1);
  tcase_add_test(tc, div_2);
  tcase_add_test(tc, div_3);
  tcase_add_test(tc, div_4);
  tcase_add_test(tc, div_5);
  tcase_add_test(tc, div_6);
  tcase_add_test(tc, div_7);
  tcase_add_test(tc, div_8);
  tcase_add_test(tc, div_9);
  tcase_add_test(tc, bank_round_t1);
  tcase_add_test(tc, bank_round_t2);
  tcase_add_test(tc, bank_round_t3);
  suite_add_tcase(suite, tc);
  return suite;
}

int main() {
  srand(time(0));
  Suite *comparisons_suite = test_comparisons();
  SRunner *suite_runner = srunner_create(comparisons_suite);
  srunner_run_all(suite_runner, CK_NORMAL);
  srunner_free(suite_runner);
  Suite *ariphmetics_suite = test_ariphmetics();
  suite_runner = srunner_create(ariphmetics_suite);
  srunner_run_all(suite_runner, CK_NORMAL);
  srunner_free(suite_runner);
  Suite *div_suite = test_div();
  suite_runner = srunner_create(div_suite);
  srunner_run_all(suite_runner, CK_NORMAL);
  srunner_free(suite_runner);
  Suite *sub_suite = test_sub();
  suite_runner = srunner_create(sub_suite);
  srunner_run_all(suite_runner, CK_NORMAL);
  srunner_free(suite_runner);
  Suite *mul_suite = test_mul();
  suite_runner = srunner_create(mul_suite);
  srunner_run_all(suite_runner, CK_NORMAL);
  srunner_free(suite_runner);
  Suite *trun_suite = suite_truncate();
  suite_runner = srunner_create(trun_suite);
  srunner_run_all(suite_runner, CK_NORMAL);
  srunner_free(suite_runner);
  Suite *negete_suite = suite_negate();
  suite_runner = srunner_create(negete_suite);
  srunner_run_all(suite_runner, CK_NORMAL);
  srunner_free(suite_runner);
  Suite *round_suite = suite_round();
  suite_runner = srunner_create(round_suite);
  srunner_run_all(suite_runner, CK_NORMAL);
  srunner_free(suite_runner);
  Suite *floor_suite = suite_floor();
  suite_runner = srunner_create(floor_suite);
  srunner_run_all(suite_runner, CK_NORMAL);

  int failed = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  return failed ? 1 : 0;
}
