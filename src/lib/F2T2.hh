/*
 * @author: hsay
 * @file:   F2T2.hh
 */
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <thread>
#include "timer.hh"
#include <valarray>

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
        X = FFT(x); //<<-- works for only 2^n
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

/*
    the below code is taken from 
    https://rosettacode.org/wiki/Fast_Fourier_transform
*/

#ifdef ROSETTA

const double PI = 3.141592653589793238460;

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

// Cooley–Tukey FFT (in-place, divide-and-conquer)
// Higher memory requirements and redundancy although more intuitive
void offt(CArray& x)
{
    const size_t N = x.size();
    if (N <= 1) return;

    // divide
    CArray even = x[std::slice(0, N/2, 2)];
    CArray  odd = x[std::slice(1, N/2, 2)];

    // conquer
    offt(even);
    offt(odd);

    // combine
    for (size_t k = 0; k < N/2; ++k)
    {
        Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
        x[k    ] = even[k] + t;
        x[k+N/2] = even[k] - t;
    }
}

// Cooley-Tukey FFT (in-place, breadth-first, decimation-in-frequency)
// Better optimized but less intuitive
// !!! Warning : in some cases this code make result different from not optimased version above (need to fix bug)
// The bug is now fixed @2017/05/30 
void nfft(CArray &x)
{
	// DFT
	unsigned int N = x.size(), k = N, n;
	double thetaT = 3.14159265358979323846264338328L / N;
	Complex phiT = Complex(cos(thetaT), -sin(thetaT)), T;
	while (k > 1)
	{
		n = k;
		k >>= 1;
		phiT = phiT * phiT;
		T = 1.0L;
		for (unsigned int l = 0; l < k; l++)
		{
			for (unsigned int a = l; a < N; a += n)
			{
				unsigned int b = a + k;
				Complex t = x[a] - x[b];
				x[a] += x[b];
				x[b] = t * T;
			}
			T *= phiT;
		}
	}
	// Decimate
	unsigned int m = (unsigned int)log2(N);
	for (unsigned int a = 0; a < N; a++)
	{
		unsigned int b = a;
		// Reverse bits
		b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
		b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
		b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
		b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
		b = ((b >> 16) | (b << 16)) >> (32 - m);
		if (b > a)
		{
			Complex t = x[a];
			x[a] = x[b];
			x[b] = t;
		}
	}
	//// Normalize (This section make it not working correctly)
	//Complex f = 1.0 / sqrt(N);
	//for (unsigned int i = 0; i < N; i++)
	//	x[i] *= f;
}

// inverse fft (in-place)
void ifft(CArray& x)
{
    // conjugate the complex numbers
    x = x.apply(std::conj);

    // forward fft
    nfft( x );

    // conjugate the complex numbers again
    x = x.apply(std::conj);

    // scale the numbers
    x /= x.size();
}

#endif