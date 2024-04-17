#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int code = 0;
  if (!result) {
    code = 1;
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
    if (sign1 == 0 && sign2 == 0) {
      // Если уменьшаемое и вычитаемое положительные
      if (s21_is_greater_or_equal(value_1, value_2)) {
        // Если уменьшаемое больше или равно вычитаемому
        // Вычитаем из уменьшаемого вычитаемое
        // v1 = 2; v2 = 1;
        // v1 - v2 = 2 - 1 = v1 - v2
        code = s21_sub_help(value_1, value_2, result);
      } else {
        // Если уменьшаемое меньше вычитаемомого
        // Вычитаем из вычитаемого уменьшаемое, у результата меняем знак
        // v1 = 1; v2 = 2;
        // v1 - v2 = 1 - 2 = - (2 - 1) = -(v2 - v1)
        code = s21_sub_help(value_2, value_1, result);
        s21_negate(*result, result);
      }
    } else if (sign1 == 0 && sign2 == 1) {
      // Если уменьшаемое положительное, а вычитаемое отрицательное
      // вызываем суммирование (используя abs)
      // v1 = 2; v2 = -1;
      // v1 - v2 = 2 - -1 = 2 + 1 = v1 + abs(v2)
      // v1 = 1; v2 = -2;
      // v1 - v2 = 1 - -2 = 1 + 2 = v1 + abs(v2)
      code = s21_add(value_1, s21_abs(value_2), result);
    } else if (sign1 == 1 && sign2 == 0) {
      // Если уменьшаемое отрицательное, а вычитаемое положительное
      // вызываем суммирование (используя abs), у результата меняем знак
      // v1 = -2; v2 = 1;
      // v1 - v2 = -2 - 1 = - (2 + 1) = - (abs(v1) + v2)
      // v1 = -1; v2 = 2;
      // v1 - v2 = -1 - 2 = - (1 + 2) = - (abs(v1) + v2)
      code = s21_add(s21_abs(value_1), value_2, result);
      s21_negate(*result, result);
    } else if (sign1 == 1 && sign2 == 1) {
      // Если уменьшаемое и вычитаемое отрицательные
      if (s21_is_greater_or_equal(value_1, value_2)) {
        // Если уменьшаемое больше или равно вычитаемому
        // Вычитаем из вычитаемого уменьшаемое (используя abs)
        // v1 = -1; v2 = -2;
        // v1 - v2 = -1 - -2 = -1 + 2 = 2 - 1 = abs(v2) - abs(v1)
        code = s21_sub_help(s21_abs(value_2), s21_abs(value_1), result);
      } else {
        // Если уменьшаемое меньше вычитаемомого
        // Вычитаем из уменьшаемого вычитаемое (используя abs), у результата
        // меняем знак v1 = -2; v2 = -1; v1 - v2 = -2 - -1 = -2 + 1 = 1 - 2 = -
        // (2 - 1) = - (abs(v1) - abs(v2))
        code = s21_sub_help(s21_abs(value_1), s21_abs(value_2), result);
        s21_negate(*result, result);
      }
    }
    if (code == 1 && s21_get_sign(result)) code = 2;
    if (code) s21_zero_decimal(result);
  }
  return code;
}