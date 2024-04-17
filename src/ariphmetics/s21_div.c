#include "../s21_decimal.h"

/// @brief Деление
/// @param value_1
/// @param value_2
/// @param result
/// @return 0 - OK 1 - число слишком велико или равно бесконечности 2 - число
/// слишком мало или равно отрицательной бесконечности 3 - деление на 0
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0, sign = 0;
  if (!result)
    error = 1;
  else {
    if (s21_is_decimal_no_empty(value_2)) {
      int scale = 0, res_scale = 0;
      s21_big_decimal v1 = {0}, v2 = {0}, r = {0};
      s21_from_decimal_to_big(&v1, &value_1);
      s21_from_decimal_to_big(&v2, &value_2);
      if (s21_get_sign(&value_1) != s21_get_sign(&value_2)) sign = 1;

      scale = s21_div_big_decimal(v1, v2, &r);
      //  Установка знака результата в случае разных знаков операндов.
      s21_set_scale(&value_1, s21_get_scale(&value_1) + scale);
      // Установка нового масштаба для чисел value_1.
      res_scale = s21_get_scale(&value_1) - s21_get_scale(&value_2);
      // Вычисление нового масштаба результата.
      if (res_scale > 0) {
        // Если новый масштаб положен.
        res_scale = s21_post_normalization(&r, res_scale);
        //   Результат после нормализации и достижение окончательного масштаба.
      } else if (res_scale < 0) {
        // Если новый масштаб отрицателен.
        s21_multiply_number_by_10_n_times(&r, abs(res_scale));
        //   Увеличение масштаба результата и получение нового масштаба.
        res_scale = s21_post_normalization(&r, 0);
        //   Результат после нормализации и достижение окончательного масштаба.
      }
      if (res_scale >= 0) {
        // Если окончательный масштаб неотрицателен.
        s21_from_big_to_decimal(&r, result);
        //   Преобразование результата в формате маленького decimal.
        s21_set_scale(result, res_scale);
        s21_set_sign(result, sign);
        //   Установка окончательного масштабного результата.
      } else {
        error = 1;
        //    Установка флага ошибка.
      }
    } else {
      error = 3;
      // Установка флага ошибки, указывающего на разделение на ноль.
    }
    if (error == 1 && s21_get_sign(result)) error = 2;
    //   Обработка ошибок, связанных с отрицательным результатом.
    if (error) s21_zero_decimal(result);
    //   Очистка результата в случае ошибки.
  }
  return error;
}