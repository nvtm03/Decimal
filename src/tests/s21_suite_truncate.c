#include "../tests.h"

START_TEST(simple_truncate) {
  // -39.104096094745301845239149102
  // 01111110 01011010 00100110 01110000
  // 11110011 01000010 11100010 00010000
  // 00001010 10100100 00110010 00101110
  // 10000000 00011011 00000000 00000000
  s21_decimal dec;
  clear_s21_decimal(&dec);
  dec.bits[0] = 178532910;
  dec.bits[1] = 4081246736;
  dec.bits[2] = 2119837296;
  dec.bits[3] = 2149253120;

  s21_decimal ans;
  clear_s21_decimal(&ans);

  // -39
  // 00000000 00000000 00000000 00000000
  // 00000000 00000000 00000000 00000000
  // 00000000 00000000 00000000 00100111
  // 10000000 00000000 00000000 00000000
  s21_decimal true_ans;
  clear_s21_decimal(&true_ans);
  true_ans.bits[0] = 39;
  true_ans.bits[3] = MINUS_SIGN;

  int status = s21_truncate(dec, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(simple_truncate_2) {
  s21_decimal dec;
  clear_s21_decimal(&dec);
  // 613478.421
  dec.bits[0] = 613478421;
  dec.bits[3] = 196608;  // точка после третьего знака
  s21_decimal ans;
  clear_s21_decimal(&ans);

  s21_decimal true_ans;
  clear_s21_decimal(&true_ans);
  true_ans.bits[0] = 613478;

  int status = s21_truncate(dec, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(zero_truncate) {
  s21_decimal dec;
  clear_s21_decimal(&dec);
  dec.bits[0] = 0;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = 196608;

  s21_decimal ans;
  clear_s21_decimal(&ans);

  s21_decimal true_ans;
  clear_s21_decimal(&true_ans);
  true_ans.bits[0] = 0;

  int status = s21_truncate(dec, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(part1_truncate_zero) {
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 0);
  ck_assert_int_eq(get_exp_for_decimal(result), 0);

  set_bit(&value_1, index_sign_bit, 1);
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 1);
  ck_assert_int_eq(get_exp_for_decimal(result), 0);
}
END_TEST

START_TEST(part2_truncate_zero_pow) {
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  test.bits[0] = 0;
  set_exp_for_decimal(&value_1, 21);
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 0);
  ck_assert_int_eq(get_exp_for_decimal(result), 0);

  set_bit(&value_1, index_sign_bit, 1);
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 1);
  ck_assert_int_eq(get_exp_for_decimal(result), 0);
}
END_TEST

START_TEST(part3_truncate_one) {
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 1;
  test.bits[0] = 1;
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 0);
  ck_assert_int_eq(get_exp_for_decimal(result), 0);

  set_bit(&value_1, index_sign_bit, 1);
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 1);
  ck_assert_int_eq(get_exp_for_decimal(result), 0);
}
END_TEST

START_TEST(part4_truncate_num1) {
  s21_decimal value_1 = {{422142, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{422142, 0, 0, 0}};
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 0);
  ck_assert_int_eq(get_exp_for_decimal(result), 0);

  set_bit(&value_1, index_sign_bit, 1);
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 1);
  ck_assert_int_eq(get_exp_for_decimal(result), 0);
}
END_TEST

START_TEST(part5_truncate_num2) {
  s21_decimal value_1 = {{422142, 0, 422142, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{422142, 0, 422142, 0}};
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[2], test.bits[2]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 0);
  ck_assert_int_eq(get_exp_for_decimal(result), 0);

  set_bit(&value_1, index_sign_bit, 1);
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[2], test.bits[2]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 1);
  ck_assert_int_eq(get_exp_for_decimal(result), 0);
}
END_TEST

START_TEST(part6_truncate_pow1) {
  s21_decimal value_1 = {{422142, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{422, 0, 0, 0}};
  set_exp_for_decimal(&value_1, 3);
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 0);
  ck_assert_int_eq(get_exp_for_decimal(result), 0);

  set_bit(&value_1, index_sign_bit, 1);
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 1);
  ck_assert_int_eq(get_exp_for_decimal(result), 0);
}
END_TEST

START_TEST(part7_truncate_pow2) {
  s21_decimal value_1 = {{422142, 422142, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{609885778, 422, 0, 0}};
  set_exp_for_decimal(&value_1, 3);
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[1], test.bits[1]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 0);
  ck_assert_int_eq(get_exp_for_decimal(result), 0);

  set_bit(&value_1, index_sign_bit, 1);
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[1], test.bits[1]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 1);
  ck_assert_int_eq(get_exp_for_decimal(result), 0);
}
END_TEST

START_TEST(part8_truncate_pow3) {
  s21_decimal value_1 = {{422142, 422142, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{181308, 0, 0, 0}};
  set_exp_for_decimal(&value_1, 10);
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[1], test.bits[1]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 0);
  ck_assert_int_eq(get_exp_for_decimal(result), 0);

  set_bit(&value_1, index_sign_bit, 1);
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[1], test.bits[1]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 1);
  ck_assert_int_eq(get_exp_for_decimal(result), 0);
}
END_TEST

Suite* truncate_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("truncate");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, simple_truncate);
  tcase_add_test(tc_core, simple_truncate_2);
  tcase_add_test(tc_core, zero_truncate);
  tcase_add_test(tc_core, part1_truncate_zero);
  tcase_add_test(tc_core, part2_truncate_zero_pow);
  tcase_add_test(tc_core, part3_truncate_one);
  tcase_add_test(tc_core, part4_truncate_num1);
  tcase_add_test(tc_core, part5_truncate_num2);
  tcase_add_test(tc_core, part6_truncate_pow1);
  tcase_add_test(tc_core, part7_truncate_pow2);
  tcase_add_test(tc_core, part8_truncate_pow3);
  suite_add_tcase(s, tc_core);

  return s;
}