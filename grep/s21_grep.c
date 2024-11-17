#include "s21_grep.h"

int main(int argc, char **argv) {
    if (argc > 2)
        s21_grep(argc, argv);
    else
        printf("Incorrect usage, expected [-eivclnhsfo] [pattern or filename with pattern] [filename]\n");
    return 0;
}

void s21_grep(int argc, char **argv) {
    int kArgc = argc;
    t_pattern patns[kArgc];
    init_patterns(patns, kArgc);
    int patns_cnt = 0;
    int flags[10] = {0};
    get_flags(argc, argv, patns, &patns_cnt, flags);
    scan_files(argc, argv, patns, patns_cnt, flags);
}

void scan_files(int argc, char **argv, t_pattern *patns, int patns_cnt, int *flags) {
    int kFiles_cnt = cnt_files(argc, argv);
    if (kFiles_cnt) {
        t_file files[kFiles_cnt];
        init_files(files, kFiles_cnt);
        get_files(argc, argv, files);
        files_processing(patns, patns_cnt, files, kFiles_cnt, flags);
    } else {
        printf("No files found");
    }
}

void files_processing(t_pattern *patns, int patns_cnt, t_file *files, int files_cnt, int *flags) {
    int empty_line = is_empty_line_in_patterns(patns, patns_cnt);
    int maching_lines = 0;
    for (int i = 0; i < files_cnt; i++) {
        FILE *fd = fopen(files[i].file_name, "r");
        if (fd) {
            if (empty_line) {
                if (flags[L] || flags[C] || (flags[O] && !flags[V]) ||
                    !(flags[V] && flags[O])) {
                    maching_lines = print_all(fd, flags, files + i, files_cnt);
                }
            } else {
                maching_lines = seek_in_file(fd, patns, patns_cnt, flags,
                                             files + i, files_cnt);
            }
            fclose(fd);
        } else {
            if (!flags[S]) printf("No such file or directory\n");
            files[i].valid = 0;
        }
        if (flags[C]) print_files_c(files + i, files_cnt, maching_lines, flags);
        if (flags[L]) print_files_l(files + i, maching_lines);
    }
}

int print_all(FILE *fd, int *flags, t_file *file, int files_cnt) {
    char *line = NULL;
    int line_number = 0;
    size_t size = 0;
    while (getline(&line, &size, fd) != -1) {
        if (line) {
            trim_n(line);
            line_number++;
            if (!flags[C] && !flags[L]) {
                if (strlen(line) == 1 && line[0] == '.') line[0] = '\0';
                if (!flags[H] && files_cnt > 1) printf("%s:", file->file_name);
                if (flags[N]) printf("%d:", line_number);
                printf("%s\n", line);
            }
        }
    }
    free(line);
    return line_number;
}

void print_files_c(t_file *file, int files_cnt, int maching_lines,
                   const int *flags) {
    if (!flags[H] && files_cnt > 1) printf("%s:", file->file_name);
    if (!flags[L])
        printf("%d\n", maching_lines);
    else
        printf("%d\n", maching_lines > 0 ? 1 : 0);
}

void print_files_l(t_file *file, int maching_lines) {
    if (maching_lines > 0) printf("%s\n", file->file_name);
}

int is_empty_line_in_patterns(t_pattern *patns, int patns_cnt) {
    int res = 0;
    for (int i = 0; i < patns_cnt; i++) {
        if (patns[i].is_file) {
            char *line = NULL;
            size_t size = 0;
            FILE *fd = fopen(patns[i].file_name, "r");
            if (fd) {
                while (getline(&line, &size, fd) != -1)
                    if (line && is_empty_line(line)) res = 1;
                fclose(fd);
                free(line);
            }
        } else {
            if (is_empty_line(patns[i].name)) res = 1;
        }
    }
    return res;
}

int is_empty_line(char *name) { return (strlen(name) == 1 && name[0] == '\n'); }

int seek_in_file(FILE *fd, t_pattern *patns, int patns_cnt, int *flags,
                 t_file *file, int files_cnt) {
    int matching_lines = 0;
    int line_number = 0;
    size_t size = 0;
    char *line = NULL;
    while (getline(&line, &size, fd) != -1) {
        if (line) {
            int one_time_print = 1;
            line_number++;
            trim_n(line);
            for (int i = 0; i < patns_cnt; i++) {
                int file_name_print = 1;
                seek_choice(line, patns + i, file, flags, &matching_lines,
                            files_cnt, line_number, &one_time_print,
                            &file_name_print);
            }
            if (flags[V] && one_time_print == 1) {
                print_match(line, flags, file, files_cnt, line_number,
                            &one_time_print, &matching_lines);
            }
        }
    }
    free(line);
    return matching_lines;
}

void seek_choice(char *line, t_pattern *pattern, t_file *file, int *flags,
                 int *matching_lines, int files_cnt, int line_number,
                 int *one_time_print, int *file_name_print) {
    if (flags[O] && !flags[C] && !flags[V]) {
        if (pattern->is_file) {
            seek_file_patterns(line, pattern, file, flags, matching_lines,
                               files_cnt, line_number, one_time_print,
                               file_name_print);
        } else {
            seek_o_pattern(line, pattern, file, flags, matching_lines,
                           files_cnt, line_number, file_name_print);
        }
    } else {
        if (pattern->is_file) {
            seek_file_patterns(line, pattern, file, flags, matching_lines,
                               files_cnt, line_number, one_time_print,
                               file_name_print);
        } else {
            seek_pattern(line, *pattern, file, flags, matching_lines, files_cnt,
                         line_number, one_time_print);
        }
    }
}

void seek_o_pattern(char *line, t_pattern *pattern, t_file *file, int *flags,
                    int *maching_lines, int files_cnt, int line_number,
                    int *file_name_print) {
    regex_t regex;
    trim_n(pattern->name);
    int comp_val = do_regcomp(&regex, flags, pattern->name);
    if (!comp_val) {
        regmatch_t match;
        size_t offset = 0;
        size_t len = strlen(line);
        int eflags = 0;
        while (regexec(&regex, line + offset, 1, &match, eflags) == 0) {
            if (*file_name_print) (*maching_lines)++;
            eflags = REG_NOTBOL;
            print_o_match(file_name_print, file, offset, match, line, flags,
                          line_number, files_cnt);
            offset += match.rm_eo;
            if (match.rm_so == match.rm_eo) offset += 1;
            if (offset > len) break;
        }
    }
    regfree(&regex);
}

void print_o_match(int *file_name_print, t_file *file, size_t offset,
                   regmatch_t match, char *line, int *flags, int line_number,
                   int files_cnt) {
    if (!flags[C] && !flags[L]) {
        if (strlen(line) == 1 && line[0] == '.') line[0] = '\0';
        if (*file_name_print) {
            if (!flags[H] && files_cnt > 1) printf("%s:", file->file_name);
            if (flags[N]) printf("%d:", line_number);
        }
        for (size_t i = offset + match.rm_so; i < offset + match.rm_eo; i++)
            printf("%c", line[i]);
        printf("\n");
        *file_name_print = 0;
    }
}

void seek_file_patterns(char *line, t_pattern *pattern, t_file *file,
                        int *flags, int *matching_lines, int files_cnt,
                        int line_number, int *one_time_print,
                        int *file_name_print) {
    FILE *fd = fopen(pattern->file_name, "r");
    if (fd) {
        char *file_line = NULL;
        size_t file_line_size = 0;
        while (getline(&file_line, &file_line_size, fd) != -1) {
            if (line) {
                pattern->name = file_line;
                if (flags[O] && !flags[C] && !flags[V]) {
                    seek_o_pattern(line, pattern, file, flags, matching_lines,
                                   files_cnt, line_number, file_name_print);
                } else {
                    seek_pattern(line, *pattern, file, flags, matching_lines,
                                 files_cnt, line_number, one_time_print);
                }
            }
        }
        free(file_line);
        fclose(fd);
    } else {
        if (!flags[S]) printf("No such file or directory\n");
    }
}

void seek_pattern(char *line, t_pattern pattern, t_file *file, int *flags,
                  int *matching_lines, int files_cnt, int line_number,
                  int *one_time_print) {
    regex_t regex;
    trim_n(pattern.name);
    int comp_val = do_regcomp(&regex, flags, pattern.name);
    if (!comp_val) {
        int exec_val = regexec(&regex, line, 0, NULL, 0);
        if (exec_val == 0) {
            if (!flags[V]) {
                print_match(line, flags, file, files_cnt, line_number,
                            one_time_print, matching_lines);
            }
            *one_time_print = 0;
        }
    } else {
        printf("Regex comp. fail\n");
    }
    regfree(&regex);
}

void print_match(char *line, int *flags, t_file *file, int files_cnt,
                 int line_number, int *one_time_print, int *maching_lines) {
    if (!flags[C] && !flags[L] && *one_time_print) {
        if (strlen(line) == 1 && line[0] == '.') line[0] = '\0';
        if (!flags[H] && files_cnt > 1) printf("%s:", file->file_name);
        if (flags[N]) printf("%d:", line_number);
        printf("%s\n", line);
    }
    if (*one_time_print) (*maching_lines)++;
}

void trim_n(char *line) {
    if (strlen(line) == 1 && line[0] == '\n') line[0] = '.';
    if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
}

void get_files(int argc, char **argv, t_file *files) {
    int k = 0;
    for (int i = 1; i < argc; i++)
        if (is_arg_a_file(i, argv))
            files[k++].file_name = argv[i];
}

int do_regcomp(regex_t *regex, int *flags, char *pattern) {
    int comp_val;
    if (flags[1])
        comp_val = regcomp(regex, pattern, REG_ICASE);
    else
        comp_val = regcomp(regex, pattern, 0);
    return comp_val;
}

int cnt_files(int argc, char **argv) {
    int res = 0;
    for (int i = 1; i < argc; i++)
        if (is_arg_a_file(i, argv)) res++;
    return res;
}

int is_arg_a_file(int i, char **argv) {
    int flag = 0;
    FILE *file = NULL;
    if ((file = fopen(argv[i], "r"))) {
        fclose(file);
        flag = 1;
    }
    return flag;
}

char *get_default_pattern(int argc, char **argv) {
    char *res = NULL;
    for (int i = 1; i < argc; i++) {
        if (!strspn(argv[i], "-")) {
            res = argv[i];
            break;
        }
    }
    return res;
}

char *get_e_pattern(char **argv, int i) {
    char *res = NULL;
    if (strchr(argv[i], 'e') == argv[i] + strlen(argv[i]) - 1) {
        res = argv[i + 1];
    }
    return res;
}

char *get_pattern_file_name(char **argv, int i) {
    char *res = NULL;
    if (strchr(argv[i], 'f') == argv[i] + strlen(argv[i]) - 1) {
        res = argv[i + 1];
    }
    return res;
}

void init_patterns(t_pattern *patns, int size) {
    for (int i = 0; i < size; i++) {
        patns[i].is_default = 0;
        patns[i].is_file = 0;
        patns[i].file_name = NULL;
        patns[i].name = NULL;
    }
}

void init_files(t_file *files, int size) {
    for (int i = 0; i < size; i++) {
        files[i].mached = 0;
        files[i].mached_all = 0;
        files[i].valid = 0;
        files[i].file_name = NULL;
    }
}

void get_flags(int argc, char **argv, t_pattern *patns, int *patns_cnt, int *flags) {
    int e = 0, f = 0;
    for (int i = 1; i < argc; i++) {
        if (strspn(argv[i], "-")) {
            get_flags_from_argv(argv[i], flags);
            if (strchr(argv[i], 'f')) {
                f++;
                patns[*patns_cnt].is_default = 0;
                patns[*patns_cnt].is_file = 1;
                patns[*patns_cnt].file_name =
                    get_pattern_file_name(argv, i);
                (*patns_cnt)++;
            }
            if (strchr(argv[i], 'e')) {
                e++;
                patns[*patns_cnt].is_default = 0;
                patns[*patns_cnt].is_file = 0;
                patns[*patns_cnt].name = get_e_pattern(argv, i);
                (*patns_cnt)++;
            }
        }
    }
    if (e == 0 && f == 0) {
        patns[*patns_cnt].is_file = 0;
        patns[*patns_cnt].is_default = 1;
        patns[*patns_cnt].name = get_default_pattern(argc, argv);
        (*patns_cnt)++;
    }
}

int get_flags_from_argv(char *arg, int *flags) {
    int fail = 0;
    char *flag;
    if (strlen(arg) == 1 || strlen(arg) != strspn(arg, "-eivclnhsfo")) fail = 1;
    char *e = strchr(arg, 'e');
    char *f = strchr(arg, 'f');
    if (!e) e = arg + strlen(arg);
    if (!f) f = arg + strlen(arg);
    if (e < f) {
        flags[8] = 1;
        f = e;
    }
    if (f < e) {
        flags[0] = 1;
        e = f;
    }
    if ((flag = strchr(arg, 'i')) && (e == NULL || flag < e) &&
        (f == NULL || flag < f))
        flags[1] = 1;
    if ((flag = strchr(arg, 'v')) && (e == NULL || flag < e) &&
        (f == NULL || flag < f))
        flags[2] = 1;
    if ((flag = strchr(arg, 'c')) && (e == NULL || flag < e) &&
        (f == NULL || flag < f))
        flags[3] = 1;
    if ((flag = strchr(arg, 'l')) && (e == NULL || flag < e) &&
        (f == NULL || flag < f))
        flags[4] = 1;
    if ((flag = strchr(arg, 'n')) && (e == NULL || flag < e) &&
        (f == NULL || flag < f))
        flags[5] = 1;
    if ((flag = strchr(arg, 'h')) && (e == NULL || flag < e) &&
        (f == NULL || flag < f))
        flags[6] = 1;
    if ((flag = strchr(arg, 's')) && (e == NULL || flag < e) &&
        (f == NULL || flag < f))
        flags[7] = 1;
    if ((flag = strchr(arg, 'o')) && (e == NULL || flag < e) &&
        (f == NULL || flag < f))
        flags[9] = 1;
    return fail;
}
