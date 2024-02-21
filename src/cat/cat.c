#include "cat.h"

int main(int argc, char *argv[]) {
  if (argc == 1) {
    print(stdin, NULL);
  } else {
    if (argv[1][0] == '-') {
      options cur_opt = {0};
      parse_options(argc, argv, &cur_opt);
      if (!cur_opt.cnt && optind) {
        read_file(argc, argv, &cur_opt);
      }
    } else {
      read_file(argc, argv, NULL);
    }
  }
  return 0;
}

void parse_options(int argc, char *argv[], options *cur_opt) {
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
        cur_opt->b = 1;
        break;
      case 'e':
        cur_opt->e = cur_opt->v = 1;
        break;
      case 'E':
        cur_opt->e = 1;
        break;
      case 'n':
        cur_opt->n = 1;
        break;
      case 's':
        cur_opt->s = 1;
        break;
      case 'v':
        cur_opt->v = 1;
        break;
      case 't':
        cur_opt->t = cur_opt->v = 1;
        break;
      case 'T':
        cur_opt->t = 1;
        break;
      case '?':
      default:
        cur_opt->cnt = 1;
        break;
    }
  }
}

void read_file(int argc, char **argv, options *cur_opt) {
  int i = optind ? optind : 1;
  for (; i < argc; i++) {
    FILE *f = fopen(argv[i], "r");
    if (f) {
      print(f, cur_opt);
      fclose(f);
    } else {
      printf("cat: %s: No such file or directory\n", argv[i]);
    }
  }
}

void print(FILE *f, options *cur_opt) {
  int c;
  int prev = '\n';
  if (cur_opt) {
    cur_opt->empty_lines = 0;
    cur_opt->cnt = 1;
  }
  while ((c = fgetc(f)) != EOF) {
    if (cur_opt) execute_options(&c, prev, cur_opt, f);
    if (c != EOF) fputc(c, stdout);
    prev = c;
  }
}

void execute_options(int *c, int prev, options *cur_opt, FILE *f) {
  count_empty_lines(*c, prev, cur_opt);
  compress_lines(c, f, cur_opt);
  if (*c != EOF) {
    count_lines(prev, cur_opt);
    execute_flags_et(c, *cur_opt, prev);
  }
}

void count_empty_lines(int c, int prev, options *cur_opt) {
  if (prev == '\n' && c == '\n')
    cur_opt->empty_lines++;
  else
    cur_opt->empty_lines = 0;
}

void compress_lines(int *c, FILE *f, options *cur_opt) {
  if (cur_opt->s && cur_opt->empty_lines > 1) {
    while (*c == '\n') *c = fgetc(f);
    cur_opt->empty_lines = 0;
  }
}

void count_lines(int prev, options *cur_opt) {
  if (prev == '\n' && (cur_opt->n || cur_opt->b)) {
    if (!(cur_opt->b && cur_opt->empty_lines > 0)) {
      printf("%6d\t", cur_opt->cnt);
      cur_opt->cnt++;
    }
  }
}

void execute_flags_et(int *c, options cur_opt, int prev) {
  if (*c == '\n') {
    if (cur_opt.e && (cur_opt.b)) {
      if (prev == '\n') {
        printf("%6c\t$", ' ');
      } else {
        printf("$");
      }
    } else if (cur_opt.e) {
      printf("$");
    }
  } else if (*c == '\t') {
    if (cur_opt.t) {
      printf("^");
      *c = 'I';
    }
  } else if (cur_opt.v) {
    if (*c <= 31) {
      printf("^");
      *c += 64;
    } else if (*c == 127) {
      printf("^");
      *c = '?';
    } else if (*c >= 128 && *c < 128 + 32) {
      printf("M-^");
      *c -= 64;
    }
  }
}