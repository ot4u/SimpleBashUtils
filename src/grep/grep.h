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

void parse_options(int argc, char *argv[], options *opts, char *template);
void grep(options *opts, int argc, char **argv, char *buff);
int execute_f_opt(char *template, char *filename);
void file_processing(options *opts, char *template, char *filename);
void processing(options *opts, FILE *file, regex_t reg, char *filename);
void execute_o_opt(regex_t reg, options *opts, char *line);