#include <math.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct s21_decimal {
  unsigned int bits[4];
} s21_decimal;

typedef struct s21_big_decimal {
  unsigned int bits[8];
} s21_big_decimal;

#define MAX_BLOCK_BITS 96
#define MINUS 0x80000000  // 10000000 00000000 00000000 00000000
#define SC 0x00ff0000     // 00000000 11111111 00000000 00000000

#define MAX_BIG 96
#define MINUS_BIG \
  0x80000000  // 10000000 00000000 00000000 00000000 00000000 00000000 00000000
              // 00000000
#define SC_BIG \
  0x00ff0000  // 00000000 11111111 00000000 00000000 00000000 00000000 00000000
              // 00000000

#define MAX_INT 4294967295
#define MAX_BYTE 0xFFFFFFFF

/**
 * @brief объединение для получения доступа к данным bits[3] decimal
 * 16 бит: Биты от 0 до 15, младшее слово, не используются и должны быть равны
 * нулю. 8 бит: Биты с 16 по 23 должны содержать показатель степени от 0 до 28.
 * 7 бит: Биты с 24 по 30 не используются и должны быть равны нулю.
 * 1 бит: Бит 31 содержит знак; 0 означает положительный, а 1 означает
 * отрицательный. Итого 32 бита
 */

typedef union {
  int i;
  struct {
    uint32_t empty2 : 16;
    uint32_t power : 8;
    uint32_t empty1 : 7;
    uint32_t sign : 1;
  } parts;
} decimal_bit3;

typedef union {
  int ui;
  float fl;
} floatbits;

// Прототипы функций для s21_big_decimal
void s21_set_bit_zero_big(s21_big_decimal *dst, int pos);
void s21_set_bit_one_big(s21_big_decimal *dst, int pos);
void s21_set_scale_big(s21_big_decimal *dst, int scale);
int s21_multiple_10_big(s21_big_decimal *dst);

int s21_get_scale_big(s21_big_decimal *dst);
int s21_is_set_bit_unsigned(unsigned int *dst, int index);
int s21_is_set_bit_big(s21_big_decimal *dst, int index);
int s21_get_sign_big(s21_big_decimal *dst);
void s21_set_bit_big(s21_big_decimal *dst, int pos, int bit);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
void s21_sub_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                         s21_big_decimal *result);
int s21_from_decimal_to_double(s21_decimal src, long double *dst);
// Прототипы функций для s21_decimal
void s21_set_scale(s21_decimal *dst, int scale);
int s21_get_scale(s21_decimal *dst);
int s21_check_sc_to_size(s21_decimal *dst);
void s21_set_bit_one(s21_decimal *dst, int pos);
void s21_set_bit_zero(s21_decimal *dst, int pos);
int s21_is_set_bit(s21_decimal *dst, int index);
s21_decimal s21_abs(s21_decimal value);

int s21_get_empty_bits_in_bits3_in_decimal(s21_decimal *dst);
int s21_decimal_even(s21_decimal value);
void s21_set_sign(s21_decimal *dst, int sign);
int s21_truncate(s21_decimal value, s21_decimal *result);
s21_decimal s21_decimal_get_inf(void);
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_get_sign(s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_is_correct_decimal(s21_decimal *src);
s21_decimal s21_decimal_get_inf(void);
int s21_sub_help(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_normalize(s21_big_decimal *big1, s21_big_decimal *big2,
                  s21_decimal *num1, s21_decimal *num2);
void s21_remove_zeros(s21_decimal *num1);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul_help(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
s21_decimal s21_round_banking(s21_decimal integral, s21_decimal fractional);
int s21_round(s21_decimal value, s21_decimal *result);

void s21_add_big(s21_big_decimal value_1, s21_big_decimal value_2,
                 s21_big_decimal *result);

// Обнуление decimal
void s21_zero_decimal(s21_decimal *dst);
void s21_add_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                         s21_big_decimal *result);
// Обнуление s21_big_decimal
void s21_zero_s21_big_decimal(s21_big_decimal *dst);

// Преобразование из s21_big_decimal в decimal
void s21_from_big_to_decimal(s21_big_decimal *src, s21_decimal *dst);

// Преобразование из decimal в s21_big_decimal
void s21_from_decimal_to_big(s21_big_decimal *dst, s21_decimal *src);

int s21_decimal_even(s21_decimal value);

// Функции сравнения
int s21_is_equal(s21_decimal num1, s21_decimal num2);
int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2);
int s21_is_greater(s21_decimal num1, s21_decimal num2);
int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2);
int s21_is_less(s21_decimal num1, s21_decimal num2);
int s21_is_not_equal(s21_decimal num1, s21_decimal num2);

int s21_compare_signs(s21_decimal *num1, s21_decimal *num2);
void s21_multiply_number_by_10_n_times(s21_big_decimal *num, int power);
int s21_compare_decimals(s21_decimal *num1, s21_decimal *num2);
int s21_compare_bits(unsigned int *num1, unsigned int *num2,
                     int amount_of_bits);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_add_help(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);

int s21_equation_bits_big_decimal(s21_big_decimal *value_1,
                                  s21_big_decimal *value_2);
void s21_find_highest_bit_big_decimal(s21_big_decimal v1, s21_big_decimal v2,
                                      int *bit_1, int *bit_2);
int s21_post_normalization(s21_big_decimal *result, int scale);
void s21_shift_big_dec_right(s21_big_decimal *dst, int num);
s21_big_decimal s21_big_binary_shift_left(s21_big_decimal res, int num);
s21_decimal s21_dec_binary_shift_left(s21_decimal decimal1, int shift);
int s21_div_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                        s21_big_decimal *result);
int s21_is_big_decimal_not_empty(s21_big_decimal dst);
int s21_is_greater_or_equal_big_decimal(s21_big_decimal value_1,
                                        s21_big_decimal value_2);
int s21_is_greater_big_decimal(s21_big_decimal value_1,
                               s21_big_decimal value_2);
int s21_is_decimal_no_empty(s21_decimal dst);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
