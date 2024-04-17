#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int code = 0;
  if (!result) {
    code = 1;
  } else if (s21_is_correct_decimal(&value_1) ||
             s21_is_correct_decimal(&value_2)) {
    // Проверяем, что value_1 и value_2 являются корректными decimal
    code = 1;
    *result = s21_decimal_get_inf();
  } else {
    s21_decimal nul = {0};
    s21_zero_decimal(result);
    s21_remove_zeros(&value_1);
    s21_remove_zeros(&value_2);
    int sign1 = s21_get_sign(&value_1), sign2 = s21_get_sign(&value_2);
    if (sign1 == sign2) {
      code = s21_mul_help(value_1, value_2, result);
    } else if (sign1 != sign2) {
      code = s21_mul_help(value_1, value_2, result);
      s21_set_sign(result, 1);
    }
    if (s21_is_equal(value_2, nul)) {
      s21_zero_decimal(result);
    }
    if (code == 1 && s21_get_sign(result)) code = 2;

    if (code) {
      s21_zero_decimal(result);
    }
  }

  return code;
}