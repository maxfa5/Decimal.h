#include "../s21_decimal.h"

int s21_mul_help(s21_decimal value_1, s21_decimal value_2,
                 s21_decimal *result) {
  int code = 0, bits = 0;
  s21_big_decimal v_1, v_2, result_big;
  s21_decimal one = {0};
  one.bits[0] = 1;
  int scale = s21_get_scale(&value_1) + s21_get_scale(&value_2);
  // Создание условий для представления чисел в большом формате.
  s21_from_decimal_to_big(&v_1, &value_1);
  s21_from_decimal_to_big(&v_2, &value_2);
  s21_zero_s21_big_decimal(&result_big);
  for (int i = 0; i < 190; i++) {
    if (s21_is_set_bit_big(&v_1, i)) {
      s21_add_big(result_big, s21_big_binary_shift_left(v_2, i), &result_big);
      bits++;
    }
  }
  if (bits >= 96 && s21_is_greater_or_equal(value_2, one)) {
    code = 1;
  }
  if (bits <= 0) {
    s21_zero_s21_big_decimal(&result_big);
  }
  if (!code) {
    s21_set_scale_big(&result_big, scale);
    scale = s21_post_normalization(&result_big, scale);
  }
  if (scale != -1) {
    s21_set_scale_big(&result_big, scale);
    s21_from_big_to_decimal(&result_big, result);
  } else {
    code = 1;
  }
  if (code == 1 && s21_get_sign_big(&result_big)) code = 2;
  return code;
}