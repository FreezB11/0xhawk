#include <iostream>
#include <chrono>
#include <math.h>
#define log(x) std::cout << x << std::endl;
int count_digits(int n) { return int(log10(n) + 1); }
template<typename T> T max(T &a, T &b) { return a > b ? a : b; }


int main() {

    auto start = std::chrono::high_resolution_clock::now();

    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

    return 0;
}
