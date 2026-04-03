all: clean s21_string.a test
	./test
	make gcov_report

gcov_report: 
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory out

test: s21_string.o
	gcc -Wall -Werror -Wextra -std=c11 test.c -o test -L. -l:s21_string.a -lcheck -pthread -fprofile-arcs -ftest-coverage

s21_string.a: s21_string.o
	ar rcs s21_string.a s21_string.o

s21_string.o: s21_string.c s21_string.h
	gcc -Wall -Werror -Wextra -std=c11 -c s21_string.c -o s21_string.o

clean:
	rm -rf s21_string.o s21_string.a s21_string test out coverage.info test.gcda test.gcno
