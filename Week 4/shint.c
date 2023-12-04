#include "shint.h"

#include <stdio.h>

void print_shint(struct shint* s) { printf("First byte:  %d\nSecond byte: %d\nThird byte:  %d\n", s->x, s->y, s->z); };

struct shint* create_shint(char* bytes) {
    struct shint* s = malloc(sizeof(struct shint));
    s->x = bytes[0];
    s->y = bytes[1];
    s->z = bytes[2];
    return s;
}