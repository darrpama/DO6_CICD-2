#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <errno.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define E 0
#define I 1
#define V 2
#define C 3
#define L 4
#define N 5
#define H 6
#define S 7
#define F 8
#define O 9

typedef struct s_file {
    char *file_name;
    int mached;
    int mached_all;
    int valid;
} t_file;

typedef struct s_pattern {
    char *name;
    int is_file;
    char *file_name;
    int is_default;
} t_pattern;

void s21_grep(int argc, char **argv);

/**
 * @brief Initialization massive of pattern structures
 * 
 * @param patns Pattern structures
 * @param size Number of sructures
 */
void init_patterns(t_pattern *patns, int size);


/**
 * @brief Initialization massive of file structures
 * 
 * @param files File structures
 * @param size Number of structures
 */
void init_files(t_file *files, int size);


/**
 * @brief Get the flags from argv[i] object
 * 
 * @param arg argv[i]
 * @param flags Pointer to massive of (int) where it is flags
 * @return error number 0 - OK; 1 - there is no flags
 */
void get_flags(int argc, char **argv, t_pattern *patns, int *patns_cnt, int *flags);


/**
 * @brief Get the flags from argv[i] object
 * 
 * @param arg argv[i]
 * @param flags Pointer to massive of (int) where it is flags
 * @return error number 0 - OK; 1 - there is no flags
 */
int get_flags_from_argv(char *arg, int *flags);


/**
 * @brief Get the pattern file name object for -f flag
 * 
 * @param argv 
 * @param i 
 * @return char* 
 */
char *get_pattern_file_name(char **argv, int i);

/**
 * @brief Get the e pattern object from argv[i+1]
 * 
 * @param argv 
 * @param i 
 * @return char* 
 */
char *get_e_pattern(char **argv, int i);


/**
 * @brief Initialize work with files if files is founded
 * 
 * @param argc
 * @param argv
 * @param patns Pattern structures
 * @param patns_cnt Number of sructures 
 * @param flags Pointer to massive of (int) where it is flags
 */
void scan_files(int argc, char **argv, t_pattern *patns, int patns_cnt, int *flags);


/**
 * @brief Check out is argv[i] a file
 * 
 * @param i 
 * @param argv 
 * @return int 
 */
int is_arg_a_file(int i, char **argv);


/**
 * @brief Return number of files in argv
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int cnt_files(int argc, char **argv);


/**
 * @brief Return pattern from argv
 * 
 * @param argc 
 * @param argv 
 * @return char* 
 */
char *get_default_pattern(int argc, char **argv);


/**
 * @brief Write into the files massive filenames if it is a file
 * 
 * @param argc 
 * @param argv 
 * @param files File structures 
 */
void get_files(int argc, char **argv, t_file *files);

void files_processing(t_pattern *patns, int patns_cnt, t_file *files, int files_cnt, int *flags);
int seek_in_file(FILE *fd, t_pattern *patns, int patns_cnt, int *flags, t_file *file, int files_cnt);

void print_match(char *line, int *flags, t_file *file, int files_cnt, int line_number, int *one_time_print,
                 int *maching_lines);
void print_files_c(t_file *file, int files_cnt, int maching_lines, const int *flags);

void print_files_l(t_file *file, int maching_lines);
void seek_file_patterns(char *line, t_pattern *pattern, t_file *file, int *flags, int *matching_lines,
                        int files_cnt, int line_number, int *one_time_print, int *file_name_print);
void seek_pattern(char *line, t_pattern pattern, t_file *file, int *flags, int *matching_lines, int files_cnt,
                  int line_number, int *one_time_print);
void trim_n(char *line);

void seek_choice(char *line, t_pattern *pattern, t_file *file, int *flags, int *matching_lines, int files_cnt,
                 int line_number, int *one_time_print, int *file_name_print);
void seek_o_pattern(char *line, t_pattern *pattern, t_file *file, int *flags, int *maching_lines,
                    int files_cnt, int line_number, int *file_name_print);
void print_o_match(int *file_name_print, t_file *file, size_t offset, regmatch_t match, char *line,
                   int *flags, int line_number, int files_cnt);

int is_empty_line(char *name);
int is_empty_line_in_patterns(t_pattern *patns, int patns_cnt);
int print_all(FILE *fd, int *flags, t_file *file, int files_cnt);
int do_regcomp(regex_t *regex, int *flags, char *pattern);

#endif  // SRC_GREP_S21_GREP_H_
