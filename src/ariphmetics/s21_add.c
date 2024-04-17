#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int code = 0, error = 0;
  if (!result) {
    error = 1;
  } else if (s21_is_correct_decimal(&value_1) ||
             s21_is_correct_decimal(&value_2)) {
    // Проверяем, что value_1 и value_2 являются корректными decimal
    code = 1;
    *result = s21_decimal_get_inf();
  } else {
    s21_zero_decimal(result);
    s21_remove_zeros(&value_1);
    s21_remove_zeros(&value_2);
    int sign1 = s21_get_sign(&value_1), sign2 = s21_get_sign(&value_2);
    if (sign1 == sign2 && sign1 == 0) {
      code = s21_add_help(value_1, value_2, result);
    } else if (sign1 && sign2) {
      // Если оба слагаемых отрицательные
      // вызываем суммирование (используя abs), у результата меняем знак
      // v1 = -2; v2 = -1;
      // v1 + v2 = -2 + -1 = - (2 + 1) = -(abs(v1) + abs(v2))
      // v1 = -1; v2 = -2;
      // v1 + v2 = -1 + -2 = - (1 + 2) = -(abs(v1) + abs(v2))
      code = s21_add_help(s21_abs(value_1), s21_abs(value_2), result);
      s21_negate(*result, result);

    } else if (sign1 == 1 && sign2 == 0) {
      // Если первое - отрицательное, второе - положительное
      // вызываем вычитание (используя abs), у результата меняем знак
      // v1 = -2; v2 = 1;
      // v1 + v2 = -2 + 1 = -(2 - 1) = -(abs(v1) - v2)
      // v1 = -1; v2 = 2;
      // v1 + v2 = -1 + 2 = -(1 - 2) = -(abs(v1) - v2)
      code = s21_sub(s21_abs(value_1), (value_2), result);
      s21_negate(*result, result);
    } else if (sign1 == 0 && sign2 == 1) {
      // Если первое - отрицательное, второе - положительное
      // вызываем вычитание (используя abs), у результата меняем знак
      code = s21_sub((value_1), s21_abs(value_2), result);
    }
  }
  if (!error && code == 1 && s21_get_sign(result)) code = 2;
  if (!error && code) s21_zero_decimal(result);
  return code + error;
}
