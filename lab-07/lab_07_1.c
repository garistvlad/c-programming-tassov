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

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

void transpose_wrt_main_diag(int m[MAX_SIZE][MAX_SIZE], int *n_rows, int *n_cols) {
    for (int i = 0; i < *n_rows; i++) {
        for (int j = 0; j < *n_cols; j++) {
            if (i < j || i >= *n_cols) {
                swap(&m[i][j], &m[j][i]);
            }
        }
    }
    swap(n_rows, n_cols);
}

void transpose_wrt_side_diag(int m[MAX_SIZE][MAX_SIZE], int *n_rows, int *n_cols) {
    if (*n_rows > *n_cols) {
        // add zero columns (from left)
        int new_columns_cnt = *n_rows - *n_cols;
        for (int i = 0; i < *n_rows; i++) {
            for (int j = *n_cols - 1; j >= 0; j--) {
                m[i][j+new_columns_cnt] = m[i][j];
                m[i][j] = 0;
            }
        }
    } else if (*n_cols > *n_rows) {
        // add zero rows (on top)
        int new_rows_cnt = *n_cols - *n_rows;
        for (int i = *n_rows - 1; i >= 0; i--) {
            for (int j = 0; j < *n_cols; j++) {
               m[i+new_rows_cnt][j] = m[i][j];
               m[i][j] = 0;
            }
        }
    }
    int new_size = max(*n_rows, *n_cols);
    for (int i = 0; i < new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            if (j < new_size - i - 1) {
                swap(&m[i][j], &m[new_size-j-1][new_size-i-1]);
            }
        }
    }
    swap(n_cols, n_rows);
}

int main() {
    setbuf(stdout, NULL);

    int n, m;
    int nums[MAX_SIZE][MAX_SIZE];

    printf("Enter n_rows and n_cols: ");
    scanf("%d %d", &n, &m);

    printf("Enter the matrix itself:\n");
    input_matrix(nums, n, m);

    printf("Transposed matrix w.r.t. main diagonal:\n");
    transpose_wrt_main_diag(nums, &n, &m);
    print_matrix(nums, n, m);
    // reverse transformation:
    transpose_wrt_main_diag(nums, &n, &m);

    printf("Transposed matrix w.r.t. side diagonal:\n");
    transpose_wrt_side_diag(nums, &n, &m);
    print_matrix(nums, n, m);
    
    return OK;
}
