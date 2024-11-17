CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11 -D_GNU_SOURCE

all: clean s21_grep

s21_grep:
	${CC} ${CFLAGS} s21_grep.c -o s21_grep

s21_grep_test:
	${CC} ${CFLAGS} -lcheck ./s21_grep_test.c -o s21_grep_test

clean:
	rm -rf s21_grep.d* s21_grep_test s21_grep s21_grep_test.g*s s21_grep_test.g* ../common/tmp*

check: s21_grep s21_grep_test
	cp ../../materials/linters/CPPLINT.cfg ./
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	python3 ../../materials/linters/cpplint.py --extensions=c *.c *.h
	CK_FORK=no leaks -atExit -- ./s21_grep
	CK_FORK=no leaks -atExit -- ./s21_grep_test
	rm -rf *.cfg

style: s21_grep
	cp ../../materials/linters/CPPLINT.cfg ./
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	python3 ../../materials/linters/cpplint.py --extensions=c *.c *.h
	rm -rf *.cfg

test: s21_grep s21_grep_test
	./s21_grep_test
	make clean

rebuild: clean all