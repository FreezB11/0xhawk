#include <iostream>
#include <stdexcept>
#include "matrix.hh"

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) {
    data = new double*[rows];
    for (int i = 0; i < rows; ++i) {
        data[i] = new double[cols]();
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < rows; ++i) {
        delete[] data[i];
    }
    delete[] data;
}

int Matrix::getRows() const { return rows; }
int Matrix::getCols() const { return cols; }

double& Matrix::at(int row, int col) {
    if (row >= rows || col >= cols || row < 0 || col < 0) {
        throw std::out_of_range("Index out of range");
    }
    return data[row][col];
}

double Matrix::at(int row, int col) const {
    if (row >= rows || col >= cols || row < 0 || col < 0) {
        throw std::out_of_range("Index out of range");
    }
    return data[row][col];
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrices must have the same dimensions to add");
    }
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.at(i, j) = this->at(i, j) + other.at(i, j);
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrices must have the same dimensions to subtract");
    }
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.at(i, j) = this->at(i, j) - other.at(i, j);
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows) {
        throw std::invalid_argument("Matrix dimensions do not allow multiplication");
    }
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            for (int k = 0; k < cols; ++k) {
                result.at(i, j) += this->at(i, k) * other.at(k, j);
            }
        }
    }
    return result;
}

void Matrix::display() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
