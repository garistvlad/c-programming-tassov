#include <stdio.h>
#include <assert.h>

#define OK 0
#define MAX_SIZE 256


void input_matrix(int m[MAX_SIZE][MAX_SIZE], int n_rows, int n_cols) {
    assert(n_rows > 0 && n_cols > 0);
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_cols; j++) {
            scanf("%d", &m[i][j]);
        }
    }
}

void print_matrix(int m[MAX_SIZE][MAX_SIZE], int n_rows, int n_cols) {
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_cols; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}

int find_minima(int m[MAX_SIZE][MAX_SIZE], int n_rows, int n_cols) {
    assert(n_rows > 0 && n_cols > 0);
    int min = m[0][0];
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_cols; j++) {
            if (m[i][j] < min) {
                min = m[i][j];
            }
        }
    }
    return min;
}

void delete_rows_and_cols_by_value(int m[MAX_SIZE][MAX_SIZE], int *n_rows, int *n_cols, int value) {
    int target_i, target_j;
    int found_flag = 0;
    for (int i = 0; i < *n_rows && found_flag != 1; i++) {
        for (int j = 0; j < *n_cols && found_flag != 1; j++) {
            if (m[i][j] == value) {
                found_flag = 1;
                target_i = i;
                target_j = j;
            }
        }
    }
    if (found_flag == 0) {
        return;
    }
    // delete row target_i
    for (int i = target_i; i < *n_rows; i++) {
        for (int j = 0; j < *n_cols; j++) {
            m[i][j] = m[i+1][j];
        }
    }
    *n_rows -= 1;
    // delete col target_j
    for (int i = 0; i < *n_rows; i++) {
        for (int j = target_j; j < *n_cols; j++) {
            m[i][j] = m[i][j+1];
        }
    }
    *n_cols -= 1;
    delete_rows_and_cols_by_value(m, n_rows, n_cols, value);
}

int main() {
    setbuf(stdout, NULL);

    int n, m;
    int nums[MAX_SIZE][MAX_SIZE];
    int minima;

    printf("Enter n_rows and n_cols: ");
    scanf("%d %d", &n, &m);

    printf("Enter the matrix itself:\n");
    input_matrix(nums, n, m);

    minima = find_minima(nums, n, m);
    
    delete_rows_and_cols_by_value(nums, &n, &m, minima);
    printf("After deletion, matrix %dx%d:\n", n, m);
    print_matrix(nums, n, m);
    
    return OK;
}
