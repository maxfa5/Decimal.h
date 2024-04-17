#include "../s21_decimal.h"

void s21_multiply_number_by_10_n_times(s21_big_decimal* num, int power) {
  for (int i = 0; i < power; i++) {
    s21_multiple_10_big(num);
  }
}
