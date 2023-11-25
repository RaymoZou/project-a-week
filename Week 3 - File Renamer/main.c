#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // allocate a buffer of 100

    int MAX_BUFFER_SIZE = 100;
    int MAX_STRING_SIZE = 10;

    char char_buffer[MAX_BUFFER_SIZE];
    int curr_index = 0;
    char *pointer_arr[MAX_STRING_SIZE];
    char *temp_pointer;

    while (1) {
        printf("Enter string:\n");
        scanf("%s", char_buffer);

        // if size of string exceeds MAX_BUFFER_SIZE, return error
        if ((strlen(char_buffer) + 1) > MAX_BUFFER_SIZE) {
            fprintf(stderr, "Error reading input.\n");
            return -1;
        };

        temp_pointer = malloc((strlen(char_buffer) + 1) * sizeof(char));
        strcpy(temp_pointer, char_buffer);
        pointer_arr[curr_index] = temp_pointer;

        // print all the strings that have been stored so far
        for (int i = 0; i <= curr_index; i++) {
            // printf("%d\n", i);
            printf("Item stored at index %d: %s\n", i, pointer_arr[i]);
        };

        curr_index++;
    };

    return 0;
}
