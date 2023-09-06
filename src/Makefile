GCC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
SRC = s21_decimal.c s21_big_decimal.c
OBJ = $(SRC:%.c=%.o)
TEST =  tests.c s21_big_decimal.c s21_decimal.c ./tests/*.c

all: s21_decimal.a test gcov_report
s21_decimal.a: $(OBJ)
	ar rcs s21_decimal.a $^
	rm *.o
%.o: %.c
	$(GCC)  $(FLAGS) -c $< -o $@ 
test: 
	$(GCC) $(FLAGS) -coverage $(TEST) \
	 -lcheck $(shell pkg-config --cflags --libs check) -o $@
	./$@
gcov_report: test
	lcov -t "tests" -o test.info -c -d . 
	genhtml -o test_output test.info
	@cd ./test_output ; open index.html
	rm *.gcda *.gcno test.info
clean:
	rm -rf ./test_output/
	rm *.a test