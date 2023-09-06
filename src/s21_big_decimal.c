#include "s21_decimal.h"

void print_big_decimal(s21_big_decimal value) {
    printf("exp: %d\n", value.exp);
    printf("sign: %d\nbits:\n", value.sign);

    for (int i = 5; i >= 0; --i) {
        print_bin_num(value.bits[i]);
    }
    printf("\n");
}


int s21_big_div(s21_big_decimal value_1, s21_big_decimal value_2, s21_big_decimal *result) {
    int ExitCode = 0;
    if (value_1.exp != value_2.exp) {
        s21_big_make_same_scale(&value_1, &value_2);
    }
    s21_big_decimal ten = {{10}, 0, 0};
    if (value_1.sign != value_2.sign) {
        result->sign = 1;
    }
    while(s21_check_is_less(value_1, value_2) && is_not_big_decimal_zero(value_1)) {
        s21_big_multiply(value_1, ten, &value_1);
        ++result->exp;
    }
    s21_big_decimal temp;
    while (is_not_big_decimal_zero(value_1) && result->exp <= 28) {
        s21_big_multiply(value_1, ten, &value_1);
        clear_big_decimal(&temp);

        if (s21_big_is_greater_or_equal(value_1, value_2)) {
            value_1 = s21_big_division(value_1, value_2, &temp);
            s21_big_multiply(*result, ten, result);
            big_sum(*result, temp, result);
            ++result->exp;
        }
    }
    if (!is_not_big_decimal_zero(*result)) {
        result->sign = 0;
    }
    ExitCode = s21_big_count_error_div(result);
    return ExitCode;
}

///  вычитание двух числа типа big_decimal, без учёта знака и степени (только мантисса)
void s21_big_minus(s21_big_decimal value_1, s21_big_decimal value_2, s21_big_decimal *result) {
    int bit_1 = 0;
    int bit_2 = 0;
    clear_big_decimal(result);
    s21_big_decimal temp_value_1 = value_1;
    s21_big_decimal temp_value_2 = value_2;
    if (s21_check_is_less(value_1, value_2)) {
        temp_value_1 = value_2;
        temp_value_2 = value_1;
    }
    for (int i = 0; i < 192; ++i) {
        bit_1 = big_get_bit(temp_value_1, i);
        bit_2 = big_get_bit(temp_value_2, i);
        if (bit_1 != bit_2) {
            if (bit_1) {
                big_set_bit(result, i, 1);
            } else {
                s21_big_first_not_zero(&temp_value_1, i);
                big_set_bit(result, i, 1);
            }
        }
    }
}

//  если из нуля вычитаем один, то пока не встертим 1 у нас будут 1, потом вместо этой 1 делаем 0
void s21_big_first_not_zero(s21_big_decimal *value, int i) {
    for (; big_get_bit(*value, i) == 0; ++i) {
        big_set_bit(value, i, 1);
    }
    big_set_bit(value, i, 0);
}

int s21_check_is_less(s21_big_decimal value_1, s21_big_decimal value_2) {
    int ExitCode = 0;
    int num_1 = s21_big_num_bits(value_1);
    int num_2 = s21_big_num_bits(value_2);
    if (num_1 / 32 != num_2 / 32) {
        if (num_1 < num_2) {
            ExitCode = 1;
        }
    } else {
        for (int i = 5; i > -1; --i) {
            if (value_1.bits[i] < value_2.bits[i]) {
                ExitCode = 1;
                i = -1;
            }
        }
    }
    return ExitCode;
}

//  перемножает два числа типа big_decimal с учётом знаков и степени
int s21_big_mul(s21_big_decimal value_1,s21_big_decimal value_2, s21_big_decimal *result) {
/**
 * перемножает два числа типа big_decimal
 * @param value_1
 * @param value_2
 * @param result
 * @return выдает код ошибки согласно заданию
 */
    int ExitCode = 0;
    clear_big_decimal(result);
    if (is_not_big_decimal_zero(value_1) && is_not_big_decimal_zero(value_2)) {
        s21_big_multiply(value_1, value_2, result);
        //  умножение(сложение) степеней big_decimal чисел
        result->exp = value_1.exp + value_2.exp;
    }
    if (value_1.sign != value_2.sign) {
        result->sign = 1;
    }
    
    //  выдает код ошибки
    ExitCode = s21_big_count_error_mul(result);
    return ExitCode;
}

//  умножает два числа типа big_decimal без учета степени и знака (умножает только мантиссу)
void s21_big_multiply(s21_big_decimal value_1, s21_big_decimal value_2, s21_big_decimal *result) {
    s21_big_clear_only_bits(result);
    s21_big_decimal temp = value_1;
    if (is_not_big_decimal_zero(value_1) && is_not_big_decimal_zero(value_2)) {    
        for (int i = 0; i <= s21_big_num_bits(value_2); ++i) {
            if (big_get_bit(value_2, i)) {
                big_sum(temp, *result, result);
            }
            big_shift(&temp);
        }
    }
}

//  сдвигает все число типа big_decimal на одну позицию влево(=сильно << 1 )
void big_shift(s21_big_decimal *value) {
    for (int i = s21_big_num_bits(*value) + 1; i > 0; --i) {
        big_set_bit(value, i, big_get_bit(*value, i - 1));
    }
    big_set_bit(value, 0, 0);
}

//  суммирует два числа типа big_decimal(не учитывает exp и sign, суммирует только мантиссу)
void big_sum(s21_big_decimal value_1, s21_big_decimal value_2, s21_big_decimal *result) {
    int bit_1 = 0;
    int bit_2 = 0;
    int extra = 0;
    s21_big_clear_only_bits(result);
    for (int i = 0; i < 192; ++i) {
        bit_1 = big_get_bit(value_1, i);
        bit_2 = big_get_bit(value_2, i);
        if (bit_1 != bit_2) {
            if (extra) {
                big_set_bit(result, i, 0);
            } else {
                big_set_bit(result, i, 1);
            }
        } else {
            if (bit_1) {
                if (extra) {
                    big_set_bit(result, i, 1);
                } else {
                    big_set_bit(result, i, 0);
                }
                extra = 1;
            } else {
                if (extra) {
                    big_set_bit(result, i, 1);
                    extra = 0;
                } else {
                    big_set_bit(result, i, 0);
                }
            }
        }
    }
}

int big_get_bit(s21_big_decimal value, int idx) {
    int num_bit = idx / 32;
    int idx_in_bit = idx % 32;
    return value.bits[num_bit] & 1u << idx_in_bit ? 1 : 0;
}

// возвращает индекс первой единицы в числе типа big_decimal
int s21_big_num_bits(s21_big_decimal value) {
    int i = 191;
    for (; i > -1 && !big_get_bit(value, i); i--);
    return i;
}

void big_set_bit(s21_big_decimal *value, int idx, int change_value) {
    int num_bit = idx / 32;
    int idx_in_bit = idx % 32;
    if (big_get_bit(*value, idx)) {
        if (!change_value) {
            value->bits[num_bit] &= ~(1u << idx_in_bit);
        }
    } else {
        if (change_value) {
            value->bits[num_bit] |= 1u << idx_in_bit;
        }
    }
}

int is_not_big_decimal_zero(s21_big_decimal value) {
    /**
     * @brief проверка на неравенство нулю числа типа big_decimal 
     * @param value
     * @return 1 - равно нулю;  0 - не равно нулю
     */
    int result = 0;
    for (int i = 0; i < 6; ++i) {
        if (value.bits[i] != 0) {
            result = 1;
            //  break;
        }
    }
    return result;
}

void s21_decimal_to_big_decimal(s21_decimal value, s21_big_decimal *result) {
/**
 * переводит число из decimal в big_decimal
 * @param value
 * @return возращает число типа big_decimal
 */
    // s21_big_decimal result;
    clear_big_decimal(result);
    result->sign = get_bit(value, index_sign_bit);  //  get_sign_bit_for_decimal(value);
    result->exp = get_exp_for_decimal(value);
    for (int i = 0; i < 3; ++i)
        result->bits[i] = value.bits[i];
}

int s21_big_decimal_to_decimal(s21_big_decimal value, s21_decimal *result) {
/**
 * переводит число из big_decimal в decimal
 * @param value
 * @return 0 - число поместилось  1 - число не поместилось
 */
    int ExitCode = 0;
    //s21_decimal result;
    clear_s21_decimal(result);
    if (s21_check_big_decimal(value) && value.exp < 29) {
        for (int i = 0; i < 3; ++i) {
            result->bits[i] = value.bits[i];
            set_exp_for_decimal(result, value.exp);
            set_bit(result, index_sign_bit, value.sign);
            //set_sign_bit_for_decimal(&result, value.sign);
        }
    } else {
        ExitCode = 1;
        for (int i = 0; i < 4; ++i)
            result->bits[i] = 0;
    }
    return ExitCode;
}

void clear_big_decimal(s21_big_decimal *value) {
/**
 * очищает число типа big_decimal
 * @param value
 * @return возращает число типа big_decimal
 */
    value->exp = 0;
    value->sign = 0;
    for (int i = 0; i < 6; ++i)
        value->bits[i] = 0;
}

void s21_big_clear_only_bits(s21_big_decimal *value) {
    for (int i = 0; i < 6; ++i)
        value->bits[i] = 0;
}

int s21_check_big_decimal(s21_big_decimal value) {
/**
 * проверяет, что big_decimal сможет поместиться в decimal
 * @param value
 * @return 1 - поместится; 0 - не поместится
 */
    int result = 0;
    if (value.bits[3] == 0 && value.bits[4] == 0 && value.bits[5] == 0)
        result = 1;
    return result;
}

//  приводит числа типа big_decimnal к одной степени
//  (и ,соответственно, умножает число, если его стпень увеличивается)
void s21_big_make_same_scale(s21_big_decimal *value1, s21_big_decimal *value2) {
    s21_big_decimal temp_ten = {{10}, 0, 0};
    if (value1->exp > value2->exp) {
        for (int i = value1->exp - value2->exp; i > 0; --i) {
            s21_big_multiply(*value2, temp_ten, value2);
        }
        value2->exp = value1->exp;
    } else {
        for (int i = value2->exp - value1->exp; i > 0; --i) {
            s21_big_multiply(*value1, temp_ten, value1);
        }
        value1->exp = value2->exp;
    }
}

int s21_big_is_less(s21_big_decimal value1, s21_big_decimal value2) {
    int ExitCode = 0;
    if (memcmp(value1.bits, value2.bits, 6 * sizeof(unsigned int)) != 0) {
        if (value1.exp != value2.exp) {
            s21_big_make_same_scale(&value1, &value2);
        }
        if (value1.sign == value2.sign) {
            if (value1.sign) {
                ExitCode = !s21_check_is_less(value1, value2);
            } else {
                ExitCode = s21_check_is_less(value1, value2);
            }
        } else {
            ExitCode = value1.sign ? 1 : 0;
        }
    } else if (value1.exp != value2.exp) {
        if (value1.sign) {
            ExitCode = value1.exp > value2.exp ? 0 : 1;
        } else {
            ExitCode = value1.exp > value2.exp ? 1 : 0;
        }
    } else {
        ExitCode = value1.sign > value2.sign ? 1 : 0;
    }
    return ExitCode;
}

int s21_big_is_equal(s21_big_decimal value_1, s21_big_decimal value_2) {
    s21_big_make_same_scale(&value_1, &value_2);
    int ExitCode = !memcmp(value_1.bits, value_2.bits, 6 * sizeof(unsigned int));
    ExitCode *= value_1.sign == value_2.sign;
    return ExitCode;
}

int s21_big_is_greater_or_equal(s21_big_decimal value_1, s21_big_decimal value_2) {
    return !s21_check_is_less(value_1, value_2);
}

int s21_big_is_greater(s21_big_decimal value_1, s21_big_decimal value_2) {
    return !(s21_check_is_less(value_1, value_2) && s21_big_is_equal(value_1, value_2));
}

//  возвращает целую часть в result;  и остаток в remainder
s21_big_decimal s21_big_division(s21_big_decimal value_1, s21_big_decimal value_2, s21_big_decimal *result) {
    s21_big_decimal remainder;
    clear_big_decimal(&remainder);
    s21_big_clear_only_bits(result);

    for (int i = s21_big_num_bits(value_1); i >= 0; --i) {
        big_shift(&remainder);
        big_set_bit(&remainder, 0, big_get_bit(value_1, i));

        if (s21_big_is_greater_or_equal(remainder, value_2)) {
            big_set_bit(result, i, 1);
            s21_big_minus(remainder, value_2, &remainder);
        }
    }
    return remainder;
}

//  возваращает  1 -- если число четное, 0 -- число нечетное
int s21_big_is_even(s21_big_decimal value) {
    s21_big_decimal two = {{2}, 0, 0};
    s21_big_decimal result;
    s21_big_decimal remainder = s21_big_division(value, two, &result);
    return !big_get_bit(remainder, 0);
}

void s21_big_round_truncate(s21_big_decimal *value) {
    s21_big_decimal max_s21_decimal = {{4294967295, 4294967295, 4294967295, 0, 0, 0}, 0, 0};
    s21_big_decimal ten = {{10, 0, 0, 0, 0, 0}, 0, 0};
    s21_big_decimal one = {{1, 0, 0, 0, 0, 0}, 0, 0};
    s21_big_decimal remainder = {{0}, 0 , 0};
    while (s21_check_is_less(max_s21_decimal, *value) && value->exp > 0) {
        //s21_big_decimal temp_value;
        remainder = s21_big_division(*value, ten, value);
        --value->exp;
    }
    while (value->exp > 28) {
        remainder = s21_big_division(*value, ten, value);
        --value->exp;
    }
    if ((remainder.bits[0] == 5 && !s21_big_is_even(*value)) || remainder.bits[0] > 5) {
        big_sum(*value, one, value);
    }
}


//  если есть нули обрезает их и уменьшает степень
void s21_big_cut_zeros(s21_big_decimal *value) {
    s21_big_decimal ten = {{10, 0, 0, 0, 0, 0}, 0, 0};
    s21_big_decimal remainder;
    s21_big_decimal result = *value;
    s21_big_clear_only_bits(&result);

    int temp = 1;
    while (temp) {
        remainder = s21_big_division(*value, ten, &result);
        if (!is_not_big_decimal_zero(remainder) && value->exp > 0) {
            --result.exp;
            *value = result;
        } else {
            temp = 0;
        }
    }
}


int s21_big_count_error_div(s21_big_decimal *value) {
    int ExitCode = 0;
    s21_big_decimal max_s21_decimal = {{4294967295, 4294967295, 4294967295, 0, 0, 0}, 0, 0};
    //s21_big_decimal min_s21_decimal = {{1}, 0, 28};
    s21_big_cut_zeros(value);
    s21_big_round_truncate(value);

    if (s21_check_is_less(max_s21_decimal, *value) && !value->sign) {
        ExitCode = 1;
    } else if ((s21_check_is_less(max_s21_decimal, *value) && value->sign) || value->exp > 28 ) {  //s21_check_is_less(min_s21_decimal, *value)) { //  s21_check_is_less(min_s21_decimal, *value)
        ExitCode = 2;
    }
    return ExitCode;
}

int s21_big_count_error_mul(s21_big_decimal *value) {
    int ExitCode = 0;
    s21_big_decimal max_s21_decimal = {{4294967295, 4294967295, 4294967295, 0, 0, 0}, 0, 0};
    //s21_big_decimal min_s21_decimal = {{1}, 0, 28};
    s21_big_cut_zeros(value);
    //s21_big_round_truncate(value);

    if (s21_check_is_less(max_s21_decimal, *value) && !value->sign) {
        ExitCode = 1;
    } else if ((s21_check_is_less(max_s21_decimal, *value) && value->sign) || value->exp > 28 ) {  //s21_check_is_less(min_s21_decimal, *value)) { //  s21_check_is_less(min_s21_decimal, *value)
        ExitCode = 2;
    }
    return ExitCode;
}