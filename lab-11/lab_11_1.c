#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define OK 0
#define ERROR_OPEN_FILE 1

#define INPUT_FILEPATH "./data/text.txt"
#define OUTPUT_FILEPATH "./data/processed_text.txt"

#define VOWELS "aeiouy"
#define CONSONANTS "bcdfghjklmnpqrstvwxz"

struct StringRowStats {
    int n_vowels;
    int n_conconants;
    int n_words;
};

int is_vowel(char s) {
    int size = strlen(VOWELS);
    for (int i = 0; i < size; i++) {
        if (VOWELS[i] == tolower(s)) {
            return 1;
        }
    }
    return 0;
}

int is_consonant(char s) {
    int size = strlen(CONSONANTS);
    for (int i = 0; i < size; i++) {
        if (CONSONANTS[i] == tolower(s)) {
            return 1;
        }
    }
    return 0;
}

int calculate_vowels(char *word) {
    int n_vowels = 0;
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        if (is_vowel(word[i]) == 1) {
            n_vowels += 1;
        }
    }
    return n_vowels;
}

int calculate_conconants(char *word) {
    int n_consonants = 0;
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        if (is_consonant(word[i]) == 1) {
            n_consonants += 1;
        }
    }
    return n_consonants;
}

int main() {
    setbuf(stdout, NULL);
    
    FILE *fptr;
    FILE *fptr2;
    char *buf;
    char *tmp;
    char *initial_string;
    size_t buffer_size = 1024;
    int row_chars;
    struct StringRowStats row_stats;

    fptr = fopen(INPUT_FILEPATH, "r");
    if (fptr == NULL) {
        printf("ERROR: Could not open file");
        exit(ERROR_OPEN_FILE);
    }

    fptr2 = fopen(OUTPUT_FILEPATH, "w");
    if (fptr2 == NULL) {
        printf("ERROR: Could not open file");
        exit(ERROR_OPEN_FILE);
    }

    buf = calloc(1, sizeof(char) * buffer_size);
    tmp = calloc(1, sizeof(char) * buffer_size);
    initial_string = calloc(1, sizeof(char) * buffer_size);

    int i = 0;
    while ((row_chars = getline(&buf, &buffer_size, fptr)) > 0) {
        if ((row_chars == 1) && (buf[0] == '\n')) {
            continue;
        }
        i++;
        strcpy(initial_string, buf);
        // Calculate row statistics:
        tmp = strtok(buf, " ");

        row_stats.n_words = 0;
        row_stats.n_vowels = 0;
        row_stats.n_conconants = 0;

        while (tmp!= NULL) {
            if (strlen(tmp) > 0) {
                row_stats.n_words += 1;
            }
            if (strlen(tmp) == 1 && tmp[0] == '\n') {
                row_stats.n_words -= 1;
            }
            row_stats.n_vowels += calculate_vowels(tmp);
            row_stats.n_conconants += calculate_conconants(tmp);
            tmp = strtok(NULL, " ");
        }
        fprintf(fptr2, "%d. [%d, %d, %d]. %s",
            i, row_stats.n_words, row_stats.n_vowels, row_stats.n_conconants, initial_string
        );
    }

    fclose(fptr);
    fclose(fptr2);

    free(buf);
    free(tmp);
    free(initial_string);

    return OK;
}
