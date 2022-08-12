#include <stdio.h>
#include <math.h>

#define GOLDEN_RATE 1.618
#define EPSILON 0.00001
#define OK 0

double f(double x) {
    return pow(x, 2);
}

int main() {
    setbuf(stdout, NULL);

    double a, b;
    double x1, x2, y1, y2;
    printf("Enter a and b: ");
    scanf("%lf %lf", &a, &b);

    while (fabs(b - a) > EPSILON) {
        x1 = b - (b - a) / GOLDEN_RATE;
        x2 = a + (b - a) / GOLDEN_RATE;

        y1 = f(x1);
        y2 = f(x2);

        if (y1 >= y2) {
            a = x1;
        } else {
            b = x2;
        }
    }
    printf("X_min = %.3lf\n", (a + b) / 2.0);

    return OK;
}