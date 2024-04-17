#include "../s21_decimal.h"

/// @brief Rounds a decimal value to the nearest integer
/// @param dec структура которую хотим изменить
/// @param result стркутра для записи нового числа
/// @return 1 или 0, в зависимости от успешности выполнения
int s21_round(s21_decimal value, s21_decimal *result) {
  int code = 0;
  if (!result) {
    code = 1;
  }
  if (!code) {
    s21_zero_decimal(result);
    long double fl_to_round = 0.0;
    long double difference = 0;
    s21_from_decimal_to_double(value, &fl_to_round);
    fl_to_round = round(fl_to_round);
    if (fl_to_round < 0.0) {
      s21_set_sign(result, 1);

      fl_to_round *= -1;
    }
    for (int i = 0; fl_to_round >= 1 && i < 96; i++) {
      fl_to_round = floor(fl_to_round) / 2;
      difference = fl_to_round - floor(fl_to_round);
      if (difference > 0.0) {
        s21_set_bit_one(result, i);
      } else {
        s21_set_bit_zero(result, i);
      }
    }
    s21_set_scale(result, 0);
  }
  return code;
}