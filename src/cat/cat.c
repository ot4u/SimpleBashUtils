#include <stdio.h>
#include "cat.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        cat_print(stdin);
    } else {
        cat_file(argc, argv);
    }
    return 0;
} 