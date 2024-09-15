#include <iostream>

template <typename T>
class matrix{
private:
    T** data;
    int row, col;
public:
    matrix(int r, int c);
};