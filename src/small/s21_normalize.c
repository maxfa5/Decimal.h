#include "../s21_decimal.h"

int s21_normalize(s21_big_decimal *big1, s21_big_decimal *big2,
                  s21_decimal *num1, s21_decimal *num2) {
  int scale1 = s21_get_scale(num1);
  int scale2 = s21_get_scale(num2);

  int power = (scale1 > scale2) ? scale1 : scale2;
  s21_from_decimal_to_big(big1, num1);
  s21_from_decimal_to_big(big2, num2);
  s21_multiply_number_by_10_n_times(big1, power);
  s21_multiply_number_by_10_n_times(big2, power);
  return power;
}