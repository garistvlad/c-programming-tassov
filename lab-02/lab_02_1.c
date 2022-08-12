#include <stdio.h>
#define OK 0

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
    float x, eps;
    float sum_of_series;

    setbuf(stdout, NULL);
    printf("Enter x and epsilon: ");
    scanf("%f %f", &x, &eps);

    sum_of_series = calculate_sum_untill_convergence(x, eps);
    printf("Resulting sum of series = %.3f\n", sum_of_series);
    return OK;
}