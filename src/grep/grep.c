#include "grep.h"

int main(int argc, char *argv[]) {
  options opts = {0};
  char template[BUF_SIZE] = {0};
  char file_patt[BUF_SIZE] = {0};
  parse_options(argc, argv, &opts, template, file_patt);
  if (argc >= 3) grep(&opts, argc, argv, template, file_patt);
  return 0;
}

void parse_options(int argc, char *argv[], options *opts, char *template, char *file_patt) {
  int opt;
  while ((opt = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, NULL)) != -1) {
    switch (opt) {
      case 'e':
        opts->e = 1;
        strcat(template, optarg);
        strcat(template, "|");
        break;
      case 'i':
        opts->i = 1;
        break;
      case 'v':
        opts->v = 1;
        break;
      case 'c':
        opts->c = 1;
        break;
      case 'l':
        opts->l = 1;
        break;
      case 'n':
        opts->n = 1;
        break;
      case 'h':
        opts->h = 1;
        break;
      case 's':
        opts->s = 1;
        break;
      case 'f':
        opts->f = 1;
        snprintf(file_patt, BUF_SIZE, "%s", optarg);
        break;
      case 'o':
        opts->o = 1;
        break;
      default:
        printf("error\n");
        break;
    }
  }
}

void grep(const options *opts, int argc, char **argv, char *buff, char *file_patt) {
  char template[BUF_SIZE] = {0};
  int f_pattind = 0;
  if (!opts->f && !opts->e) {
    strcat(template, argv[optind++]);
  }
  if (opts->f) {
    f_pattind = execute_f_opt(template, &file_patt);
  }
  if (opts->e) {
    strcat(template, buff);
  }
  if (template[strlen(template) - 1] == '|') template[strlen(template) - 1] = '\0';
  if (f_pattind != -1) {
    int file_exist = 0;
    if (argc - optind > 1) file_exist = 1;
    for (int i = optind; i < argc; i++) {
      file_processing(opts, template, argv[i], file_exist);
    }
  }
}

int execute_f_opt(char *template, char **filename) {
  FILE *file = fopen(*filename, "r");
  int i = 0;
  if (file) {
    int c;
    while ((c = fgetc(file)) != EOF) {
      if (c == 13 || c == 10) template[i++] = '|';
      if (c != 13 && c != 10) template[i++] = c;
    }
    template[i] = '|';
  } else {
    printf("grep: %s: No such file or directory\n", *filename);
    i = -1;
  }
  fclose(file);
  return i;
}

void file_processing(const options *opts, char *template, char *filename,
                     int file_exist) {
  int cflags = REG_EXTENDED;
  regex_t reg;
  FILE *file = fopen(filename, "r");
  if (opts->i) cflags = REG_ICASE;
  if (file != NULL) {
    regcomp(&reg, template, cflags);
    processing(opts, file, reg, &filename, file_exist);
    regfree(&reg);
    fclose(file);
  } else {
    if (!opts->s) printf("grep: %s: No such file or directory\n", filename);
  }
}

void processing(const options *opts, FILE *file, regex_t reg, char **filename,
                int file_exist) {
  char text[BUF_SIZE] = {0};
  int matching_lines = 0;
  int number_line = 1;
  regmatch_t pmatch[1];
  while (fgets(text, BUF_SIZE - 1, file) != NULL) {
    int match = 0;
    int success = regexec(&reg, text, 1, pmatch, 0);
    if (strchr(text, '\n') == NULL) strcat(text, "\n");
    if (success == 0 && !opts->v) match = 1;
    if (success == REG_NOMATCH && opts->v) match = 1;
    if (match && file_exist && !opts->h && !opts->l && !opts->c)
      printf("%s:", *filename);
    if (match && !opts->l && !opts->c && opts->n) printf("%d:", number_line);
    if (match && !opts->l && !opts->c && !opts->o) printf("%s", text);
    if (match && opts->o && !opts->c && !opts->l)
      execute_o_opt(reg, text, opts);
    matching_lines += match;
    number_line++;
  }
  if (opts->c && opts->l && matching_lines > 0) matching_lines = 1;
  if (!file_exist && opts->c) printf("%d\n", matching_lines);
  if (file_exist && opts->c) printf("%s:%d\n", *filename, matching_lines);
  if (opts->l && matching_lines > 0) printf("%s\n", *filename);
}

void execute_o_opt(regex_t reg, char *line, const options *opts) {
  while (!regexec(&reg, line, 0, NULL, 0)) {
    char buf[BUF_SIZE] = "";
    strcpy(buf, line);
    int left = 0;
    int right = strlen(buf);
    while (!regexec(&reg, buf + left, 0, NULL, 0)) {
      right--;
      buf[right] = 0;
    }
    buf[right] = line[right];
    right++;
    while (!regexec(&reg, buf + left, 0, NULL, 0)) left++;
    left--;
    if (!opts->v) printf("%s\n", buf + left);
    int len = right - left + 1;
    for (int i = 0; i < len; i++) {
      line[left++] = 127;
    }
  }
  if (opts->v) printf("%s", line);
}