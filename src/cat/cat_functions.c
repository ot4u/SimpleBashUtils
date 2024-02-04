#include <stdio.h>
#include <string.h>
#include "cat.h"

void cat_print(FILE *fp) {
    char c;
    while ((c = fgetc(fp)) != EOF) fputc(c, stdout);
}

void cat_file(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp) { 
            cat_print(fp);
            fclose(fp);
        } else {
            fprintf(stderr, "cat: %s: No such file or directory\n", argv[i]);
        }
    }
}