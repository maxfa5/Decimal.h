#include "../s21_decimal.h"

int s21_multiple_10_big(s21_big_decimal *dst) {
  int code = 0;
  int scale = s21_get_scale_big(dst), overflow = 0;
  long long tmp = 0;
  if (scale != 0) {
    scale--;
  } else {
    for (int i = 0; i < 7; i++) {
      tmp = ((long)dst->bits[i] * 10) + overflow;
      if (tmp > MAX_INT) {
        if (i == 7) {
          code = 1;
          continue;  //хитрый ход
        }
        overflow = tmp >> 32;
        tmp = (tmp << 32) >> 32;
      } else
        overflow = tmp >> 32;
      if (!code) dst->bits[i] = tmp;
    }
  }
  s21_set_scale_big(dst, scale);
  return code;
}