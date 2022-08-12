#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define MAX_TEXT_LENGTH 1024
#define MAX_WORD_LENGTH 128

int word_count(char *text) {
    int count = 0;
    int start = 0;
    int end = strlen(text);
    // skip starting and ending spaces
    while (text[start] == ' ') {
        start++;
    }
    while (text[end - 1] == ' ') {
        end--;
    }
    for (int i = start; i < end; i++) {
        // exclude repeated spaces
        if (text[i] == ' ' && text[i + 1] != ' ') {
            count++;
        }
    }
    return (count == 0) ? 0 : (count + 1);
}

void text_by_words(char *text) {
    char *chunk;
    int total_words;
    char **words;
    int n_unique_words = 0;
    int *word_counter;

    total_words = word_count(text);
    words = calloc(total_words, sizeof(char *));
    word_counter = calloc(1, sizeof(int) * total_words);
    for (int i = 0; i < total_words; i++) {
        words[i] = calloc(1, sizeof(char) * MAX_WORD_LENGTH);
    }

    while ((chunk=strsep(&text, " ")) != NULL) {
        if (chunk[0] == '\0' || chunk[0] == '\n') {
            continue;
        }
        int already_exists_flg = 0;
        for (int i = 0; i < n_unique_words; i++) {
            if (strcmp(words[i], chunk) == 0) {
                // update counter
                already_exists_flg = 1;
                word_counter[i] += 1;
                break;
            }
        }
        // add new word if not existed yet
        if (already_exists_flg == 0) {
            words[n_unique_words] = chunk;
            word_counter[n_unique_words] = 1;
            n_unique_words += 1;
        }
    }
    printf("# of unique words: %d\n", n_unique_words);
    for (int i = 0; i < n_unique_words; i++) {
        printf("%s\t%d\n", words[i], word_counter[i]);
    }

    free(word_counter);
    free(words);
}

int main() {
    setbuf(stdout, NULL);

    char text[MAX_TEXT_LENGTH];
    
    printf("Enter text:\n");
    fgets(text, sizeof(text), stdin);
    if (text[strlen(text) - 1] == '\n') {
        text[strlen(text) - 1] = '\0';
    }
    text_by_words(text);
    
    return OK;
}
