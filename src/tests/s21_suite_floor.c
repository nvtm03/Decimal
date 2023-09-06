#include "../tests.h"

START_TEST(simple_floor) {
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

  // -40
  s21_decimal true_ans;
  clear_s21_decimal(&true_ans);
  true_ans.bits[0] = 40;
  true_ans.bits[3] = MINUS_SIGN;

  int status = s21_floor(dec, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(simple_floor_2) {
  // 0.91275848761238746318274123
  // 00000000 01001011 10000000 01101001
  // 10101101 00010110 00101101 10111100
  // 00100011 10110000 01111110 01001011
  // 00000000 00011010 00000000 00000000
  s21_decimal dec;
  clear_s21_decimal(&dec);
  dec.bits[0] = 598769227;
  dec.bits[1] = 2903911868;
  dec.bits[2] = 4948073;
  dec.bits[3] = 1703936;

  s21_decimal ans;
  clear_s21_decimal(&ans);

  s21_decimal true_ans;
  clear_s21_decimal(&true_ans);
  true_ans.bits[0] = 0;
  int status = s21_floor(dec, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(simple_floor_3) {
  // -0.91275848761238746318274123
  // 00000000 01001011 10000000 01101001
  // 10101101 00010110 00101101 10111100
  // 00100011 10110000 01111110 01001011
  // 10000000 00011010 00000000 00000000
  s21_decimal dec;
  clear_s21_decimal(&dec);
  dec.bits[0] = 598769227;
  dec.bits[1] = 2903911868;
  dec.bits[2] = 4948073;
  dec.bits[3] = 1703936 + MINUS_SIGN;

  s21_decimal ans;
  clear_s21_decimal(&ans);

  s21_decimal true_ans;
  clear_s21_decimal(&true_ans);
  true_ans.bits[0] = 1;
  true_ans.bits[3] = MINUS_SIGN;
  int status = s21_floor(dec, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(simple_floor_4) {
  // -263814.1627387128
  // 00000000 00001001 01011111 01100000
  // 00110110 10010001 01001100 11111000
  // 10000000 00001010 00000000 00000000
  s21_decimal dec;
  clear_s21_decimal(&dec);
  dec.bits[0] = 915492088;
  dec.bits[1] = 614240;
  dec.bits[3] = 655360 + MINUS_SIGN;

  s21_decimal ans;
  clear_s21_decimal(&ans);

  s21_decimal true_ans;
  clear_s21_decimal(&true_ans);
  true_ans.bits[0] = 263815;
  true_ans.bits[3] = MINUS_SIGN;
  int status = s21_floor(dec, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(math_floor) {
  // 0.49999999999999999
  // 00000000 10110001 10100010 10111100
  // 00101110 11000100 11111111 11111111
  // 00000000 00010001 00000000 00000000
  s21_decimal dec;
  clear_s21_decimal(&dec);
  dec.bits[0] = 784662527;
  dec.bits[1] = 11641532;
  dec.bits[3] = 1114112;

  s21_decimal ans;
  clear_s21_decimal(&ans);

  s21_decimal true_ans;
  clear_s21_decimal(&true_ans);
  true_ans.bits[0] = 0;
  int status = s21_floor(dec, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(floor_on_int) {
  // -2179
  s21_decimal dec;
  clear_s21_decimal(&dec);
  dec.bits[0] = 2179;
  dec.bits[3] = MINUS_SIGN;

  s21_decimal ans;
  clear_s21_decimal(&ans);

  s21_decimal true_ans;
  clear_s21_decimal(&true_ans);
  true_ans.bits[0] = 2179;
  true_ans.bits[3] = MINUS_SIGN;
  int status = s21_floor(dec, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(part1_floor_zero) {
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  //set_pow(value_1, &value_1, 1);
  set_exp_for_decimal(&value_1, 1);
  s21_floor(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 0);
  ck_assert_int_eq(get_exp_for_decimal(result), 0);

  //set_sign(&value_1, 1);
  set_bit(&value_1, index_sign_bit, 1);
  s21_floor(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 1);
  ck_assert_int_eq(get_exp_for_decimal(result), 0);
}
END_TEST

START_TEST(part2_floor_one) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{1, 0, 0, 0}};
  s21_floor(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 0);
  ck_assert_int_eq(get_exp_for_decimal(result), 0);

  //set_sign(&value_1, 1);
  set_bit(&value_1, index_sign_bit, 1);
  s21_floor(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 1);
  ck_assert_int_eq(get_exp_for_decimal(result), 0);
}
END_TEST

START_TEST(part3_floor_num) {
  s21_decimal value_1 = {{422142, 0, 422142, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{422142, 0, 422142, 0}};
  s21_floor(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[2], test.bits[2]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 0);
  ck_assert_int_eq(get_exp_for_decimal(result), 0);

  //set_sign(&value_1, 1);
  set_bit(&value_1, index_sign_bit, 1);
  s21_floor(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[2], test.bits[2]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 1);
  ck_assert_int_eq(get_exp_for_decimal(result), 0);
}
END_TEST

START_TEST(part4_floor_pow1) {
  s21_decimal value_1 = {{422142, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{422, 0, 0, 0}};
  //set_pow(value_1, &value_1, 3);
  set_exp_for_decimal(&value_1, 3);
  s21_floor(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 0);
  ck_assert_int_eq(get_exp_for_decimal(result), 0);

  test.bits[0] = 423;
  //set_sign(&value_1, 1);
  set_bit(&value_1, index_sign_bit, 1);
  s21_floor(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 1);
  ck_assert_int_eq(get_exp_for_decimal(result), 0);
}
END_TEST

START_TEST(part5_floor_pow2) {
  s21_decimal value_1 = {{422142, 422142, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{609885778, 422, 0, 0}};
  //set_pow(value_1, &value_1, 3);
  set_exp_for_decimal(&value_1, 3);
  s21_floor(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[1], test.bits[1]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 0);
  ck_assert_int_eq(get_exp_for_decimal(result), 0);

  test.bits[0] = 609885779;
  //set_sign(&value_1, 1);
  set_bit(&value_1, index_sign_bit, 1);
  s21_floor(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[1], test.bits[1]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 1);
  ck_assert_int_eq(get_exp_for_decimal(result), 0);
}
END_TEST

START_TEST(part6_floor_pow3) {
  s21_decimal value_1 = {{422942, 422142, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{181308, 422, 0, 0}};
  //set_pow(value_1, &value_1, 10);
  set_exp_for_decimal(&value_1, 10);
  s21_floor(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 0);
  ck_assert_int_eq(get_exp_for_decimal(result), 0);

  test.bits[0] = 181309;
  //set_sign(&value_1, 1);
  set_bit(&value_1, index_sign_bit, 1);
  s21_floor(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_bit(result, index_sign_bit), 1);
  ck_assert_int_eq(get_exp_for_decimal(result), 0);
}
END_TEST

Suite* floor_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("floor");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, simple_floor);
  tcase_add_test(tc_core, simple_floor_2);
  tcase_add_test(tc_core, simple_floor_3);
  tcase_add_test(tc_core, simple_floor_4);
  tcase_add_test(tc_core, math_floor);
  tcase_add_test(tc_core, floor_on_int);
  tcase_add_test(tc_core, part1_floor_zero);
  tcase_add_test(tc_core, part2_floor_one);
  tcase_add_test(tc_core, part3_floor_num);
  tcase_add_test(tc_core, part4_floor_pow1);
  tcase_add_test(tc_core, part5_floor_pow2);
  tcase_add_test(tc_core, part6_floor_pow3);
  suite_add_tcase(s, tc_core);

  return s;
}