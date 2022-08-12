#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define ERROR_OPEN_FILE 1

#define N_SUBJECTS 5
#define INPUT_FILEPATH "./data/students.txt"
#define OUTPUT_FILEPATH "./data/filtered_students.txt"
#define FIELDS_DELIMETER ";"
#define NUMBERS_DELIMETER " "

#define MAX_STRING_LENGTH 1024
#define MAX_STUDENTS 128

struct Student {
    char *name;
    int marks[N_SUBJECTS];
};

void print_array(int *nums, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

int sum_array(int *nums, int size) {
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += nums[i];
    }
    return total;
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void minimas_sort(int *nums, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (nums[j] < nums[i]) {
                swap(&nums[i], &nums[j]);
            }
        }
    }
}

void swap_students(struct Student *a, struct Student *b) {
    struct Student tmp = *a;
    *a = *b;
    *b = tmp;
}

int compare_students(struct Student a, struct Student b) {
    // returns: 1 - greater (a > b), 0 - equal (a = b), -1 - lower (a < b)
    // 1. compare by marks (they are expected to be already sorted)
    for (int i = N_SUBJECTS - 1; i >= 0; i--) {
        if (a.marks[i] > b.marks[i]) {
            return 1;
        } else if (a.marks[i] < b.marks[i]) {
            return -1;
        }
    }
    // 2. compare names, because all the marks are equal
    int name_comparator = strcmp(a.name, b.name);
    if (name_comparator > 0) {
        return 1;
    } else if (name_comparator < 0) {
        return - 1;
    } else {
        return 0;
    }
}

void sort_students(struct Student *group, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (compare_students(group[j], group[i]) == -1) {
                swap_students(&group[i], &group[j]);
            }
        }
    }
}

void print_groupped_students(struct Student *group, int size) {
    int total_score = sum_array(group[size - 1].marks, N_SUBJECTS);
    printf("------- Total: %2d -------\n", total_score);
    for (int i = size - 1; i >= 0; i--) {
        if (total_score != sum_array(group[i].marks, N_SUBJECTS)) {
            total_score = sum_array(group[i].marks, N_SUBJECTS);
            printf("\n------- Total: %2d -------\n", total_score);
        }
        printf("%s\n", group[i].name);
    }
    printf("-------------------------\n");
}

int check_should_be_deleted(struct Student a) {
    int n_failures = 0;
    for (int i = 0; i < N_SUBJECTS; i++) {
        if (a.marks[i] == 2) {
            n_failures += 1;
        }
    }
    return (n_failures >= 2) ? 1 : 0;
}

int main() {
    setbuf(stdout, NULL);

    FILE *fptr;
    struct Student student;
    char *buf;
    char *tmp;
    struct Student group[MAX_STUDENTS];

    fptr = fopen(INPUT_FILEPATH, "r");
    if (fptr == NULL) {
        printf("Error with file opening");
        exit(ERROR_OPEN_FILE);
    }

    buf = calloc(1, sizeof(char) * MAX_STRING_LENGTH);

    int n_students = 0;
    while (fgets(buf, MAX_STRING_LENGTH, fptr)) {
        if(strlen(buf) > 0 && buf[strlen(buf) - 1] == '\n') {
            buf[strlen(buf) - 1] = '\0';
        }
        // to skip empty strings:
        if (strlen(buf) == 0) {
            continue;
        }
        // 1st field - name
        tmp = strsep(&buf, FIELDS_DELIMETER);
        student.name = tmp;
        // 2d field - marks
        for (int i = 0; i < N_SUBJECTS && tmp != NULL; i++) {
            if (i == 0) {
                tmp = strtok(buf, NUMBERS_DELIMETER);
            } else {
                tmp = strtok(NULL, NUMBERS_DELIMETER);
            }
            student.marks[i] = atoi(tmp);
        }

        if (check_should_be_deleted(student) == 1) {
            continue;
        }
        minimas_sort(student.marks, N_SUBJECTS);
        group[n_students] = student;
        n_students++;
    }

    fclose(fptr);

    sort_students(group, n_students);
    // print_groupped_students(group, n_students);

    // Write sorted and groupped students to OUTPUT FILE
    fptr = fopen(OUTPUT_FILEPATH, "w");
    int total_score = sum_array(group[0].marks, N_SUBJECTS);
    for (int i = 0; i < n_students; i++) {
        if (total_score != sum_array(group[i].marks, N_SUBJECTS)) {
            total_score = sum_array(group[i].marks, N_SUBJECTS);
            fprintf(fptr, "\n");
        }
        fprintf(fptr, "%s\n", group[i].name);
    }
    fclose(fptr);

    return OK;
}
