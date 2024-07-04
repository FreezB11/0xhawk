#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

// Function to create a matrix
Matrix create_matrix(int rows, int cols) {
    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    mat.data = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
        mat.data[i] = (double *)malloc(cols * sizeof(double));
    }
    return mat;
}

// Function to free memory allocated for a matrix
void free_matrix(Matrix mat) {
    for (int i = 0; i < mat.rows; i++) {
        free(mat.data[i]);
    }
    free(mat.data);
}

// Function to print a matrix
void print_matrix(Matrix mat) {
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            printf("%lf ", mat.data[i][j]);
        }
        printf("\n");
    }
}

// Function to add two matrices
Matrix matrix_add(Matrix mat1, Matrix mat2) {
    Matrix result = create_matrix(mat1.rows, mat1.cols);
    for (int i = 0; i < mat1.rows; i++) {
        for (int j = 0; j < mat1.cols; j++) {
            result.data[i][j] = mat1.data[i][j] + mat2.data[i][j];
        }
    }
    return result;
}

// Function to subtract two matrices
Matrix matrix_subtract(Matrix mat1, Matrix mat2) {
    Matrix result = create_matrix(mat1.rows, mat1.cols);
    for (int i = 0; i < mat1.rows; i++) {
        for (int j = 0; j < mat1.cols; j++) {
            result.data[i][j] = mat1.data[i][j] - mat2.data[i][j];
        }
    }
    return result;
}

// Function to multiply two matrices
Matrix matrix_multiply(Matrix mat1, Matrix mat2) {
    Matrix result = create_matrix(mat1.rows, mat2.cols);
    for (int i = 0; i < mat1.rows; i++) {
        for (int j = 0; j < mat2.cols; j++) {
            result.data[i][j] = 0;
            for (int k = 0; k < mat1.cols; k++) {
                result.data[i][j] += mat1.data[i][k] * mat2.data[k][j];
            }
        }
    }
    return result;
}

// Function to multiply a matrix by a scalar
Matrix scalar_multiply(double scalar, Matrix mat) {
    Matrix result = create_matrix(mat.rows, mat.cols);
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            result.data[i][j] = scalar * mat.data[i][j];
        }
    }
    return result;
}

// Function to apply a function element-wise to a matrix
Matrix apply_function(Matrix mat, double (*func)(double)) {
    Matrix result = create_matrix(mat.rows, mat.cols);
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            result.data[i][j] = func(mat.data[i][j]);
        }
    }
    return result;
}
