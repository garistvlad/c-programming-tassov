#include <stdio.h>
#include <stdbool.h>

#define OK 0
#define ERROR_WRONG_INPUT 1

float f1(float x) {
    // y = 2x
    return 2 * x;
}

float f2(float x) {
    // y = 2
    return 2;
}

float f3(float x) {
    // y = 6 - x
    return 6 - x;
}

int main() {
    setbuf(stdout, NULL);
    
    float x, y;
    bool is_inside_flag;

    printf("Enter coordinates of a point (x, y): ");
    int n = scanf("%f %f", &x, &y);
    if (n != 2) {
        printf("Error: wrong input\n");
        return ERROR_WRONG_INPUT;
    }

    is_inside_flag = (y <= f1(x) && y >= f2(x) && y <= f3(x));
    if (is_inside_flag) {
        printf("INSIDE\n");
    } else {
        printf("OUTSIDE\n");
    }

    return OK;
}
