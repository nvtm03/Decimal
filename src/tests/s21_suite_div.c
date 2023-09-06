#include "../tests.h"

START_TEST(div_0) {
  // 6 / 3 = 2
  s21_decimal decimal;
  s21_decimal decimal2;
  s21_decimal decimal3;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&decimal2);
  clear_s21_decimal(&decimal3);
  int true_result_status = 0;
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000110
  decimal.bits[0] = 6;

  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000011
  decimal2.bits[0] = 3;
  int our_result_status = s21_div(decimal, decimal2, &decimal3);
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000010
  ck_assert_int_eq(decimal3.bits[0], 2);
  ck_assert_int_eq(decimal3.bits[1], 0);
  ck_assert_int_eq(decimal3.bits[2], 0);
  ck_assert_int_eq(decimal3.bits[3], 0);
  ck_assert_int_eq(our_result_status, true_result_status);
}
END_TEST

START_TEST(div_1) {
  // 4294967296 / 2 = 2147483648
  s21_decimal decimal;
  s21_decimal decimal2;
  s21_decimal decimal3;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&decimal2);
  clear_s21_decimal(&decimal3);
  int true_result_status = 0;
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000001  0000000000000000 0000000000000000
  decimal.bits[1] = 1;

  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000010
  decimal2.bits[0] = 2;
  int our_result_status = s21_div(decimal, decimal2, &decimal3);
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 1000000000000000
  ck_assert_int_eq(decimal3.bits[0], 2147483648);
  ck_assert_int_eq(decimal3.bits[1], 0);
  ck_assert_int_eq(decimal3.bits[2], 0);
  ck_assert_int_eq(decimal3.bits[3], 0);
  ck_assert_int_eq(our_result_status, true_result_status);
}
END_TEST

START_TEST(div_2) {
  // 4294967296 / 3 = 1431655765
  s21_decimal decimal;
  s21_decimal decimal2;
  s21_decimal decimal3;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&decimal2);
  clear_s21_decimal(&decimal3);
  int true_result_status = 0;
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000001  0000000000000000 0000000000000000
  decimal.bits[1] = 1;

  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000011
  decimal2.bits[0] = 3;
  int our_result_status = s21_div(decimal, decimal2, &decimal3);
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  1010101010101010 101010101010101
  ck_assert_int_eq(decimal3.bits[0], 1431655765);
  ck_assert_int_eq(decimal3.bits[1], 2202883413);
  ck_assert_int_eq(decimal3.bits[2], 776102145);
  ck_assert_int_eq(decimal3.bits[3], 1245184);
  ck_assert_int_eq(our_result_status, true_result_status);
}
END_TEST

START_TEST(div_3) {
  // 429496729.6 / 2 = 21474836.48
  s21_decimal decimal;
  s21_decimal decimal2;
  s21_decimal decimal3;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&decimal2);
  clear_s21_decimal(&decimal3);
  int true_result_status = 0;
  // 0000000000000001 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000001  0000000000000000 0000000000000000
  decimal.bits[1] = 1;
  decimal.bits[3] = 65536;

  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000010
  decimal2.bits[0] = 2;
  int our_result_status = s21_div(decimal, decimal2, &decimal3);
  // 0000000000000010 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  1000000000000000 0000000000000000
  ck_assert_int_eq(decimal3.bits[0], 2147483648);
  ck_assert_int_eq(decimal3.bits[1], 0);
  ck_assert_int_eq(decimal3.bits[2], 0);
  ck_assert_int_eq(decimal3.bits[3], 65536);
  ck_assert_int_eq(our_result_status, true_result_status);
}
END_TEST

START_TEST(div_4) {
  // 3 / 5 = 0.6
  s21_decimal decimal;
  s21_decimal decimal2;
  s21_decimal decimal3;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&decimal2);
  clear_s21_decimal(&decimal3);
  int true_result_status = 0;
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000011
  decimal.bits[0] = 3;

  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000101
  decimal2.bits[0] = 5;
  int our_result_status = s21_div(decimal, decimal2, &decimal3);
  // 0000000000000001 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000110
  ck_assert_int_eq(decimal3.bits[0], 6);
  ck_assert_int_eq(decimal3.bits[1], 0);
  ck_assert_int_eq(decimal3.bits[2], 0);
  ck_assert_int_eq(decimal3.bits[3], 65536);
  ck_assert_int_eq(our_result_status, true_result_status);
}
END_TEST

START_TEST(div_5) {
  // 1 / 3 = 0.3333333333333333333333333333
  s21_decimal decimal;
  s21_decimal decimal2;
  s21_decimal decimal3;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&decimal2);
  clear_s21_decimal(&decimal3);
  int true_result_status = 0;
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000001
  decimal.bits[0] = 1;

  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000011
  decimal2.bits[0] = 3;
  int our_result_status = s21_div(decimal, decimal2, &decimal3);
  // 0000000000011010 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000111111100 1010000001010101
  ck_assert_int_eq(decimal3.bits[0], 89478485);
  ck_assert_int_eq(decimal3.bits[1], 347537611);
  ck_assert_int_eq(decimal3.bits[2], 180700362);
  ck_assert_int_eq(decimal3.bits[3], 1835008);
  ck_assert_int_eq(our_result_status, true_result_status);
}
END_TEST

START_TEST(div_6) {
  // 2 / 3 = 0.6666666666666666666666666667
  s21_decimal decimal;
  s21_decimal decimal2;
  s21_decimal decimal3;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&decimal2);
  clear_s21_decimal(&decimal3);
  int true_result_status = 0;
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000010
  decimal.bits[0] = 2;

  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000011
  decimal2.bits[0] = 3;
  int our_result_status = s21_div(decimal, decimal2, &decimal3);
  // 0000000000011010 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000001111111001 0100000010101011
  ck_assert_int_eq(decimal3.bits[0], 178956971);
  ck_assert_int_eq(decimal3.bits[1], 695075222);
  ck_assert_int_eq(decimal3.bits[2], 361400724);
  ck_assert_int_eq(decimal3.bits[3], 1835008);
  ck_assert_int_eq(our_result_status, true_result_status);
}
END_TEST

START_TEST(div_7) {
  // -6/3
  s21_decimal decimal;
  s21_decimal decimal2;
  s21_decimal decimal3;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&decimal2);
  clear_s21_decimal(&decimal3);
  int true_result_status = 0;
  // 1000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000110
  decimal.bits[0] = 6;
  decimal.bits[3] = MINUS_SIGN;

  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000011
  decimal2.bits[0] = 3;
  int our_result_status = s21_div(decimal, decimal2, &decimal3);
  // 1000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000010
  ck_assert_int_eq(decimal3.bits[0], 2);
  ck_assert_int_eq(decimal3.bits[1], 0);
  ck_assert_int_eq(decimal3.bits[2], 0);
  ck_assert_int_eq(decimal3.bits[3], MINUS_SIGN);
  ck_assert_int_eq(our_result_status, true_result_status);
}
END_TEST


// === division === //
START_TEST(div_8) {
  s21_decimal value_1 = {{20, 0, 0, 0}};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {0};
  test.bits[0] = 10;
  set_bit(&value_1, 127, 0);
  set_bit(&value_2, 127, 1);
  int res = s21_div(value_1, value_2, &result);
  // dec_output(result);
  // printf("RES: %d\n", res);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_bit(result, 127), 1);
  ck_assert_uint_eq(get_exp_for_decimal(result), 0);
  ck_assert_uint_eq(res, 0);
}
END_TEST

START_TEST(div_9) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{3, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_10) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(3, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_11) {  // тут как по мне должно быть норм
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  set_bit(&val1, 127, 0);
  set_bit(&val2, 127, 0);
  // set_pow(val1, &val1, 1);
  // set_pow(val2, &val2, 3);
  set_exp_for_decimal(&val1, 1);
  set_exp_for_decimal(&val2, 3);
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_12) {
  s21_decimal value_1 = {{4, 0, 0, 0}};
  s21_decimal value_2 = {{4, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {0};
  // set_pow(value_1, &value_1, 0);
  // set_pow(value_2, &value_2, 3);
  set_exp_for_decimal(&value_1, 0);
  set_exp_for_decimal(&value_2, 3);
  test.bits[0] = 1000;
  int res = s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_bit(result, 127), 0);
  ck_assert_uint_eq(get_exp_for_decimal(result), 0);
  ck_assert_uint_eq(res, 0);
}
END_TEST

START_TEST(div_13) {  // делимое меньше нечётного делителя
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal value_2 = {{5, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal test = {{2, 0, 0, 65536}};
  int res = s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(s21_is_equal(result, test), 1);
  ck_assert_uint_eq(get_bit(result, 127), 0);
  ck_assert_uint_eq(res, 0);
}
END_TEST

START_TEST(div_14) {  // тест переполнения 1
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal value_2 = {{1, 0, 1, 2147483648}};
  s21_decimal result = {0};
  int res = s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(res, 0);
}
END_TEST



Suite *suite_s21_div(void) {
  Suite *s23;
  TCase *tc23;
  s23 = suite_create("s21_DIV");
  tc23 = tcase_create("case_DIV");
  tcase_add_test(tc23, div_0);
  tcase_add_test(tc23, div_1);
  tcase_add_test(tc23, div_2);
  tcase_add_test(tc23, div_3);
  tcase_add_test(tc23, div_4);
  tcase_add_test(tc23, div_5);
  tcase_add_test(tc23, div_6);
  tcase_add_test(tc23, div_7);
  tcase_add_test(tc23, div_8);
  tcase_add_test(tc23, div_9);
  tcase_add_test(tc23, div_10);
  tcase_add_test(tc23, div_11);
  tcase_add_test(tc23, div_12);
  tcase_add_test(tc23, div_13);
  tcase_add_test(tc23, div_14);

  suite_add_tcase(s23, tc23);
  return s23;
}