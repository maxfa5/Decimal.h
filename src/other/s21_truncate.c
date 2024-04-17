#include "../s21_decimal.h"

/// @brief Возвращает целове число, отбрасывая дробную часть
/// @param dec структура которую хотим изменить
/// @param result стркутра для записи нового числа
/// @return 1 или 0, в зависимости от успешности выполнения
int s21_truncate(s21_decimal value, s21_decimal *result) {
  int code = 0;
  if (!result) {
    code = 1;
  } else {
    s21_zero_decimal(result);
    float difference = 0;
    if (s21_get_scale(&value)) {
      long double fl_to_int = 0.0;
      s21_from_decimal_to_double(value, &fl_to_int);
      fl_to_int = trunc(fl_to_int);
      if (fl_to_int < 0.0) {
        s21_set_sign(result, 1);

        fl_to_int *= -1;
      }
      //перевод в 2 СС
      for (int i = 0; fl_to_int >= 1 && i < 96; i++) {
        fl_to_int = floor(fl_to_int) / 2;
        difference =
            fl_to_int - floor(fl_to_int);  // находим разницу между значением и
                                           // его целой частью
        if (difference > 0.0) {
          s21_set_bit_one(result, i);
        } else {
          s21_set_bit_zero(result, i);
        }
      }
      s21_set_scale(result, 0);
    } else {
      for (int i = 0; i < 4; ++i) {
        result->bits[i] = value.bits[i];
      }
    }
  }
  return code;
}