#include "../s21_decimal.h"

int s21_sub_help(s21_decimal value_1, s21_decimal value_2,
                 s21_decimal *result) {
  int code = 0, scale = 0;
  s21_big_decimal v_1, v_2, result_big;
  s21_zero_s21_big_decimal(&result_big);
  s21_from_decimal_to_big(&v_1, &value_1);
  s21_from_decimal_to_big(&v_2, &value_2);
  int power = s21_normalize(&v_1, &v_2, &value_1, &value_2);
  int tmp = 0, dolg = 0;
  for (int i = 0; i < 190; i++) {
    tmp = s21_is_set_bit_big(&v_1, i) - (s21_is_set_bit_big(&v_2, i) + dolg);
    if (dolg) dolg = 0;
    if (tmp == -1) {
      dolg = 1;
      tmp = 1;
    }
    if (tmp == -2) {
      dolg = 1;
      tmp = 0;
    }
    s21_set_bit_big(&result_big, i, tmp);
    if (tmp) tmp--;
  }
  if (!code) {
    s21_set_scale_big(&result_big, power);
    scale = s21_post_normalization(&result_big, power);
  }
  if (scale != -1) {
    s21_set_scale_big(&result_big, scale);
    s21_from_big_to_decimal(&result_big, result);
  } else {
    code = 1;
  }
  return code;
}