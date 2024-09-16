#include "matrix.h"

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols), data(rows, std::vector<float>(cols, 0.0f)) {}

float& Matrix::at(int row, int col) {
    return data[row][col];
}
