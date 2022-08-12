#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define MAX_LENGTH 128

void print_string_array(char **arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%s ", arr[i]);
    }
    printf("\n");
}

int get_str_length(char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len += 1;
    }
    return len;
}

void georginify_name(char *name) {
    int len = get_str_length(name);
    if (len < 2) {
        return;
    }
    if (name[len - 2] == 'o' && name[len - 1] == 'v') {
        char *new_ending = "idze";
        int new_ending_len = get_str_length(new_ending);
        for (int i = 0; i < new_ending_len; i++) {
            name[len - 2 + i] = new_ending[i];
        }
    }
}

int main() {
    setbuf(stdout, NULL);

    int n;
    printf("Enter number of names: ");
    scanf("%d", &n);

    char **names = calloc(n, sizeof(char*));
    for (int i = 0; i < n; i++) {
        names[i] = calloc(1, sizeof(char) * MAX_LENGTH);
    }

    printf("Enter the names themself:\n");
    for (int i = 0; i < n; i++) {
        // fgets(names[i], sizeof(names[i]), stdin);
        scanf("%s", names[i]);
    }

    for (int i = 0; i < n; i++) {
        georginify_name(names[i]);
    }
    printf("Let's add some Georgia:\n");
    print_string_array(names, n);

    // free memory
    for (int i = 0; i < n; i++) {
        free(names[i]);
    }
    free(names);

    return OK;
}
