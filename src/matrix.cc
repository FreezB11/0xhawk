#include "matrix.h"

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols), data(rows, std::vector<float>(cols, 0.0f)) {}

float& Matrix::at(int row, int col) {
    return data[row][col];
}

std::vector<std::vector<std::complex<float>>> Matrix::computeDFT() const {
    std::vector<std::vector<std::complex<float>>> dftResult(rows, std::vector<std::complex<float>>(cols));
    const std::complex<float> I(0, 1); // Imaginary unit
    float pi = 3.14159265358979323846;

    // Perform 2D DFT
    for (int u = 0; u < rows; ++u) {
        for (int v = 0; v < cols; ++v) {
            std::complex<float> sum(0.0f, 0.0f);
            for (int x = 0; x < rows; ++x) {
                for (int y = 0; y < cols; ++y) {
                    float angle = 2 * pi * ((u * x / float(rows)) + (v * y / float(cols)));
                    std::complex<float> expTerm = std::exp(-I * angle);
                    sum += data[x][y] * expTerm;
                }
            }
            dftResult[u][v] = sum;
        }
    }

    return dftResult;
}

Matrix Matrix::convolve(const Matrix& main, const Matrix& kernel){
    Matrix output(main.rows,main.cols);


    

    return output;
};