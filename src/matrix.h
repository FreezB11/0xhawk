#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <complex>

class Matrix {
public:
    int rows, cols;
    std::vector<std::vector<float>> data;

    // Constructor
    Matrix(int rows, int cols);

    // Access element at (i, j)
    float& at(int row, int col);
    std::vector<std::vector<std::complex<float>>> computeDFT() const;

    // Matrix operations (e.g., addition, multiplication, etc.) can be added later
};

#endif // MATRIX_H
