#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OK 0
#define ERROR_OPEN_FILE 1

#define CARS_FILEPATH "data/cars.txt"
#define FIELD_LENGTH 64

typedef struct Car {
    char brand[FIELD_LENGTH];
    char model[FIELD_LENGTH];
    char category[2];
    int year;
    int power;
    float capacity;
} car;


void add() {
    FILE *fptr;
    car new_car;
    
    fptr = fopen(CARS_FILEPATH, "ab");
    if (!fptr) {
        exit(ERROR_OPEN_FILE);
    }

    printf("Enter car brand: ");
    scanf("%s", new_car.brand);

    printf("Enter car model: ");
    scanf("%s", new_car.model);

    printf("Enter vehicle category: ");
    scanf("%s", new_car.category);

    printf("Enter year of production: ");
    scanf("%d", &new_car.year);

    printf("Enter engine power [HP]: ");
    scanf("%d", &new_car.power);

    printf("Enter capacity [L]: ");
    scanf("%f", &new_car.capacity);

    fwrite(&new_car, sizeof(new_car), 1, fptr);

    fclose(fptr);
}

void delete() {
    FILE *fptr;
    FILE *tmpptr;
    car some_car;
    char brand_to_delete[FIELD_LENGTH];
    int found = 0;

    fptr = fopen(CARS_FILEPATH, "rb");
    tmpptr = fopen("data/tmp.txt", "wb");

    printf("Enter the brand to delete from file: ");
    scanf("%s", brand_to_delete);

    while(fread(&some_car, sizeof(some_car), 1, fptr)) {
        if (strcmp(some_car.brand, brand_to_delete) == 0) {
            found = 1;
        } else {
            fwrite(&some_car, sizeof(some_car), 1, tmpptr);
        }
    }

    fclose(fptr);
    fclose(tmpptr);
    if (found == 1) {
        printf("Car `%s` was successfully deleted\n", brand_to_delete);
        remove(CARS_FILEPATH);
        rename("data/tmp.txt", CARS_FILEPATH);
    } else {
        printf("Car `%s` was not found\n", brand_to_delete);
    }
}

void display() {
    FILE *fptr;
    car some_car;
    
    fptr = fopen(CARS_FILEPATH, "rb");
    if (!fptr) {
        exit(ERROR_OPEN_FILE);
    }

    while(fread(&some_car, sizeof(some_car), 1, fptr)) {
        printf("%-10s %-10s %2s %5d %5d %5.1f\n", some_car.brand, some_car.model, some_car.category, some_car.year, some_car.power, some_car.capacity);
    }

    fclose(fptr);
}

void search_by_brand() {
    FILE *fptr;
    car some_car;
    char brand_to_find[FIELD_LENGTH];
    int found = 0;

    fptr = fopen(CARS_FILEPATH, "rb");
    if (!fptr) {
        exit(ERROR_OPEN_FILE);
    }

    printf("Enter the brand to find: ");
    scanf("%s", brand_to_find);

    while(fread(&some_car, sizeof(some_car), 1, fptr)) {
        if (strcmp(some_car.brand, brand_to_find) == 0) {
            found = 1;
            printf("%-10s %-10s %2s %5d %5d %5.1f\n", some_car.brand, some_car.model, some_car.category, some_car.year, some_car.power, some_car.capacity);
        }
    }

    if (found == 0) {
        printf("There were no cars found with brand `%s`.\n", brand_to_find);
    }

    fclose(fptr);

}

void search_by_year() {
    FILE *fptr;
    car some_car;
    int year_to_find;
    int found = 0;

    fptr = fopen(CARS_FILEPATH, "rb");
    if (!fptr) {
        exit(ERROR_OPEN_FILE);
    }

    printf("Enter the year to find: ");
    scanf("%d", &year_to_find);

    while(fread(&some_car, sizeof(some_car), 1, fptr)) {
        if (year_to_find == some_car.year) {
            found = 1;
            printf("%-10s %-10s %2s %5d %5d %5.1f\n", some_car.brand, some_car.model, some_car.category, some_car.year, some_car.power, some_car.capacity);
        }
    }

    if (found == 0) {
        printf("There were no cars found produced in `%d`.\n", year_to_find);
    }

    fclose(fptr);
}

int get_number_of_cars() {
    FILE *fptr;
    car some_car;
    int n = 0;
    fptr = fopen(CARS_FILEPATH, "rb");
    while (fread(&some_car, sizeof(some_car), 1, fptr)) {
        n++;
    }
    fclose(fptr);
    return n;
}

void swap(car *one, car *two) {
    car tmp = *one;
    *one = *two;
    *two = tmp;
}

void sort_by_brand() {
    FILE *fptr;
    car *cars;
    int n;

    n = get_number_of_cars();
    fptr = fopen(CARS_FILEPATH, "rb");
    cars = (car *)calloc(n, sizeof(car));
    // read list of cars
    for (int i = 0; i < n; i++) {
        fread(&cars[i], sizeof(car), 1, fptr);
    }
    fclose(fptr);
    // sort it by brand
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if(strcmp(cars[j].brand, cars[i].brand) < 0) {
                swap(&cars[i], &cars[j]);
            }
        }
    }
    // save to file
    fptr = fopen(CARS_FILEPATH, "wb");
    for (int i = 0; i < n; i++) {
        fwrite(&cars[i], sizeof(car), 1, fptr);
    }

    fclose(fptr);
    free(cars);

}

void sort_by_power() {
    FILE *fptr;
    car *cars;
    int n;

    n = get_number_of_cars();
    fptr = fopen(CARS_FILEPATH, "rb");
    cars = (car *)calloc(n, sizeof(car));
    // read list of cars
    for (int i = 0; i < n; i++) {
        fread(&cars[i], sizeof(car), 1, fptr);
    }
    fclose(fptr);
    // sort it by brand
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if(cars[j].power < cars[i].power) {
                swap(&cars[i], &cars[j]);
            }
        }
    }
    // save to file
    fptr = fopen(CARS_FILEPATH, "wb");
    for (int i = 0; i < n; i++) {
        fwrite(&cars[i], sizeof(car), 1, fptr);
    }

    fclose(fptr);
    free(cars);
}

void sort_by_capacity() {
    FILE *fptr;
    car *cars;
    int n;

    n = get_number_of_cars();
    fptr = fopen(CARS_FILEPATH, "rb");
    cars = (car *)calloc(n, sizeof(car));
    // read list of cars
    for (int i = 0; i < n; i++) {
        fread(&cars[i], sizeof(car), 1, fptr);
    }
    fclose(fptr);
    // sort it by brand
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if(cars[j].capacity < cars[i].capacity) {
                swap(&cars[i], &cars[j]);
            }
        }
    }
    // save to file
    fptr = fopen(CARS_FILEPATH, "wb");
    for (int i = 0; i < n; i++) {
        fwrite(&cars[i], sizeof(car), 1, fptr);
    }

    fclose(fptr);
    free(cars);
}

int main() {
    setbuf(stdout, NULL);
    
    int cmd;
    int cmd_level_two;

    do
    {
        printf("\n");
        printf("1. ADD\n");
        printf("2. DELETE\n");
        printf("3. DISPLAY\n");
        printf("4. SEARCH\n");
        printf("5. SORT\n");
        printf("0. EXIT\n");

        printf("\nYour command: ");
        scanf("%d", &cmd);

        switch (cmd) {
        case 1:
            add();
            break;
        case 2:
            delete();
            break;
        case 3:
            display();
            break;
        case 4:
            printf("1. BY BRAND\n");
            printf("2. BY YEAR\n");
            printf("0. BACK\n");

            printf("\nYour command: ");
            scanf("%d", &cmd_level_two);

            switch (cmd_level_two) {
            case 1:
                search_by_brand();
                break;
            case 2:
                search_by_year();
                break;
            default:
                break;
            }
            break;
        case 5:
            printf("1. BY BRAND\n");
            printf("2. BY POWER\n");
            printf("3. BY CAPACITY\n");
            printf("0. BACK\n");

            printf("\nYour command: ");
            scanf("%d", &cmd_level_two);

            switch (cmd_level_two) {
            case 1:
                sort_by_brand();
                break;
            case 2:
                sort_by_power();
                break;
            case 3:
                sort_by_capacity();
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    } while (cmd != 0);
    
    return OK;
}