#include <stdio.h>

#define OK 0
#define MAX_SIZE 256

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void sort(int *nums, int size) {
    /* O(n^2) sort by minimas */
    int min_id;
    for (int i = 0; i < size; i++) {
        min_id = i;
        for (int j = i; j < size; j++) {
            if (nums[j] < nums[i]) {
                min_id = j;
            }
        }
        if (nums[min_id] < nums[i]) {
            swap(&nums[i], &nums[min_id]);
        }
    }
}

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

int drop_duplicates(int *nums, int size) {
    /* Remove duplicates from an array and return new array size */
    sort(nums, size);
    int cur_id = 0;
    int new_size = size;
    for (int i = 1; i < size; i++) {
        if (nums[i] == nums[cur_id]) {
            new_size -= 1;
        } else {
            cur_id += 1;
            nums[cur_id] = nums[i];
        }
    }
    return new_size;
}

int main() {
    setbuf(stdout, NULL);

    int nums[MAX_SIZE];
    int size, new_size;
    // int repetitions[MAX_SIZE];

    printf("Enter array size: ");
    scanf("%d", &size);
    
    printf("Enter an integer array: ");
    fill_array(nums, size);
    
    new_size = drop_duplicates(nums, size);
    print_array(nums, new_size);

    return OK;
}
