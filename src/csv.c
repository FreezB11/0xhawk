#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COLS 100
#define MAX_ROWS 100

int main() {
    FILE *file = fopen("data.csv", "r"); // Replace "data.csv" with your CSV file path
    if (!file) {
        printf("Failed to open file\n");
        return 1;
    }

    char buffer[1024];
    char *field;
    char *row[MAX_COLS];
    int row_count = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        field = strtok(buffer, ",");
        row_count = 0;
        while (field != NULL && row_count < MAX_COLS) {
            row[row_count++] = strdup(field);
            field = strtok(NULL, ",");
        }
        
        // Process row data here
        // Example: print each field
        for (int i = 0; i < row_count; i++) {
            printf("%s ", row[i]);
            free(row[i]); // Free memory allocated by strdup
        }
        printf("\n");
    }

    fclose(file);
    return 0;
}