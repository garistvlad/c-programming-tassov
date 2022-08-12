#include <stdio.h>

#define OK 0
#define MAX_LENGH 256

char *punctuations = ",.!?:;";

int get_str_length(char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len += 1;
    }
    return len;
}

int check_is_punctuation(char s) {
    for (int i = 0; punctuations[i] != '\0'; i++) {
        if (s == punctuations[i]) {
            return 1;
        }
    }
    return 0;
}

void remove_symbol(char *str, int position_id) {
    int len = get_str_length(str);
    
    str[position_id] = '\0';
    // shift right part back to the left | _at
    for (int i = 0; i < (len - position_id - 1); i++) {
        str[position_id + i] = str[position_id + i + 1];
        str[position_id + i + 1] = '\0';
    }
}

void drop_repeated_spaces(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == ' ' && (str[i+1] == ' ' || check_is_punctuation(str[i+1]) == 1)) {
            remove_symbol(str, i);
        } else {
            i++;
        }
    }
}

void trim(char *str) {
    int len = get_str_length(str);
    // remove ending spaces
    while (1) {
        if (str[len-1] == ' ') {
            remove_symbol(str, len - 1);
            len = get_str_length(str);
        } else {
            break;
        }
    }
    // remove starting spaces
    while (1) {
        if (str[0] == ' ') {
            remove_symbol(str, 0);
        } else {
            break;
        }
    }
}

int main() {
    setbuf(stdout, NULL);

    char str[MAX_LENGH];
    
    printf("Enter your string:\n");
    fgets(str, sizeof(str), stdin);

    printf("Clean string:\n");
    trim(str);
    drop_repeated_spaces(str);

    printf("%s", str);

    return OK;
}
