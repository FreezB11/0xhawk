#include <iostream>
#include <chrono>
#include <math.h>
#define log(x) std::cout << x << std::endl;
int count_digits(int n) { return int(log10(n) + 1); }
template<typename T> T max(T &a, T &b) { return a > b ? a : b; }

template<typename t>
t kmf(t a,t b){
    if(a < 1000000 || b < 1000000){
        return a*b;
    }
    t m = T max(count_digits(a),count_digits(b));
    t m2 = floor(m/2);
}

int main() {

    auto start = std::chrono::high_resolution_clock::now();

    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

    return 0;
}
