#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct options {
  bool b;
  bool e;
  bool n;
  bool s;
  bool t;
  bool v;
  int cnt;
  int empty_lines;
} options;

void lines_count(int prev, options *s_opt);
void compress_lines(int *c, FILE *fp, options *s_opt);
void count_empty(int *c, int *prev, options *s_opt);
void cook_non_printed(int *c, options *s_opt);
void cat(int *c, int *prev, options *s_opt, FILE *fp);
void cat_print(FILE *fp, options *s_opt);
void cat_file(int argc, char *argv[], options *s_opt);
void parse_options(int argc, char *argv[], options *s_opt);