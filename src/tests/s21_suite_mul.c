#include "../tests.h"

START_TEST(mul_0) {
  // 15 * 25 = 375
  s21_decimal decimal;
  s21_decimal decimal2;
  s21_decimal decimal3;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&decimal2);
  clear_s21_decimal(&decimal3);
  int true_result_status = 0;
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000001111
  decimal.bits[0] = 15;

  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000011001
  decimal2.bits[0] = 25;
  int our_result_status = s21_mul(decimal, decimal2, &decimal3);
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000101110111
  ck_assert_int_eq(decimal3.bits[0], 375);
  ck_assert_int_eq(decimal3.bits[1], 0);
  ck_assert_int_eq(decimal3.bits[2], 0);
  ck_assert_int_eq(decimal3.bits[3], 0);
  ck_assert_int_eq(our_result_status, true_result_status);
}
END_TEST

START_TEST(mul_1) {
  // 15 * -25 = -375
  s21_decimal decimal;
  s21_decimal decimal2;
  s21_decimal decimal3;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&decimal2);
  clear_s21_decimal(&decimal3);
  int true_result_status = 0;
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000001111
  decimal.bits[0] = 15;

  // 1000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000011001
  decimal2.bits[0] = 25;
  decimal2.bits[3] = MINUS_SIGN;
  int our_result_status = s21_mul(decimal, decimal2, &decimal3);
  // 1000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000101110111
  ck_assert_int_eq(decimal3.bits[0], 375);
  ck_assert_int_eq(decimal3.bits[1], 0);
  ck_assert_int_eq(decimal3.bits[2], 0);
  ck_assert_int_eq(decimal3.bits[3], MINUS_SIGN);
  ck_assert_int_eq(our_result_status, true_result_status);
}
END_TEST

START_TEST(mul_2) {
  //-15 * -25 = 375
  s21_decimal decimal;
  s21_decimal decimal2;
  s21_decimal decimal3;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&decimal2);
  clear_s21_decimal(&decimal3);
  int true_result_status = 0;
  // 1000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000001111
  decimal.bits[0] = 15;
  decimal.bits[3] = MINUS_SIGN;
  // 1000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000011001
  decimal2.bits[0] = 25;
  decimal2.bits[3] = MINUS_SIGN;
  int our_result_status = s21_mul(decimal, decimal2, &decimal3);
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000101110111
  ck_assert_int_eq(decimal3.bits[0], 375);
  ck_assert_int_eq(decimal3.bits[1], 0);
  ck_assert_int_eq(decimal3.bits[2], 0);
  ck_assert_int_eq(decimal3.bits[3], 0);
  ck_assert_int_eq(our_result_status, true_result_status);
}
END_TEST

START_TEST(mul_3) {
  // 0.015 * 0.0000025 = 0.0000000375
  s21_decimal decimal;
  s21_decimal decimal2;
  s21_decimal decimal3;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&decimal2);
  clear_s21_decimal(&decimal3);
  int true_result_status = 0;
  // 0000000000000011 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000001111
  decimal.bits[0] = 15;
  decimal.bits[3] = 196608;
  // 0000000000000111 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000011001
  decimal2.bits[0] = 25;
  decimal2.bits[3] = 458752;
  int our_result_status = s21_mul(decimal, decimal2, &decimal3);
  // 0000000000001010 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000101110111
  ck_assert_int_eq(decimal3.bits[0], 375);
  ck_assert_int_eq(decimal3.bits[1], 0);
  ck_assert_int_eq(decimal3.bits[2], 0);
  ck_assert_int_eq(decimal3.bits[3], 655360);
  ck_assert_int_eq(our_result_status, true_result_status);
}
END_TEST

START_TEST(mul_4) {
  // 0.0000000375 * 0.0000000375 = 0.00000000000000140625
  s21_decimal decimal;
  s21_decimal decimal2;
  s21_decimal decimal3;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&decimal2);
  clear_s21_decimal(&decimal3);
  int true_result_status = 0;
  // 0000000000001010 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000101110111
  decimal.bits[0] = 375;
  decimal.bits[3] = 655360;
  // 0000000000001010 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000101110111
  decimal2.bits[0] = 375;
  decimal2.bits[3] = 655360;
  int our_result_status = s21_mul(decimal, decimal2, &decimal3);
  // 0000000000010100 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000010 0010010101010001
  ck_assert_int_eq(decimal3.bits[0], 140625);
  ck_assert_int_eq(decimal3.bits[1], 0);
  ck_assert_int_eq(decimal3.bits[2], 0);
  ck_assert_int_eq(decimal3.bits[3], 1310720);
  ck_assert_int_eq(our_result_status, true_result_status);
}
END_TEST

START_TEST(mul_5) {
  // 2147483648 * 2 = 4294967296
  s21_decimal decimal;
  s21_decimal decimal2;
  s21_decimal decimal3;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&decimal2);
  clear_s21_decimal(&decimal3);
  int true_result_status = 0;
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  1000000000000000 0000000000000000
  decimal.bits[0] = 2147483648;
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000010
  decimal2.bits[0] = 2;
  int our_result_status = s21_mul(decimal, decimal2, &decimal3);
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000001  0000000000000000 0000000000000000
  ck_assert_int_eq(decimal3.bits[0], 0);
  ck_assert_int_eq(decimal3.bits[1], 1);
  ck_assert_int_eq(decimal3.bits[2], 0);
  ck_assert_int_eq(decimal3.bits[3], 0);
  ck_assert_int_eq(our_result_status, true_result_status);
}
END_TEST

START_TEST(mul_6) {
  // 2147483648 * 3 = 6442450944
  s21_decimal decimal;
  s21_decimal decimal2;
  s21_decimal decimal3;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&decimal2);
  clear_s21_decimal(&decimal3);
  int true_result_status = 0;
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  1000000000000000 0000000000000000
  decimal.bits[0] = 2147483648;
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000011
  decimal2.bits[0] = 3;
  int our_result_status = s21_mul(decimal, decimal2, &decimal3);
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000001  1000000000000000 0000000000000000
  ck_assert_int_eq(decimal3.bits[0], 2147483648);
  ck_assert_int_eq(decimal3.bits[1], 1);
  ck_assert_int_eq(decimal3.bits[2], 0);
  ck_assert_int_eq(decimal3.bits[3], 0);
  ck_assert_int_eq(our_result_status, true_result_status);
}
END_TEST

START_TEST(mul_7) {
  // 39614081257132168796771975168 * 10
  s21_decimal decimal;
  s21_decimal decimal2;
  s21_decimal decimal3;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&decimal2);
  clear_s21_decimal(&decimal3);
  int true_result_status = 1;
  // 0000000000000000 0000000000000000  1000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  decimal.bits[2] = 2147483648;
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000001010
  decimal2.bits[0] = 10;
  int our_result_status = s21_mul(decimal, decimal2, &decimal3);
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000001  1000000000000000 0000000000000000
  ck_assert_int_eq(our_result_status, true_result_status);
}
END_TEST

START_TEST(mul_8) {
  // very small numbers ???????
  s21_decimal decimal;
  s21_decimal decimal2;
  s21_decimal decimal3;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&decimal2);
  clear_s21_decimal(&decimal3);
  int true_result_status = 2;
  // 0000000000011100 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000001
  decimal.bits[0] = 1;
  decimal.bits[3] = 1835008;  // 10^-28
  // 0000000000011100 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000101
  decimal2.bits[0] = 5;
  decimal2.bits[3] = 524288;  // 5*10^-8

  int our_result_status = s21_mul(decimal, decimal2, &decimal3);
  ck_assert_int_eq(our_result_status, true_result_status);
}
END_TEST

// mult
START_TEST(part1_mult_value_1_is_one) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 1;
  value_2.bits[0] = 10;
  test.bits[0] = 10;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  set_bit(&value_1, index_sign_bit, 1);
  memset(&result, 0, sizeof(s21_decimal));
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_bit(result, index_sign_bit), 1);
}
END_TEST

START_TEST(part1_mult_value_2_is_one) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 15;
  value_2.bits[0] = 1;
  test.bits[0] = 15;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
}
END_TEST

START_TEST(part1_mult_value_1_is_zero) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 0;
  value_2.bits[0] = 100;
  test.bits[0] = 0;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
}
END_TEST

START_TEST(part1_mult_value_2_is_zero) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 7;
  value_2.bits[0] = 0;
  test.bits[0] = 0;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
}
END_TEST

START_TEST(part1_mult_max) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 5;
  int res = s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(res, 1);
  set_bit(&value_2, index_sign_bit, 1);
  res = s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(res, 2);
}
END_TEST

START_TEST(part1_mult_big_power) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 2147483647;
  value_2.bits[0] = 255;
  test.bits[0] = 2147483393;
  test.bits[1] = 127;
  set_exp_for_decimal(&value_2, 10);
  int res = s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[1], test.bits[1]);
  ck_assert_uint_eq(get_exp_for_decimal(result), 10);
  ck_assert_uint_eq(get_bit(result, index_sign_bit), 0);
  ck_assert_uint_eq(res, 0);
}
END_TEST

START_TEST(part1_mult_big_negative_over) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 2147483647;
  value_1.bits[1] = 2147483647;
  value_1.bits[2] = 2147483647;
  value_2.bits[0] = 15;
  //set_pow(value_2, &value_2, 1);
  set_exp_for_decimal(&value_2, 1);
  //set_sign(&value_2, 1);
  set_bit(&value_2, index_sign_bit, 1);
  int res = s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(res, 2);
}
END_TEST

START_TEST(part1_mult_big_over) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 2147483647;
  value_1.bits[1] = 2147483647;
  value_1.bits[2] = 2147483647;
  value_2.bits[0] = 15;
  //set_pow(value_2, &value_2, 1);
  set_exp_for_decimal(&value_2, 1);
  int res = s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(res, 1);
}
END_TEST

START_TEST(part1_mult_value_1_is_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  //set_sign(&value_1, 1);
  set_bit(&value_1, index_sign_bit, 1);
  //get_bit(result, index_sign_bit)
  value_1.bits[0] = 15;
  value_2.bits[0] = 1;
  test.bits[0] = 15;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_bit(result, index_sign_bit), 1);
}
END_TEST

START_TEST(part1_mult_value_2_is_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 15;
  //set_sign(&value_2, 1);
  set_bit(&value_2, index_sign_bit, 1);
  //get_bit(result, index_sign_bit)
  value_2.bits[0] = 1;
  test.bits[0] = 15;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_bit(result, index_sign_bit), 1);
}
END_TEST

START_TEST(part1_mult_value_1_is_zero_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  //set_sign(&value_1, 1);
  set_bit(&value_1, index_sign_bit, 1);
  //get_bit(result, index_sign_bit)
  value_1.bits[0] = 0;
  value_2.bits[0] = 100;
  test.bits[0] = 0;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_bit(result, index_sign_bit), 1);
}
END_TEST

START_TEST(part1_mult_value_2_is_zero_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 7;
  //set_sign(&value_2, 1);
  set_bit(&value_2, index_sign_bit, 1);
  //get_bit(result, index_sign_bit)
  value_2.bits[0] = 0;
  test.bits[0] = 0;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_bit(result, index_sign_bit), 1);
}
END_TEST

START_TEST(part1_mult_value_1_2_is_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  // set_sign(&value_1, 1);
  // set_sign(&value_2, 1);
  set_bit(&value_1, index_sign_bit, 1);
  set_bit(&value_2, index_sign_bit, 1);
  //get_bit(result, index_sign_bit)
  value_1.bits[0] = 0;
  value_2.bits[0] = 100;
  test.bits[0] = 0;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_bit(result, index_sign_bit), 0);
  // set_pow(value_1, &value_1, 5);
  // set_pow(value_2, &value_2, 29);
  set_exp_for_decimal(&value_1, 5);
  set_exp_for_decimal(&value_2, 29);
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
}
END_TEST

Suite *suite_s21_mul(void) {
  Suite *s23;
  TCase *tc23;
  s23 = suite_create("s21_MUL");
  tc23 = tcase_create("case_MUL");
  tcase_add_test(tc23, mul_0);
  tcase_add_test(tc23, mul_1);
  tcase_add_test(tc23, mul_2);
  tcase_add_test(tc23, mul_3);
  tcase_add_test(tc23, mul_4);
  tcase_add_test(tc23, mul_5);
  tcase_add_test(tc23, mul_6);
  tcase_add_test(tc23, mul_7);
  tcase_add_test(tc23, mul_8);


  tcase_add_test(tc23, part1_mult_value_1_is_one);
  tcase_add_test(tc23, part1_mult_value_2_is_one);
  tcase_add_test(tc23, part1_mult_value_1_is_zero);
  tcase_add_test(tc23, part1_mult_value_2_is_zero);
  tcase_add_test(tc23, part1_mult_max);
  tcase_add_test(tc23, part1_mult_big_power);
  tcase_add_test(tc23, part1_mult_big_negative_over);
  tcase_add_test(tc23, part1_mult_big_over);
  tcase_add_test(tc23, part1_mult_value_1_is_minus);
  tcase_add_test(tc23, part1_mult_value_2_is_minus);
  tcase_add_test(tc23, part1_mult_value_1_is_zero_minus);
  tcase_add_test(tc23, part1_mult_value_2_is_zero_minus);
  tcase_add_test(tc23, part1_mult_value_1_2_is_minus);
  suite_add_tcase(s23, tc23);
  return s23;
}


