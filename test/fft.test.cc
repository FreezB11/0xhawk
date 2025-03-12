#define ROSETTA
#include "../src//lib/F2T2.hh"


int main(){
    const Complex test[] = { 1.0,2.0,3.0,0.0,4.0,5.0,6.0,7.0};
    CArray data(test, 8);

    // forward fft
    Timer t;
    nfft(data);
    t.stop();
    Timer t1;
    ifft(data);
    t1.stop();

    


    // std::cout << "fft" << std::endl;
    // for (int i = 0; i < 8; ++i)
    // {
    //     std::cout << data[i] << std::endl;
    // }

    // inverse fft
    // ifft(data);

    // std::cout << std::endl << "ifft" << std::endl;
    // for (int i = 0; i < 8; ++i)
    // {
    //     std::cout << data[i] << std::endl;
    // }
    return 0;
}