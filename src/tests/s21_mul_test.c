#include "s21_decimal_test.h"

START_TEST(mul_0) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_2) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_3) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_6) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_7) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_8) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_9) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(2, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_10) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_11) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_12) {
  s21_decimal value_1 = {{5, 0, 0, 0}};
  s21_decimal value_2 = {{7, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{35, 0, 0, 0}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(mul_13) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0, 0, 0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{1, 0xFFFFFFFE, 0, 0}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(mul_14) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = s21_decimal_get_inf();
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(mul_15) {
  s21_decimal value_1 = {{123456u, 123u, 0, 0}};
  s21_decimal value_2 = {{654321u, 654u, 0, 0}};
  s21_decimal_set_sign(&value_2, S21_POSITIVE);
  s21_decimal_set_sign(&value_1, S21_NEGATIVE);
  s21_set_scale(&value_1, 2);
  s21_set_scale(&value_2, 3);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0xcedabe40, 0x99c0c5d, 0x13a3a, 0x80050000}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

// START_TEST(mul_16) {
//   s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
//   s21_decimal value_2 = {{2, 0, 0, 0}};
//   s21_decimal_set_sign(&value_2, S21_POSITIVE);
//   s21_decimal_set_sign(&value_1, S21_NEGATIVE);
//   s21_decimal result = {{0, 0, 0, 0}};
//   s21_decimal check = {{0, 0, 0, 0}};
//   int return_value = s21_mul(value_1, value_2, &result);
//   ck_assert_int_eq(s21_is_equal(result, check), 1);
//   ck_assert_int_eq(return_value, 2);
// }
// END_TEST

START_TEST(mul_17) {
  s21_decimal value_1 = {{17, 0, 0, 0}};
  s21_decimal_set_sign(&value_1, S21_POSITIVE);
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(mul_19) {
  s21_decimal src1, src2;
  int a = -32768;
  int b = 32768;
  int res_our_dec = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int res_origin = -1073741824;
  s21_decimal res_od = {0};
  s21_mul(src1, src2, &res_od);
  s21_from_decimal_to_int(res_od, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(mul_test_1) {
  int num1 = -10;
  int num2 = -10;
  int prod_int = 100;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, prod_int);
}
END_TEST

START_TEST(mul_test_2) {
  int num1 = 10;
  int num2 = 20;
  int prod_int = 200;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, prod_int);
}
END_TEST

START_TEST(mul_test_3) {
  int num1 = -10;
  int num2 = 20;
  int prod_int = -200;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, prod_int);
}
END_TEST

START_TEST(mul_test_4) {
  int num1 = 9403;
  int num2 = 202;
  int res_origin = 1899406;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mul_test_5) {
  int num1 = -32768;
  int num2 = 2;
  int res_origin = -65536;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mul_test_6) {
  int num1 = -32768;
  int num2 = 32768;
  int res_origin = -1073741824;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mul_test_7) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {0};

  ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));

  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(mul_test_8) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0}};
  s21_decimal result = {0};

  ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));

  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(mul_test_9) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_decimal value_2 = {{5, 0, 0, 0}};
  s21_decimal result = {0};

  ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));

  ck_assert_int_eq(result.bits[0], 50);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(mul_test_10) {
  s21_decimal value_1 = {{8, 0, 0, 0}};
  s21_decimal value_2 = {{10, 0, 0, 0}};
  s21_decimal result = {0};

  ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));

  ck_assert_int_eq(result.bits[0], 80);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(mul_test_11) {
  s21_decimal value_1 = {{10, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{4, 0, 0, 0}};
  s21_decimal result = {0};

  ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));

  ck_assert_int_eq(result.bits[0], 40);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(mul_test_12) {
  s21_decimal value_1 = {{123, 0, 0, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0x80000000}};
  s21_decimal result = {0};

  ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));

  ck_assert_int_eq(result.bits[0], 123);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(mul_test_13) {
  s21_decimal value_1 = {{1, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{1, 0, 0, 0x80000000}};
  s21_decimal result = {0};

  ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));

  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(mul_test_14) {
  // 26409387498605864508043122005
  s21_decimal value_1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -0.0000000000000025
  s21_decimal value_2 = {{0x19, 0x0, 0x0, 0x80100000}};
  // -66023468746514.661270107805012
  s21_decimal result = {{0xD5555554, 0x80000000, 0xD5555554, 0x800F0000}};

  ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));
}
END_TEST
// Тесты не корректные!
// START_TEST(mul_test_15) {
//     // -26409387498605864508043122005
//     s21_decimal value_1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
//     // 6148914691236517205
//     s21_decimal value_2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
//     // overflow
//     int result = S21_ARITHMETIC_SMALL;

//     ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));
// }
// END_TEST

// START_TEST(mul_test_16) {
//   // -26409387498605864508043122005
//   s21_decimal value_1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
//   // -6148914691236517205
//   s21_decimal value_2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
//   // overflow
//   int result = S21_ARITHMETIC_BIG;

//   ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));
// }
// END_TEST
//Тесты на некорректные данные

START_TEST(test_mul_fail_1) {
  // 792281625.14264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int error = s21_mul(decimal1, decimal2, NULL);

  ck_assert_int_ne(error, S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_2) {
  // степень 154
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal1 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int error = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(error, S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_3) {
  // степень 29
  s21_decimal decimal1 = {{-1, 0, 0, 0x1D0000}};
  // s21_decimal_print(decimal1);
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  // s21_decimal_print(decimal2);
  s21_decimal result;
  // s21_decimal_print(result);
  int error = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(error, S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_4) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{0, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int error = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(error, S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_5) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int error = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(error, S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_6) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C8000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int error = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(error, S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_7) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x11C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int error = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(error, S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_8) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x401C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int error = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(error, S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_9) {
  // Просто все единицы
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int error = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(error, S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_10) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal2 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int error = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(error, S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_11) {
  // степень 29 (показатель степени должен быть от 0 до
  // 28)tcase_add_test(tc_core, test_s21_mul_8);
  s21_decimal decimal2 = {{-1, 0, 0, 0x1D0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int error = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(error, S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_12) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal2 = {{0, 0, 0, 0x1D0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int error = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_ne(error, S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_13) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int error = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(error, S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_14) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x1C8000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int error = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(error, S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_15) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x11C0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int error = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(error, S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_16) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x401C0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int error = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(error, S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_17) {
  // Просто все единицы
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int error = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(error, S21_ARITHMETIC_OK);
}
END_TEST

Suite *suite_mul(void) {
  Suite *s = suite_create("suite_mul");
  TCase *tc = tcase_create("mul_tc");

  tcase_add_test(tc, mul_0);
  tcase_add_test(tc, mul_1);
  tcase_add_test(tc, mul_2);
  tcase_add_test(tc, mul_3);
  tcase_add_test(tc, mul_4);
  tcase_add_test(tc, mul_5);
  tcase_add_test(tc, mul_6);
  tcase_add_test(tc, mul_7);
  tcase_add_test(tc, mul_8);
  tcase_add_test(tc, mul_9);
  tcase_add_test(tc, mul_10);
  tcase_add_test(tc, mul_11);
  tcase_add_test(tc, mul_12);
  tcase_add_test(tc, mul_13);
  tcase_add_test(tc, mul_14);
  tcase_add_test(tc, mul_15);
  // tcase_add_test(tc, mul_16);
  tcase_add_test(tc, mul_17);
  tcase_add_test(tc, mul_19);

  /*Serzhunya*/

  tcase_add_test(tc, mul_test_1);
  tcase_add_test(tc, mul_test_2);
  tcase_add_test(tc, mul_test_3);
  tcase_add_test(tc, mul_test_4);
  tcase_add_test(tc, mul_test_5);
  tcase_add_test(tc, mul_test_6);
  tcase_add_test(tc, mul_test_7);
  tcase_add_test(tc, mul_test_8);
  tcase_add_test(tc, mul_test_9);
  tcase_add_test(tc, mul_test_10);
  tcase_add_test(tc, mul_test_11);
  tcase_add_test(tc, mul_test_12);
  tcase_add_test(tc, mul_test_13);
  tcase_add_test(tc, mul_test_14);
  // tcase_add_test(tc, mul_test_15);
  // tcase_add_test(tc, mul_test_16);
  tcase_add_test(tc, test_mul_fail_1);
  tcase_add_test(tc, test_mul_fail_2);
  tcase_add_test(tc, test_mul_fail_3);
  tcase_add_test(tc, test_mul_fail_4);
  tcase_add_test(tc, test_mul_fail_5);
  tcase_add_test(tc, test_mul_fail_6);
  tcase_add_test(tc, test_mul_fail_7);
  tcase_add_test(tc, test_mul_fail_8);
  tcase_add_test(tc, test_mul_fail_9);
  tcase_add_test(tc, test_mul_fail_10);
  tcase_add_test(tc, test_mul_fail_11);
  tcase_add_test(tc, test_mul_fail_12);
  tcase_add_test(tc, test_mul_fail_13);
  tcase_add_test(tc, test_mul_fail_14);
  tcase_add_test(tc, test_mul_fail_15);
  tcase_add_test(tc, test_mul_fail_16);
  tcase_add_test(tc, test_mul_fail_17);
  /*Serzhunya*/

  suite_add_tcase(s, tc);
  return s;
}