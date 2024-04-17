#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int result = 0;
  if (!dst) {
    result = 1;
  } else {
    s21_decimal truncated_decimal;
    s21_truncate(src, &truncated_decimal);
    *dst = truncated_decimal.bits[0];
    if (s21_get_sign(&truncated_decimal)) {
      *dst *= -1;
    }
  }
  return result;
}