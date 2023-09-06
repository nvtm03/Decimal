#include "../tests.h"

START_TEST(is_equal_simple) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&second_decimal);
  int A = 5123;
  convertation_result status = s21_from_int_to_decimal(A, &decimal);
  convertation_result second_status =
      s21_from_int_to_decimal(A, &second_decimal);
  ck_assert_int_eq(1, s21_is_equal(decimal, second_decimal));
  ck_assert_int_eq(status, second_status);
}
END_TEST

START_TEST(is_equal_0_decimal) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&second_decimal);
  int A = 5123;
  s21_from_int_to_decimal(A, &decimal);
  ck_assert_int_eq(0, s21_is_equal(decimal, second_decimal));
}
END_TEST

START_TEST(is_not_equal) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&second_decimal);
  int A = 5123;
  int B = 5122;
  convertation_result status = s21_from_int_to_decimal(A, &decimal);
  convertation_result second_status =
      s21_from_int_to_decimal(B, &second_decimal);
  ck_assert_int_eq(status, second_status);
  ck_assert_int_eq(1, s21_is_not_equal(decimal, second_decimal));
}
END_TEST

START_TEST(is_not_equal_EQ) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&second_decimal);
  int A = -5123;
  convertation_result status = s21_from_int_to_decimal(A, &decimal);
  s21_from_int_to_decimal(A, &second_decimal);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(0, s21_is_not_equal(decimal, second_decimal));
}
END_TEST

START_TEST(is_not_equal_SIGN) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&second_decimal);
  int A = -5123;
  int B = 5123;
  convertation_result status = s21_from_int_to_decimal(A, &decimal);
  convertation_result second_status =
      s21_from_int_to_decimal(B, &second_decimal);
  ck_assert_int_eq(status, second_status);
  ck_assert_int_eq(1, s21_is_not_equal(decimal, second_decimal));
}
END_TEST

START_TEST(is_greater_le) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&second_decimal);
  int A = 5123;
  int B = -5123;
  convertation_result status = s21_from_int_to_decimal(A, &decimal);
  convertation_result second_status =
      s21_from_int_to_decimal(B, &second_decimal);
  ck_assert_int_eq(status, second_status);
  ck_assert_int_eq(0, s21_is_greater(second_decimal, decimal));
}
END_TEST

START_TEST(is_greater_stand) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&second_decimal);
  int A = -5123;
  int B = 5123;
  convertation_result status = s21_from_int_to_decimal(A, &decimal);
  convertation_result second_status =
      s21_from_int_to_decimal(B, &second_decimal);
  ck_assert_int_eq(status, second_status);
  ck_assert_int_eq(1, s21_is_greater(second_decimal, decimal));
}
END_TEST

START_TEST(is_greater_eq) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&second_decimal);
  int B = 5123;
  int A = B;
  convertation_result status = s21_from_int_to_decimal(A, &decimal);
  convertation_result second_status =
      s21_from_int_to_decimal(B, &second_decimal);
  ck_assert_int_eq(status, second_status);
  ck_assert_int_eq(1, s21_is_greater_or_equal(decimal, second_decimal));
}
END_TEST

START_TEST(is_greater_0) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&second_decimal);
  int A = 0;
  int B = 5123;
  convertation_result status = s21_from_int_to_decimal(A, &decimal);
  convertation_result second_status =
      s21_from_int_to_decimal(B, &second_decimal);
  ck_assert_int_eq(status, second_status);
  ck_assert_int_eq(0, s21_is_greater(decimal, second_decimal));
}
END_TEST

START_TEST(is_less_ne) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&second_decimal);
  int A = -5124;
  int B = -5123;
  convertation_result status = s21_from_int_to_decimal(A, &decimal);
  convertation_result second_status =
      s21_from_int_to_decimal(B, &second_decimal);
  ck_assert_int_eq(status, second_status);
  ck_assert_int_eq(1, s21_is_less(decimal, second_decimal));
}
END_TEST

START_TEST(is_less_equal) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&second_decimal);
  int B = 5123;
  int A = B;
  convertation_result status = s21_from_int_to_decimal(A, &decimal);
  convertation_result second_status =
      s21_from_int_to_decimal(B, &second_decimal);
  ck_assert_int_eq(status, second_status);
  ck_assert_int_eq(0, s21_is_less(decimal, second_decimal));
}
END_TEST

START_TEST(is_less_Classic) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&second_decimal);
  int A = 0;
  int B = 5123;
  convertation_result status = s21_from_int_to_decimal(A, &decimal);
  convertation_result second_status =
      s21_from_int_to_decimal(B, &second_decimal);
  ck_assert_int_eq(status, second_status);
  ck_assert_int_eq(1, s21_is_less(decimal, second_decimal));
}
END_TEST

START_TEST(is_less_or_equal_Classic) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&second_decimal);
  int B = 5123;
  int A = B;
  convertation_result status = s21_from_int_to_decimal(A, &decimal);
  convertation_result second_status =
      s21_from_int_to_decimal(B, &second_decimal);
  ck_assert_int_eq(status, second_status);
  ck_assert_int_eq(1, s21_is_less_or_equal(decimal, second_decimal));
}
END_TEST

START_TEST(is_less_or_equal_Norm) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&second_decimal);
  int B = 5123;
  int A = 51240;
  convertation_result status = s21_from_int_to_decimal(A, &decimal);
  convertation_result second_status =
      s21_from_int_to_decimal(B, &second_decimal);
  ck_assert_int_eq(status, second_status);
  ck_assert_int_eq(0, s21_is_less_or_equal(decimal, second_decimal));
}
END_TEST

//================= comparison functions tests =================
// === is_less === //
START_TEST(is_less_plus_both) {  // 1337 < 1338 == 1 yes
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1338, &num2);
  ck_assert_int_eq(1, s21_is_less(num1, num2));
}
END_TEST

START_TEST(is_less_min_num1) {  // -1337 < 1338 == 1 yes
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(-1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1338, &num2);
  ck_assert_int_eq(1, s21_is_less(num1, num2));
}
END_TEST

START_TEST(is_less_min_num2) {  // 1337 < -1338 == 0 no
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(-1338, &num2);
  ck_assert_int_eq(0, s21_is_less(num1, num2));
}
END_TEST

START_TEST(is_less_min_both) {  // -1337 < -1338 == 0 no
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(-1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(-1338, &num2);
  ck_assert_int_eq(0, s21_is_less(num1, num2));
}
END_TEST

// === is_greater === //
START_TEST(is_greater_plus_both) {  // 1337 > 1338 == 0 no
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1338, &num2);
  ck_assert_int_eq(0, s21_is_greater(num1, num2));
}
END_TEST

START_TEST(is_greater_min_num1) {  // -1337 > 1338 == 0 no
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(-1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1338, &num2);
  ck_assert_int_eq(0, s21_is_greater(num1, num2));
}
END_TEST

START_TEST(is_greater_min_num2) {  // 1337 > -1338 == 1 yes
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(-1338, &num2);
  ck_assert_int_eq(1, s21_is_greater(num1, num2));
}
END_TEST

START_TEST(is_greater_min_both) {  // -1337 > -1338 == 1 yes
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(-1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(-1338, &num2);
  ck_assert_int_eq(1, s21_is_greater(num1, num2));
}
END_TEST

// === is_less_or_equal === //
START_TEST(is_less_or_equal_num1_less) {  // 1337 <= 1338 == 1 yes
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1338, &num2);
  ck_assert_int_eq(1, s21_is_less_or_equal(num1, num2));
}
END_TEST

START_TEST(is_less_or_equal_num2_less) {  // 1338 <= 1337 == 0 no
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1338, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1337, &num2);
  ck_assert_int_eq(0, s21_is_less_or_equal(num1, num2));
}
END_TEST

START_TEST(is_less_or_equal_both_equal) {  // 1337 <= 1337 == 1 yes
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1337, &num2);
  ck_assert_int_eq(1, s21_is_less_or_equal(num1, num2));
}
END_TEST

// === is_greater_or_equal === //
START_TEST(is_greater_or_equal_num1_less) {  // 1337 >= 1338 == 0 no
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1338, &num2);
  ck_assert_int_eq(0, s21_is_greater_or_equal(num1, num2));
}
END_TEST

START_TEST(is_greater_or_equal_num2_less) {  // 1338 >= 1337 == 1 yes
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1338, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1337, &num2);
  ck_assert_int_eq(1, s21_is_greater_or_equal(num1, num2));
}
END_TEST

START_TEST(is_greater_or_equal_both_equal) {  // 1337 >= 1337 == 1 yes
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1337, &num2);
  ck_assert_int_eq(1, s21_is_greater_or_equal(num1, num2));
}
END_TEST

// === is_equal === //
START_TEST(is_equal_true) {  // 1337 = 1337 == 1 yes
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1337, &num2);
  ck_assert_int_eq(1, s21_is_equal(num1, num2));
}
END_TEST

START_TEST(is_equal_false) {  // 1337 = 1338 == 0 no
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1338, &num2);
  ck_assert_int_eq(0, s21_is_equal(num1, num2));
}
END_TEST

START_TEST(is_equal_min_num1) {  // 1337 = 1338 == 0 no
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(-1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1338, &num2);
  ck_assert_int_eq(0, s21_is_equal(num1, num2));
}
END_TEST

START_TEST(is_equal_min_num2) {  // 1337 = 1338 == 0 no
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(-1338, &num2);
  ck_assert_int_eq(0, s21_is_equal(num1, num2));
}
END_TEST

START_TEST(is_equal_min_both) {  // 1337 = 1338 == 0 no
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(-1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(-1338, &num2);
  ck_assert_int_eq(0, s21_is_equal(num1, num2));
}
END_TEST

// === is_not_equal === //
START_TEST(is_not_equal_true) {  // 1337 != 1338 == 1 yes
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1338, &num2);
  ck_assert_int_eq(1, s21_is_not_equal(num1, num2));
}
END_TEST

START_TEST(is_not_equal_false) {  // 1337 != 1337 == 0 no
  s21_decimal num1 = {0};
  s21_from_int_to_decimal(1337, &num1);
  s21_decimal num2 = {0};
  s21_from_int_to_decimal(1337, &num2);
  ck_assert_int_eq(0, s21_is_not_equal(num1, num2));
}
END_TEST
// END OF baggmela tests


Suite* comparsion_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("equal");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, is_equal_simple);
  tcase_add_test(tc_core, is_equal_0_decimal);
  tcase_add_test(tc_core, is_not_equal);
  tcase_add_test(tc_core, is_not_equal_SIGN);
  tcase_add_test(tc_core, is_not_equal_EQ);
  tcase_add_test(tc_core, is_greater_stand);
  tcase_add_test(tc_core, is_greater_le);
  tcase_add_test(tc_core, is_greater_0);
  tcase_add_test(tc_core, is_greater_eq);
  tcase_add_test(tc_core, is_less_Classic);
  tcase_add_test(tc_core, is_less_equal);
  tcase_add_test(tc_core, is_less_ne);
  tcase_add_test(tc_core, is_less_or_equal_Classic);
  tcase_add_test(tc_core, is_less_or_equal_Norm);
  
  tcase_add_test(tc_core, is_less_plus_both);
  tcase_add_test(tc_core, is_less_min_num1);
  tcase_add_test(tc_core, is_less_min_num2);
  tcase_add_test(tc_core, is_less_min_both);
  tcase_add_test(tc_core, is_greater_plus_both);
  tcase_add_test(tc_core, is_greater_min_num1);
  tcase_add_test(tc_core, is_greater_min_num2);
  tcase_add_test(tc_core, is_greater_min_both);
  tcase_add_test(tc_core, is_less_or_equal_num1_less);
  tcase_add_test(tc_core, is_less_or_equal_num2_less);
  tcase_add_test(tc_core, is_less_or_equal_both_equal);
  tcase_add_test(tc_core, is_greater_or_equal_num1_less);
  tcase_add_test(tc_core, is_greater_or_equal_num2_less);
  tcase_add_test(tc_core, is_greater_or_equal_both_equal);
  tcase_add_test(tc_core, is_equal_false);
  tcase_add_test(tc_core, is_equal_true);
  tcase_add_test(tc_core, is_equal_min_num1);
  tcase_add_test(tc_core, is_equal_min_num2);
  tcase_add_test(tc_core, is_equal_min_both);
  tcase_add_test(tc_core, is_not_equal_false);
  tcase_add_test(tc_core, is_not_equal_true);
  suite_add_tcase(s, tc_core);
  return s;
}

