#include "../s21_decimal.h"

// return
// 0 ==
// 1 >
// 2 <
int s21_compare_bits(unsigned int* num1, unsigned int* num2,
                     int amount_of_bits) {
  int code = 0;
  int bit1, bit2;
  for (int i = amount_of_bits; i >= 0 && !code; i--) {
    bit1 = s21_is_set_bit_unsigned(num1, i);
    bit2 = s21_is_set_bit_unsigned(num2, i);
    if (bit1 > bit2)
      code = 1;
    else if (bit1 < bit2)
      code = 2;
  }
  return code;
}