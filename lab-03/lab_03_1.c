#include <stdio.h>
#include <math.h>

#define OK 0
#define EPSILON 0.00001

double f(double x) {
    return sin(x);
}

int main() {
    setbuf(stdout, NULL);

    double a, b;
    printf("Enter a and b: ");
    scanf("%lf %lf", &a, &b);

    double y;
    double area_under_curve = 0;
    for (double x = a; x <= b; x += EPSILON) {
        y = f(x);
        area_under_curve += fabs(y * EPSILON);
    }
    printf("Area under curve from %.3lf to %.3lf is %.3lf\n", a, b, area_under_curve);
    
    return OK;
}