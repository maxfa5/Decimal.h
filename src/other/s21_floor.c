#include "../s21_decimal.h"

// /**
//  * @brief Округляет value до ближайшего целого числа в сторону отрицательной
//  бесконечности.
//  *
//  * @param value округляемое число
//  * @param result указатель, куда будет записан результат
//  * @return int код ошибки:
//  *      0 - OK
//  *      1 - ошибка вычисления
//  */
int s21_floor(s21_decimal value, s21_decimal *result) {
  int code = 0;

  if (!result) {
    // Если указатель на decimal является NULL
    code = 1;
  } else if (s21_is_correct_decimal(&value)) {
    // Проверяем, что value является корректными decimal
    code = 1;
    *result = s21_decimal_get_inf();
  } else {
    // В остальных случаях округляем
    s21_zero_decimal(result);
    int sign = s21_get_sign(&value);
    s21_decimal fractional;
    s21_decimal value_unsigned_truncated;
    // Убираем знак
    s21_decimal value_unsigned = s21_abs(value);

    // Убираем дробную часть числа
    s21_truncate(value_unsigned, &value_unsigned_truncated);

    // Считаем убранную дробную часть числа
    s21_sub(value_unsigned, value_unsigned_truncated, &fractional);
    s21_decimal t = {0}, t2 = {0};
    t2.bits[0] = 1;
    // Если дробная часть была больше нуля и число было отрицательным, то
    // прибавляем 1
    if (sign == 1 && s21_is_greater(fractional, t)) {
      s21_add(value_unsigned_truncated, t2, &value_unsigned_truncated);
    }

    *result = value_unsigned_truncated;
    // Возвращаем знак
    s21_set_sign(result, sign);
  }

  return code;
}