#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ERROR_OUT_OF_MEMORY -1


void print_matrix(int **data, int n_rows, int n_cols) {
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_cols; j++) {
            printf("%d ", data[i][j]);
        }
        printf("\n");
    }
}

void input_matrix(int **data, int n_rows, int n_cols) {
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_cols; j++) {
            scanf("%d", &data[i][j]);
        }
    }
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int abs(int a) {
    return (a > 0) ? a : -a;
}

int min(int a, int b) {
    return (a > b) ? b : a;
}

void sort_one_diag(int **data, int n_rows, int n_cols, int margin) {
    /* margin - size of step forward/backward from a main diagonal */
    int diag_size;
    if (margin >= 0) {
        diag_size = min(n_cols - abs(margin), n_rows);
    } else {
        diag_size = min(n_rows - abs(margin), n_cols);
    }

    int *arr = calloc(diag_size, sizeof(int));
    
    for (int i = 0; i < diag_size; i++) {
        if (margin <= 0) {
            arr[i] = data[abs(margin) + i][i];
        } else {
            arr[i] = data[i][i + abs(margin)];
        }
    }

    // sort by minimas
    for (int i = 0; i < diag_size; i++) {
        int min_id = i;
        for (int j = i; j < diag_size; j++) {
            if (arr[min_id] > arr[j]) {
                min_id = j;
            }
        }
        swap(&arr[i], &arr[min_id]);
        if (margin <= 0) {
            swap(&data[abs(margin) + i][i], &data[abs(margin) + min_id][min_id]);
        } else {
            swap(&data[i][i + abs(margin)], &data[min_id][min_id + abs(margin)]);
        }
    }

    free(arr);
}

void sort_all_diags(int **data, int n_rows, int n_cols) {
    for (int i = -(n_rows - 2); i <= n_cols - 2; i++) {
        sort_one_diag(data, n_rows, n_cols, i);
    }
}

int main() {
    setbuf(stdout, NULL);

    int n_rows, n_cols;
    int **nums;

    printf("Enter number of rows and columns: ");
    scanf("%d %d", &n_rows, &n_cols);

    nums = calloc(n_rows, sizeof(int*));
    if (!nums) {
        return ERROR_OUT_OF_MEMORY;
    }
    for (int i = 0; i < n_rows; i++) {
        nums[i] = calloc(n_cols, sizeof(int));
    }

    printf("Input the matrix elements:\n");
    input_matrix(nums, n_rows, n_cols);

    printf("Result:\n");
    sort_all_diags(nums, n_rows, n_cols);
    print_matrix(nums, n_rows, n_cols);

    // free memory
    for (int i = 0; i < n_rows; i++) {
        free(nums[i]);
    }
    free(nums);

    return OK;
}
