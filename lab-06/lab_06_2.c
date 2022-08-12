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

int get_row_maxima(int *nums, int n_items) {
    assert(n_items > 0);
    int maxima = nums[0];
    for (int i = 1; i < n_items; i++) {
        if (nums[i] > maxima) {
            maxima = nums[i];
        }
    }
    return maxima;
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubble_sort_custom(int *nums, int * ids, int n) {
    assert(n >= 0);
    if (n == 0) {
        return;
    }
    for (int j = n - 1; j > 0; j--) {
        for (int i = 0; i < j; i++) {
            if (nums[i] > nums[i + 1]) {
                swap(&nums[i], &nums[i + 1]);
                swap(&ids[i], &ids[i + 1]);
            }
        }
    }
}

void print_array(int *nums, int n) {
    assert(n >= 0);
    for (int i = 0; i < n; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

void sort_by_rows_maxima(int m[MAX_SIZE][MAX_SIZE], int n_rows, int n_cols) {
    int maximas[n_rows];
    int target_ids[n_rows];
    // find maximas
    for (int i = 0; i < n_rows; i++) {
        int maxima_i = get_row_maxima(m[i], n_cols);
        target_ids[i] = i;
        maximas[i] = maxima_i;
    }
    // sort maximas
    bubble_sort_custom(maximas, target_ids, n_rows);
    
    // reorder rows of matrix
    for (int i = 0; i < n_rows; i++) {
        int target_i = target_ids[i];
        if (i == target_i) {
            continue;
        }
        // swap elements of matrix
        for (int j = 0; j < n_cols; j++) {
            swap(&m[i][j], &m[target_i][j]);
        }
        /* Change the target_ids array to avoid reverse swapping:
            - i -> target[i]
            - target[i] -> i
        */
        for (int k = 0; k < n_rows; k++) {
            if (target_ids[k] == i) {
                target_ids[k] = target_i;
            } else if (target_ids[k] == target_i) {
                target_ids[k] = i;
            }
        }
    }
}

int main() {
    setbuf(stdout, NULL);

    int n, m;
    int nums[MAX_SIZE][MAX_SIZE];

    printf("Enter n_rows and n_cols: ");
    scanf("%d %d", &n, &m);

    printf("Enter the matrix itself:\n");
    input_matrix(nums, n, m);

    sort_by_rows_maxima(nums, n, m);
    printf("Sorted matrix:\n");
    print_matrix(nums, n, m);

    return OK;
}
