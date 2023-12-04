#include <stdio.h>
#include <stdlib.h>
#include "shint.h"
#include "shint.c"

int main() {
    unsigned char* byteArray = malloc(sizeof(char) * 3);
    byteArray[0] = 1;
    byteArray[1] = 23;
    byteArray[2] = 33;

    struct shint *shint = create_shint(byteArray);
    print_shint(shint);

    return 0;
};

