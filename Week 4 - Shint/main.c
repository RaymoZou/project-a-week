#include <stdio.h>
#include <stdlib.h>
#include "shint.h"
#include "shint.c"

int main() {
    unsigned char* byteArray = malloc(sizeof(char) * 3);
    byteArray[0] = 1; // 0000 0001
    byteArray[1] = 2; // 0000 0010
    byteArray[2] = 16; // 0001 0000

    // 0000 0001 0000 0010 0001 0000 (binary) = 66 064 (decimal)

    struct shint *shint = create_shint(byteArray);
    print_shint(shint);

    return 0;
};

