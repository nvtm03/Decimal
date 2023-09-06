#ifndef SRC_TESTS_TEST_MAIN_H_
#define SRC_TESTS_TEST_MAIN_H_
#define MINUS_SIGN 2147483648
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "s21_decimal.h"
Suite* suite_s21_sub(void);
Suite* suite_s21_mul(void);
Suite* suite_s21_add(void);
Suite* suite_s21_div(void);
Suite* comparsion_suite(void);
Suite* conversion_suite(void);
Suite* floor_suite(void);
Suite* round_suite(void);
Suite* truncate_suite(void);
Suite* negate_suite(void);
void do_suite(Suite* suite, int* res);
#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

typedef enum {
  OPERATION_OK = 0,
  NUMBER_TOO_BIG,
  NUMBER_TOO_SMALL,
  DIVISION_BY_ZERO
} operation_result;

typedef enum {
  CONVERTATION_OK = 0,
  CONVERTATION_ERROR = 1
} convertation_result;

#endif  //  SRC_TESTS_TEST_MAIN_H_
