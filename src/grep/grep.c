#include "cat.h"

int main(int argc, char *argv[]) {
  options s_opt = {0};
  char pattern[BUF_SIZE] = {0};
  return 0;
}

void parse_options(int argc, char *argv[], options *s_opt, char *pattern) {
  int opt;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) !=
         -1) {
    switch (opt) {
      case 'e':
        s_opt->e = 1;
        snprintf(pattern, BUF_SIZE, "%s", optarg);
        break;
      case 'i':
        s_opt->i = 1;
        break;
      case 'v':
        s_opt->v = 1;
        break;
      case 'c':
        s_opt->c = 1;
        break;
      case 'l':
        s_opt->l = 1;
        break;
      case 'n':
        s_opt->n = 1;
        break;
      case 'h':
        s_opt->h = 1;
        break;
      case 's':
        s_opt->s = 1;
        break;
      case 'f':
        s_opt->f = 1;
        snprintf(pattern, BUF_SIZE, "%s", optarg);
        break;
      case 'o':
        s_opt->o = 1;
        break;
      default:
        printf("error\n");r
        break;
    }
  }
}