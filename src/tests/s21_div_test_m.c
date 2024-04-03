#include "s21_decimal_test.h"

START_TEST(div_0) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_2) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_3) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(3, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_4) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(3, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_5) {
  s21_decimal value_1 = {{35, 0, 0, 0}};
  s21_decimal value_2 = {{5, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{70, 0, 0, 0}};
  s21_set_scale(&value_1, 1);
  s21_set_scale(&value_2, 2);
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(div_6) {
  s21_decimal value_1 = {{0x88888888, 0x88888888, 0x88888888, 0}};
  s21_decimal value_2 = {{0x2, 0, 0, 0}};
  s21_decimal_set_sign(&value_2, S21_POSITIVE);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x44444444, 0x44444444, 0x44444444, 0}};
  s21_decimal_set_sign(&check, S21_POSITIVE);
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(div_7) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_decimal_set_sign(&value_1, S21_POSITIVE);
  s21_decimal value_2 = {{8, 0, 0, 0}};
  s21_decimal_set_sign(&value_2, S21_POSITIVE);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{125, 0, 0, 0}};
  s21_set_scale(&check, 2);
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(div_8) {
  s21_decimal value_1 = {{15, 0, 0, 0}};
  s21_decimal_set_sign(&value_1, S21_POSITIVE);
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 3);
}
END_TEST

START_TEST(div_9) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0}};
  s21_set_scale(&value_2, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{1000u, 0, 0, 0}};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_div_test_1) {
  s21_decimal v1 = {{35}};
  s21_decimal v2 = {{8}};
  s21_decimal res;
  s21_decimal check = {{4375}};
  check.bits[3] = 3 << 16;
  int r = s21_div(v1, v2, &res);
  ck_assert_int_eq(r, 0);
  ck_assert_uint_eq(res.bits[0], check.bits[0]);
  ck_assert_uint_eq(res.bits[1], check.bits[1]);
  ck_assert_uint_eq(res.bits[2], check.bits[2]);
  ck_assert_uint_eq(res.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_div_test_2) {
  s21_decimal v1 = {{160}};
  s21_decimal v2 = {{10}};
  s21_decimal res;
  s21_decimal check = {{16}};
  check.bits[3] = 0;
  int r = s21_div(v1, v2, &res);
  ck_assert_int_eq(r, 0);
  ck_assert_uint_eq(res.bits[0], check.bits[0]);
  ck_assert_uint_eq(res.bits[1], check.bits[1]);
  ck_assert_uint_eq(res.bits[2], check.bits[2]);
  ck_assert_uint_eq(res.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_div_test_3) {
  s21_decimal v1 = {{160}};
  s21_decimal v2 = {{0}};
  s21_decimal res;
  int r = s21_div(v1, v2, &res);
  ck_assert_int_eq(r, 3);
}
END_TEST

START_TEST(s21_div_test_4) {
  s21_decimal v1 = {{35210}};
  s21_decimal v2 = {{3521}};
  s21_decimal res;
  s21_decimal check = {{10}};
  int r = s21_div(v1, v2, &res);
  ck_assert_int_eq(r, 0);
  ck_assert_uint_eq(res.bits[0], check.bits[0]);
  ck_assert_uint_eq(res.bits[1], check.bits[1]);
  ck_assert_uint_eq(res.bits[2], check.bits[2]);
  ck_assert_uint_eq(res.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_div_test_5) {
  s21_decimal v1 = {{1, 0, 0, 2147483648}};
  s21_decimal v2 = {{0b01000000000000000000000000000000,
                     0b01000110011101001110110111101010,
                     0b10011111001011001001110011010000}};
  s21_decimal res;
  int r = s21_div(v1, v2, &res);
  ck_assert_int_eq(r, 2);
}
END_TEST

START_TEST(s21_div_test_6) {
  s21_decimal v1 = {{1}};
  s21_decimal v2 = {{1}};
  v2.bits[3] = 28 << 16;
  s21_decimal res;
  s21_decimal check = {{0b00010000000000000000000000000000,
                        0b00111110001001010000001001100001,
                        0b00100000010011111100111001011110, 0}};
  int r = s21_div(v1, v2, &res);
  ck_assert_int_eq(r, 0);
  ck_assert_uint_eq(res.bits[0], check.bits[0]);
  ck_assert_uint_eq(res.bits[1], check.bits[1]);
  ck_assert_uint_eq(res.bits[2], check.bits[2]);
  ck_assert_uint_eq(res.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_div_test_8) {
  s21_decimal v1 = {{1, 103, 2, 2147942400}};
  s21_decimal v2 = {{0b00000000000000000000000000000101,
                     0b00000000000000000000001000000011, 0b1010, 65536}};
  s21_decimal res;
  s21_decimal check = {{2, 0, 0, 2147942400}};
  int r = s21_div(v1, v2, &res);
  ck_assert_int_eq(r, 0);
  ck_assert_uint_eq(res.bits[0], check.bits[0]);
  ck_assert_uint_eq(res.bits[1], check.bits[1]);
  ck_assert_uint_eq(res.bits[2], check.bits[2]);
  ck_assert_uint_eq(res.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_div_test_9) {
  s21_decimal v1 = {{1}};
  s21_decimal v2 = {{3, 0, 0, 2147483648}};
  s21_decimal res;
  s21_decimal check = {{0b00000101010101010101010101010101,
                        0b00010100101101110000000011001011,
                        0b00001010110001010100010011001010, 2149318656}};
  int r = s21_div(v1, v2, &res);
  ck_assert_int_eq(r, 0);
  ck_assert_uint_eq(res.bits[0], check.bits[0]);
  ck_assert_uint_eq(res.bits[1], check.bits[1]);
  ck_assert_uint_eq(res.bits[2], check.bits[2]);
  ck_assert_uint_eq(res.bits[3], check.bits[3]);
}
END_TEST

Suite *suite_div_m(void) {
  Suite *s = suite_create("suite_div_m");
  TCase *tc = tcase_create("case_div");

  tcase_add_test(tc, div_0);
  tcase_add_test(tc, div_1);
  tcase_add_test(tc, div_2);
  tcase_add_test(tc, div_3);
  tcase_add_test(tc, div_4);
  tcase_add_test(tc, div_5);
  tcase_add_test(tc, div_6);
  tcase_add_test(tc, div_7);
  tcase_add_test(tc, div_8);
  tcase_add_test(tc, div_9);
  tcase_add_test(tc, s21_div_test_1);
  tcase_add_test(tc, s21_div_test_2);
  tcase_add_test(tc, s21_div_test_3);
  tcase_add_test(tc, s21_div_test_4);
  tcase_add_test(tc, s21_div_test_5);
  tcase_add_test(tc, s21_div_test_6);
  tcase_add_test(tc, s21_div_test_8);
  tcase_add_test(tc, s21_div_test_9);

  suite_add_tcase(s, tc);
  return s;
}