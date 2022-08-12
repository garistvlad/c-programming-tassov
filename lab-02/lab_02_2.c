#include <stdio.h>
#define OK 0

#define NUMBER_OF_POINTS 5

float calculate_sum_untill_convergence(float x, float eps) {
    // (x + n) / n! | starts from 1
    int i = 1;
    float numerator = x + i, denominator = 1;
    float prev = numerator / denominator;
    float cur;
    float result = prev;
    while (1) {
        i += 1;
        numerator = x + i;
        denominator *= i;
        cur = numerator / denominator;
        result += cur;
        if (prev - cur < eps) {
            return result;
        }
        prev = cur;
    }
}

int main() {
    float a, b, eps;
    float x, y;

    setbuf(stdout, NULL);
    printf("Enter a, b and epsilon: ");
    scanf("%f %f %f", &a, &b, &eps);

    printf("|%7c | %7c|\n", 'x', 'y');
    for (int i = 0; i < NUMBER_OF_POINTS; i++) {
        // split by NUMBER_OF_POINTS equal intervals
        x = a + (float)i * (b - a) / (float)(NUMBER_OF_POINTS - 1);
        y = calculate_sum_untill_convergence(x, eps);
        printf("|%7.3f | %7.3f|\n", x, y);
    }
    return OK;
}
