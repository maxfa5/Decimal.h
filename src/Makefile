CC = gcc
CFLAGS =-std=c11 -lm 
SRC = ariphmetics/*.c converters/*.c small/*.c other/*.c comparisons/*.c
TEST_SRC = tests.c
LIBSFLAGS = -lcheck -lsubunit -lrt -lpthread -lm -lgcov
GCOV_FLAGS = -fprofile-arcs -ftest-coverage  --coverage
LIB = s21_decimal.a
GCOVR_PATH =~/.local/bin/gcovr
REPORT = report/index.html

all : s21_decimal.a

s21_decimal.a:
	rm -rf $(LIB)
	$(CC) $(CFLAGS) -Wall -Werror -Wextra -c $(SRC)
	ar rc $(LIB) *.o
	ranlib $(LIB)
	rm -rf *.o

test: clean s21_decimal.a
	$(CC) $(CFLAGS) -L. -l:$(LIB) $(GCOV_FLAGS) $(SRC) ${TEST_SRC} -o test_result $(LIBSFLAGS)
	./test_result
	
gcov_report: test
	mkdir report
	gcovr -r . --html  --html-details  -o $(REPORT)  -e ${TEST_SRC}
	xdg-open $(REPORT)

clean:
	rm -rf test_result
	rm -rf report
	rm -rf *.gcno
	rm -rf *.gcda

rebuild: clean s21_decimal.a


format:
	clang-format -n *.c other/*.c small/*.c ariphmetics/*.c comparisons/*.c converters/*.c *.h
	clang-format -i *.c other/*.c small/*.c ariphmetics/*.c comparisons/*.c converters/*.c *.h

manual_test:
	$(CC) $(SRC) manual_test.c $(CFLAGS) -o result
