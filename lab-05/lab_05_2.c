#include <stdio.h>
#include <assert.h>

#define OK 0
#define MAX_SIZE 256

void fill_array(int *nums, int size) {
    for (int i = 0; i < size; i++) {
        scanf("%d", &nums[i]);
    }
}

void print_array(int *nums, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void custom_sort(int *nums, int size) {
    /* Sort this way:
    - first, positive numbers in ascending order
    - then, zeroes
    - finally, negative numbers in descending order
    */
    // sorted positives
    int n_positive = 0;
    for (int i = 0; i < size; i++) {
        if (nums[i] <= 0) {
            continue;
        }
        int min_positive_id = i;
        for (int j = i; j < size; j++) {
            if (nums[j] > 0 && nums[j] < nums[i]) {
                min_positive_id = j;
            }
        }
        swap(&nums[i], &nums[min_positive_id]);
        swap(&nums[n_positive], &nums[i]);
        n_positive += 1;
    }
    // zeroes
    int n_zeroes = 0;
    for (int i = n_positive; i < size; i++) {
        if (nums[i] == 0) {
            swap(&nums[n_positive + n_zeroes], &nums[i]);
            n_zeroes += 1;
        }
    }
    // sorted negatives, reversed order
    for (int i = n_positive + n_zeroes; i < size; i++) {
        int max_id = i;
        for (int j = i; j < size; j++) {
            if (nums[j] > nums[max_id]) {
                max_id = j;
            }
        }
        if (max_id != i) {
            swap(&nums[max_id], &nums[i]);
        }
    }
}

int main() {
    setbuf(stdout, NULL);

    int nums[MAX_SIZE];
    int size;
    // int repetitions[MAX_SIZE];

    printf("Enter array size: ");
    scanf("%d", &size);
    assert(size > 0);
    
    printf("Enter an integer array: ");
    fill_array(nums, size);
    
    custom_sort(nums, size);
    print_array(nums, size);

    return OK;
}
