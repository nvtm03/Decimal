#include "s21_decimal.h"
#include <stdlib.h>

void print_decimal(s21_decimal value) {
    for (int i = 3; i >= 0; --i)
        print_bin_num(value.bits[i]);
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int ExitCode = 0;
    s21_big_decimal temp_value_1;
    s21_big_decimal temp_value_2;
    s21_big_decimal temp_result;
    clear_big_decimal(&temp_result);
    s21_decimal_to_big_decimal(value_1, &temp_value_1);
    s21_decimal_to_big_decimal(value_2, &temp_value_2);

    if (!is_not_big_decimal_zero(temp_value_2)) {
        ExitCode = 3;
    } else if (is_not_big_decimal_zero(temp_value_1) && !is_not_big_decimal_zero(temp_value_2)) {
        if (temp_value_1.sign != temp_value_2.sign) {
            ExitCode = 2;
        } else {
            ExitCode = 1;
        }
    } else {
        ExitCode = s21_big_div(temp_value_1, temp_value_2, &temp_result);
    }
    if (!ExitCode) {
        s21_big_decimal_to_decimal(temp_result, result);
    }
    return ExitCode;
}

//  всё верно
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_big_decimal temp_value_1;
    s21_big_decimal temp_value_2;
    s21_decimal_to_big_decimal(value_1, &temp_value_1);
    s21_decimal_to_big_decimal(value_2, &temp_value_2);
    s21_big_decimal temp_result;
    clear_big_decimal(&temp_result);

    int ExitCode = s21_big_mul(temp_value_1, temp_value_2, &temp_result);
    if (!ExitCode) {
        s21_big_decimal_to_decimal(temp_result, result);
    }
    return ExitCode;
}

void print_bin_num(int num) {
    for(int i=sizeof(num)*8-1; i>=0; --i){
        printf("%d", num&(1<<i)?1:0);
    }
    printf("  ");
}

int get_bit(s21_decimal value, int idx) {
    int num_bit = idx / 32;
    int idx_in_bit = idx % 32;
    return value.bits[num_bit] & 1u << idx_in_bit ? 1 : 0;
}

void set_bit(s21_decimal *value, int idx, int change_value) {
    int num_bit = idx / 32;
    int idx_in_bit = idx % 32;
    if (get_bit(*value, idx)) {
        if (!change_value) {
            value->bits[num_bit] &= ~(1u << idx_in_bit);
        }
    } else {
        if (change_value) {
            value->bits[num_bit] |= 1u << idx_in_bit;
        }
    }
}



void clear_s21_decimal(s21_decimal *dec) {
    dec->bits[0] = 0;
    dec->bits[1] = 0;
    dec->bits[2] = 0;
    dec->bits[3] = 0;
}

void set_exp_for_decimal(s21_decimal *dec, unsigned char exp) {
    int cBit = 0;
    for (int bit = 16; bit < index_start_exp + length_exp_section; ++bit) {
        bool b = (1 << cBit) & exp;
        cBit++;

        if (b)
            dec->bits[3] |= (1 << bit);
        else
            dec->bits[3] &= ~(1 << bit);
    }
}

unsigned char get_exp_for_decimal(s21_decimal dec) {
    unsigned char result = 0;
    int cBit = 0;
    for (int bit = 16; bit < index_start_exp + length_exp_section; ++bit) {
        bool b = (1 << bit) & dec.bits[3];

        if (b)
            result |= (1 << cBit);
        else
            result &= ~(1 << cBit);

        cBit++;
    }
    return result;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
    s21_big_decimal temp_value_1;
    s21_big_decimal temp_value_2;
    s21_decimal_to_big_decimal(value_1, &temp_value_1);
    s21_decimal_to_big_decimal(value_2, &temp_value_2);
    int ExitCode = s21_big_is_less(temp_value_1, temp_value_2);
    return ExitCode;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
    s21_big_decimal temp_value_1;
    s21_big_decimal temp_value_2;
    s21_decimal_to_big_decimal(value_1, &temp_value_1);
    s21_decimal_to_big_decimal(value_2, &temp_value_2);
    int ExitCode = s21_big_is_equal(temp_value_1, temp_value_2);
    return ExitCode;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
    return !s21_is_equal(value_1, value_2);
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
    return s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2);
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
    return !s21_is_less_or_equal(value_1, value_2);
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
    return !s21_is_less(value_1, value_2);
}

int s21_negate(s21_decimal value, s21_decimal *result) {
    int ExitCode = 1;
    if (get_exp_for_decimal(value) < 29) {
        set_bit(&value, index_sign_bit, !get_bit(value, index_sign_bit));
        *result = value;
        ExitCode = 0;
    }
    return ExitCode;
}


int s21_floor(s21_decimal value, s21_decimal *result) {
    int ExitCode = 0;
    if (get_exp_for_decimal(value) < 29) {
        s21_big_decimal temp_value;
        s21_big_decimal ten = {{10}, 0, 0};
        s21_big_decimal one = {{1}, 0, 0};
        s21_decimal_to_big_decimal(value, &temp_value);
        if (temp_value.exp != 0) {
            if (!(!is_not_big_decimal_zero(temp_value) && temp_value.sign)) {
                while (temp_value.exp != 0) {
                    s21_big_division(temp_value, ten, &temp_value);
                    --temp_value.exp;
                }
                if (temp_value.sign) {
                        big_sum(temp_value, one, &temp_value);
                }
            } else {
                temp_value.exp = 0;
            }
        } else {
            if (!is_not_big_decimal_zero(temp_value)) {
                temp_value.sign = 0;
            }
        }
        s21_big_decimal_to_decimal(temp_value, result);
    } else {
        ExitCode = 1;
    }
    return ExitCode;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
    int ExitCode = 0;
    if (get_exp_for_decimal(value) < 29) {
        s21_big_decimal temp_value;
        s21_big_decimal ten = {{10}, 0, 0};
        s21_decimal_to_big_decimal(value, &temp_value);
        while (temp_value.exp != 0) {
                    s21_big_division(temp_value, ten, &temp_value);
                    --temp_value.exp;
        }
        s21_big_decimal_to_decimal(temp_value, result);
    } else {
        ExitCode = 1;
    }
    return ExitCode;
}

int s21_round(s21_decimal value, s21_decimal *result) {
    int ExitCode = 0;
    if (get_exp_for_decimal(value) < 29) {
        s21_big_decimal temp_value;
        s21_big_decimal ten = {{10}, 0, 0};
        s21_big_decimal one = {{1}, 0, 0};
        s21_decimal_to_big_decimal(value, &temp_value);
        s21_big_decimal remainder;
        clear_big_decimal(&remainder);
        while (temp_value.exp != 0) {
            remainder = s21_big_division(temp_value, ten, &temp_value);
            --temp_value.exp;
        }
        if (remainder.bits[0] >= 5) {
            big_sum(temp_value, one, &temp_value);
        }
        s21_big_decimal_to_decimal(temp_value, result);
    } else {
        ExitCode = 1;
    }
    return ExitCode;
}

int s21_big_is_not_equal(s21_big_decimal value_1, s21_big_decimal value_2) {
    return !s21_big_is_equal(value_1, value_2);
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int ExitCode = 0;
    s21_big_decimal temp_value_1;
    s21_big_decimal temp_value_2;
    s21_big_decimal temp_result;
    s21_decimal_to_big_decimal(value_1, &temp_value_1);
    s21_decimal_to_big_decimal(value_2, &temp_value_2);
    clear_big_decimal(&temp_result);
    if (temp_value_1.exp != temp_value_2.exp) {
        s21_big_make_same_scale(&temp_value_1, &temp_value_2);
    }
    if (is_not_big_decimal_zero(temp_value_1) || is_not_big_decimal_zero(temp_value_2)) {
    
    if (temp_value_1.sign != temp_value_2.sign) {
        if (temp_value_1.sign) {
            s21_big_minus(temp_value_1, temp_value_2, &temp_result);
            if (s21_big_is_greater_or_equal(temp_value_1, temp_value_2) && s21_big_is_not_equal(temp_value_1, temp_value_2)) {
                temp_result.sign = 1;
            }
        } else {
             s21_big_minus(temp_value_1, temp_value_2, &temp_result);
            
            if (s21_big_is_greater_or_equal(temp_value_2, temp_value_1) && s21_big_is_not_equal(temp_value_1, temp_value_2)) {
                temp_result.sign = 1;
            }
        }
        temp_result.exp = temp_value_1.exp;
    } else {
        big_sum(temp_value_1, temp_value_2, &temp_result);
        if (temp_value_1.sign) {
            temp_result.sign = 1;
        }
        temp_result.exp = temp_value_1.exp;
    }
        if (!is_not_big_decimal_zero(temp_result)) {
            temp_result.sign = 0;
        }
    } else {
        temp_result.sign = temp_value_1.sign && temp_value_2.sign;
        temp_result.exp = temp_value_1.exp;
    }
    ExitCode = s21_big_count_error_div(&temp_result);
    if (!ExitCode) {
        s21_big_decimal_to_decimal(temp_result, result);
    }
    return ExitCode;   
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int ExitCode = 0;
    set_bit(&value_2, index_sign_bit, !get_bit(value_2, index_sign_bit));
    ExitCode = s21_add(value_1, value_2, result);
    return ExitCode;
}

//  grangerc
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  clear_s21_decimal(dst);  //Обнуляем decimal
  if (src < 0) {
    set_bit(dst, index_sign_bit, 1);
    src = -src;
  }  // если число отрицательное, меняем знак числа и устанавливаем знак в
     // decimal
  dst->bits[0] = src;
  return 0;
}

//  grangerc
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int conversation_result = 0;  // результат преобразования: 0 - ОК, 1 - НЕ ОК
  int sign = 1;  //параметр знака
  unsigned char scale = get_exp_for_decimal(src);
  if (!dst || (src.bits[1] || src.bits[2])) {
    conversation_result = 1;
  } else {
    if (get_bit(src, index_sign_bit)) {
      sign = -1;
    }
    if (scale > 0 && scale <= 28) {
      *dst = (src.bits[0] / pow(10, scale)) * sign;
    } else {
      *dst = src.bits[0] * sign;
    }
  }
  return conversation_result;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    int ExitCode = 0;
    int exp = get_exp_for_decimal(src);
    if (dst != NULL && exp < 29) {
        long double temp_dst = 0.0;
        for (int i = 0; i < 96; ++i) {
            if (get_bit(src, i)) {
                temp_dst += pow(2, i);
            }
        }
        if (get_bit(src, index_sign_bit)) {
            temp_dst = -temp_dst;
        }
        if (exp) {
            temp_dst /= pow(10, exp);
        }
        *dst = temp_dst;
    } else {
        ExitCode = 1;
    }
    return ExitCode;
}

int s21_float_num_bits(float value) {
    int i = 0;
    for (; i < 23 && !(*(int *)&value & (1u << i)); ++i);
    return i;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    int ExitCode = 0;
    float max_float = 79228162514264337593543950335.0;
    float min_float = 1.0e-28;
    clear_s21_decimal(dst);
    if (fabs(src) < max_float && fabs(src) > min_float) {
        int exp = ((*(int *)&src & ~(1u << 31)) >> 23) - 127;
        int temp = 0;
        int i = s21_float_num_bits(src);
        int temp_i = 0;
        int flag = 0;
        for (; i <= 22; ++i) {
            if (*(int *)&src & (1u << i)) {
                temp |= (1u << temp_i);
                if (!flag) {
                    exp += i - 23;
                    flag = 1;
                }
            }
            ++temp_i;
        }
        temp |= (1u << temp_i);
        s21_decimal first;
        s21_from_int_to_decimal(temp, &first);
        s21_decimal second;
        s21_from_int_to_decimal(pow(2, abs(exp)), &second);
        if (exp < 0) {
            s21_div(first, second, dst);
        } else {
            s21_mul(first, second, dst);
        }
        if (src < 0) {
            set_bit(dst, index_sign_bit, 1);
        }
    } else {
        ExitCode = 1;
    }
    return ExitCode;
}


