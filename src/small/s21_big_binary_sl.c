#include "../s21_decimal.h"

/// @brief Сдвиг big decimal влево +
/// @param dst
/// @param num
/// @return
s21_big_decimal s21_big_binary_shift_left(s21_big_decimal res, int num) {
  int error = 0;
  int buffer[8] = {0};
  for (int k = 0; k < num; k++) {
    for (int i = 0; i < 6; i++) {
      buffer[i] = s21_is_set_bit_big(&res, (i + 1) * 32 - 1);
    }
    for (int i = 6; i > 0 && !error; i--) {
      if (s21_is_set_bit_big(&res, 255)) error = 1;
      res.bits[i] <<= 1;
      s21_set_bit_big(&res, i * 32, buffer[i - 1]);
    }
    res.bits[0] <<= 1;
  }
  return res;
}