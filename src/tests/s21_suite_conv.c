#include "../tests.h"


#define RESET "\033[0m"
#define RED "\e[0;91m"
#define GREEN "\033[32m"
#define BLUE "\e[0;94m"

#define S21_TRUE 1
#define S21_FALSE 0
#define CONVERTERS_S21_TRUE 0
#define CONVERTERS_S21_FALSE 1
#define U_MAX_INT 4294967295          // 0b11111111111111111111111111111111
#define MAX_INT 2147483647            // 0b01111111111111111111111111111111
#define EXPONENT_MINUS_1 2147549184   // 0b10000000000000010000000000000000
#define EXPONENT_PLUS_1 65536         // 0b00000000000000010000000000000000
#define EXPONENT_PLUS_2 196608        // 0b00000000000000110000000000000000
#define EXPONENT_MINUS_28 2149318656  // 0b10000000000111000000000000000000
#define EXPONENT_PLUS_28 1835008      // 0b00000000000111000000000000000000
#define MINUS 2147483648              // 0b10000000000000000000000000000000
#define MAX_DECIMAL 79228162514264337593543950335.0F
#define MIN_DECIMAL -79228162514264337593543950335.0F


START_TEST(from_float_to_decimal_simple) {
  s21_decimal decimal;
  clear_s21_decimal(&decimal);
  float number = 100.5;
  s21_from_float_to_decimal(number, &decimal);
}
END_TEST

START_TEST(float_eq_float) {
  s21_decimal decimal;
  clear_s21_decimal(&decimal);
  float A = 100.5;
  float B = 0.0;
  s21_from_float_to_decimal(A, &decimal);
  s21_from_decimal_to_float(decimal, &B);
  ck_assert_float_eq(A, B);
}
END_TEST

START_TEST(float_eq_float_minus) {
  s21_decimal decimal;
  clear_s21_decimal(&decimal);
  float A = -100.5;
  float B = 0.0;
  s21_from_float_to_decimal(A, &decimal);
  s21_from_decimal_to_float(decimal, &B);
  ck_assert_float_eq(A, B);
}
END_TEST


START_TEST(int_decimal_int_1) {
  s21_decimal decimal;
  clear_s21_decimal(&decimal);
  int i = INT32_MAX, res = 0;
  s21_from_int_to_decimal(i, &decimal);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(int_decimal_int_2) {
  s21_decimal decimal;
  clear_s21_decimal(&decimal);
  int i = INT32_MIN, res = 0;
  s21_from_int_to_decimal(i, &decimal);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(int_decimal_int_3) {
  s21_decimal decimal;
  clear_s21_decimal(&decimal);
  int i = 0, res = 0;
  s21_from_int_to_decimal(i, &decimal);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(int_decimal_int_4) {
  s21_decimal decimal;
  clear_s21_decimal(&decimal);
  int i = -123456, res = 0;
  s21_from_int_to_decimal(i, &decimal);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(int_decimal_int_5) {
  s21_decimal decimal;
  clear_s21_decimal(&decimal);
  int i = 987654, res = 0;
  s21_from_int_to_decimal(i, &decimal);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(int_decimal_int_6) {
  s21_decimal decimal;
  clear_s21_decimal(&decimal);
  int i = -1, res = 0;
  s21_from_int_to_decimal(i, &decimal);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(int_decimal_int_7) {
  s21_decimal decimal;
  clear_s21_decimal(&decimal);
  int i = 2, res = 0;
  s21_from_int_to_decimal(i, &decimal);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST



START_TEST(float_decimal_float_2) {
  s21_decimal decimal;
  clear_s21_decimal(&decimal);
  float f = -3.0, res = 0;
  s21_from_float_to_decimal(f, &decimal);
  s21_from_decimal_to_float(decimal, &res);
  ck_assert_float_eq(f, res);
}
END_TEST

START_TEST(float_decimal_float_3) {
  s21_decimal decimal;
  clear_s21_decimal(&decimal);
  float f = 0, res = 0;
  s21_from_float_to_decimal(f, &decimal);
  s21_from_decimal_to_float(decimal, &res);
  ck_assert_float_eq(f, res);
}
END_TEST


START_TEST(float_to_decimal_56) {
    s21_decimal val;
    float num = -2147483648;
    s21_from_float_to_decimal(num, &val);
    ck_assert_int_eq(val.bits[0], 2147483647);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 2147483648);
}
END_TEST


START_TEST(float_to_decimal_58) {
    s21_decimal val = {0};
    s21_from_float_to_decimal(1.02E+09, &val);
    ck_assert_int_eq(val.bits[0], 1020000000);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(float_to_decimal_60) {
    s21_decimal val = {0};
    float a = 1.0 / 0.0;
    s21_from_float_to_decimal(a, &val);
    ck_assert_int_eq(val.bits[0], 0);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(float_to_decimal_61) {
    s21_decimal val = {0};
    float a = -1.0 / 0.0;
    s21_from_float_to_decimal(a, &val);
    ck_assert_int_eq(val.bits[0], 0);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(float_to_decimal_62) {
    s21_decimal val = {0};
    float a = 1e-30;
    s21_from_float_to_decimal(a, &val);
    ck_assert_int_eq(val.bits[0], 0);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);
}
END_TEST


START_TEST(float_to_decimal_69) {
    s21_decimal dec = {0};
    float a = 1.0 / 0.0;
    int ret = s21_from_float_to_decimal(a, &dec);
    ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(float_to_decimal_70) {
    s21_decimal dec = {0};
    float a = -1.0 / 0.0;
    s21_from_float_to_decimal(a, &dec);
    ck_assert_int_eq(dec.bits[0], 0);
    ck_assert_int_eq(dec.bits[1], 0);
    ck_assert_int_eq(dec.bits[2], 0);
    ck_assert_int_eq(dec.bits[3], 0);
}
END_TEST



START_TEST(float_to_decimal_73) {
    float f = 1.0 / 0.0;
    s21_decimal result = {0};
    s21_decimal check = {{0, 0, 0, 0}};
    int return_value = s21_from_float_to_decimal(f, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(return_value, 1);
}
END_TEST






// FROM_INT_TO_DECIMAL


int a, add, equal;

START_TEST(s21_test_from_int_to_decimal_0) {
  a = 100;
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;

  add = s21_from_int_to_decimal(a, ptr_b);  // a записываем в b
  s21_decimal etalon = {{100, 0, 0, 0}};
  ck_assert_int_eq(add, CONVERTERS_S21_TRUE);
  // выходное значение s21_from_int_to_decimal - 0 TRUE и 1 FALSE
  // s21_is_equal Возвращаемое значение: 0 - FALSE 1 - TRUE
  equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_from_int_to_decimal_1) {
  a = 100;
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;

  add = s21_from_int_to_decimal(a, ptr_b);  // a записываем в b
  s21_decimal etalon = {{1000, 0, 0, 0}};
  ck_assert_int_eq(add, CONVERTERS_S21_TRUE);
  // выходное значение s21_from_int_to_decimal -
  // 0 TRUE и 1 FALSE
  // s21_is_equal Возвращаемое значение: 0 - FALSE 1 - TRUE
  equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, S21_FALSE);
}
END_TEST

START_TEST(s21_test_from_int_to_decimal_2) {
  a = INT_MAX;
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;

  add = s21_from_int_to_decimal(a, ptr_b);  // a записываем в b
  s21_decimal etalon = {{INT_MAX, 0, 0, 0}};
  ck_assert_int_eq(
      add, CONVERTERS_S21_TRUE);  // выходное значение s21_from_int_to_decimal -
                                  // 0 TRUE и 1 FALSE
  // s21_is_equal Возвращаемое значение: 0 - FALSE 1 - TRUE
  equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_from_int_to_decimal_3) {
  a = -INT_MAX;
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;

  add = s21_from_int_to_decimal(a, ptr_b);  // a записываем в b
  s21_decimal etalon = {{INT_MAX, 0, 0, 0}};
  ck_assert_int_eq(
      add, CONVERTERS_S21_TRUE);  // выходное значение s21_from_int_to_decimal -
                                  // 0 TRUE и 1 FALSE
  // s21_is_equal Возвращаемое значение: 0 - FALSE 1 - TRUE
  equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, S21_FALSE);
}
END_TEST

START_TEST(s21_test_from_int_to_decimal_4) {
  a = -INT_MAX;
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;

  add = s21_from_int_to_decimal(a, ptr_b);  // a записываем в b
  s21_decimal etalon = {{INT_MAX, 0, 0, ~(INT_MAX)}};
  ck_assert_int_eq(
      add, CONVERTERS_S21_TRUE);  // выходное значение s21_from_int_to_decimal -
                                  // 0 TRUE и 1 FALSE
  // s21_is_equal Возвращаемое значение: 0 - FALSE 1 - TRUE
  equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, S21_TRUE);
}
END_TEST

START_TEST(s21_test_from_int_to_decimal_5) {
  a = 0;  // ERROR of NAN
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;

  add = s21_from_int_to_decimal(a, ptr_b);  // a записываем в b
  s21_decimal etalon = {{INT_MAX, 0, 0, ~(INT_MAX)}};
  ck_assert_int_eq(
      add, CONVERTERS_S21_TRUE);  // выходное значение s21_from_int_to_decimal -
                                  // 0 TRUE и 1 FALSE
  // s21_is_equal Возвращаемое значение: 0 - FALSE 1 - TRUE
  equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, S21_FALSE);
}
END_TEST

START_TEST(from_int_to_decimal_0) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = 123456789;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(from_int_to_decimal_1) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = -123456789;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest1) {
  // 6412
  int src1 = 1;
  s21_decimal origin, result;
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);

  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest2) {
  // 6428
  int src1 = -1;
  s21_decimal origin, result;
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);

  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest3) {
  // 6444
  int src1 = 0;
  s21_decimal origin, result;
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);

  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest4) {
  // 6460
  int src1 = 0;
  s21_decimal origin, result;
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);

  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest5) {
  // 6476
  int src1 = -987879878;
  s21_decimal origin, result;
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);

  origin.bits[0] = 0b00111010111000011101100111000110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest6) {
  // 6492
  int src1 = -2147483646;
  s21_decimal origin, result;
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);

  origin.bits[0] = 0b01111111111111111111111111111110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest7) {
  // 6508
  int src1 = 2147483646;
  s21_decimal origin, result;
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);

  origin.bits[0] = 0b01111111111111111111111111111110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest8) {
  // 6524
  int src1 = 796132784;
  s21_decimal origin, result;
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);

  origin.bits[0] = 0b00101111011101000000010110110000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest9) {
  // 6540
  int src1 = -12345677;
  s21_decimal origin, result;
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);
  origin.bits[0] = 0b00000000101111000110000101001101;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST


// FROM_DECIMAL_TO_INT

START_TEST(s21_from_decimal_to_int_1) {
  s21_decimal src;
  int result = 0, number = 0;
  src.bits[0] = INT_MAX;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_float_eq(number, 2147483647);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_int_2) {
  s21_decimal src;
  int result = 0, number = 0;
  src.bits[0] = 133141;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 133141);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_int_3) {
  s21_decimal src;
  int result = 0, number = 0;
  src.bits[0] = 2147483647;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  src.bits[3] |= (1 << 31);
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -2147483647);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_int_4) {
  s21_decimal src;
  int result = 0, number = 0;
  long int c = 2147483648;
  src.bits[0] = 123451234;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = c;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -123451234);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_int_5) {
  s21_decimal src;
  int result = 0, number = 0;
  long int c = 2147483648;
  src.bits[0] = 18;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = c;  // 2147483648
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -18);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_int_6) {
  s21_decimal src;
  int result = 0, number = 0;
  long int c = 4294967295;
  src.bits[0] = c;
  src.bits[1] = c;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 0);
  ck_assert_int_eq(result, 1);
}
END_TEST

int check, result, code;

START_TEST(s21_test_from_decimal_to_int_0) {
  s21_decimal a = {{100, 0, 0, 0}};
  check = 100;
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_1) {
  s21_decimal a = {{INT_MAX, 0, 0, 0}};
  check = INT_MAX;
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_2) {
  s21_decimal a = {{INT_MAX, INT_MAX, 0, 0}};
  a.bits[0] |= (1 << 31);
  check = 0;
  code = s21_from_decimal_to_int(a, &result);
  //   ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_3) {
  s21_decimal a = {{INT_MAX, INT_MAX, INT_MAX, 0}};
  check = 0;
  code = s21_from_decimal_to_int(a, &result);
  //   ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_4) {
  s21_decimal a = {{INT_MAX, INT_MAX, INT_MAX, INT_MAX}};
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_6) {
  s21_decimal a = {{U_MAX_INT, U_MAX_INT, 0, 0}};
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_7) {
  s21_decimal a = {{U_MAX_INT, U_MAX_INT, U_MAX_INT, 0}};
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_8) {
  s21_decimal a = {{U_MAX_INT, U_MAX_INT, U_MAX_INT, U_MAX_INT}};
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_9) {
  s21_decimal a = {{INT_MAX, 0, 0, MINUS}};
  check = -INT_MAX;
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_10) {
  s21_decimal a = {{INT_MAX, 0, 0, MINUS}};
  check = -INT_MAX;
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_11) {
  s21_decimal a = {{INT_MAX, 0, 0, EXPONENT_PLUS_1}};
  check = 214748364;  // (int)(INT_MAX / 10^1)
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_12) {
  s21_decimal a = {{INT_MAX, 0, 0, EXPONENT_MINUS_28}};
  check = 0;  // (int)(INT_MAX / 10^28)
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_14) {
  s21_decimal a = {{INT_MAX, 0, 0, EXPONENT_PLUS_28}};
  check = 0;  // (int)(INT_MAX / 10^28)
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_15) {
  s21_decimal a;
  a.bits[0] = 0b10000000000000000000000000000000;
  a.bits[1] = 0b00000000000000000000000000000000;
  a.bits[2] = 0b00000000000000000000000000000000;
  a.bits[3] = 0b00000000000000000000000000000001;
  check = -2147483648;
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_16) {
  s21_decimal a;
  a.bits[0] = 0b00000000000000000000000000000001;
  a.bits[1] = 0b00000000000000000000000000000000;
  a.bits[2] = 0b00000000000000000000000000000000;
  a.bits[3] = 0b00000000000000000000000000000000;
  check = 1;
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_17) {
  s21_decimal a;
  a.bits[0] = 0b10000000000000000000000000000001;
  a.bits[1] = 0b00000000000000000000000000000000;
  a.bits[2] = 0b00000000000000000000000000000000;
  a.bits[3] = 0b00000000000000000000000000000000;
  check = -2147483647;
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest1) {
  // 6556
  s21_decimal src1;
  // src1 = 2;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  int result;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 2);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest2) {
  // 6570
  s21_decimal src1;
  // src1 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  int result;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest3) {
  // 6584
  s21_decimal src1;
  // src1 = 3.5;

  src1.bits[0] = 0b00000000000000000000000000100011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  int result;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 3);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest4) {
  // 6598
  s21_decimal src1;
  // src1 = 4.5;

  src1.bits[0] = 0b00000000000000000000000000101101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  int result;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 4);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest5) {
  // 6612
  s21_decimal src1;
  // src1 = -4.5;

  src1.bits[0] = 0b00000000000000000000000000101101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000010000000000000000;
  int result;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, -4);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest11) {
  // 6696
  s21_decimal src1;
  // src1 = 1;

  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  int result;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest12) {
  // 6710
  s21_decimal src1;
  // src1 = 1.25;

  src1.bits[0] = 0b00000000000000000000000001111101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000100000000000000000;
  int result;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest13) {
  // 6724
  s21_decimal src1;
  // src1 = -1.25;

  src1.bits[0] = 0b00000000000000000000000001111101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000100000000000000000;
  int result;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, -1);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest14) {
  // 6738
  s21_decimal src1;
  // src1 = -12.25;

  src1.bits[0] = 0b00000000000000000000010011001001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000100000000000000000;
  int result;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, -12);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest15) {
  // 6752
  s21_decimal src1;
  // src1 = -3.5;

  src1.bits[0] = 0b00000000000000000000000000100011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000010000000000000000;
  int result;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, -3);
}
END_TEST

Suite* conversion_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("conversion");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, int_decimal_int_1);
  tcase_add_test(tc_core, int_decimal_int_2);
  tcase_add_test(tc_core, int_decimal_int_3);
  tcase_add_test(tc_core, int_decimal_int_4);
  tcase_add_test(tc_core, int_decimal_int_5);
  tcase_add_test(tc_core, int_decimal_int_6);
  tcase_add_test(tc_core, int_decimal_int_7);


  tcase_add_test(tc_core, float_decimal_float_2);
  tcase_add_test(tc_core, float_decimal_float_3);


  tcase_add_test(tc_core, from_float_to_decimal_simple);
  tcase_add_test(tc_core, float_eq_float);
  tcase_add_test(tc_core, float_eq_float_minus);

    tcase_add_test(tc_core, float_to_decimal_56);
    tcase_add_test(tc_core, float_to_decimal_58);
    tcase_add_test(tc_core, float_to_decimal_60);
    tcase_add_test(tc_core, float_to_decimal_61);
    tcase_add_test(tc_core, float_to_decimal_62);
    tcase_add_test(tc_core, float_to_decimal_69);
    tcase_add_test(tc_core, float_to_decimal_70);
    tcase_add_test(tc_core, float_to_decimal_73);




  tcase_add_test(tc_core, s21_test_from_int_to_decimal_0);
  tcase_add_test(tc_core, s21_test_from_int_to_decimal_1);
  tcase_add_test(tc_core, s21_test_from_int_to_decimal_2);
  tcase_add_test(tc_core, s21_test_from_int_to_decimal_3);
  tcase_add_test(tc_core, s21_test_from_int_to_decimal_4);
  tcase_add_test(tc_core, s21_test_from_int_to_decimal_5);
  tcase_add_test(tc_core, s21_from_int_to_decimalTest1);
  tcase_add_test(tc_core, s21_from_int_to_decimalTest2);
  tcase_add_test(tc_core, s21_from_int_to_decimalTest3);
  tcase_add_test(tc_core, s21_from_int_to_decimalTest4);
  tcase_add_test(tc_core, s21_from_int_to_decimalTest5);
  tcase_add_test(tc_core, s21_from_int_to_decimalTest6);
  tcase_add_test(tc_core, s21_from_int_to_decimalTest7);
  tcase_add_test(tc_core, s21_from_int_to_decimalTest8);
  tcase_add_test(tc_core, s21_from_int_to_decimalTest9);
  tcase_add_test(tc_core, from_int_to_decimal_0);
  tcase_add_test(tc_core, from_int_to_decimal_1);


  // grangerc
  tcase_add_test(tc_core, s21_from_decimal_to_int_1);
  tcase_add_test(tc_core, s21_from_decimal_to_int_2);
  tcase_add_test(tc_core, s21_from_decimal_to_int_3);
  tcase_add_test(tc_core, s21_from_decimal_to_int_4);
  tcase_add_test(tc_core, s21_from_decimal_to_int_5);
  tcase_add_test(tc_core, s21_from_decimal_to_int_6);

  tcase_add_test(tc_core, s21_test_from_decimal_to_int_0);
  tcase_add_test(tc_core, s21_test_from_decimal_to_int_1);
  tcase_add_test(tc_core, s21_test_from_decimal_to_int_2);
  tcase_add_test(tc_core, s21_test_from_decimal_to_int_3);
  tcase_add_test(tc_core, s21_test_from_decimal_to_int_4);
  tcase_add_test(tc_core, s21_test_from_decimal_to_int_6);
  tcase_add_test(tc_core, s21_test_from_decimal_to_int_7);
  tcase_add_test(tc_core, s21_test_from_decimal_to_int_8);
  tcase_add_test(tc_core, s21_test_from_decimal_to_int_9);
  tcase_add_test(tc_core, s21_test_from_decimal_to_int_10);
  tcase_add_test(tc_core, s21_test_from_decimal_to_int_11);
  tcase_add_test(tc_core, s21_test_from_decimal_to_int_12);
  tcase_add_test(tc_core, s21_test_from_decimal_to_int_14);
  tcase_add_test(tc_core, s21_test_from_decimal_to_int_15);
  tcase_add_test(tc_core, s21_test_from_decimal_to_int_16);
  tcase_add_test(tc_core, s21_test_from_decimal_to_int_17);
  tcase_add_test(tc_core, s21_from_decimal_to_intTest1);
  tcase_add_test(tc_core, s21_from_decimal_to_intTest2);
  tcase_add_test(tc_core, s21_from_decimal_to_intTest3);
  tcase_add_test(tc_core, s21_from_decimal_to_intTest4);
  tcase_add_test(tc_core, s21_from_decimal_to_intTest5);
  tcase_add_test(tc_core, s21_from_decimal_to_intTest11);
  tcase_add_test(tc_core, s21_from_decimal_to_intTest12);
  tcase_add_test(tc_core, s21_from_decimal_to_intTest13);
  tcase_add_test(tc_core, s21_from_decimal_to_intTest14);
  tcase_add_test(tc_core, s21_from_decimal_to_intTest15);

  suite_add_tcase(s, tc_core);

  return s;
}


// Suite *suite_from_int_to_decimal(void) {
//   Suite *s;
//   TCase *tc_core;
//   s = suite_create("s21_from_int_to_decimal");
//   tc_core = tcase_create("case_from_int_to_decimal");

//   // tcase_add_test(tc_core, s21_from_int_to_decimal_1);

//   tcase_add_test(tc_core, s21_test_from_int_to_decimal_0);
//   tcase_add_test(tc_core, s21_test_from_int_to_decimal_1);
//   tcase_add_test(tc_core, s21_test_from_int_to_decimal_2);
//   tcase_add_test(tc_core, s21_test_from_int_to_decimal_3);
//   tcase_add_test(tc_core, s21_test_from_int_to_decimal_4);
//   tcase_add_test(tc_core, s21_test_from_int_to_decimal_5);
//   tcase_add_test(tc_core, s21_from_int_to_decimalTest1);
//   tcase_add_test(tc_core, s21_from_int_to_decimalTest2);
//   tcase_add_test(tc_core, s21_from_int_to_decimalTest3);
//   tcase_add_test(tc_core, s21_from_int_to_decimalTest4);
//   tcase_add_test(tc_core, s21_from_int_to_decimalTest5);
//   tcase_add_test(tc_core, s21_from_int_to_decimalTest6);
//   tcase_add_test(tc_core, s21_from_int_to_decimalTest7);
//   tcase_add_test(tc_core, s21_from_int_to_decimalTest8);
//   tcase_add_test(tc_core, s21_from_int_to_decimalTest9);
//   tcase_add_test(tc_core, from_int_to_decimal_0);
//   tcase_add_test(tc_core, from_int_to_decimal_1);


//   // grangerc
//   tcase_add_test(tc_core, s21_from_decimal_to_int_1);
//   tcase_add_test(tc_core, s21_from_decimal_to_int_2);
//   tcase_add_test(tc_core, s21_from_decimal_to_int_3);
//   tcase_add_test(tc_core, s21_from_decimal_to_int_4);
//   tcase_add_test(tc_core, s21_from_decimal_to_int_5);
//   tcase_add_test(tc_core, s21_from_decimal_to_int_6);

//   tcase_add_test(tc_core, s21_test_from_decimal_to_int_0);
//   tcase_add_test(tc_core, s21_test_from_decimal_to_int_1);
//   tcase_add_test(tc_core, s21_test_from_decimal_to_int_2);
//   tcase_add_test(tc_core, s21_test_from_decimal_to_int_3);
//   tcase_add_test(tc_core, s21_test_from_decimal_to_int_4);
//   tcase_add_test(tc_core, s21_test_from_decimal_to_int_6);
//   tcase_add_test(tc_core, s21_test_from_decimal_to_int_7);
//   tcase_add_test(tc_core, s21_test_from_decimal_to_int_8);
//   tcase_add_test(tc_core, s21_test_from_decimal_to_int_9);
//   tcase_add_test(tc_core, s21_test_from_decimal_to_int_10);
//   tcase_add_test(tc_core, s21_test_from_decimal_to_int_11);
//   tcase_add_test(tc_core, s21_test_from_decimal_to_int_12);
//   tcase_add_test(tc_core, s21_test_from_decimal_to_int_14);
//   tcase_add_test(tc_core, s21_test_from_decimal_to_int_15);
//   tcase_add_test(tc_core, s21_test_from_decimal_to_int_16);
//   tcase_add_test(tc_core, s21_test_from_decimal_to_int_17);
//   tcase_add_test(tc_core, s21_from_decimal_to_intTest1);
//   tcase_add_test(tc_core, s21_from_decimal_to_intTest2);
//   tcase_add_test(tc_core, s21_from_decimal_to_intTest3);
//   tcase_add_test(tc_core, s21_from_decimal_to_intTest4);
//   tcase_add_test(tc_core, s21_from_decimal_to_intTest5);
//   tcase_add_test(tc_core, s21_from_decimal_to_intTest11);
//   tcase_add_test(tc_core, s21_from_decimal_to_intTest12);
//   tcase_add_test(tc_core, s21_from_decimal_to_intTest13);
//   tcase_add_test(tc_core, s21_from_decimal_to_intTest14);
//   tcase_add_test(tc_core, s21_from_decimal_to_intTest15);




//   suite_add_tcase(s, tc_core);
//   return s;
// }




// /* Данная функция проверяет 32 бита интового числа на совпадение с decimal
// Если биты не одинаковы, то функция возвращает ошибку. Нужна для тестирования
// проекта функции decimal_to_int */
// int check_bits_decimal_int(s21_decimal *src, int num) {
//   int error = 0;
//   for (int i = 0; i < 32; i++) {
//     if (((src->bits[0] & (1 << i)) && !(num & (1 << i))) ||
//         ((src->bits[0] & (1 << i)) && (num & (1 << i)))) {
//       error = 1;
//       break;
//     }
//   }
//   return error;
// }

// int main(void) {
//   int no_failed;
//   Suite *s;
//   Suite *ss;
//   SRunner *runner;

//   s = suite_from_int_to_decimal();
//   ss = suite_from_decimal_to_int();
//   runner = srunner_create(s);
//   srunner_add_suite(runner, ss);
//   srunner_run_all(runner, CK_NORMAL);

//   no_failed = srunner_ntests_failed(runner);
//   srunner_free(runner);
//   return no_failed == 0 ? 0 : 1;
// }
