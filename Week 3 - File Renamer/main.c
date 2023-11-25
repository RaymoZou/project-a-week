#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // allocate a buffer of 100

    int MAX_BUFFER_SIZE = 100;
    char char_buffer[MAX_BUFFER_SIZE];
    // array of 10 pointers
    // char *pointer_arr[10];
    char *pointer;

    printf("What is your name? \n");
    scanf("%s", char_buffer);
    // printf("%d", sizeof(char_buffer));

    // if string length + 1 exceeds char_buffer size, return error
    if ((strlen(char_buffer) + 1) > MAX_BUFFER_SIZE) {
        fprintf(stderr, "Error reading input.\n");
        return -1;
    };

    // allocate memory
    pointer = malloc((strlen(char_buffer) + 1) * sizeof(char));
    // copy buffer -> name
    strcpy(pointer, char_buffer);

    // Print information about the name entered
    printf("Your name is %s\n", pointer);
    printf("String length: %d\n", strlen(pointer));

    free(pointer);

    return 0;
}
