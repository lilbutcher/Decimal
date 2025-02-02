#include "s21_decimal.h"

/*
  checks if the decimal layout is set correctly
  returns 1 if ok, 0 upon error
*/

int s21_decimal_correctness(s21_decimal decimal) {
  int res = 1;
  if ((s21_decimal_low_empty_check(decimal) != 0) ||
      (s21_decimal_high_empty_check(decimal) != 0)) {
    res = 0;
  } else {
    int exponent = s21_decimal_get_exponent(decimal);
    if (exponent < 0 || exponent > 28) {
      res = 0;
    }
  }
  return res;
}

/*
  checks if the 0-15 bits are set to 0 (returns the int value of the bits)
*/
int s21_decimal_low_empty_check(s21_decimal decimal) {
  s21_decimal_bit3 bit3;
  bit3.i = decimal.bits[3];
  return bit3.layout.low_empty;
}

/*
  checks if the 24-30 bits are set to 0 (returns the int value of the bits)
*/
int s21_decimal_high_empty_check(s21_decimal decimal) {
  s21_decimal_bit3 bit3;
  bit3.i = decimal.bits[3];
  return bit3.layout.high_empty;
}

/*
  returns the exponent
*/
int s21_decimal_get_exponent(s21_decimal decimal) {
  s21_decimal_bit3 bit3;
  bit3.i = decimal.bits[3];
  return bit3.layout.exponent;
}

/*
  sets the exponent to the desired value
*/
void s21_decimal_set_exponent(s21_decimal *decimal, int exponent) {
  s21_decimal_bit3 bit3;
  bit3.i = decimal->bits[3];
  bit3.layout.exponent = exponent;
  decimal->bits[3] = bit3.i;
}

/*
  returns the sign of a s21_decimal number
*/
int s21_decimal_get_sign(s21_decimal decimal) {
  s21_decimal_bit3 bit3;
  bit3.i = decimal.bits[3];
  return bit3.layout.sign;
}

/*
  sets a desired sign to the s21_decimal number provided
*/
void s21_decimal_set_sign(s21_decimal *decimal, int sign) {
  s21_decimal_bit3 bit3;
  bit3.i = decimal->bits[3];
  if (sign == S21_POSITIVE) {
    bit3.layout.sign = S21_POSITIVE;
  } else {
    bit3.layout.sign = S21_NEGATIVE;
  }

  decimal->bits[3] = bit3.i;
}

/*
  checks if the s21_decimal value is even
  returns 1 if even, 0 if odd
*/
int s21_decimal_is_even(s21_decimal value) { return (value.bits[0] & 1) != 1; }

/// @brief генератор случайных чисел
/// @param a
/// @param b
/// @return
float s21_rand_r(float a, float b) {
  float m = (float)rand() / RAND_MAX;
  float num = a + m * (b - a);
  return num;
}

// From another rep
/// @brief Установка знака
/// @param dst
void s21_set_sign(s21_decimal *dst) { dst->bits[3] = dst->bits[3] | 1u << 31; }