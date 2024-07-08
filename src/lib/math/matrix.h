#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    int rows;
    int cols;
    double **data;
} Matrix;

Matrix create_matrix(int rows, int cols);
void free_matrix(Matrix mat);
void print_matrix(Matrix mat);
Matrix matrix_add(Matrix mat1, Matrix mat2);
Matrix matrix_subtract(Matrix mat1, Matrix mat2);
Matrix matrix_multiply(Matrix mat1, Matrix mat2);
Matrix scalar_multiply(double scalar, Matrix mat);
Matrix apply_function(Matrix mat, double (*func)(double));

#endif /* MATRIX_H */
