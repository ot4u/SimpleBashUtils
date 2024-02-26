#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 4096

typedef struct options {
  bool e, i, v, c, l, n, h, s, f, o;
} options;

void parse_options(int argc, char *argv[], options *opts, char *template,
                   char *file_patt);
void grep(const options *opts, int argc, char **argv, const char *buff,
          char *file_patt);
int execute_f_opt(char *template, char **filename);
void file_processing(const options *opts, char *template, char *filename,
                     int file_exist);
void processing(const options *opts, FILE *file, regex_t reg, char **filename,
                int file_exist);
void execute_o_opt(regex_t reg, char *line, const options *opts,
                   int number_line);