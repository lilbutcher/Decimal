#include <stdio.h>
#include <string.h>

#include "s21_decimal.h"

/*
  **ERROR CODES FOR CONVERSION MODULE**

  s21_conversion_errors enum:
    S21_CONVERSION_OK = 0,
    S21_CONVERSION_ERROR = 1
*/

/*
  converts an integer number into s21_decimal
  returns s21_conversion_errors int code
*/
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  s21_conversion_errors error = S21_CONVERSION_OK;
  if (!dst) error = S21_CONVERSION_ERROR;
  if (error == S21_CONVERSION_OK) {
    *dst = s21_decimal_get_zero();
    int sign;
    if (src < 0) {
      sign = S21_NEGATIVE;
      // -INT_MIN cannot be represented as an int
      if (src != INT_MIN) {
        src = -src;
      }
    } else {
      sign = S21_POSITIVE;
    }
    dst->bits[0] = src;
    s21_decimal_set_sign(dst, sign);
  }
  return error;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  *dst = s21_decimal_get_zero();
  s21_conversion_errors error = S21_CONVERSION_OK;
  if (error == S21_CONVERSION_OK) {
    if (fabs(src) < powl(10.0, -1 * 28)) {
      error = S21_CONVERSION_ERROR;
    } else if (src > powl(2.0, MAX_BITS_INTEGRAL)) {
      error = S21_CONVERSION_ERROR;
    } else if (src < (-1 * powl(2.0, MAX_BITS_INTEGRAL))) {
      error = S21_CONVERSION_ERROR;
    } else if ((isnan(src))) {
      error = S21_CONVERSION_ERROR;
    } else {
      int exp = 0;
      if (src < 0.0) s21_decimal_set_sign(dst, S21_NEGATIVE);
      src = fabsl(src);
      for (; !(int)src && exp < 28; src *= 10) exp++;
      int i = 0;
      for (; src < powl(2.0, MAX_BITS_INTEGRAL) && exp < 28 && i < 7; i++) {
        src *= (long double)10.0;
        exp++;
      }
      for (i = 0; src >= powl(10.0, -1 * 8) && i < MAX_BITS_INTEGRAL; i++) {
        src = floorl(src) / 2;
        if (src - floorl(src) > powl(10.0, (-1 * 8))) {
          *dst = s21_decimal_set_bit(*dst, i);
        }
      }
      s21_decimal_set_exponent(dst, exp);
    }
  }
  return error;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  s21_conversion_errors error = S21_CONVERSION_OK;
  int exponent = s21_decimal_get_exponent(src);
  if (src.bits[1] || src.bits[2]) {
    error = S21_CONVERSION_ERROR;
  } else {
    *dst = src.bits[0];
    if (exponent > 0 && exponent <= 28) {
      *dst /= pow(10, exponent);
    }
  }
  if (s21_decimal_get_sign(src) == S21_NEGATIVE) *dst = *dst * (-1);
  return error;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  s21_conversion_errors error = S21_CONVERSION_OK;
  if (!dst) {
    error = S21_CONVERSION_ERROR;
  } else if (!s21_decimal_correctness(src)) {
    error = S21_CONVERSION_ERROR;
    *dst = 0.0;
  }
  double tmp_bit = 0.0;
  int sign = s21_decimal_get_sign(src);
  int scale = s21_decimal_get_exponent(src);
  for (int i = 0; i < MAX_BITS_INTEGRAL; i++) {
    if (s21_decimal_test_bit(src, i) != 0) {
      tmp_bit += pow(2.0, i);
    }
  }
  double powscale = pow(10, scale);
  tmp_bit /= powscale;
  if (sign == S21_NEGATIVE) {
    tmp_bit *= -1.0;
  }
  *dst = (float)tmp_bit;

  return error;
}
