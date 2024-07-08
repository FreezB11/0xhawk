#ifndef MATRIX_HH
#define MATRIX_HH

class Matrix {
private:
    int rows;
    int cols;
    double** data;

public:
    Matrix(int rows, int cols);
    ~Matrix();

    int getRows() const;
    int getCols() const;

    double& at(int row, int col);
    double at(int row, int col) const;

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;

    void display() const;
};

#endif // MATRIX_HH
