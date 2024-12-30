#pragma once

#include <eigen3/Eigen/Dense>
#include <math.h>

Eigen::MatrixXf convolve(Eigen::MatrixXf base, Eigen::MatrixXf kernel,int padding = 0, int stride = 1){
    int base_rows = base.rows();
    int base_cols = base.cols();
    int kernel_row = kernel.rows();
    int kernel_col = kernel.cols();

    /*
        image[i][j] * kernel[i][j]= 

    */

}

// Activation functions

double sigmoid(double x){
    return (exp(x)/( 1 + exp(x)));
}

double binary_step(double c){
    if( c >= 0){
        return 1.0f;
    }else{
        return 0.0f;
    }
}

double tanh(double x){
    double t = exp(2*x);
    return ((t-1)/(t+1));
}

double relu(double x){
    if( x<= 0.0f){
        return 0.0f;
    }else{
        return x;
    }
}