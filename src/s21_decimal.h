#ifndef S21_NEW_DECIMAL_H_
#define S21_NEW_DECIMAL_H_

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define EXPONENT_PLUS_1 65536  // Дмитрий
#define EXPONENT_PLUS_2 196608  // Дмитрий
#define MINUS_SIGN 2147483648  // Дмитрий

#define index_start_exp 16  //  Индекс начала секции содержащей коэфициэнт масштабирования
#define length_exp_section 8  //  Длинна секции
#define index_sign_bit 127  //  Индекс содержания знакового бита

typedef struct {
    unsigned int bits[6];
    int sign;
    int exp;
} s21_big_decimal;

typedef struct {
    unsigned int bits[4];
    /**
     * 0 - младшие биты
     * 1 - средние биты
     * 2 - старшие биты
     * 3 - коэффициент масштабирования и знак
     */
} s21_decimal;

//  support func for decimal
void print_bin_num(int num);
void print_decimal(s21_decimal value);
int get_bit(s21_decimal value, int idx);
void set_bit(s21_decimal *value, int idx, int change_value);
void set_exp_for_decimal(s21_decimal *dec, unsigned char exp);
unsigned char get_exp_for_decimal(s21_decimal dec);
//void clear_bits(s21_decimal *value) {

//  преобразование
int s21_big_decimal_to_decimal(s21_big_decimal value, s21_decimal *result);
void s21_decimal_to_big_decimal(s21_decimal value, s21_big_decimal *result);
int s21_from_int_to_decimal(int src, s21_decimal *dst);

// очистка
void clear_big_decimal(s21_big_decimal *value);
void clear_s21_decimal(s21_decimal *dec);


//  support func for big_decimal
int s21_check_big_decimal(s21_big_decimal value);
int s21_big_num_bits(s21_big_decimal value);
int big_get_bit(s21_big_decimal value, int idx);
void big_set_bit(s21_big_decimal *value, int idx, int change_value);
void big_sum(s21_big_decimal value_1, s21_big_decimal value_2, s21_big_decimal *result);
void big_shift(s21_big_decimal *value);
int is_not_big_decimal_zero(s21_big_decimal value);
void s21_big_first_not_zero(s21_big_decimal *value, int i);
int s21_check_is_less(s21_big_decimal value_1, s21_big_decimal value_2);
void print_big_decimal(s21_big_decimal value);
void s21_big_make_same_scale(s21_big_decimal *value1, s21_big_decimal *value2);
int s21_big_is_greater(s21_big_decimal value_1, s21_big_decimal value_2);


int s21_big_is_greater_or_equal(s21_big_decimal value_1, s21_big_decimal value_2);
s21_big_decimal s21_big_division(s21_big_decimal value_1, s21_big_decimal value_2, s21_big_decimal *result);
int s21_big_is_even(s21_big_decimal value);
void s21_big_round_truncate(s21_big_decimal *value);
void s21_big_clear_only_bits(s21_big_decimal *value);
void s21_big_cut_zeros(s21_big_decimal *value);
//int s21_big_count_error(s21_big_decimal *value);
int s21_big_count_error_mul(s21_big_decimal *value);
int s21_big_count_error_div(s21_big_decimal *value);
int s21_big_div(s21_big_decimal value_1, s21_big_decimal value_2, s21_big_decimal *result);


//  основные операции с big_decimal
void s21_big_multiply(s21_big_decimal value_1, s21_big_decimal value_2, s21_big_decimal *result);
int s21_big_mul(s21_big_decimal value_1,s21_big_decimal value_2, s21_big_decimal *result);
void s21_big_minus(s21_big_decimal value_1, s21_big_decimal value_2, s21_big_decimal *result);
int s21_big_is_less(s21_big_decimal value1, s21_big_decimal value2);
int s21_big_is_equal(s21_big_decimal value_1, s21_big_decimal value_2);
int s21_big_is_not_equal(s21_big_decimal value_1, s21_big_decimal value_2);

// основные операции
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

#endif  //  S21_NEW_DECIMAL_H_
