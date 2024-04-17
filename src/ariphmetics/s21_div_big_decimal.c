#include "../s21_decimal.h"

/// @brief Деление big decimal
/// @param value_1
/// @param value_2
/// @param result
/// @return 0 - OK 1 - число слишком велико или равно бесконечности 2 - число
/// слишком мало или равно отрицательной бесконечности 3 - деление на 0

int s21_div_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                        s21_big_decimal *result) {
  int b_1 = 0, b_2 = 0, bit_2 = 0, save_scale = 0;
  //    Объявление функций хранения битов, разницы в битах и
  //    ​​дополнительных показателей.
  s21_big_decimal tmp = {0};
  //   Создание временной переменной для хранения результатов деления.
  s21_find_highest_bit_big_decimal(value_1, value_2, &b_1, &b_2);
  //    На самом прохождении старшего бита для двух чисел.
  bit_2 = b_2;
  //   Сохранение значений самого старшего бита для последующего использования.
  for (int i = 0; i < 96 && s21_is_big_decimal_not_empty(value_1);) {
    // Начало цикла, который показал результат, пока не прошло 96 итераций и
    // value_1не стало пустым.
    if (i > 0) {
      value_2 = s21_big_binary_shift_left(value_2, 1);
      //   Сдвиг влево числа value_2.
      s21_multiply_number_by_10_n_times(result, 1);
      //    Увеличение результата на 1.
      s21_multiply_number_by_10_n_times(&value_1, 1);
      //   величение показателя числа value_1на 1.
      save_scale++;
      //   Увеличение счетчика сохраненной меры.
    }
    int scale = s21_equation_bits_big_decimal(&value_1, &value_2);
    save_scale += scale;
    // Увеличение сохраненной величины на значение scale.
    b_1 = b_2 = 0;
    // Обнуление функций b_1 и b_2.
    s21_find_highest_bit_big_decimal(value_1, value_2, &b_1, &b_2);
    // Повторное нахождение самого старшего бита для двух чисел.
    int diff = b_2 - bit_2;
    // Вычисление разницы в битах между текущей и предыдущей позицией самого
    // старшего бита.
    if (diff < 0) diff = 0;
    // Если разница отрицательна, устанавливается в 0.
    for (; diff >= 0 && s21_is_big_decimal_not_empty(value_1);)
    // Внутренний цикл, выполняется, пока разница в битах неотрицательна и
    // value_1не стала пустым.
    /*Если value_2больше value_1, то устанавливается соответствующий
    бит в tmp0, иначе вычитание результата.
    Увеличивается счетчик итераций i, придается значение diffи
    делается соответствующий параметр.
    */
    {
      if (s21_is_greater_big_decimal(value_2, value_1)) {
        s21_set_bit_big(&tmp, 0, 0);
      } else {
        s21_sub_big_decimal(value_1, value_2, &value_1);
        s21_set_bit_big(&tmp, 0, 1);
      }
      i++;
      diff--;
      if (diff >= 0) s21_shift_big_dec_right(&value_2, 1);
      tmp = s21_big_binary_shift_left(tmp, 1);
      // Если diffнеотрицательно, то получается дополнительный сдвиг
      // влево для учета разницы в битах.
    }
    if (diff >= 0) tmp = s21_big_binary_shift_left(tmp, diff + 1);
    s21_shift_big_dec_right(&tmp, 1);
    // Окончательный поворот вправо для коррекции положения.
    s21_add_big_decimal(*result, tmp, result);
    // Сложение tmpс результатом.
    s21_zero_s21_big_decimal(&tmp);
    // Обнуление временной переменной.
  }
  return save_scale;
  //   Возврат значения сохраненной scale.
}
