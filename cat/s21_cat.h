#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct cat_flags {
    int b, e, n, s, t, v, E, T;
} cat_flags;

typedef struct cat_state {
    int linenum, replienum, emptynum, numflag, nonemptynum;
    char cuCh;
} cat_state;

int argvCheck(int argc, char** argv, cat_flags* flags);
int flagExistingCheck(const char* str);
int parcer1(int Flagslen, const char* str, cat_flags* flags);
int parcer2(const char* str, cat_flags* flags);
int isFileExist(const char* filename);
void s21_cat(const char* filename, cat_flags* flags, cat_state* state);

#endif  // SRC_CAT_S21_CAT_H_
