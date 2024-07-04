#include <stdio.h>
#include <stdlib.h>

// Define a struct to encapsulate the array
typedef struct {
    int rows;
    int cols;
    int **data;
} Array2D;

// Function prototypes
void print2DArray(Array2D arr);
void free2DArray(Array2D arr);

int main() {
    // Dynamically allocate memory for the struct
    Array2D arr;
    arr.rows = 3;
    arr.cols = 4;

    // Dynamically allocate memory for the 2D array
    arr.data = (int **)malloc(arr.rows * sizeof(int *));
    for (int i = 0; i < arr.rows; i++) {
        arr.data[i] = (int *)malloc(arr.cols * sizeof(int));
    }

    // Initialize the 2D array with some values
    for (int i = 0; i < arr.rows; i++) {
        for (int j = 0; j < arr.cols; j++) {
            arr.data[i][j] = 1;
        }
    }

    // Pass the struct to the function
    print2DArray(arr);

    // Free dynamically allocated memory
    free2DArray(arr);

    return 0;
}

// Function definition to print the 2D array encapsulated in the struct
void print2DArray(Array2D arr) {
    for (int i = 0; i < arr.rows; i++) {
        for (int j = 0; j < arr.cols; j++) {
            printf("%d ", arr.data[i][j]);
        }
        printf("\n");
    }
}

// Function to free dynamically allocated memory for the 2D array
void free2DArray(Array2D arr) {
    for (int i = 0; i < arr.rows; i++) {
        free(arr.data[i]);
    }
    free(arr.data);
}
