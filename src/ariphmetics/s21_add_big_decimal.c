#include "../s21_decimal.h"

// Сложение в формате большого децимала
void s21_add_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                         s21_big_decimal *result) {
  int ovf = 0;
  // Проходим через каждый бит (224 бит)
  for (int i = 0; i < 192; i++) {
    // Складываем текущие биты и остаток от предыдущего шага
    int res =
        s21_is_set_bit_big(&value_1, i) + s21_is_set_bit_big(&value_2, i) + ovf;
    // Вычисляем новый остаток для следующего шага
    ovf = res / 2;
    // Устанавливаем текущий бит в результате
    s21_set_bit_big(result, i, res % 2);
  }
}