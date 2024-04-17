#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int result = 0;
  if (!dst) {
    result = 1;
  } else {
    s21_zero_decimal(dst);
    if (src >= 0) {
      dst->bits[0] = src;
    } else {
      s21_set_sign(dst, 1);  // устанавливаем минус
      dst->bits[0] = abs(src);
    }
  }
  return result;
}