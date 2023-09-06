#include "../tests.h"

START_TEST(s21_negate_1) {
  s21_decimal dec;
  s21_decimal ans;
  clear_s21_decimal(&dec);
  dec.bits[0] = 2814903;
  dec.bits[3] = 65536 + MINUS_SIGN;

  s21_decimal true_ans;
  clear_s21_decimal(&true_ans);
  true_ans.bits[0] = 2814903;
  true_ans.bits[3] = 65536;

  int status = s21_negate(dec, &ans);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(s21_negate_2) {
  s21_decimal dec;
  s21_decimal ans;
  clear_s21_decimal(&dec);
  dec.bits[0] = 2814903;
  dec.bits[1] = 2384901;
  dec.bits[2] = 27498;
  dec.bits[3] = 0;

  s21_decimal true_ans;
  clear_s21_decimal(&true_ans);
  true_ans.bits[0] = 2814903;
  true_ans.bits[1] = 2384901;
  true_ans.bits[2] = 27498;
  true_ans.bits[3] = MINUS_SIGN;

  int status = s21_negate(dec, &ans);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(part1_negate_zero) {
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  s21_negate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 1);
}
END_TEST

START_TEST(part2_negate_zero_signed) {
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  //set_sign(&value_1, 1);
  set_bit(&value_1, index_sign_bit, 1);
  s21_negate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 0);
}
END_TEST

START_TEST(part3_negate_one) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{1, 0, 0, 0}};
  // set_sign(&test, 1);
  s21_negate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 1);
}
END_TEST

START_TEST(part4_negate_one_signed) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{1, 0, 0, 0}};
  //set_sign(&value_1, 1);
  set_bit(&value_1, index_sign_bit, 1);
  s21_negate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 0);
}
END_TEST

START_TEST(part5_negate_num) {
  s21_decimal value_1 = {{422142, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{422142}};
  s21_negate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 1);
}
END_TEST

START_TEST(part6_negate_num_signed) {
  s21_decimal value_1 = {{422142, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{422142, 0, 0, 0}};
  //set_sign(&value_1, 1);
  set_bit(&value_1, index_sign_bit, 1);
  s21_negate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 0);
}
END_TEST

START_TEST(part7_negate_pow) {
  s21_decimal value_1 = {{422142, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{422142, 0, 0, 0}};
  //set_pow(value_1, &value_1, 2);
  set_exp_for_decimal(&value_1, 2);
  s21_negate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 1);
  ck_assert_int_eq(get_exp_for_decimal(result), 2);
}
END_TEST

START_TEST(part8_negate_pow_signed) {
  s21_decimal value_1 = {{422142, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{422142, 0, 0, 0}};
  //set_sign(&value_1, 1);
  set_bit(&value_1, index_sign_bit, 1);
  //set_pow(value_1, &value_1, 2);
  set_exp_for_decimal(&value_1, 2);
  s21_negate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 0);
  ck_assert_int_eq(get_exp_for_decimal(result), 2);
}
END_TEST


Suite* negate_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("negate");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_negate_1);
  tcase_add_test(tc_core, s21_negate_2);
  tcase_add_test(tc_core, part1_negate_zero);
  tcase_add_test(tc_core, part2_negate_zero_signed);
  tcase_add_test(tc_core, part3_negate_one);
  tcase_add_test(tc_core, part4_negate_one_signed);
  tcase_add_test(tc_core, part5_negate_num);
  tcase_add_test(tc_core, part6_negate_num_signed);
  tcase_add_test(tc_core, part7_negate_pow);
  tcase_add_test(tc_core, part8_negate_pow_signed);
  suite_add_tcase(s, tc_core);

  return s;
}