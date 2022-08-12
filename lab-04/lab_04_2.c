#include <stdio.h>

#define OK 0
#define MAX_SIZE 256

void swap(int *a, int *b) {
    float tmp = *a;
    *a = *b;
    *b = tmp;
}

int count(int *nums, int element, int size) {
    /* count number of occurence of element inside an array */
    int n = 0;
    for (int i = 0; i < size; i++) {
        if (nums[i] == element) {
            n += 1;
        }
    }
    return n;
}

void print_array(int *nums, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

int main() {
    setbuf(stdout, NULL);

    int nums[MAX_SIZE];
    int n;
    int min_id, max_id;

    printf("Enter size of array: ");
    scanf("%d", &n);
    printf("Enter an array of integers: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    min_id = 0;
    max_id = 0;
    for (int i = 1; i < n; i++) {
        if (nums[i] < nums[min_id]) {
            min_id = i;
        }
        if (nums[i] > nums[max_id]) {
            max_id = i;
        }
    }

    if (min_id != max_id && count(nums, nums[min_id], n) == 1 && count(nums, nums[max_id], n) == 1) {
        swap(&nums[min_id], &nums[max_id]);
    }

    print_array(nums, n);
    
    return OK;
}
