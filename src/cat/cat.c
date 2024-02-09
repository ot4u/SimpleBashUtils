#include "cat.h"

int main(int argc, char *argv[]) { 
  
  return 0; 
}

void parse_options(int argc, char *argv[], options *s_opt) {
  int opt;
  int opt_ind;
  const struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                        {"number", 0, 0, 'n'},
                                        {"squeeze-blank", 0, 0, 's'},
                                        {0, 0, 0, 0}};
  while ((opt = getopt_long(argc, argv, "+bensvtTE", long_options, &opt_ind)) !=
         -1) {
    switch (opt) {
      case 'b':
        s_opt->b = 1;
      case 'e':
        s_opt->e = 1;
        s_opt->v = 1;
      case 'n':
        s_opt->n = 1;
      case 's':
        s_opt->s = 1;
      case 'v':
        s_opt->v = 1;
      case 't':
        s_opt->t = 1;
        s_opt->v = 1;
      case 'T':
        s_opt->t = 1;
      case 'E':
        s_opt->e = 1;
      default:
        fprintf(stderr, "usage 'bensvt'");
    }
  }
}

void reader(char *argv, options *s_opt) {
  FILE *f = fopen(argv[optind], "r");
  if (f) {
    int c;
    while ((c = fgetc(f)) != EOF) {
      if (s_opt->b) do_flag_b();
      else if (s_opt->e) do_flag_b();
      else if (s_opt->e) do_flag_b();
      else if (s_opt->e) do_flag_b();
      else if (s_opt->e) do_flag_b();
      else if (s_opt->e) do_flag_b();
      else if (s_opt->e) do_flag_b();
      else cat_print(f);
  } else {
    fprintf(stderr, "cat: %s: No such file or directory\n", argv[optind]);
  }
}

void cat_print(FILE *fp) {
  char c;
  while ((c = fgetc(fp)) != EOF) fputc(c, stdout);
}