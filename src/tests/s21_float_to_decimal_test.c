#include "s21_decimal_test.h"

START_TEST(test_1) {
  s21_decimal var;
  float value = 0;
  s21_from_float_to_decimal(5.0, &var);
  s21_from_decimal_to_float(var, &value);
  ck_assert_float_eq_tol(5.0, value, 10e-35);
}
END_TEST

START_TEST(test_2) {
  s21_decimal var;
  float value = 0;
  s21_from_float_to_decimal(5.01245, &var);
  s21_from_decimal_to_float(var, &value);
  ck_assert_float_eq_tol(5.01245, value, 10e+5);
}
END_TEST

START_TEST(test_3) {
  s21_decimal var;
  float value = 0;
  s21_from_float_to_decimal(1.0125, &var);
  s21_from_decimal_to_float(var, &value);
  ck_assert_float_eq_tol(1.0125, value, 10e-5);
}
END_TEST

START_TEST(test_4) {
  s21_decimal var;
  float value = 0;
  s21_from_float_to_decimal(5.01245, &var);
  s21_from_decimal_to_float(var, &value);
  ck_assert_float_eq_tol(5.01245, value, 10e+25);
}
END_TEST

Suite *suite_float_to_decimal(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("suite_add");
  tc = tcase_create("case_add");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);

  suite_add_tcase(s, tc);
  return s;
}

// //--------------------------s21_from_float_to_decimal---------------------------------

// START_TEST(test_s21_from_float_to_decimal_1) {
//   s21_decimal result;
//   s21_from_float_to_decimal(1234567.0, &result);
//   ck_assert_int_eq(result.bits[0], 1234567);
//   ck_assert_int_eq(result.bits[1], 0);
//   ck_assert_int_eq(result.bits[2], 0);
//   ck_assert_int_eq(result.bits[3], 0);
// }
// END_TEST

// START_TEST(test_s21_from_float_to_decimal_2) {
//   s21_decimal result;
//   s21_from_float_to_decimal(1.234567, &result);
//   ck_assert_int_eq(result.bits[0], 1234567);
//   ck_assert_int_eq(result.bits[1], 0);
//   ck_assert_int_eq(result.bits[2], 0);
//   ck_assert_int_eq(result.bits[3], 6 << 16);
// }
// END_TEST
