#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>

#define BUF_SIZE 4096

typedef struct options {
  bool e, i, v, c, l, n, h, s, f, o;
} options;

void parse_options(int argc, char *argv[], options *s_opt, char *pattern);