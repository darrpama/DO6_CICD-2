#include "s21_cat.h"

int main(int argc, char** argv) {
    cat_flags flags = {0};
    if (argc > 1) {
        argvCheck(argc, argv, &flags);
        //  printf("Argvcheck = %d", Argvcheck);
    } else {
        printf("Incorrect usage, expected flag or filename");
    }
    return 0;
}

int argvCheck(int argc, char** argv, cat_flags* flags) {
    int err = 0;
    int stopParce = 0;
    cat_state state = {0};
    for (int i = 1; i < argc; i++) {
        char* str = argv[i];
        int FlagsLen = strlen(str);
        int FlagExistingCheck = flagExistingCheck(str);

        if (FlagExistingCheck == 3 && !stopParce) {
            err = parcer1(FlagsLen, str, flags);
        } else if (FlagExistingCheck == 2 && !stopParce) {
            err = parcer2(str, flags);
        } else {
            stopParce = 1;
            int isFile = isFileExist(str);
            if (isFile)
                s21_cat(str, flags, &state);
        }
        if (err)
            printf("Illegal option: %s", str);
    }

    return err;
}

int flagExistingCheck(const char* str) {
    int returnNum = 1;
    if (str[0] != '-')
        returnNum = 1;
    if (str[0] == '-' && str[1] == '-')
        returnNum = 2;
    if (str[0] == '-' && str[1] != '-')
        returnNum = 3;
    return returnNum;
}

int parcer1(int Flagslen, const char* str, cat_flags* flags) {
    int err = 0;
    for (int i = 1; i < Flagslen; i++) {
        char flag = str[i];
        if (flag == 'b') {
            flags->b = 1;
        } else if (flag == 'e') {
            flags->e = 1;
            flags->v = 1;
        } else if (flag == 'E') {
            flags->e = 1;
        } else if (flag == 'n') {
            flags->n = 1;
        } else if (flag == 's') {
            flags->s = 1;
        } else if (flag == 't') {
            flags->t = 1;
            flags->v = 1;
        } else if (flag == 'T') {
            flags->t = 1;
        } else if (flag == 'v') {
            flags->v = 1;
        } else {
            err = 1;
        }
        if (flags->n && flags-> b)
            flags->n = 0;
    }
    return err;
}

int parcer2(const char* str, cat_flags* flags) {
    int err = 0;
    if (strcmp(str, "--number-nonblank") > 0) {
        flags->b = 1;
    } else if (strcmp(str, "--number") > 0) {
        flags->n = 1;
    } else if (strcmp(str, "--squeeze-blank") > 0) {
        flags->s = 1;
    } else {
        err = 1;
    }
    printf("%d", err);
    return err;
}

int isFileExist(const char *filename) {
    int flag = 0;
    FILE *file = NULL;
    if ((file = fopen(filename, "r"))) {
        fclose(file);
        flag = 1;
    } else {
        printf("File doesn't exist");
    }
    return flag;
}

void s21_cat(const char* filename, cat_flags* flags, cat_state* state) {
    FILE* file = NULL;
    char ch, tmpCh = '\n';
    file = fopen(filename, "r");
    state->linenum = 0;
    state->replienum = 0;
    state->nonemptynum = 1;
    while ((ch = getc(file)) != EOF && !feof(file) && !ferror(file)) {
        if (tmpCh == '\n') {
            state->linenum++;
        }
        if (ch == '\n') {
            state->replienum = state->replienum + 1;
        } else {
            state->replienum = 0;
        }
        if (state->replienum > 2 && flags->s == 1) {
            ch = '\0';
        }
        if (ch == '\t' && (flags->t || flags->T)) {
            printf("^");
            ch = 'I';
        }
        if (tmpCh == '\n' && flags->n) {
            printf("%6d\t", state->linenum);
        }
        if (ch == '\n' && (flags->e || flags->E)) {
            printf("$");
        }
        if (tmpCh == '\n' && ch != '\n' && flags->b) {
            printf("%6d\t", state->nonemptynum);
            state->nonemptynum++;
        }
        if ((flags->v)) {
            if ((ch >= 0 && ch < 9) || (ch > 10 && ch <= 31)) {
                ch += 64;
                printf("^");
            } else if (ch == 127) {
                ch -= 64;
                printf("^");
            }
        }
        tmpCh = ch;
        // printf("\nreplienum = %d, linenum = %d\n", state->replienum, state->linenum);
        putchar(ch);
    }
    fclose(file);
}
