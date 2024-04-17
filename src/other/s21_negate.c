#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int code = 0;
  if (!result) code = 1;
  if (s21_is_correct_decimal(&value)) {
    *result = s21_decimal_get_inf();
    code = 1;
  } else if (!code) {
    *result = value;
    if (s21_get_sign(&value)) {
      s21_set_sign(result, 0);
    } else {
      s21_set_sign(result, 1);
    }
  }
  return code;
}