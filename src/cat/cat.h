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

void read_file(int argc, char *argv[], options *cur_opt);
void print(FILE *fp, options *cur_opt);
void parse_options(int argc, char *argv[], options *cur_opt);
void execute_options(int *c, int *prev, options *cur_opt, FILE *fp);
void count_empty_lines(int c, int prev, options *cur_opt);
void compress_lines(int *c, FILE *fp, options *cur_opt);
void count_lines(int prev, options *cur_opt);
void execute_flags_et(int *c, options *cur_opt);