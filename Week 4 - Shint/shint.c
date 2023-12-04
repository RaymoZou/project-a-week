#include "shint.h"

#include <stdio.h>

void print_shint(struct shint* s) {
    //  printf("First byte:  %d\nSecond byte: %d\nThird byte:  %d\n", s->x,
    //  s->y, s->z);
    char firstByte = s->x;
    char secondByte = s->y;
    char thirdByte = s->z;

    int shint_int = (firstByte << 16) | (secondByte << 8) | thirdByte;
    // 0000 XXXX YYYY ZZZZ
    printf("%d", shint_int);
};

struct shint* create_shint(char* bytes) {
    struct shint* s = malloc(sizeof(struct shint));
    s->x = bytes[0];
    s->y = bytes[1];
    s->z = bytes[2];
    return s;
};