#include "../s21_decimal.h"

void s21_set_sign(s21_decimal *dst, int sign) {
  if (!sign)
    dst->bits[3] &= ~MINUS;  //установить +
  else
    dst->bits[3] |= MINUS;  //установить -
}

int s21_get_sign_big(s21_big_decimal *dst) {
  decimal_bit3 bit3;
  bit3.i = dst->bits[7];
  return bit3.parts.sign;
}

int s21_get_sign(s21_decimal *dst) {
  decimal_bit3 bit3;
  bit3.i = dst->bits[3];
  return bit3.parts.sign;
}

void s21_set_bit_zero_big(s21_big_decimal *dst, int pos) {
  dst->bits[pos / 32] &= ~(1 << pos);
}

void s21_set_bit_one_big(s21_big_decimal *dst, int pos) {
  dst->bits[pos / 32] |= (1 << pos);
}

void s21_set_scale_big(s21_big_decimal *dst, int scale) {  //вставить степень
  decimal_bit3 bits3;
  bits3.i = dst->bits[7];
  bits3.parts.empty1 = 0;  //зануляем все биты кроме знака
  bits3.parts.empty2 = 0;
  bits3.parts.power = scale;
  dst->bits[7] = bits3.i;
}

void s21_set_scale(s21_decimal *dst, int scale) {  //вставить степень
  dst->bits[3] &= MINUS;  //зануляем все биты кроме знака
  dst->bits[3] |= (scale << 16) & SC;
}

int s21_get_scale_big(s21_big_decimal *dst) {
  decimal_bit3 bits3;
  bits3.i = dst->bits[7];
  return bits3.parts.power;
}

int s21_get_scale(s21_decimal *dst) {
  int scale = 0;
  scale = (dst->bits[3] & SC) >> 16;
  return scale;
}

int s21_check_sc_to_size(s21_decimal *dst) {
  int code = 0;
  int scale = s21_get_scale(dst);
  if (scale < 0 || scale > 28) {
    code = 1;
  }
  return code;
}
void s21_set_bit_big(s21_big_decimal *dst, int pos, int bit) {
  if (bit) {
    s21_set_bit_one_big(dst, pos);
  } else {
    s21_set_bit_zero_big(dst, pos);
  }
}
void s21_set_bit_one(s21_decimal *dst, int pos) {
  dst->bits[(pos - 1) / 32] |= (1 << pos);
}

void s21_set_bit_zero(s21_decimal *dst, int pos) {
  dst->bits[(pos - 1) / 32] &= ~(1 << pos);
}

int s21_is_set_bit(s21_decimal *dst, int index) {
  return !!(dst->bits[index / 32] & (1U << index % 32));
}

int s21_is_set_bit_unsigned(unsigned int *dst, int index) {
  return !!(dst[index / 32] & (1U << index % 32));
}

int s21_is_set_bit_big(s21_big_decimal *dst, int index) {
  return !!(dst->bits[index / 32] & (1U << index % 32));
}

s21_decimal s21_decimal_get_inf(void) {
  s21_decimal result = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF}};
  return result;
}

s21_decimal s21_abs(s21_decimal value) {
  s21_decimal result = value;
  s21_set_sign(&result, 0);
  return result;
}

int s21_get_empty_bits_in_bits3_in_decimal(s21_decimal *dst) {
  decimal_bit3 bits3;
  bits3.i = dst->bits[3];
  return bits3.parts.empty1 + bits3.parts.empty2;
}

/**
 * @brief Проверяет, что value явялется четным
 * Проверка на чётность:
 * (n &  1) ==  1;
 *
 * @param value
 * @return int код результата
 *          1 - четное
 *          0 - нечетное
 */
int s21_decimal_even(s21_decimal value) { return (value.bits[0] & 1) != 1; }

//  Обнуление decimal
void s21_zero_decimal(s21_decimal *dst) {
  dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
}

void s21_zero_s21_big_decimal(s21_big_decimal *dst) {
  dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = dst->bits[4] =
      dst->bits[5] = dst->bits[6] = dst->bits[7] = 0;
}

void s21_from_big_to_decimal(s21_big_decimal *src, s21_decimal *dst) {
  dst->bits[0] = src->bits[0];
  dst->bits[1] = src->bits[1];
  dst->bits[2] = src->bits[2];
  dst->bits[3] = src->bits[7];
}

void s21_from_decimal_to_big(s21_big_decimal *dst, s21_decimal *src) {
  s21_zero_s21_big_decimal(dst);
  dst->bits[0] = src->bits[0];
  dst->bits[1] = src->bits[1];
  dst->bits[2] = src->bits[2];
  dst->bits[7] = src->bits[3];
}

/// @brief Проверка на пустоту
/// @param dst
/// @return 0 или число большее 0
int s21_is_big_decimal_not_empty(s21_big_decimal dst) {
  return dst.bits[0] + dst.bits[1] + dst.bits[2] + dst.bits[3] + dst.bits[4] +
         dst.bits[5] + dst.bits[6];
}

int s21_is_correct_decimal(s21_decimal *src) {
  int code = 0;
  if (!(src && s21_get_empty_bits_in_bits3_in_decimal(src) == 0 &&
        s21_check_sc_to_size(src))) {
    code = 0;
  } else {
    code = 1;
  }
  return code;
}

void s21_remove_zeros(s21_decimal *num1) {
  int number = 0, scale = s21_get_scale(num1);
  s21_big_decimal ten = {{10, 0, 0, 0}};
  s21_big_decimal tmp = {0};
  s21_from_decimal_to_big(&tmp, num1);

  for (; !number && scale >= 1; scale--) {
    number = tmp.bits[0] % 10;
    s21_div_big_decimal(tmp, ten, &tmp);
    if (!number) {
      s21_from_big_to_decimal(&tmp, num1);
      s21_set_scale(num1, scale);
    }
  }
}

/// @brief  Поиск наибольшего бита в big decimal
/// @param v1
/// @param v2
/// @param bit_1
/// @param bit_2
void s21_find_highest_bit_big_decimal(s21_big_decimal v1, s21_big_decimal v2,
                                      int *bit_1, int *bit_2) {
  for (int i = 190; i >= 0 && (!(*bit_1) || !(*bit_2)); i--) {
    if (*bit_1 == 0 && s21_is_set_bit_big(&v1, i)) *bit_1 = i;
    if (*bit_2 == 0 && s21_is_set_bit_big(&v2, i)) *bit_2 = i;
  }
}

/// @brief Уравнение big decimal
/// @param value_1
/// @param value_2
/// @return scale
int s21_equation_bits_big_decimal(s21_big_decimal *value_1,
                                  s21_big_decimal *value_2) {
  int scale = 0;
  while (s21_is_greater_big_decimal(*value_2, *value_1)) {
    s21_multiply_number_by_10_n_times(value_1, 1);
    scale++;
  }
  while (s21_is_greater_or_equal_big_decimal(*value_1, *value_2)) {
    *value_2 = s21_big_binary_shift_left(*value_2, 1);
  }
  s21_shift_big_dec_right(value_2, 1);
  return scale;
}

/// @brief Больше или равно
/// @param value_1
/// @param value_2
/// @return 0 - если < , 1 - если >=
int s21_is_greater_or_equal_big_decimal(s21_big_decimal value_1,
                                        s21_big_decimal value_2) {
  int result = 0, out = 0;
  for (int i = 6; i >= 0 && !out && !result; i--) {
    if (value_1.bits[i] != 0 || value_2.bits[i] != 0) {
      if (value_1.bits[i] >= value_2.bits[i]) {
        result = 1;
      }
      out = 1;
    }
  }
  return result;
}

/// @brief Больше
/// @param value_1
/// @param value_2
/// @return 0 - если < , 1 - если >
int s21_is_greater_big_decimal(s21_big_decimal value_1,
                               s21_big_decimal value_2) {
  int result = 0, out = 0;
  for (int i = 6; i >= 0 && !result && !out; i--) {
    if (value_1.bits[i] || value_2.bits[i]) {
      if (value_1.bits[i] > value_2.bits[i]) {
        result = 1;
      }
      if (value_1.bits[i] != value_2.bits[i]) out = 1;
    }
  }
  return result;
}

/// @brief Проверка на пустоту
/// @param dst
/// @return 0 или число большее 0
int s21_is_decimal_no_empty(s21_decimal dst) {
  return dst.bits[0] + dst.bits[1] + dst.bits[2];
}

/// @brief  Перевод из decimal в double
/// @param src
/// @param dst
/// @return
int s21_from_decimal_to_double(s21_decimal src, long double *dst) {
  long double temp = (double)*dst;
  for (int i = 0; i < 96; i++) {
    temp += s21_is_set_bit(&src, i) * pow(2, i);
  }
  temp = temp * pow(10, -s21_get_scale(&src));
  if (s21_is_set_bit(&src, 127)) temp = temp * (-1);
  *dst = temp;
  return 0;
}

/// @brief Пост-нормализация для big decimal
/// @param result
/// @param scale
/// @return Число больше, равно или меньше нуля
int s21_post_normalization(s21_big_decimal *result, int scale) {
  int dop = 0;
  s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0}};
  // Пока есть значащие биты в старших разрядах и есть необходимость в
  // уменьшении масштаба
  while ((result->bits[3] || result->bits[4] || result->bits[5] ||
          result->bits[6]) &&
         scale > 0) {
    // Если scale равен 1 и есть старший бит в 3-ем разряде, устанавливаем флаг
    // dop
    if (scale == 1 && result->bits[3]) dop = 1;

    // Уменьшаем масштаб числа на 1
    s21_div_big_decimal(*result, ten, result);
    scale--;
  }
  if (dop && scale == 0 && result->bits[3] == 0 &&
      s21_is_set_bit_big(result, 0))
    s21_set_bit_big(result, 0, 0);

  if ((result->bits[3] || result->bits[4] || result->bits[5] ||
       result->bits[6]))
    scale = -1;

  return scale;
}

/// @brief Сдвиг big decimal вправо +
/// @param dst
/// @param num
void s21_shift_big_dec_right(s21_big_decimal *dst, int num) {
  int buffer[7] = {0};
  for (int k = 0; k < num; k++) {
    for (int i = 0; i < 6; i++) {
      buffer[i] = s21_is_set_bit_big(dst, (i + 1) * 32);
    }
    for (int i = 0; i < 6; i++) {
      dst->bits[i] >>= 1;
      s21_set_bit_big(dst, (i + 1) * 32 - 1, buffer[i]);
    }
    dst->bits[7] >>= 1;
  }
}

/**
 * @brief производит округление числа по правилам банковского округления.
 * Число передается отдельно в виде целой части integral и дробной части
 * fractional
 *
 * Вспомогательная функция для внутренних расчетов, переполнение не
 * контролируется и осуществляется за пределами функции
 * @param integral целая часть числа
 * @param fractional дробная часть числа
 * @return s21_decimal округленный результат
 */
s21_decimal s21_round_banking(s21_decimal integral, s21_decimal fractional) {
  s21_decimal zerofive = {0};
  zerofive.bits[0] = 5;
  s21_set_scale(&zerofive, 1);
  s21_decimal result;

  if (s21_is_equal(fractional, zerofive)) {
    // Если дробная часть ровно 0.5
    if (s21_decimal_even(integral)) {
      // Если целая часть четная, то оставляем её
      result = integral;
    } else {
      s21_decimal one = {0};
      one.bits[0] = 1;
      // Если целая часть нечетная, то увеличиваем её на 1
      s21_add(integral, one, &result);
    }
  } else if (s21_is_greater(fractional, zerofive)) {
    s21_decimal one = {0};
    one.bits[0] = 1;
    // Если дробная часть > 0.5, то увеличиваем целую часть на 1
    s21_add(integral, one, &result);
  } else {
    // Если дробная часть < 0.5, то оставляем целую часть без изменений
    result = integral;
  }

  return result;
}