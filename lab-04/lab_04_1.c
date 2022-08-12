#include <stdio.h>

#define OK 0
#define MAX_LENGTH 256

int main() {
    setbuf(stdout, NULL);

    double nums[MAX_LENGTH];
    int n;
    int first_neg_id, last_neg_id;
    
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    printf("Enter an array: ");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &nums[i]);
    }

    // find first and last negative element ids
    first_neg_id = -1;
    last_neg_id = -1;
    for (int i = 0; i < n; i++) {
        if (nums[i] >= 0) {
            continue;
        }
        if (first_neg_id == -1) {
            first_neg_id = i;
        } else {
            last_neg_id = i;
        }
    }

    if (first_neg_id == -1 && last_neg_id == -1) {
        // no negative numbers -> print 'NO NEGATIVE NUMBERS FOUND'.
        printf("NO NEGATIVE NUMBERS FOUND\n");
    } else if (last_neg_id == -1) {
        // one negative number -> 0
        printf("%.3f\n", 0.0);
    } else {
        // 2 or more negative numbers -> avg sum of positive numbers between
        double sum = 0.0;
        double positive_counter = 0;
        for (int i = first_neg_id + 1; i < last_neg_id; i++) {
            if (nums[i] > 0) {
                positive_counter += 1;
                sum += nums[i];
            }
        }
        printf("%.3lf\n", sum / positive_counter);
    }

    return OK;
}
