#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OK 0
#define MAX_LENGTH 1024
#define MAX_WORD_LENGTH 64
#define MAX_N_WORDS 64

void print_string_array(char words[MAX_N_WORDS][MAX_WORD_LENGTH], int size) {
    for(int i = 0; i < size; i++) {
        printf("%s", words[i]);
    }
    printf("\n");
}

void juslify_text(char *text, int width) {
    int capacity = width;
    char row[MAX_N_WORDS][MAX_WORD_LENGTH];
    char *chunk;

    int i = 0;
    while ((chunk=strsep(&text, " ")) != NULL) {
        if (chunk[0] == ' ' || chunk[0] == '\n') {
            continue;
        }
        int required_len = strlen(chunk);
        if (i == 0 && capacity > required_len) {
            // add first element
            strcpy(row[i], chunk);
            capacity -= required_len;
        } else if (i > 0 && capacity > (required_len + 1)) {
            // add one more element and space after previous one
            strcpy(row[i], chunk);
            strcat(row[i-1], " ");
            capacity -= (required_len + 1);
        } else {
            // 1. fill existing row by spaces (where possible)
            if (i == 1) {
                while (capacity > 0) {
                    strcat(row[i-1], " ");
                    capacity -= 1;
                }
            } else {
                while (capacity > 0) {
                    for (int j = 0; j < i-1 && capacity > 0; j++) {
                        strcat(row[j], " ");
                        capacity -= 1;
                    }
                }
            }
            // 2. print existing row
            print_string_array(row, i);
            // 3. clean the buffer (capacity became equal to width)
            i = 0;
            capacity = width - required_len;
            strcpy(row[i], chunk);
        }
        i += 1;
    }
    if (i > 0) {
        print_string_array(row, i);
    }
}

int main() {
    setbuf(stdout, NULL);

    char text[MAX_LENGTH];
    int width;

    printf("Enter your text:\n");
    fgets(text, sizeof(text), stdin);
    if (text[strlen(text) - 1] == '\n') {
        text[strlen(text) - 1] = '\0';
    }

    printf("Max width: ");
    scanf("%d", &width);

    juslify_text(text, width);
    
    return OK;
}
