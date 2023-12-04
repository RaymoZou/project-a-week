#ifndef SHINT_H
#define SHINT_H

struct shint {
    char x;
    char y;
    char z;
};

// prints the shint in decimal format
void print_shint(struct shint* s);

// takes a pointer to an array of 3 individual bytes and stores to be read consecutively
struct shint* create_shint(char* bytes);

#endif