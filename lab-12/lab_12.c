#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OK 0
#define ERROR_OPEN_FILE 1

#define LONG_STRING_LENGTH 128
#define SHORT_STRING_LENGTH 32

#define MOVIES_FILEPATH "data/movies.bin"
#define YEAR_INDEX "data/year_index.bin"
#define NAME_INDEX "data/name_index.bin"
#define DELETED_LABEL "__DELETED__"

typedef struct Movie {
    char name[LONG_STRING_LENGTH];
    char director[LONG_STRING_LENGTH];
    int year;
    char genre[SHORT_STRING_LENGTH];
    int length;
} movie;

void display();
int interpolation_search(int year);
void add();
void delete();
void search_by_year();
void search_by_genre();
int get_file_length();
void swap(movie *a, movie *b);
void sort_by_name();
void sort_by_year();
void display_deleted();


int main() {
    setbuf(stdout, NULL);
    
    int cmd;
    int cmd_next;

    do {

        printf("\n1. Add movie\n");
        printf("2. Delete movie\n");
        printf("3. Search movies\n");
        printf("4. Sort movies\n");
        printf("5. Display all movies\n");
        printf("6. Display deleted movies\n");
        printf("0. Exit\n");

        printf("\nEnter your command: ");
        scanf("%d", &cmd);

        switch (cmd)
        {
        case 1:
            add();
            break;
        case 2:
            delete();
            break;
        case 3:
            printf("\n1. Search by year\n");
            printf("2. Search by genre\n");
            printf("0. Back to menu\n");

            printf("\nEnter your command: ");
            scanf("%d", &cmd_next);

            switch (cmd_next)
            {
            case 1:
                search_by_year();
                break;
            case 2:
                search_by_genre();
                break;
            default:
                break;
            }

            break;
        case 4:
            printf("\n1. Sort by name\n");
            printf("2. Sort by year\n");
            printf("0. Back to menu\n");

            printf("\nEnter your command: ");
            scanf("%d", &cmd_next);

            switch (cmd_next)
            {
            case 1:
                sort_by_name();
                break;
            case 2:
                // movies are sorted by year by default
                display();
                break;
            default:
                break;
            }
            
            break;
        case 5:
            display();
            break;
        case 6:
            display_deleted();
            break;
        default:
            break;
        }
    } while (cmd != 0);

    return OK;
}

void add() {
    FILE *fptr, *yptr, *nptr;
    movie some_movie;

    // file pointer
    fptr = fopen(MOVIES_FILEPATH, "a+b");
    // year index file pointer
    yptr = fopen(YEAR_INDEX, "a+b");
    // name index file pointer
    nptr = fopen(NAME_INDEX, "a+b");

    fflush(stdin);
    printf("Enter movie name: ");
    scanf("%[^\n]s", some_movie.name);
    fflush(stdin);

    printf("Enter director: ");
    scanf("%[^\n]s", some_movie.director);
    fflush(stdin);

    printf("Enter year of release: ");
    scanf("%d", &some_movie.year);
    fflush(stdin);

    printf("Enter genre: ");
    scanf("%[^\n]s", some_movie.genre);
    fflush(stdin);

    printf("Enter movie length in minutes: ");
    scanf("%d", &some_movie.length);

    fwrite(&some_movie, sizeof(some_movie), 1, fptr);
    fwrite(some_movie.name, sizeof(some_movie.name), 1, nptr);
    fwrite(&some_movie.year, sizeof(some_movie.year), 1, yptr);

    fclose(fptr);
    fclose(yptr);
    fclose(nptr);

    sort_by_year();
}

void sort_by_year() {
    FILE *fptr, *yptr, *nptr;
    int n;
    movie movie_a, movie_b;
    int year_a, year_b;
    char name_a[LONG_STRING_LENGTH];
    char name_b[LONG_STRING_LENGTH];

    fptr = fopen(MOVIES_FILEPATH, "r+b");
    yptr = fopen(YEAR_INDEX, "r+b");
    nptr = fopen(NAME_INDEX, "r+b");

    n = get_file_length();

    for (int i = 0; i < n; i++) {
        fseek(yptr, sizeof(int) * i, SEEK_SET);
        fread(&year_a, sizeof(int), 1, yptr);
        
        for (int j = i + 1; j < n; j++) {
            fseek(yptr, sizeof(int) * j, SEEK_SET);
            fread(&year_b, sizeof(int), 1, yptr);
            
            if (year_b < year_a) {
                
                // replace in year index
                fseek(yptr, sizeof(int) * i, SEEK_SET);
                fwrite(&year_b, sizeof(int), 1, yptr);
                fseek(yptr, sizeof(int) * j, SEEK_SET);
                fwrite(&year_a, sizeof(int), 1, yptr);
                
                year_a = year_b;
                
                // replace in movies file
                fseek(fptr, sizeof(movie) * i, SEEK_SET);
                fread(&movie_a, sizeof(movie), 1, fptr);
                fseek(fptr, sizeof(movie) * j, SEEK_SET);
                fread(&movie_b, sizeof(movie), 1, fptr);
                
                fseek(fptr, sizeof(movie) * i, SEEK_SET);
                fwrite(&movie_b, sizeof(movie), 1, fptr);
                fseek(fptr, sizeof(movie) * j, SEEK_SET);
                fwrite(&movie_a, sizeof(movie), 1, fptr);

                // replace in names file
                fseek(nptr, LONG_STRING_LENGTH * i, SEEK_SET);
                fread(name_a, LONG_STRING_LENGTH, 1, nptr);
                fseek(nptr, LONG_STRING_LENGTH * j, SEEK_SET);
                fread(name_b, LONG_STRING_LENGTH, 1, nptr);

                fseek(nptr, LONG_STRING_LENGTH * i, SEEK_SET);
                fwrite(name_b, LONG_STRING_LENGTH, 1, nptr);
                fseek(nptr, LONG_STRING_LENGTH * j, SEEK_SET);
                fwrite(name_a, LONG_STRING_LENGTH, 1, nptr);

            }
        }
    }

    fclose(yptr);
    fclose(nptr);
    fclose(fptr);
}

void delete() {
    FILE *nptr;
    int found = 0;
    char movie_to_delete[LONG_STRING_LENGTH];
    char some_name[LONG_STRING_LENGTH];

    nptr = fopen(NAME_INDEX, "r+b");
    if (nptr == NULL) {
        exit(ERROR_OPEN_FILE);
    }

    printf("Enter the movie name to delete:\n");
    fflush(stdin);
    scanf("%[^\n]s", movie_to_delete);
    while(fread(&some_name, LONG_STRING_LENGTH, 1, nptr)) {
        if (strcmp(some_name, movie_to_delete) == 0) {
            found = 1;
            // shift cursor back and replace this name in index file:
            fseek(nptr, LONG_STRING_LENGTH * (-1), SEEK_CUR);
            fwrite(DELETED_LABEL, LONG_STRING_LENGTH, 1, nptr);
        }
    }

    if (found == 1) {
        printf("Movie `%s` was successfully deleted\n", movie_to_delete);
    } else {
        printf("Movie `%s` was not found\n", movie_to_delete);
    }

    fclose(nptr);

}

void display() {
    FILE *fptr, *nptr;
    char some_name[LONG_STRING_LENGTH];
    movie some_movie;

    fptr = fopen(MOVIES_FILEPATH, "rb");
    nptr = fopen(NAME_INDEX, "rb");
    
    int i = 0;
    while(fread(some_name, LONG_STRING_LENGTH, 1, nptr)) {
        // skip deleted movies
        if (strcmp(some_name, DELETED_LABEL) != 0) {
            fseek(fptr, sizeof(movie) * i, SEEK_SET);
            fread(&some_movie, sizeof(movie), 1, fptr);
            printf("%-25s %-20s %6d %-10s %6d\n", some_movie.name, some_movie.director, some_movie.year, some_movie.genre, some_movie.length);
        }
        i += 1;
    }

    fclose(fptr);
    fclose(nptr);
}

void display_deleted() {
    FILE *fptr, *nptr;
    char some_name[LONG_STRING_LENGTH];
    movie some_movie;

    fptr = fopen(MOVIES_FILEPATH, "rb");
    nptr = fopen(NAME_INDEX, "rb");
    
    int i = 0;
    while(fread(some_name, LONG_STRING_LENGTH, 1, nptr)) {
        // skip deleted movies
        if (strcmp(some_name, DELETED_LABEL) == 0) {
            fseek(fptr, sizeof(movie) * i, SEEK_SET);
            fread(&some_movie, sizeof(movie), 1, fptr);
            printf("%-25s %-20s %6d %-10s %6d\n", some_movie.name, some_movie.director, some_movie.year, some_movie.genre, some_movie.length);
        }
        i += 1;
    }

    fclose(fptr);
    fclose(nptr);
}

int get_file_length() {
    FILE *fptr;
    int n;

    fptr = fopen(YEAR_INDEX, "rb");

    fseek(fptr, 0, SEEK_END);
    n = ftell(fptr) / sizeof(int);

    fclose(fptr);

    return n;
}

int interpolation_search(int year) {
    FILE *yptr;
    int low, high, mid;
    int year_high, year_low, year_mid;

    yptr = fopen(YEAR_INDEX, "rb");
    
    high = get_file_length() - 1;
    low = 0;

    while (low <= high) {
        
        fseek(yptr, sizeof(int) * low, SEEK_SET);
        fread(&year_low, sizeof(int), 1, yptr);

        fseek(yptr, sizeof(int) * high, SEEK_SET);
        fread(&year_high, sizeof(int), 1, yptr);

        // mid = low + (high - low) * (year - year_low) / (year_high - year_low);
        mid = (low + high) / 2;

        fseek(yptr, sizeof(int) * mid, SEEK_SET);
        fread(&year_mid, sizeof(int), 1, yptr);

        if (year_mid >= year) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    if (high + 1 <= get_file_length() - 1) {
        high = high + 1;
    } else {
        high = get_file_length() - 1;
    }

    fseek(yptr, sizeof(int) * high, SEEK_SET);
    fread(&year_high, sizeof(int), 1, yptr);
    fclose(yptr);

    if (year_high == year) {
        return high;
    } else {
        return -1;
    }

}

void search_by_year() {
    FILE *fptr, *nptr;
    int year;
    int first_index;
    movie some_movie;
    char some_name[LONG_STRING_LENGTH];
    int found = 0;

    fptr = fopen(MOVIES_FILEPATH, "rb");
    nptr = fopen(NAME_INDEX, "rb");

    printf("Enter the year to find: ");
    scanf("%d", &year);

    first_index = interpolation_search(year);
    if (first_index != -1) {
        // start from found index and further
        int i = first_index;
        fseek(fptr, sizeof(movie) * first_index, SEEK_SET);
        while(fread(&some_movie, sizeof(some_movie), 1, fptr)) {
            if (some_movie.year == year) {
                // confirm that it is not a deleted movie:
                fseek(nptr, LONG_STRING_LENGTH * i, SEEK_SET);
                fread(some_name, LONG_STRING_LENGTH, 1, nptr);
                if (strcmp(some_name, DELETED_LABEL) != 0) {
                    found = 1;
                    printf("%-25s %-20s %6d %-10s %6d\n", some_movie.name, some_movie.director, some_movie.year, some_movie.genre, some_movie.length);
                }
                i++;
            } else {
                break;
            }
        }
    }

    fclose(fptr);
    fclose(nptr);

    if (found == 0) {
        printf("There were no movies with year `%d`\n", year);
    }
}

void search_by_genre() {
    FILE *fptr, *nptr;
    char genre[SHORT_STRING_LENGTH];
    int found = 0;
    movie some_movie;
    char some_name[LONG_STRING_LENGTH];

    fptr = fopen(MOVIES_FILEPATH, "rb");
    if (fptr == NULL) {
        exit(ERROR_OPEN_FILE);
    }
    nptr = fopen(NAME_INDEX, "rb");

    printf("Enter the genre to find: ");
    fflush(stdin);
    scanf("%[^\n]s", genre);
    int i = 0;
    while(fread(&some_movie, sizeof(some_movie), 1, fptr)) {
        fseek(nptr, LONG_STRING_LENGTH * i, SEEK_SET);
        fread(some_name, LONG_STRING_LENGTH, 1, nptr);
        i++;

        if (strcmp(some_name, DELETED_LABEL) == 0) {
            continue;
        }

        if (strcmp(some_movie.genre, genre) == 0) {
            found = 1;
            printf("%-25s %-20s %6d %-10s %6d\n", some_movie.name, some_movie.director, some_movie.year, some_movie.genre, some_movie.length);
        }
    }

    if (found == 0) {
        printf("There were no movies with genre `%s`\n", genre);
    }

    fclose(fptr);
    fclose(nptr);
}

void swap(movie *a, movie *b) {
    movie tmp = *a;
    *a = *b;
    *b = tmp;
}

void sort_by_name() {
    FILE *fptr, *nptr;
    int n;
    movie some_movie;
    movie *movies;
    char some_name[LONG_STRING_LENGTH];

    fptr = fopen(MOVIES_FILEPATH, "rb");
    if (fptr == NULL) {
        exit(ERROR_OPEN_FILE);
    }
    nptr = fopen(NAME_INDEX, "rb");

    n = get_file_length();
    movies = calloc(n, sizeof(movie));

    int j = 0;
    for (int i = 0; i < n; i++) {
        fread(&some_movie, sizeof(movie), 1, fptr);

        fseek(nptr, LONG_STRING_LENGTH * i, SEEK_SET);
        fread(some_name, LONG_STRING_LENGTH, 1, nptr);
        if (strcmp(some_name, DELETED_LABEL) != 0) {
            movies[i-j] = some_movie;
        } else {
            j++;
        }
    }
    n -= j;

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (strcmp(movies[j].name, movies[i].name) < 0) {
                swap(&movies[j], &movies[i]);
            }
        }
    }

    printf("%-25s %-20s %6s %-10s %6s\n", "Name", "Director", "Year", "Genre", "Length");
    for (int i = 0; i < n; i++) {
        // show only not deleted films:
        printf("%-25s %-20s %6d %-10s %6d\n", movies[i].name, movies[i].director, movies[i].year, movies[i].genre, movies[i].length);
    }

    free(movies);
    fclose(fptr);
    fclose(nptr);
}
