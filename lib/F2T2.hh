/*
 * @author: hsay
 * @file:   F2T2.hh
 */
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <thread>
#include "timer.h"

#define pi 3.14159265358979323846
/*
Pseudo code for fft

    function FFT(x)
     N = length(x)
     if N<= 1:
        return x
     
     // Divide step: seperate into even and odd indexed elements
     even = FFT(x[0], x[2], x[4], ......,x[N-2])
     odd  = FFT(x[1], x[3], x[5], ......,x[N-1])

     // Initialixe output array
     X = new array of length N

     for k = 0 to N/2 - 1:
        // compute the "twidle factor"
        twiddle = exp(-2Πi * k / N) * odd[k]

        X[k] = even[k] + twiddle
        X[k+ N/2] = even[k] - twiddle

     return X

*/

// Bit reversal function
int bit_reverse(int n, int bits) {
    int reversed = 0;
    for (int i = 0; i < bits; ++i) {
        reversed = (reversed << 1) | (n & 1);
        n >>= 1;
    }
    return reversed;
}

std::vector<std::complex<double>> iterativeFFT(std::vector<std::complex<double>>& x) {
    int N = x.size();
    int bits = log2(N);

    // Bit-reversed addressing
    for (int i = 0; i < N; ++i) {
        int j = bit_reverse(i, bits);
        if (i < j) {
            std::swap(x[i], x[j]);
        }
    }

    // Iterative FFT computation
    for (int len = 2; len <= N; len *= 2) {
        double angle = -2 * pi / len;
        std::complex<double> wlen(cos(angle), sin(angle));
        for (int i = 0; i < N; i += len) {
            std::complex<double> w(1);
            for (int j = 0; j < len / 2; ++j) {
                std::complex<double> u = x[i + j];
                std::complex<double> v = x[i + j + len / 2] * w;
                x[i + j] = u + v;
                x[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    return x;
}


std::vector<std::complex<double>> FFT(std::vector<std::complex<double>> &x){
    int N = x.size();
    std::vector<std::complex<double>> twiddlefactor(N/2, 0.0);

    for(int i = 0; i < N/2; i++){
        twiddlefactor[i] = std::polar(1.0,(-2*pi*i)/N);
    }

    if(N <= 1)
        return x;

    std::vector<std::complex<double>> even;
    std::vector<std::complex<double>> odd;
    
    for(int i = 0; i < N; i++){
        if(i%2 == 0){
            even.push_back(x[i]);
        }else{
            odd.push_back(x[i]);
        }
    }
   
    even = FFT(even);
    odd = FFT(odd);

    std::vector<std::complex<double>> X(N,0.0);

    for( int k = 0; k < N/2; k++){
        //std::complex<double> twiddle = std::polar(1.0,(-2*pi* k) / N) * odd[k];

        X[k] = even[k] + twiddlefactor[k] * odd[k];
        X[k+ N/2] = even[k] - twiddlefactor[k] * odd[k];
    }

    return X;
}

#ifdef fft_test
int main(){

    std::vector<std::complex<double>> x({1,2});
    std::vector<std::complex<double>> X,Y;
    {
        Timer timer;
        X = FFT(x);
    }

    {
        Timer timer;
        Y = iterativeFFT(x);
    }

    for(int i =0; i < X.size(); i++){
        std::cout << X[i] << " ";
    }
    for(int i =0; i < Y.size(); i++){
        std::cout << Y[i] << " ";
    }

    return 0;
}
#endif
