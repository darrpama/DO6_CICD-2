OS := $(shell uname -s)
CC = gcc

ifeq ($(OS), Darwin)
	@CFLAGS = -Wall -Wextra -Werror -std=c11
else
	@CFLAGS = -Wall -Wextra -Werror -std=c11 -D_GNU_SOURCE
endif

all: check s21_cat test clean

s21_cat: s21_cat.o 
	$(CC) $(CFLAGS) s21_cat.o -o s21_cat

s21_cat.o: s21_cat.c s21_cat.h
	$(CC) $(CFLAGS) -c s21_cat.c -o s21_cat.o

clean:
	rm -rf *.o
	rm s21_cat

test:
	chmod 777 tests.sh
	./tests.sh

style: s21_cat
	@cp ../../materials/linters/CPPLINT.cfg ./
	@python3 ./../../materials/linters/cpplint.py --extensions=c s21_cat.c s21_cat.h *.c *.h
	@rm -f CPPLINT.cfg

cppcheck: s21_cat
	@cppcheck s21_cat.c s21_cat.h *.c *.h

check: style cppcheck