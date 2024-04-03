

#include "s21_decimal.h"
/*
  **ERROR CODES FOR ARITHMETIC MODULE**

  s21_arithmetic_errors enum:
    S21_ARITHMETIC_OK = 0,
    S21_ARITHMETIC_BIG = 1,
    S21_ARITHMETIC_SMALL = 2,
    S21_ARITHMETIC_ZERO_DIV = 3,
    S21_ARITHMETIC_INCORRECT_DATA = 4
*/

/*
  returns the absolute value of a s21_decimal number
*/
s21_decimal s21_abs(s21_decimal value) {
  s21_decimal res = value;
  s21_decimal_set_sign(&res, S21_POSITIVE);
  return res;
}

/*
  performs an addition of value_1 and value_2 and saves into result
  returns s21_arithmetic_errors code
*/
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_arithmetic_errors error = S21_ARITHMETIC_OK;
  if (!result) {
    error = S21_ARITHMETIC_INCORRECT_DATA;
  } else if (!s21_decimal_correctness(value_1) ||
             !s21_decimal_correctness(value_2)) {
    error = S21_ARITHMETIC_INCORRECT_DATA;
    *result = s21_decimal_get_inf();
  } else {
    // all of the tests are passed
    *result = s21_decimal_get_zero();
    s21_decimal res = s21_decimal_get_zero();
    int sign_1 = s21_decimal_get_sign(value_1);
    int sign_2 = s21_decimal_get_sign(value_2);
    if (sign_1 == S21_POSITIVE && sign_2 == S21_POSITIVE) {
      s21_add_helper(value_1, value_2, &res);
    } else if (sign_1 == S21_POSITIVE && sign_2 == S21_NEGATIVE) {
      s21_sub(value_1, s21_abs(value_2), &res);
    } else if (sign_1 == S21_NEGATIVE && sign_2 == S21_POSITIVE) {
      s21_sub(s21_abs(value_1), value_2, &res);
      s21_negate(res, &res);
    } else if (sign_1 == S21_NEGATIVE && sign_2 == S21_NEGATIVE) {
      s21_add_helper(s21_abs(value_1), s21_abs(value_2), &res);
      s21_negate(res, &res);
    }
    *result = res;
  }
  //обработка ошибок
  if (error != S21_ARITHMETIC_INCORRECT_DATA) {
    error = s21_decimal_error_add(value_1, value_2, result);
    *result = s21_decimal_zero_detection(*result);
  }
  return error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_arithmetic_errors error = S21_ARITHMETIC_OK;
  if (!result) {
    error = S21_ARITHMETIC_INCORRECT_DATA;
  } else if (!s21_decimal_correctness(value_1) ||
             !s21_decimal_correctness(value_2)) {
    error = S21_ARITHMETIC_INCORRECT_DATA;
    *result = s21_decimal_get_inf();
  } else {
    *result = s21_decimal_get_zero();
    s21_decimal res = s21_decimal_get_zero();
    int sign_1 = s21_decimal_get_sign(value_1);
    int sign_2 = s21_decimal_get_sign(value_2);
    if (sign_1 == S21_POSITIVE && sign_2 == S21_POSITIVE) {
      error = s21_sub_helper(value_1, value_2, &res);
    } else if (sign_1 == S21_POSITIVE && sign_2 == S21_NEGATIVE) {
      error = s21_add(value_1, s21_abs(value_2), &res);
      if (error == 2) error = 1;
    } else if (sign_1 == S21_NEGATIVE && sign_2 == S21_POSITIVE) {
      error = s21_add(s21_abs(value_1), value_2, &res);
      if (error != S21_ARITHMETIC_SMALL) s21_negate(res, &res);
    } else if (sign_1 == S21_NEGATIVE && sign_2 == S21_NEGATIVE) {
      s21_sub_helper(s21_abs(value_1), s21_abs(value_2), &res);
      s21_negate(res, &res);
    }
    if (s21_decimal_get_sign(res) == S21_NEGATIVE &&
        error == S21_ARITHMETIC_BIG) {
      error = S21_ARITHMETIC_SMALL;
    }
    *result = res;
  }
  if (error != S21_ARITHMETIC_INCORRECT_DATA) {
    error = s21_decimal_error_sub(value_1, value_2, result);
    *result = s21_decimal_zero_detection(*result);
  }

  return error;
}

/*
  performs multiplication of value_1 and value_2 and saves into result
  returns s21_arithmetic_errors code
*/
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_arithmetic_errors error = S21_ARITHMETIC_OK;
  if (!result) {
    error = S21_ARITHMETIC_INCORRECT_DATA;
  } else if (!s21_decimal_correctness(value_1) ||
             !s21_decimal_correctness(value_2)) {
    error = S21_ARITHMETIC_INCORRECT_DATA;
    *result = s21_decimal_get_inf();
  } else {
    // all of the tests are passed
    *result = s21_decimal_get_zero();
    s21_decimal res = s21_decimal_get_zero();
    int sign_1 = s21_decimal_get_sign(value_1);
    int sign_2 = s21_decimal_get_sign(value_2);
    if (sign_1 == S21_POSITIVE && sign_2 == S21_POSITIVE) {
      error = s21_mul_helper(value_1, value_2, &res);
    } else if (sign_1 == S21_POSITIVE && sign_2 == S21_NEGATIVE) {
      error = s21_mul_helper(value_1, s21_abs(value_2), &res);
      s21_negate(res, &res);
    } else if (sign_1 == S21_NEGATIVE && sign_2 == S21_POSITIVE) {
      error = s21_mul_helper(s21_abs(value_1), value_2, &res);
      s21_negate(res, &res);
    } else if (sign_1 == S21_NEGATIVE && sign_2 == S21_NEGATIVE) {
      error = s21_mul_helper(s21_abs(value_1), s21_abs(value_2), &res);
    }
    if (error == S21_ARITHMETIC_BIG) {
      if (s21_decimal_get_sign(res) == S21_NEGATIVE) {
        error = S21_ARITHMETIC_SMALL;
      }
    }
    if (error == S21_ARITHMETIC_OK &&
        s21_is_not_equal(value_1, s21_decimal_get_zero()) &&
        s21_is_not_equal(value_2, s21_decimal_get_zero()) &&
        s21_is_equal(res, s21_decimal_get_zero())) {
      error = S21_ARITHMETIC_SMALL;
    }
    *result = res;
  }
  // error = s21_decimal_error_mul(value_1, value_2, result);
  return error;
}


int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_arithmetic_errors error = S21_ARITHMETIC_OK;
  if (!result) {
    error = S21_ARITHMETIC_INCORRECT_DATA;
  } else if (!s21_decimal_correctness(value_1) ||
             !s21_decimal_correctness(value_2)) {
    error = S21_ARITHMETIC_INCORRECT_DATA;
    *result = s21_decimal_get_inf();
  } else if (s21_decimal_get_non_zero_bit(value_2) == -1) {
    error = S21_ARITHMETIC_ZERO_DIV;
  } else {
    s21_decimal res = {{0, 0, 0, 0}};

    s21_decimal ten = {{10, 0, 0, 0}};

    int sign_1 = s21_decimal_get_sign(value_1);
    int sign_2 = s21_decimal_get_sign(value_2);

    s21_big_decimal big_value_1 = {{{{0, 0, 0, 0}}, {{0, 0, 0, 0}}}};
    s21_big_decimal big_value_2 = {{{{0, 0, 0, 0}}, {{0, 0, 0, 0}}}};
    s21_big_decimal big_remainder = {{{{0, 0, 0, 0}}, {{0, 0, 0, 0}}}};

    s21_decimal_levelling(value_1, value_2, &big_value_1, &big_value_2);

    int i = 0;

    s21_big_decimal big_res = {{{{0, 0, 0, 0}}, {{0, 0, 0, 0}}}};

    big_res = s21_big_decimal_binary_division(big_value_1, big_value_2,
                                              &big_remainder);

    while (s21_big_decimal_binary_is_zero(big_remainder) != 1 && i < 28) {
      s21_big_decimal remainderin = {{{{0, 0, 0, 0}}, {{0, 0, 0, 0}}}};
      big_res = s21_big_decimal_binary_multiplication(big_res, ten);
      big_remainder = s21_big_decimal_binary_multiplication(big_remainder, ten);
      remainderin = s21_big_decimal_binary_division(big_remainder, big_value_2,
                                                    &big_remainder);
      big_res = s21_big_decimal_binary_addition(big_res, remainderin);
      i++;
    }

    if (s21_big_decimal_binary_is_zero(big_res) == 1) {
      big_res.decimals[1].bits[0] = 123;
    }

    if (big_res.decimals[1].bits[0] != 0 || big_res.decimals[1].bits[1] != 0 ||
        big_res.decimals[1].bits[2] != 0 || big_res.decimals[1].bits[3] != 0 ||
        big_res.decimals[0].bits[3] != 0) {
      if ((sign_1 == S21_POSITIVE && sign_2 == S21_POSITIVE) ||
          (sign_1 == S21_NEGATIVE && sign_2 == S21_NEGATIVE)) {
        return 1;
      } else {
        return 2;
      }
    }
    s21_decimal_set_exponent(&res, i);
    res.bits[0] = big_res.decimals[0].bits[0];
    res.bits[1] = big_res.decimals[0].bits[1];
    res.bits[2] = big_res.decimals[0].bits[2];

    if ((sign_1 == S21_POSITIVE && sign_2 == S21_POSITIVE) ||
        (sign_1 == S21_NEGATIVE && sign_2 == S21_NEGATIVE)) {
    } else {
      res.bits[3] = s21_set_bit(res.bits[3], 31);
    }

    *result = res;
  }
  return error;
}

/*
HELPERS
*/

/*
  function performs addition on two positive s21_decimal numbers
  writes into *result
  returns s21_arithmetic_errors code
*/
int s21_add_helper(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result) {
  s21_arithmetic_errors error = S21_ARITHMETIC_OK;
  s21_big_decimal big_value_1;
  s21_big_decimal big_value_2;
  int exponent_1 = s21_decimal_get_exponent(value_1);
  int exponent_2 = s21_decimal_get_exponent(value_2);
  int exponent_max = s21_max(exponent_1, exponent_2);
  // level the values (both the exponent and sign will be nullified)
  s21_decimal_levelling(value_1, value_2, &big_value_1, &big_value_2);
  //  add the values as two humongous integral numbers
  s21_big_decimal big_res =
      s21_big_decimal_binary_addition(big_value_1, big_value_2);
  //  figure out how to shift the decimal point to fit the result into 96 bits
  //  of mantissa Check overflow
  int shift = s21_big_decimal_shift_to_decimal(big_res);
  int res_exponent = exponent_max - shift;
  s21_decimal ten = s21_decimal_get_zero();
  s21_from_int_to_decimal(10, &ten);
  while (shift > 28) {
    big_res = s21_big_decimal_binary_division(
        big_res, s21_decimal_to_big_decimal(ten), NULL);
    --shift;
  }
  s21_big_decimal remainder =
      s21_decimal_to_big_decimal(s21_decimal_get_zero());
  s21_decimal power_of_ten = s21_decimal_power_ten(shift);
  s21_big_decimal big_power_of_ten = s21_decimal_to_big_decimal(power_of_ten);
  // make the result fit into 96 bits of mantissa
  big_res =
      s21_big_decimal_binary_division(big_res, big_power_of_ten, &remainder);
  s21_decimal_set_exponent(&remainder.decimals[0], shift);
  big_res.decimals[0] =
      s21_bank_round(big_res.decimals[0], remainder.decimals[0]);
  s21_decimal_set_exponent(&big_res.decimals[0], res_exponent);
  if (!s21_decimal_binary_is_zero(big_res.decimals[1]) ||
      !s21_decimal_correctness(big_res.decimals[0])) {
    error = S21_ARITHMETIC_BIG;
    *result = s21_decimal_get_inf();
  } else {
    *result = big_res.decimals[0];
  }
  return error;
}

int s21_sub_helper(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result) {
  s21_arithmetic_errors error = S21_ARITHMETIC_OK;
  s21_big_decimal big_value_1;
  s21_big_decimal big_value_2;
  int compare_result = s21_is_greater(value_1, value_2);
  int exponent_1 = s21_decimal_get_exponent(value_1);
  int exponent_2 = s21_decimal_get_exponent(value_2);
  int exponent_max = s21_max(exponent_1, exponent_2);
  int sign = 0;
  if (exponent_1 == exponent_2) {
    s21_decimal res;
    if (s21_decimal_binary_compare(value_1, value_2) == -1) {
      res = s21_decimal_binary_subtraction(value_2, value_1);
      s21_negate(res, &res);
    } else {
      res = s21_decimal_binary_subtraction(value_1, value_2);
    }
    *result = res;
  } else {
    // level the values (both the exponent and sign will be nullified)
    s21_decimal_levelling(value_1, value_2, &big_value_1, &big_value_2);
    // add the values as two humongous integral numbers
    s21_big_decimal big_res;
    if (compare_result == S21_TRUE) {
      big_res = s21_big_decimal_binary_subtraction(big_value_1, big_value_2);
    } else {
      big_res = s21_big_decimal_binary_subtraction(big_value_2, big_value_1);
      sign = 1;
    }

    // figure out how to shift the decimal point to fit the result into 96
    // bits of mantissa
    int shift = s21_big_decimal_shift_to_decimal(big_res);
    int res_exponent = exponent_max - shift;
    s21_decimal ten = s21_decimal_get_zero();
    s21_from_int_to_decimal(10, &ten);
    while (shift > 28) {
      big_res = s21_big_decimal_binary_division(
          big_res, s21_decimal_to_big_decimal(ten), NULL);
      --shift;
    }
    s21_big_decimal remainder =
        s21_decimal_to_big_decimal(s21_decimal_get_zero());
    s21_decimal power_of_ten = s21_decimal_power_ten(shift);
    s21_big_decimal big_power_of_ten = s21_decimal_to_big_decimal(power_of_ten);
    // make the result fit into 96 bits of mantissa
    big_res =
        s21_big_decimal_binary_division(big_res, big_power_of_ten, &remainder);
    s21_decimal_set_exponent(&remainder.decimals[0], shift);
    s21_decimal_set_exponent(&big_res.decimals[0], res_exponent);
    *result = big_res.decimals[0];
    s21_decimal_set_sign(result, sign);
  }
  return error;
}

/*
  function performs multiplication on two positive s21_decimal numbers
  writes into *result
  returns s21_arithmetic_errors code
*/
int s21_mul_helper(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result) {
  s21_arithmetic_errors error = S21_ARITHMETIC_OK;
  int exponent_1 = s21_decimal_get_exponent(value_1);
  int exponent_2 = s21_decimal_get_exponent(value_2);
  s21_decimal_clear_bit3(&value_1);
  s21_decimal_clear_bit3(&value_2);
  s21_big_decimal res = s21_decimal_binary_multiplication(value_1, value_2);
  int shift = s21_big_decimal_shift_to_decimal(res);
  int exponent_res = exponent_1 + exponent_2 - shift;
  if (exponent_res < 0) {
    error = S21_ARITHMETIC_BIG;
    *result = s21_decimal_get_inf();
  } else {
    s21_decimal ten = s21_decimal_get_zero();
    s21_from_int_to_decimal(10, &ten);
    while (shift > 28) {
      res = s21_big_decimal_binary_division(
          res, s21_decimal_to_big_decimal(ten), NULL);
      --shift;
    }
    if (exponent_res > 28) {
      s21_big_decimal tmp = res;
      int exponent_tmp = exponent_res;
      while (exponent_tmp > 28) {
        tmp = s21_big_decimal_binary_division(
            tmp, s21_decimal_to_big_decimal(ten), NULL);
        --exponent_tmp;
      }
      shift = exponent_res - exponent_tmp + shift;
      exponent_res = exponent_tmp;
    }
    s21_big_decimal remainder =
        s21_decimal_to_big_decimal(s21_decimal_get_zero());
    s21_decimal power_of_ten_tmp = s21_decimal_get_zero();
    s21_from_int_to_decimal(pow(10., (double)shift), &power_of_ten_tmp);
    s21_big_decimal power_of_ten = s21_decimal_to_big_decimal(power_of_ten_tmp);
    res = s21_big_decimal_binary_division(res, power_of_ten, &remainder);
    s21_decimal_set_exponent(&remainder.decimals[0], shift);
    res.decimals[0] = s21_bank_round(res.decimals[0], remainder.decimals[0]);
    s21_decimal_set_exponent(&res.decimals[0], exponent_res);
    if (!s21_decimal_binary_is_zero(res.decimals[1]) ||
        !s21_decimal_correctness(res.decimals[0])) {
      error = S21_ARITHMETIC_BIG;
      *result = s21_decimal_get_inf();
    } else {
      *result = res.decimals[0];
    }
  }

  return error;
}

/*
  returns max of two integers
*/
int s21_max(int value_1, int value_2) {
  return value_1 > value_2 ? value_1 : value_2;
}

/*
  calculates the amount of divisions by 10 for the value
  to fit into 96bits of mantissa in s21_decimal
  returns an int exponent of 10
*/
int s21_big_decimal_shift_to_decimal(s21_big_decimal value) {
  int res = 0;
  if (!(s21_decimal_binary_is_zero(value.decimals[0]) &&
        s21_decimal_binary_is_zero(value.decimals[1]))) {
    s21_big_decimal max = s21_decimal_to_big_decimal(s21_decimal_get_max());
    s21_big_decimal quotient =
        s21_big_decimal_binary_division(value, max, NULL);
    if (s21_decimal_correctness(quotient.decimals[0]))
      while (S21_TRUE) {
        s21_decimal power_of_ten = s21_decimal_get_zero();
        s21_from_int_to_decimal(pow(10., res), &power_of_ten);
        int compare_res =
            s21_decimal_binary_compare(quotient.decimals[0], power_of_ten);
        if (compare_res == 0 || compare_res == -1) {
          break;
        }
        ++res;
      }
    s21_decimal power_of_ten = s21_decimal_get_zero();
    s21_from_int_to_decimal(pow(10., res), &power_of_ten);
    s21_big_decimal tmp = s21_big_decimal_binary_division(
        value, s21_decimal_to_big_decimal(power_of_ten), NULL);
    if (!s21_decimal_binary_is_zero(tmp.decimals[1]) ||
        tmp.decimals[0].bits[3] != 0) {
      ++res;
    }
  }
  return res;
}

/*
  levelled values are only the integral part of the decimal, hence if exponents
  differ significantly — we may get a lot of trailing zeros

  we store the levelled values in a uint256 in case of overflow
*/
void s21_decimal_levelling(s21_decimal value_1, s21_decimal value_2,
                           s21_big_decimal *big_value_1,
                           s21_big_decimal *big_value_2) {
  int exponent_1 = s21_decimal_get_exponent(value_1);
  int exponent_2 = s21_decimal_get_exponent(value_2);
  s21_decimal tmp1 = value_1;
  s21_decimal tmp2 = value_2;
  s21_decimal_clear_bit3(&tmp1);
  s21_decimal_clear_bit3(&tmp2);
  if (exponent_1 > exponent_2) {
    *big_value_1 = s21_decimal_to_big_decimal(tmp1);
    *big_value_2 = s21_decimal_binary_multiplication(
        tmp2, s21_decimal_power_ten(exponent_1 - exponent_2));
  } else if (exponent_1 < exponent_2) {
    *big_value_1 = s21_decimal_binary_multiplication(
        tmp1, s21_decimal_power_ten(exponent_2 - exponent_1));
    *big_value_2 = s21_decimal_to_big_decimal(tmp2);
  } else {
    *big_value_1 = s21_decimal_to_big_decimal(tmp1);
    *big_value_2 = s21_decimal_to_big_decimal(tmp2);
  }
}

s21_decimal s21_decimal_power_ten(int power_of_ten) {
  s21_decimal ten = s21_decimal_get_zero(), res = s21_decimal_get_zero();
  res.bits[0] = 0b0000000000000000000000000001;
  ten.bits[0] = 0b0000000000000000000000001010;
  s21_big_decimal big_res = s21_decimal_to_big_decimal(res);
  for (int i = 0; i < power_of_ten; i++) {
    big_res = s21_decimal_binary_multiplication(big_res.decimals[0], ten);
  }
  return big_res.decimals[0];
}
//обработка ошибок для сложения
int s21_decimal_error_add(s21_decimal value_1, s21_decimal value_2,
                          s21_decimal *result) {
  float min_float;
  s21_decimal min, max;
  if (s21_is_greater(value_1, value_2)) {
    max = value_1;
    min = value_2;
  } else {
    max = value_2;
    min = value_1;
  }
  s21_from_decimal_to_float(min, &min_float);
  int error = 0;
  int sign_1 = s21_decimal_get_sign(value_1);
  int sign_2 = s21_decimal_get_sign(value_2);
  s21_decimal_clear_bit3(&value_1);
  s21_decimal_clear_bit3(&value_2);
  s21_decimal diff =
      s21_decimal_binary_subtraction(s21_decimal_get_max(), value_1);
  int compare_result = s21_decimal_binary_compare(value_2, diff);
  if (compare_result == 1) {
    if (s21_is_equal(max, s21_decimal_get_max()) && min_float >= 0 &&
        min_float < 1) {
      max = s21_decimal_get_max();
      max.bits[0] -= 1;
      *result = max;
    } else if (sign_1 == S21_POSITIVE && sign_2 == S21_POSITIVE) {
      error = S21_ARITHMETIC_BIG;
      *result = s21_decimal_get_inf();
    } else if (sign_1 == S21_NEGATIVE && sign_2 == S21_NEGATIVE) {
      error = S21_ARITHMETIC_SMALL;
      *result = s21_decimal_get_zero();
    }
  }
  return error;
}

//обработка ошибок для вычитания
int s21_decimal_error_sub(s21_decimal value_1, s21_decimal value_2,
                          s21_decimal *result) {
  float min_float;
  s21_decimal min, max;
  if (s21_is_greater(value_1, value_2)) {
    max = value_1;
    min = value_2;
  } else {
    max = value_2;
    min = value_1;
  }
  s21_from_decimal_to_float(min, &min_float);
  int error = 0;
  int sign_1 = s21_decimal_get_sign(value_1);
  int sign_2 = s21_decimal_get_sign(value_2);
  s21_decimal_clear_bit3(&value_1);
  s21_decimal_clear_bit3(&value_2);
  s21_decimal diff =
      s21_decimal_binary_subtraction(s21_decimal_get_max(), value_1);
  int compare_result = s21_decimal_binary_compare(value_2, diff);
  if (compare_result == 1) {
    if (s21_is_equal(max, s21_decimal_get_max()) && min_float >= 0 &&
        min_float < 1) {
      max = s21_decimal_get_max();
      max.bits[0] -= 1;
      *result = max;
    } else if (sign_1 == S21_NEGATIVE && sign_2 == S21_POSITIVE) {
      error = S21_ARITHMETIC_SMALL;
      *result = s21_decimal_get_zero();
    } else if (sign_1 == S21_POSITIVE && sign_2 == S21_NEGATIVE) {
      error = S21_ARITHMETIC_BIG;
      *result = s21_decimal_get_inf();
    }
  }
  return error;
}
//обработка ошибок для умножения
int s21_decimal_error_mul(s21_decimal value_1, s21_decimal value_2,
                          s21_decimal *result) {
  int error = 0;
  int sign_1 = s21_decimal_get_sign(value_1);
  int sign_2 = s21_decimal_get_sign(value_2);
  s21_decimal_clear_bit3(&value_1);
  s21_decimal_clear_bit3(&value_2);
  s21_decimal max, min;
  if (s21_decimal_binary_compare(value_1, value_2) == 1) {
    max = value_1;
    min = value_2;
  } else {
    max = value_2;
    min = value_1;
  }
  s21_decimal one = {{1, 0, 0, 0}};
  s21_decimal diff = s21_decimal_binary_subtraction(s21_decimal_get_max(), max);
  int compare_result = s21_decimal_binary_compare(max, diff);
  if (compare_result == 1 && s21_decimal_binary_compare(min, one) == 1) {
    if (sign_1 == S21_NEGATIVE && sign_2 == S21_NEGATIVE) {
      error = S21_ARITHMETIC_BIG;
      *result = s21_decimal_get_inf();
    } else if (sign_1 == S21_POSITIVE && sign_2 == S21_POSITIVE) {
      error = S21_ARITHMETIC_BIG;
      *result = s21_decimal_get_inf();
    } else {
      error = S21_ARITHMETIC_SMALL;
      *result = s21_decimal_get_zero();
    }
  }
  return error;
}

s21_decimal s21_decimal_zero_detection(s21_decimal value) {
  if (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0) {
    value = s21_decimal_get_zero();
  }
  return value;
}

int s21_big_decimal_binary_is_zero(s21_big_decimal decimal) {
  return decimal.decimals[0].bits[0] == 0 && decimal.decimals[0].bits[1] == 0 &&
         decimal.decimals[0].bits[2] == 0 && decimal.decimals[0].bits[3] == 0 &&
         decimal.decimals[1].bits[0] == 0 && decimal.decimals[1].bits[1] == 0 &&
         decimal.decimals[1].bits[2] == 0 && decimal.decimals[1].bits[3] == 0;
}

int my_compare(int qwe_1, int qwe_2) {
  if (qwe_1 < qwe_2) {
    return -1;
  } else if (qwe_1 > qwe_2) {
    return 1;
  } else {
    return 0;
  }
}
