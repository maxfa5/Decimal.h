#include "../s21_decimal.h"

// return
// 0 +/+
// 1 -/-
// 2 +/-
// 3 -/+
int s21_compare_signs(s21_decimal* num1, s21_decimal* num2) {
  int code = 0;
  int sign1 = s21_get_sign(num1);
  int sign2 = s21_get_sign(num2);

  if (!sign1 && !sign2)
    code = 1;
  else if (sign1 && !sign2)
    code = 2;
  else if (!sign1 && sign2)
    code = 3;

  return code;
}