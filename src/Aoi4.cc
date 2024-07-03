#include <iostream>
#include <math.h>
#define log(x) std::cout << x << std::endl;
int count_digits(int n) { return int(log10(n) + 1); }
template<typename T> T max(T &a, T &b) { return a > b ? a : b; }
#include "A014.hh"

vector::vector(int dat){
    data = dat;
    log(data)
}