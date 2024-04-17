#include "../s21_decimal.h"

// Вычитание в формате большого децимала
void s21_sub_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                         s21_big_decimal *result) {
  int tmp = 0;
  for (int i = 0; i < 192; i++) {
    int res =
        s21_is_set_bit_big(&value_1, i) - s21_is_set_bit_big(&value_2, i) - tmp;
    tmp = res < 0;
    res = abs(res);
    s21_set_bit_big(result, i, res % 2);
  }
}