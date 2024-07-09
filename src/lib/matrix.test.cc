#include <iostream>
#include "math/matrix.hh"

int main() {
    Matrix m1(2, 3);
    Matrix m2(2, 3);

    // Initialize m1
    m1.at(0, 0) = 1; m1.at(0, 1) = 2; m1.at(0, 2) = 3;
    m1.at(1, 0) = 4; m1.at(1, 1) = 5; m1.at(1, 2) = 6;

    // Initialize m2 
    m2.at(0, 0) = 7; m2.at(0, 1) = 8; m2.at(0, 2) = 9;
    m2.at(1, 0) = 10; m2.at(1, 1) = 11; m2.at(1, 2) = 12;

    Matrix m3 = m1 + m2;
    Matrix m4 = m1 - m2;

    std::cout << "Matrix m1:" << std::endl;
    m1.display();

    std::cout << "Matrix m2:" << std::endl;
    m2.display();

    std::cout << "Matrix m3 (m1 + m2):" << std::endl;
    m3.display();

    std::cout << "Matrix m4 (m1 - m2):" << std::endl;
    m4.display();

    // For multiplication example
    Matrix m5(3, 2);
    m5.at(0, 0) = 1; m5.at(0, 1) = 2;
    m5.at(1, 0) = 3; m5.at(1, 1) = 4;
    m5.at(2, 0) = 5; m5.at(2, 1) = 6;

    Matrix m6 = m1 * m5;

    std::cout << "Matrix m5:" << std::endl;
    m5.display();

    std::cout << "Matrix m6 (m1 * m5):" << std::endl;
    m6.display();

    return 0;
}
