#include <stdio.h>
#include "calculas.hh"
#include <math.h>


double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

int Binary(double x){
    if (x>0){
        return 1;
    }else{
        return 0;
    }
    
}

double mtanh(double x){
    return (exp(x) - exp(-x))/(exp(x)+exp(-x));
}

double sigmoid_derivative(double x) {
    return x * (1.0 - x);
}

double relu(double x){
    if(x<=0){
        return 0;
    }else{
        return x;
    }
}
float df(float (*func)(float),float x){
    // float eps = 1.61011979e-4;
    //float eps = 1.61012e-4;
    float df = (func(x+eps) -func(x-eps))/(2*eps);
    return df;
}
