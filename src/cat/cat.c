#include "cat.h"

int main(int argc, char *argv[]) {
  if (argc == 1) {
    cat_print(stdin, NULL);
  } else {
    if (argv[1][0] == '-') {
      options s_opt = {0};
      parse_options(argc, argv, &s_opt);
      if (!s_opt.cnt && optind) {
        printf("Parsed options successfully: %d\n", optind - 1);
        cat_file(argc, argv, &s_opt);
      }
    } else {
      cat_file(argc, argv, NULL);
    }
  }
  return 0;
}

void cat_print(FILE *fp, options *s_opt) {
  int c;
  int prev = '\n';
  if (s_opt) {
    s_opt->empty_lines = 0;
    s_opt->cnt = 1;
    ;
  }
  while ((c = fgetc(fp)) != EOF) {
    if (s_opt) cat_cook(&c, &prev, s_opt, fp);
    if (c != EOF) fputc(c, stdout);
    prev = c;
  }
}

void count_empty(int *c, int *prev, options *s_opt) {
  if (*prev == '\n' && *c == '\n')
    s_opt->empty_lines++;
  else
    s_opt->empty_lines = 0;
}

void cat(int *c, int *prev, options *s_opt, FILE *fp) {
  count_empty(c, prev, s_opt);
  compress_lines(c, fp, s_opt);
  if (*c != EOF) {
    lines_counter(*prev, s_opt);
    cook_non_printed(c, s_opt);
  }
}
void lines_count(int prev, options *s_opt) {
  if (prev == '\n' && (s_opt->n || s_opt->b)) {
    if (!(s_opt->b && s_opt->empty_lines > 0)) {
      printf("%6d\t", s_opt->cnt);
      s_opt->cnt++;
    }
  }
}

void compress_lines(int *c, FILE *fp, options *s_opt) {
  if (s_opt->s && s_opt->empty_lines > 1) {
    while (*c == '\n') *c = fgetc(fp);
    s_opt->empty_lines = 0;
  }
}

void cook_non_printed(int *c, options *s_opt) {
  if (*c == '\n') {
    if (s_opt->e) printf("$");
  } else if (*c == '\t') {
    if (s_opt->t) {
      printf("^");
      *c = 'I';
    }
  } else if (s_opt->v) {
    if (*c <= 31) {
      printf("^");
      *c += 64;
    } else if (*c == 127) {
      printf("M-^");
      *c -= '?';
    } else if (*c >= 128 && *c < 128 + 32) {
      printf("M-^");
      *c -= 64;
    }
  }
}

void cat_file(int argc, char *argv[], options *s_opt) {
  int i = optind ? optind : 1;
  for (; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");
    if (fp) {
      cat_print(fp, s_opt);
      fclose(fp);
    } else {
      fprintf(stderr, "cat: %s: No such file or directory\n", argv[i]);
    }
  }
}

void parse_options(int argc, char *argv[], options *s_opt) {
  const struct option long_options[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {NULL, 0, NULL, 0}};
  int opt;
  while ((opt = getopt_long(argc, argv, "beEnsvtT", long_options, NULL)) !=
         -1) {
    switch (opt) {
      case 'b':
        s_opt->b = 1;
        break;
      case 'e':
        s_opt->e = s_opt->v = 1;
        break;
      case 'E':
        s_opt->e = 1;
        break;
      case 'n':
        s_opt->n = 1;
        break;
      case 's':
        s_opt->s = 1;
        break;
      case 'v':
        s_opt->v = 1;
        break;
      case 't':
        s_opt->t = s_opt->v = 1;
        break;
      case 'T':
        s_opt->t = 1;
        break;
      case '?':
      default:
        s_opt->cnt = 1;
        break;
    }
  }
}