#define ROSETTA
#include "../lib/F2T2.hh"


int main(){
    const Complex test[] = { 1.0,2.0,3.0,0.0};
    CArray data(test, 8);

    // forward fft
    nfft(data);

    std::cout << "fft" << std::endl;
    for (int i = 0; i < 8; ++i)
    {
        std::cout << data[i] << std::endl;
    }

    // inverse fft
    ifft(data);

    std::cout << std::endl << "ifft" << std::endl;
    for (int i = 0; i < 8; ++i)
    {
        std::cout << data[i] << std::endl;
    }
    return 0;
}