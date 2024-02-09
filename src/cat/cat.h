#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void parse_options(int argc, char *argv[], options *s_opt);
void reader(char *argv, options *s_opt);

typedef struct options {
    bool b;
    bool e;
    bool n;
    bool s;
    bool t;
    bool v;
} options;