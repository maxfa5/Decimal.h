#include "../s21_decimal.h"

// return
// 0 ==
// 1 >
// 2 <
int s21_compare_decimals(s21_decimal* num1, s21_decimal* num2) {
  int code = 0;

  int signs = s21_compare_signs(num1, num2);
  if (signs < 2)  //Если у чисел одинаковые знаки
  {
    int scale1 = s21_get_scale(num1);
    int scale2 = s21_get_scale(num2);

    //если хотя бы одно из чисел нецелое
    if (scale1 || scale2) {
      s21_big_decimal big1, big2;
      s21_normalize(&big1, &big2, num1, num2);
      code = s21_compare_bits((unsigned int*)&big1, (unsigned int*)&big2,
                              223);  // 223 - все биты big_decimal
    }

    //если оба числа целые
    else {
      code = s21_compare_bits((unsigned int*)num1, (unsigned int*)num2,
                              95);  // 95 - все биты decimal;
    }

    //если оба числа отрицательные, то инвертируем результат
    if (signs && code) {
      if (code == 1)
        code = 2;
      else if (code == 2)
        code = 1;
    }
  }

  //если числа имеют разные знаки, то положительное число всегда больше другого
  else if (signs == 2)
    code = 1;  // num1 положительное, num2 отрицательное
  else
    code = 2;  // num1 отрицательное, num2 положительное

  if (s21_is_decimal_no_empty(*num1) == 0 &&
      s21_is_decimal_no_empty(*num2) == 0)
    code = 0;

  return code;
}