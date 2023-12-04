#ifndef SHINT_H
#define SHINT_H

struct shint {
    char x;
    char y;
    char z;
};

void print_shint(struct shint* s);

struct shint* create_shint(char* bytes);

#endif