#include "../s21_decimal.h"

// return
// 0 - FALSE
// 1 - TRUE
int s21_is_equal(s21_decimal num1, s21_decimal num2) {
  return ((s21_compare_decimals(&num1, &num2) == 0) ? 1 : 0);
}
int s21_is_greater(s21_decimal num1, s21_decimal num2) {
  return ((s21_compare_decimals(&num1, &num2) == 2) ? 1 : 0);
}
int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2) {
  int result = s21_compare_decimals(&num1, &num2);
  return ((result == 2) || (result == 0) ? 1 : 0);
}
int s21_is_less(s21_decimal num1, s21_decimal num2) {
  return ((s21_compare_decimals(&num1, &num2) == 1) ? 1 : 0);
}
int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2) {
  int result = s21_compare_decimals(&num1, &num2);
  return ((result == 1) || (result == 0) ? 1 : 0);
}
int s21_is_not_equal(s21_decimal num1, s21_decimal num2) {
  int result = s21_compare_decimals(&num1, &num2);
  return ((result == 1) || (result == 2) ? 1 : 0);
}