#include <stdio.h>
#include <stdbool.h>

void cat_print(FILE *fp);
void cat_file(int argc, char *argv[]);

typedef struct options {
    bool non_blank_rows; // -b
    bool show_end; // -e
    bool all_rows; // -n
    bool squeezed; // -s
    bool show_tabs; // -t
    bool show_all; // -v
    int count;
} options;

void parse_options(int argc, char *argv[], options *s_opt);