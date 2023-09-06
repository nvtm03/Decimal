#include "../tests.h"

START_TEST(add_0) {
  // 4294967296 + 429496729,5 = 4724464025.5
  s21_decimal decimal;
  s21_decimal decimal2;
  s21_decimal decimal3;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&decimal2);
  clear_s21_decimal(&decimal3);
  int true_result_status = 0;
  // 1000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000001  0000000000000000 0000000000000000
  decimal.bits[1] = 1;

  // 0000000000000001 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  1111111111111111 1111111111111111
  decimal2.bits[0] = 4294967295;
  decimal2.bits[3] = 65536;
  int our_result_status = s21_add(decimal, decimal2, &decimal3);
  // 0000000000000001 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000001010  1111111111111111 1111111111111111
  ck_assert_int_eq(decimal3.bits[0], 4294967295);
  ck_assert_int_eq(decimal3.bits[1], 10);
  ck_assert_int_eq(decimal3.bits[3], 65536);
  ck_assert_int_eq(our_result_status, true_result_status);
}
END_TEST

START_TEST(add_1) {
  // 4294967296 + 429496729,5 = 4724464025.5
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

  // 1000000000000001 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  1111111111111111 1111111111111111
  decimal2.bits[0] = 4294967295;
  decimal2.bits[3] = 2147549184;
  int our_result_status = s21_add(decimal, decimal2, &decimal3);
  // 0000000000000001 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000001001  0000000000000000 0000000000000001
  ck_assert_int_eq(decimal3.bits[0], 1);
  ck_assert_int_eq(decimal3.bits[1], 9);
  ck_assert_int_eq(decimal3.bits[3], 65536);
  ck_assert_int_eq(our_result_status, true_result_status);
}
END_TEST

START_TEST(add_2) {
  // 12 + 75,5 = 87.5
  s21_decimal decimal;
  s21_decimal decimal2;
  s21_decimal decimal3;
  clear_s21_decimal(&decimal);
  clear_s21_decimal(&decimal2);
  clear_s21_decimal(&decimal3);
  int true_result_status = 0;
  // 0000000000000000 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000000000001100
  decimal.bits[0] = 12;  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  // 0000000000000001 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000001011110011
  decimal2.bits[0] = 755;
  decimal2.bits[3] = 65536;
  int our_result_status = s21_add(decimal, decimal2, &decimal3);
  // 0000000000000001 0000000000000000  0000000000000000 0000000000000000
  // 0000000000000000 0000000000000000  0000000000000000 0000001101101011
  ck_assert_int_eq(decimal3.bits[0], 875);
  ck_assert_int_eq(decimal3.bits[3], 65536);
  ck_assert_int_eq(our_result_status, true_result_status);
}
END_TEST


//
// Created by Дмитрий on 25.05.2023.
//
//#define UINT_MAX   4294967295U
#define EXPONENT_PLUS_1 65536
#define EXPONENT_PLUS_2 196608

START_TEST(add_19) {
        s21_decimal val1 = {{15, 0, 0, ~(UINT_MAX / 2)}};
        s21_decimal val2 = {{2, 0, 0, 0}};
        s21_decimal res = {{0}};
        ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_20) {
    s21_decimal val1 = {{15, 0, 0, 0}};
    s21_decimal val2 = {{15, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal res = {{0}};
    ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_21) {
    s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    s21_decimal val2 = {{1, 0, 0, 0}};
    s21_decimal res = {{0}};
    ck_assert_int_eq(1, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_3) {
    s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal res = {{0}};
    ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_4) {
    s21_decimal val1 = {{8, 0, 0, 0}};
    s21_decimal val2 = {{2, 0, 0, 0}};
    s21_decimal res;
    ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_5) {
    s21_decimal val1 = {{2, 0, 0, 0}};
    s21_decimal val2 = {{8, 0, 0, 0}};
    s21_decimal res = {{0}};
    ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_6) {
    s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{2, 0, 0, 0}};
    s21_decimal res = {{0}};
    ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_7) {
    s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{8, 0, 0, 0}};
    s21_decimal res = {{0}};
    ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_8) {
    s21_decimal val1 = {{0}};
    s21_decimal val2 = {{0}};
    s21_decimal res = {{0}};
    ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_9) {
    s21_decimal val1 = {{4, 0, 0, 0}};
    s21_decimal val2 = {{8, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal res = {0};
    ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_10) {
    s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{0}};
    s21_decimal res = {{0}};
    ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_11) {
    s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{4, 0, 0, 0}};
    s21_decimal res = {{0}};
    ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_12) {
    s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal res = {{0}};
    ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_13) {
    s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal res = {{0}};
    ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_14) {
    s21_decimal val1 = {{4, 0, 0, 0}};
    s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
    s21_decimal res = {{0}};
    ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_15) {
    s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    s21_decimal res = {{0}};
    ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_16) {
    s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
    s21_decimal res = {{0}};
    ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST


START_TEST(s21_test_decimal_add_0) {
    s21_decimal c = {{5, 0, 0, 0}};
    s21_decimal d = {{5, 0, 0, 0}};
    s21_decimal etalon = {{10, 0, 0, 0}};
    s21_decimal res = {{0, 0, 0, 0}};

    // 0 - OK 1 - число слишком велико или равно бесконечности
    // 2 - число слишком мало или равно отрицательной бесконечности
    // 3 - деление на 0
    int add = s21_add(c, d, &res);
    int equal = s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(add, 0);
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_1) {
    s21_decimal c = {{100, 0, 0, 0}};
    s21_decimal d = {{100, 0, 0, 0}};
    s21_decimal etalon = {{100, 0, 0, 0}};
    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;
    // 0 - OK 1 - число слишком велико или равно бесконечности
    // 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    // Возвращаемое значение: 0 - FALSE 1 - TRUE
    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(add, 0);
    ck_assert_int_eq(equal, 0);
}
END_TEST

START_TEST(s21_test_decimal_add_3) {
    s21_decimal c = {{1000, 0, 0, 0}};
    s21_decimal d = {{1000, 0, 0, 0}};
    s21_decimal etalon = {{2000, 0, 0, 0}};
    s21_decimal result = {{0, 0, 0, 0}};
    s21_decimal* p_result = &result;
    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_result);
    ck_assert_int_eq(add, 0);
    // Возвращаемое значение: 0 - FALSE 1 - TRUE
    int equal = s21_is_equal(result, etalon);
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_4) {
    s21_decimal c = {{1000, 0, 0, ~(INT_MAX)}};
    s21_decimal d = {{1000, 0, 0, 0}};
    s21_decimal etalon = {{0, 0, 0, 0}};
    s21_decimal result = {{0, 0, 0, 0}};
    s21_decimal* p_result = &result;
    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_result);
    ck_assert_int_eq(add, 0);
    // Возвращаемое значение: 0 - FALSE 1 - TRUE
    int equal = s21_is_equal(result, etalon);
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_5) {
    s21_decimal c = {{1, 0, 0, ~(INT_MAX)}};
    s21_decimal d = {{1, 0, 0, ~(INT_MAX)}};
    s21_decimal etalon = {{2, 0, 0, ~(INT_MAX)}};
    s21_decimal result = {{0, 0, 0, 0}};
    s21_decimal* p_result = &result;
    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_result);
    ck_assert_int_eq(add, 0);
    // Возвращаемое значение: 0 - FALSE 1 - TRUE
    int equal = s21_is_equal(*p_result, etalon);
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_6) {
    s21_decimal c = {{0, 0, 0, 0}};
    s21_decimal d = {{0, 0, 0, 0}};
    s21_decimal etalon = {{0, 0, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_7) {
    s21_decimal c = {{1, 0, 0, 0}};
    s21_decimal d = {{1, 0, 0, 0}};
    s21_decimal etalon = {{2, 0, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_8) {
    s21_decimal c = {{1000, 0, 0, 0}};
    s21_decimal d = {{1000, 0, 0, 0}};
    s21_decimal etalon = {{2000, 0, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_9) {
    s21_decimal c = {{INT_MAX, 0, 0, 0}};
    s21_decimal d = {{INT_MAX, 0, 0, 0}};
    s21_decimal etalon = {{UINT32_MAX - 1, 0, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_10) {
    s21_decimal c = {{UINT32_MAX, 0, 0, 0}};
    s21_decimal d = {{1, 0, 0, 0}};
    s21_decimal etalon = {{0, 1, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    ck_assert_int_eq(res.bits[3], etalon.bits[3]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[0], etalon.bits[0]);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_11) {
    s21_decimal c = {{0, UINT_MAX - 1, 0, 0}};
    s21_decimal d = {{0, 1, 0, 0}};
    s21_decimal etalon = {{0, UINT_MAX, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_12) {
    s21_decimal c = {{0, 0, UINT_MAX - 1, 0}};
    s21_decimal d = {{0, 0, 1, 0}};
    s21_decimal etalon = {{0, 0, UINT_MAX, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_13) {
    s21_decimal c = {{0, 0, 0, ~(INT_MAX)}};
    s21_decimal d = {{0, 0, 0, ~(INT_MAX)}};
    s21_decimal etalon = {{0, 0, 0, ~(INT_MAX)}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_14) {
    s21_decimal c = {{1, 0, 0, ~(INT_MAX)}};
    s21_decimal d = {{1, 0, 0, 0}};
    s21_decimal etalon = {{0, 0, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_15) {  // -1 + (-1) = -2
    s21_decimal c = {{1, 0, 0, ~(INT_MAX)}};
    s21_decimal d = {{1, 0, 0, ~(INT_MAX)}};
    s21_decimal etalon = {{2, 0, 0, ~(INT_MAX)}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    ck_assert_int_eq(res.bits[3], etalon.bits[3]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[0], etalon.bits[0]);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_16) {
    s21_decimal c = {{11, 0, 0, EXPONENT_PLUS_1}};
    s21_decimal d = {{0, 0, 0, 0}};
    s21_decimal etalon = {{11, 0, 0, EXPONENT_PLUS_1}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_17) {
    s21_decimal c = {{11, 0, 0, EXPONENT_PLUS_1}};
    s21_decimal d = {{1, 0, 0, 0}};
    s21_decimal etalon = {{21, 0, 0, EXPONENT_PLUS_1}};

    s21_decimal res = {{0, 0, 0, 0}};

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, &res);
    ck_assert_int_eq(add, 0);

    ck_assert_int_eq(res.bits[0], etalon.bits[0]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[3], etalon.bits[3]);

    int equal = s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_18) {
    s21_decimal c = {{111, 0, 0, EXPONENT_PLUS_1}};
    s21_decimal d = {{1, 0, 0, 0}};
    s21_decimal etalon = {{121, 0, 0, EXPONENT_PLUS_1}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    ck_assert_int_eq(res.bits[0], etalon.bits[0]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[3], etalon.bits[3]);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_19) {
    s21_decimal c = {{111, 0, 0, EXPONENT_PLUS_2}};
    s21_decimal d = {{1, 0, 0, 0}};
    s21_decimal etalon = {{1111, 0, 0, EXPONENT_PLUS_2}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    ck_assert_int_eq(res.bits[0], etalon.bits[0]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[3], etalon.bits[3]);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_20) {
    s21_decimal c = {0};
    c.bits[0] = 0b11111111111111111111111111111110;
    c.bits[1] = 0b00000000000000000000000000000000;
    c.bits[2] = 0b00000000000000000000000000000000;
    c.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal d = {{1, 0, 0, 0}};
    s21_decimal etalon = {0};
    etalon.bits[0] = 0b11111111111111111111111111111111;
    etalon.bits[1] = 0b00000000000000000000000000000000;
    etalon.bits[2] = 0b00000000000000000000000000000000;
    etalon.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    ck_assert_int_eq(res.bits[0], etalon.bits[0]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[3], etalon.bits[3]);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_21) {
    s21_decimal c = {{UINT32_MAX - 1, UINT32_MAX, 0, 0}};
    s21_decimal d = {{1, 0, 0, 0}};
    s21_decimal etalon = {{UINT32_MAX, UINT32_MAX, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    ck_assert_int_eq(res.bits[0], etalon.bits[0]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[3], etalon.bits[3]);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_25) {
    s21_decimal c = {{0b00000000000000000001100101111001, 0, 0, 0}};
    s21_decimal d = {{0b00000000000000010010000110001001, 0, 0, 0}};
    s21_decimal etalon = {{0b00000000000000010011101100000010, 0, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_26) {
    s21_decimal c = {{0b10001001111001111111111111111111,
                      0b10001010110001110010001100000100, 0, 0}};
    s21_decimal d = {{0b00000000000000000000000000000001, 0, 0, 0}};
    s21_decimal etalon = {{0b10001001111010000000000000000000,
                           0b10001010110001110010001100000100, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_27) {
    s21_decimal c = {{UINT_MAX, UINT_MAX, 0, 0}};
    s21_decimal d = {{0b00000000000000000000000000000001, 0, 0, 0}};
    s21_decimal etalon = {{0, 0, 1, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_28) {
    s21_decimal c = {
            {0b10000010111000100101101011101101, 0b11111001111010000010010110101101,
             0b10110000001111101111000010010100, 0b10000000000011100000000000000000}};

    s21_decimal d = {{0b00000011010000001001011100101110, 0, 0, 0}};

    s21_decimal etalon = {
            {0b01110001001010101101101011101101, 0b00101110001111001110000111111000,
             0b10110000001111101110111101101101, 0b10000000000011100000000000000000}};

    s21_decimal res = {{0, 0, 0, 0}};

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, &res);
    ck_assert_int_eq(add, 0);

    ck_assert_int_eq(res.bits[0], etalon.bits[0]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[3], etalon.bits[3]);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_29) {
    s21_decimal c = {
            {0b10000010111000100101101011101101, 0b11111001111010000010010110101101,
             0b10110000001111101111000010010100, 0b10000000000011100000000000000000}};
    s21_decimal d = {
            {0b01001000000110110001111110011000, 0b11111011111111011000100101101101,
             0b00000000000001000110110101110111, 0b10000000000110000000000000000000}};
    s21_decimal etalon = {
            {0b10110110001010011011010111011010, 0b11111001111010100000110001111111,
             0b10110000001111101111000010010100, 0b10000000000011100000000000000000}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    ck_assert_int_eq(res.bits[0], etalon.bits[0]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[3], etalon.bits[3]);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_30) {
    s21_decimal src1, src2, origin;
    src1.bits[0] = 0b01001110111001000011100101110110;
    src1.bits[1] = 0b01001011001101011010000111011001;
    src1.bits[2] = 0b00011001101110010111010010111111;
    src1.bits[3] = 0b00000000000011110000000000000000;
    src2.bits[0] = 0b00000000000000000000000000000000;
    src2.bits[1] = 0b00000000000000000000000000000000;
    src2.bits[2] = 0b00000000000000000000000000000000;
    src2.bits[3] = 0b00000000000000000000000000000000;
    origin.bits[0] = 0b01001110111001000011100101110110;
    origin.bits[1] = 0b01001011001101011010000111011001;
    origin.bits[2] = 0b00011001101110010111010010111111;
    origin.bits[3] = 0b00000000000011110000000000000000;

    s21_decimal result = {{0, 0, 0, 0}};
    s21_decimal* p_res = &result;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(src1, src2, p_res);
    ck_assert_int_eq(add, 0);

    ck_assert_int_eq(origin.bits[0], result.bits[0]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[3], result.bits[3]);

    int equal = s21_is_equal(
            result, origin);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_0) {
    s21_decimal c = {{0, 0, 0, 0}};
    s21_decimal d = {{0, 0, 0, 0}};
    s21_decimal etalon = {{0, 0, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_1) {
    s21_decimal c = {{1, 0, 0, 0}};
    s21_decimal d = {{1, 0, 0, 0}};
    s21_decimal etalon = {{2, 0, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_2) {
    s21_decimal c = {{1000, 0, 0, 0}};
    s21_decimal d = {{1000, 0, 0, 0}};
    s21_decimal etalon = {{2000, 0, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_4) {
    s21_decimal c = {{INT_MAX, 0, 0, 0}};
    s21_decimal d = {{INT_MAX, 0, 0, 0}};
    s21_decimal etalon = {{UINT32_MAX - 1, 0, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_5) {
    s21_decimal c = {{UINT_MAX, 0, 0, 0}};
    s21_decimal d = {{1, 0, 0, 0}};
    s21_decimal etalon = {{0, 1, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    ck_assert_int_eq(res.bits[3], etalon.bits[3]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[0], etalon.bits[0]);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_6) {
    s21_decimal c = {{0, UINT_MAX - 1, 0, 0}};
    s21_decimal d = {{0, 1, 0, 0}};
    s21_decimal etalon = {{0, UINT_MAX, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_7) {
    s21_decimal c = {{0, 0, UINT_MAX - 1, 0}};
    s21_decimal d = {{0, 0, 1, 0}};
    s21_decimal etalon = {{0, 0, UINT_MAX, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_8) {
    s21_decimal c = {{0, 0, 0, ~(INT_MAX)}};
    s21_decimal d = {{0, 0, 0, ~(INT_MAX)}};
    s21_decimal etalon = {{0, 0, 0, ~(INT_MAX)}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_9) {
    s21_decimal c = {{1, 0, 0, 0b10000000000000000000000000000000}};
    s21_decimal d = {{1, 0, 0, 0}};
    s21_decimal etalon = {{0, 0, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    ck_assert_int_eq(res.bits[0], etalon.bits[0]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[3], etalon.bits[3]);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_10) {  // -1 + (-1) = -2
    s21_decimal c = {{1, 0, 0, ~(INT_MAX)}};
    s21_decimal d = {{1, 0, 0, ~(INT_MAX)}};
    s21_decimal etalon = {{2, 0, 0, ~(INT_MAX)}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    ck_assert_int_eq(res.bits[0], etalon.bits[0]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[3], etalon.bits[3]);

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_11) {
    s21_decimal c = {{11, 0, 0, EXPONENT_PLUS_1}};
    s21_decimal d = {{0, 0, 0, 0}};
    s21_decimal etalon = {{11, 0, 0, EXPONENT_PLUS_1}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_12) {
    s21_decimal c = {{11, 0, 0, EXPONENT_PLUS_1}};
    s21_decimal d = {{1, 0, 0, 0}};
    s21_decimal etalon = {{21, 0, 0, EXPONENT_PLUS_1}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_13) {
    s21_decimal c = {{111, 0, 0, EXPONENT_PLUS_1}};
    s21_decimal d = {{1, 0, 0, 0}};
    s21_decimal etalon = {{121, 0, 0, EXPONENT_PLUS_1}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    ck_assert_int_eq(res.bits[0], etalon.bits[0]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[3], etalon.bits[3]);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_14) {
    s21_decimal c = {{111, 0, 0, EXPONENT_PLUS_2}};
    s21_decimal d = {{1, 0, 0, 0}};
    s21_decimal etalon = {{1111, 0, 0, EXPONENT_PLUS_2}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);
    ck_assert_int_eq(res.bits[0], etalon.bits[0]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[3], etalon.bits[3]);

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_20) {
    s21_decimal c = {{0b00000000000000000001100101111001, 0, 0, 0}};
    s21_decimal d = {{0b00000000000000010010000110001001, 0, 0, 0}};
    s21_decimal etalon = {{0b00000000000000010011101100000010, 0, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_21) {
    s21_decimal c = {{0b10001001111001111111111111111111,
                      0b10001010110001110010001100000100, 0, 0}};
    s21_decimal d = {{0b00000000000000000000000000000001, 0, 0, 0}};
    s21_decimal etalon = {{0b10001001111010000000000000000000,
                           0b10001010110001110010001100000100, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_22) {
    s21_decimal c = {{UINT_MAX, UINT_MAX, 0, 0}};
    s21_decimal d = {{0b00000000000000000000000000000001, 0, 0, 0}};
    s21_decimal etalon = {{0, 0, 1, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_decimal_add_simple_23) {
    s21_decimal c = {
            {0b10000010111000100101101011101101, 0b11111001111010000010010110101101,
             0b10110000001111101111000010010100, 0b10000000000011100000000000000000}};
    s21_decimal d = {{0b00000011010000001001011100101110, 0, 0, 0}};
    s21_decimal etalon = {
            {0b01110001001010101101101011101101, 0b00101110001111001110000111111000,
             0b10110000001111101110111101101101, 0b10000000000011100000000000000000}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    ck_assert_int_eq(res.bits[0], etalon.bits[0]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[3], etalon.bits[3]);

    // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
    // мало или равно отрицательной бесконечности 3 - деление на 0
    int equal =
            s21_is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
    ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_add_max_31) {
    s21_decimal src1 = {0};
    src1.bits[0] = 0b11111111111111111111111111111111;
    src1.bits[1] = 0b11111111111111111111111111111111;
    src1.bits[2] = 0b11111111111111111111111111111111;
    src1.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal src2 = {0};
    src2.bits[0] = 0b00000000000000000000000000000010;
    src2.bits[1] = 0b00000000000000000000000000000000;
    src2.bits[2] = 0b00000000000000000000000000000000;
    src2.bits[3] = 0b00000000000000110000000000000000;
    s21_decimal s21_res = {0};
    ck_assert_int_eq(s21_add(src1, src2, &s21_res), 0);
}
END_TEST

START_TEST(s21_add_max_32) {
    s21_decimal src1 = {0};
    src1.bits[0] = 0b11111111111111111111111111111111;
    src1.bits[1] = 0b11111111111111111111111111111111;
    src1.bits[2] = 0b11111111111111111111111111111111;
    src1.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal src2 = {0};
    src2.bits[0] = 0b00000000000000000000000000000101;
    src2.bits[1] = 0b00000000000000000000000000000000;
    src2.bits[2] = 0b00000000000000000000000000000000;
    src2.bits[3] = 0b00000000000000010000000000000000;
    s21_decimal s21_res = {0};
    ck_assert_int_eq(s21_add(src1, src2, &s21_res), 1);
}
END_TEST

START_TEST(s21_add_max_33) {
    s21_decimal src1 = {0};
    src1.bits[0] = 0b11111111111111111111111111111111;
    src1.bits[1] = 0b11111111111111111111111111111111;
    src1.bits[2] = 0b11111111111111111111111111111111;
    src1.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal src2 = {0};
    src2.bits[0] = 0b00000000000000000000000000000001;
    src2.bits[1] = 0b00000000000000000000000000000000;
    src2.bits[2] = 0b00000000000000000000000000000000;
    src2.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal s21_res = {0};
    ck_assert_int_eq(s21_add(src1, src2, &s21_res), 1);
}
END_TEST

START_TEST(s21_add_max_34) {
    s21_decimal src1 = {0};
    src1.bits[0] = 0b11111111111111111111111111111111;
    src1.bits[1] = 0b11111111111111111111111111111111;
    src1.bits[2] = 0b11111111111111111111111111111111;
    src1.bits[3] = 0b10000000000000000000000000000000;
    s21_decimal src2 = {0};
    src2.bits[0] = 0b00000000000000000000000000000110;
    src2.bits[1] = 0b00000000000000000000000000000000;
    src2.bits[2] = 0b00000000000000000000000000000000;
    src2.bits[3] = 0b0000000000000010000000000000000;
    s21_decimal original_res = {0};
    original_res.bits[0] = 0b11111111111111111111111111111110;
    original_res.bits[1] = 0b11111111111111111111111111111111;
    original_res.bits[2] = 0b11111111111111111111111111111111;
    original_res.bits[3] = 0b10000000000000000000000000000000;
    s21_decimal s21_res = {0};
    s21_add(src1, src2, &s21_res);
    ck_assert_int_eq(s21_add(src1, src2, &s21_res), 0);
    ck_assert_int_eq(original_res.bits[0], s21_res.bits[0]);
    ck_assert_int_eq(original_res.bits[1], s21_res.bits[1]);
    ck_assert_int_eq(original_res.bits[2], s21_res.bits[2]);
    ck_assert_int_eq(original_res.bits[3], s21_res.bits[3]);
}
END_TEST

START_TEST(s21_add_max_35) {
    s21_decimal src1 = {0};
    src1.bits[0] = 0b11111111111111111111111111111111;
    src1.bits[1] = 0b11111111111111111111111111111111;
    src1.bits[2] = 0b11111111111111111111111111111111;
    src1.bits[3] = 0b10000000000000000000000000000000;
    s21_decimal src2 = {0};
    src2.bits[0] = 0b00000000000000000000000000000101;
    src2.bits[1] = 0b00000000000000000000000000000000;
    src2.bits[2] = 0b00000000000000000000000000000000;
    src2.bits[3] = 0b00000000000000010000000000000000;
    s21_decimal original_res = {0};
    original_res.bits[0] = 0b11111111111111111111111111111110;
    original_res.bits[1] = 0b11111111111111111111111111111111;
    original_res.bits[2] = 0b11111111111111111111111111111111;
    original_res.bits[3] = 0b10000000000000000000000000000000;
    s21_decimal s21_res = {0};
    s21_add(src1, src2, &s21_res);
    ck_assert_int_eq(s21_add(src1, src2, &s21_res), 0);
    ck_assert_int_eq(original_res.bits[0], s21_res.bits[0]);
    ck_assert_int_eq(original_res.bits[1], s21_res.bits[1]);
    ck_assert_int_eq(original_res.bits[2], s21_res.bits[2]);
    ck_assert_int_eq(original_res.bits[3], s21_res.bits[3]);
}
END_TEST

START_TEST(s21_add_max_36) {
    s21_decimal src1 = {0};
    src1.bits[0] = 0b11111111111111111111111111111111;
    src1.bits[1] = 0b11111111111111111111111111111111;
    src1.bits[2] = 0b11111111111111111111111111111111;
    src1.bits[3] = 0b10000000000000000000000000000000;
    s21_decimal src2 = {0};
    src2.bits[0] = 0b00000000000000000000000000000001;
    src2.bits[1] = 0b00000000000000000000000000000000;
    src2.bits[2] = 0b00000000000000000000000000000000;
    src2.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal original_res = {0};
    original_res.bits[0] = 0b11111111111111111111111111111110;
    original_res.bits[1] = 0b11111111111111111111111111111111;
    original_res.bits[2] = 0b11111111111111111111111111111111;
    original_res.bits[3] = 0b10000000000000000000000000000000;
    s21_decimal s21_res = {0};
    s21_add(src1, src2, &s21_res);
    ck_assert_int_eq(s21_add(src1, src2, &s21_res), 0);
    ck_assert_int_eq(original_res.bits[0], s21_res.bits[0]);
    ck_assert_int_eq(original_res.bits[1], s21_res.bits[1]);
    ck_assert_int_eq(original_res.bits[2], s21_res.bits[2]);
    ck_assert_int_eq(original_res.bits[3], s21_res.bits[3]);
}
END_TEST

START_TEST(add_test_37) {
    s21_decimal src1 = {0};
    src1.bits[0] = 0b00000000000000000000001111111111;
    src1.bits[1] = 0b00000000000000000000000000000000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b00000000000000010000000000000000;
    s21_decimal src2 = {0};
    src2.bits[0] = 0b00000000000000000000001111111111;
    src2.bits[1] = 0b00000000000000000000000000000000;
    src2.bits[2] = 0b00000000000000000000000000000000;
    src2.bits[3] = 0b00000000000000100000000000000000;
    s21_decimal original_res = {0};
    original_res.bits[0] = 0b00000000000000000010101111110101;
    original_res.bits[1] = 0b00000000000000000000000000000000;
    original_res.bits[2] = 0b00000000000000000000000000000000;
    original_res.bits[3] = 0b00000000000000100000000000000000;
    s21_decimal s21_res = {0};
    s21_add(src1, src2, &s21_res);
    ck_assert_int_eq(s21_add(src1, src2, &s21_res), 0);
    ck_assert_int_eq(original_res.bits[0], s21_res.bits[0]);
    ck_assert_int_eq(original_res.bits[1], s21_res.bits[1]);
    ck_assert_int_eq(original_res.bits[2], s21_res.bits[2]);
    ck_assert_int_eq(original_res.bits[3], s21_res.bits[3]);
}
END_TEST


Suite *suite_s21_add(void) {
  Suite *s23;
  TCase *tc23;
  s23 = suite_create("s21_ADD");
  tc23 = tcase_create("case_ADD");
  tcase_add_test(tc23, add_0);
  tcase_add_test(tc23, add_1);
  tcase_add_test(tc23, add_2);


    tcase_add_test(tc23, add_19);
    tcase_add_test(tc23, add_20);
    tcase_add_test(tc23, add_21);
    tcase_add_test(tc23, add_3);
    tcase_add_test(tc23, add_4);
    tcase_add_test(tc23, add_5);
    tcase_add_test(tc23, add_6);
    tcase_add_test(tc23, add_7);
    tcase_add_test(tc23, add_8);
    tcase_add_test(tc23, add_9);
    tcase_add_test(tc23, add_10);
    tcase_add_test(tc23, add_11);
    tcase_add_test(tc23, add_12);
    tcase_add_test(tc23, add_13);
    tcase_add_test(tc23, add_14);
    tcase_add_test(tc23, add_15);
    tcase_add_test(tc23, add_16);

    tcase_add_test(tc23, s21_test_decimal_add_0);
    tcase_add_test(tc23, s21_test_decimal_add_1);
    tcase_add_test(tc23, s21_test_decimal_add_3);
    tcase_add_test(tc23, s21_test_decimal_add_4);
    tcase_add_test(tc23, s21_test_decimal_add_5);
    tcase_add_test(tc23, s21_test_decimal_add_6);
    tcase_add_test(tc23, s21_test_decimal_add_7);
    tcase_add_test(tc23, s21_test_decimal_add_8);
    tcase_add_test(tc23, s21_test_decimal_add_9);
    tcase_add_test(tc23, s21_test_decimal_add_10);
    tcase_add_test(tc23, s21_test_decimal_add_11);
    tcase_add_test(tc23, s21_test_decimal_add_12);
    tcase_add_test(tc23, s21_test_decimal_add_13);
    tcase_add_test(tc23, s21_test_decimal_add_14);
    tcase_add_test(tc23, s21_test_decimal_add_15);
    tcase_add_test(tc23, s21_test_decimal_add_16);
    tcase_add_test(tc23, s21_test_decimal_add_17);
    tcase_add_test(tc23, s21_test_decimal_add_18);
    tcase_add_test(tc23, s21_test_decimal_add_19);
    tcase_add_test(tc23, s21_test_decimal_add_20);
    tcase_add_test(tc23, s21_test_decimal_add_21);
    tcase_add_test(tc23, s21_test_decimal_add_25);
    tcase_add_test(tc23, s21_test_decimal_add_26);
    tcase_add_test(tc23, s21_test_decimal_add_27);
    tcase_add_test(tc23, s21_test_decimal_add_28);
    tcase_add_test(tc23, s21_test_decimal_add_29);
    tcase_add_test(tc23, s21_test_decimal_add_30);

    tcase_add_test(tc23, s21_test_decimal_add_simple_0);
    tcase_add_test(tc23, s21_test_decimal_add_simple_1);
    tcase_add_test(tc23, s21_test_decimal_add_simple_2);
    tcase_add_test(tc23, s21_test_decimal_add_simple_4);
    tcase_add_test(tc23, s21_test_decimal_add_simple_5);
    tcase_add_test(tc23, s21_test_decimal_add_simple_6);
    tcase_add_test(tc23, s21_test_decimal_add_simple_7);
    tcase_add_test(tc23, s21_test_decimal_add_simple_8);
    tcase_add_test(tc23, s21_test_decimal_add_simple_9);
    tcase_add_test(tc23, s21_test_decimal_add_simple_10);
    tcase_add_test(tc23, s21_test_decimal_add_simple_11);
    tcase_add_test(tc23, s21_test_decimal_add_simple_12);
    tcase_add_test(tc23, s21_test_decimal_add_simple_13);
    tcase_add_test(tc23, s21_test_decimal_add_simple_14);
    tcase_add_test(tc23, s21_test_decimal_add_simple_20);
    tcase_add_test(tc23, s21_test_decimal_add_simple_21);
    tcase_add_test(tc23, s21_test_decimal_add_simple_22);
    tcase_add_test(tc23, s21_test_decimal_add_simple_23);

    tcase_add_test(tc23, s21_add_max_31);
    tcase_add_test(tc23, s21_add_max_32);
    tcase_add_test(tc23, s21_add_max_33);
    tcase_add_test(tc23, s21_add_max_34);
    tcase_add_test(tc23, s21_add_max_35);
    tcase_add_test(tc23, s21_add_max_36);
    tcase_add_test(tc23, add_test_37);


  suite_add_tcase(s23, tc23);
  return s23;
}