#include <stdio.h>

#include "s21_decimal.h"
/*
  **ERROR CODES FOR OTHER FUNCTIONS MODULE**

  s21_other_errors enum:
    S21_OTHER_OK = 0,
    S21_OTHER_ERROR = 1
*/

/*
  rounds value to the closest integer number and stores in *result
  if the value is equidistant from two integers — rounds to the closest even
  number returns an error code
*/

int s21_round(s21_decimal value, s21_decimal *result) {
  s21_other_errors error = S21_OTHER_OK;
  int exponent = s21_decimal_get_exponent(value);
  if (!result) {
    error = S21_OTHER_ERROR;
  } else if (!s21_decimal_correctness(value)) {
    error = S21_OTHER_ERROR;
    *result = s21_decimal_get_inf();
  } else if (exponent == 0) {
    *result = value;
  } else {
    int sign_1 = s21_decimal_get_sign(value);  // запоминаем знак
    s21_decimal set = {{4294967295, 4294967295, 4294967295, 0}};
    s21_decimal ten = {{10, 0, 0, 0}};
    s21_decimal one = {{0x1, 0x0, 0x0, 0x0}};
    s21_decimal remainder = {{0, 0, 0, 0}};
    value = s21_decimal_binary_and(value, set);  // убираем експоненту и знак

    for (int i = 0; i != (exponent - 1); i++) {
      value = s21_decimal_binary_division(value, ten, &remainder);
    }
    s21_decimal_binary_division(value, ten, &remainder);

    if (remainder.bits[0] >= 5) {
      value = s21_decimal_binary_division(value, ten, NULL);
      value = s21_decimal_binary_addition(value, one);
    } else {
      value = s21_decimal_binary_division(value, ten, NULL);
    }

    if (sign_1 == S21_NEGATIVE) {
      value.bits[3] = s21_set_bit(value.bits[3], 31);
    }

    *result = value;
  }
  return error;
}

/*
  banking rounding
  the integral and fractional parts of a number are accepted separately
  overflow is not controlled
  returns new rounded s21_decimal
*/
s21_decimal s21_bank_round(s21_decimal integral, s21_decimal fraction) {
  s21_decimal point_five = {{0x5, 0x0, 0x0, 0x10000}};
  s21_decimal one = {{0x1, 0x0, 0x0, 0x0}};
  s21_decimal res;
  if (s21_is_equal(fraction, point_five)) {
    if (s21_decimal_is_even(integral)) {
      res = integral;
    } else {
      res = s21_decimal_binary_addition(integral, one);
    }
  } else if (s21_is_greater(fraction, point_five)) {
    res = s21_decimal_binary_addition(integral, one);
  } else {
    res = integral;
  }
  return res;
}

/*
  removes trailing zeros from an s21_decimal
  returns new s21_decimal without the trailing zeros
*/
s21_decimal s21_decimal_remove_trailing_zeros(s21_decimal value) {
  s21_decimal res = value;
  int sign = s21_decimal_get_sign(value);
  int exponent = s21_decimal_get_exponent(value);
  if (s21_decimal_correctness(value) && exponent > 0) {
    s21_decimal remainder = s21_decimal_get_zero();
    s21_decimal tmp = value;
    s21_decimal_clear_bit3(&tmp);
    s21_decimal ten = s21_decimal_get_zero();
    s21_from_int_to_decimal(10, &ten);
    while (exponent > 0) {
      tmp = s21_decimal_binary_division(tmp, ten, &remainder);
      if (s21_decimal_binary_is_zero(remainder)) {
        --exponent;
        res = tmp;
      } else {
        break;
      }
    }
    s21_decimal_set_exponent(&res, exponent);
    s21_decimal_set_sign(&res, sign);
  }
  return res;
}

/*
  truncates all of the fractional digits of a s21_decimal, including trailing
  zeros writes into *result returns an error code
*/
int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_other_errors error = S21_OTHER_OK;
  int exponent = s21_decimal_get_exponent(value);
  if (!result) {
    error = S21_OTHER_ERROR;
  } else if (!s21_decimal_correctness(value)) {
    error = S21_OTHER_ERROR;
    *result = s21_decimal_get_inf();
  } else if (exponent == 0) {
    *result = value;
  } else {
    int sign_1 = s21_decimal_get_sign(value);  // запоминаем знак
    s21_decimal set = {{4294967295, 4294967295, 4294967295, 0}};
    s21_decimal ten = {{10, 0, 0, 0}};
    s21_decimal remainder = {{0, 0, 0, 0}};
    value = s21_decimal_binary_and(value, set);  // убираем експоненту и знак

    for (int i = 0; i != exponent; i++) {
      value = s21_decimal_binary_division(value, ten, &remainder);
    }

    if (sign_1 == S21_NEGATIVE) {
      value.bits[3] = s21_set_bit(value.bits[3], 31);
    }

    *result = value;
  }
  return error;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  s21_other_errors error = S21_OTHER_OK;
  if (!result) {
    error = S21_OTHER_ERROR;
  } else {
    *result = value;
    s21_decimal_set_sign(result, !s21_decimal_get_sign(value));
    // if the decimal is incorrect, we set the error variable, but still change
    // the sign
    if (!s21_decimal_correctness(value)) {
      error = S21_OTHER_ERROR;
    }
  }
  return error;
}

int s21_floor(s21_decimal value, s21_decimal *result) {  // тестов нет
  s21_other_errors error = S21_OTHER_OK;
  int exponent = s21_decimal_get_exponent(value);
  if (!result) {
    error = S21_OTHER_ERROR;
  } else if (!s21_decimal_correctness(value)) {
    error = S21_OTHER_ERROR;
    *result = s21_decimal_get_inf();
  } else if (exponent == 0) {
    *result = value;
  } else {
    int sign_1 = s21_decimal_get_sign(value);  // запоминаем знак
    s21_decimal set = {{4294967295, 4294967295, 4294967295, 0}};
    s21_decimal ten = {{10, 0, 0, 0}};
    s21_decimal one = {{0x1, 0x0, 0x0, 0x0}};
    s21_decimal remainder = {{0, 0, 0, 0}};

    value = s21_decimal_binary_and(value, set);  // убираем експоненту и знак

    for (int i = 0; i != (exponent - 1); i++) {
      value = s21_decimal_binary_division(value, ten, &remainder);
    }
    s21_decimal_binary_division(value, ten, &remainder);

    if (sign_1 == S21_NEGATIVE) {
      value = s21_decimal_binary_division(value, ten, NULL);
      value = s21_decimal_binary_addition(value, one);
    } else {
      value = s21_decimal_binary_division(value, ten, NULL);
    }

    if (sign_1 == S21_NEGATIVE) {
      value.bits[3] = s21_set_bit(value.bits[3], 31);
    }

    *result = value;
  }
  return error;
}
