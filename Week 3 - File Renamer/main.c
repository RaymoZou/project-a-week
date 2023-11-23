#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("Name of this program: %s\n", argv[0]);
    printf("The number of arguments passed was: %d\n", argc);
    // argv is a pointer to character array
    return 0;
}
