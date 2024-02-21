#include "grep.h"

int main(int argc, char *argv[]) {
  options opts = {0};
  char template[BUF_SIZE] = {0};
  parse_options(argc, argv, &opts, template);
  if (argc >= 3) grep(&opts, argc, argv, template);
  return 0;
}

void parse_options(int argc, char *argv[], options *opts, char *template) {
  int opt;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        opts->e = 1;
        snprintf(template, BUF_SIZE, "%s", optarg);
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
        snprintf(template, BUF_SIZE, "%s", optarg);
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

void grep(options *opts, int argc, char **argv, char *buff) {
  char template[BUF_SIZE] = {0};
  int f_pattind = 0;
  if (!opts->f && !opts->e) {
    snprintf(template, BUF_SIZE, "%s", argv[optind++]);
  }
  if (opts->f) {
    f_pattind = execute_f_opt(template, buff);
  }
  if (!opts->f && opts->e) {
    snprintf(template, BUF_SIZE, "%s", buff);
  }
  if (f_pattind != -1) {
    int file_exist = 0;
    if (argc - optind > 1) file_exist = 1;
    for (int i = optind; i < argc; i++) {
      const FILE *file = fopen(argv[i], "r");
      if (file == NULL) {
        printf("grep: %s: No such file or directory", argv[i]);
      } else {
        if (file_exist && !opts->h && !opts->l) printf("%s:", argv[i]);
        file_processing(opts, template, argv[i]);
      }
    }
  }
}

int execute_f_opt(char *template, char *filename) {
  FILE *file = fopen(filename, "r");
  int i = 0;
  if (file) {
    int c;
    while ((c = fgetc(file)) != EOF) {
      if (c == 13 || c == 10) template[i++] = '|';
      if (c != 13 && c != 10) template[i++] = c;
    }
  } else {
    printf("grep: %s: No such file or directory", filename);
    i = -1;
  }
  if (template[i - 1] == '|') template[i - 1] = '\0';
  fclose(file);
  return i;
}

void file_processing(options *opts, char *template, char *filename) {
  int cflags = REG_EXTENDED;
  regex_t reg;
  FILE *file = fopen(filename, "r");
  if (opts->i) cflags = REG_ICASE;
  if (file) {
    regcomp(&reg, template, cflags);
    processing(opts, file, reg, filename);
    regfree(&reg);
    fclose(file);
  }
}

void processing(options *opts, FILE *file, regex_t reg, char *filename) {
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
    if (match && !opts->l && !opts->c && opts->n) printf("%d:", number_line);
    if (match && !opts->l && !opts->c && !opts->o) printf("%s", text);
    if (match && opts->o) execute_o_opt(reg, opts, text);
    matching_lines += match;
    number_line++;
  }
  if (opts->l && matching_lines > 0) printf("%s\n", filename);
  if (opts->c && !opts->l) printf("%d\n", matching_lines);
}

void execute_o_opt(regex_t reg, options *opts, char *line) {
  while (regexec(&reg, line, 0, NULL, 0) == opts->v) {
    char *temp = (char *)calloc(strlen(line) + 1, 1);
    strcpy(temp, line);
    int end = strlen(line);
    while (regexec(&reg, temp, 0, NULL, 0) == opts->v) {
      end--;
      temp[strlen(temp) - 1] = 0;
    }
    temp[strlen(temp)] = line[strlen(temp)];
    int start = 0;
    while (regexec(&reg, temp, 0, NULL, 0) == opts->v && strlen(temp) > 0) {
      start--;
      int j = 0;
      while (temp[j] != 0) {
        temp[j] = temp[j + 1];
        j++;
      }
    }
    start--;
    int i = strlen(temp);
    while (i != 0) {
      temp[i] = temp[i - 1];
      i--;
    }
    temp[0] = line[start];
    printf("%s\n", temp);
    free(temp);
    i = start + 1;
    while (line[i] != 0) {
      line[i - start - 1] = line[i];
      i++;
    }
    line[i - start - 1] = 0;
  }
}