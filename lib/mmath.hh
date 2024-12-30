#pragma once

#include <eigen3/Eigen/Dense>

Eigen::MatrixXf convolve(Eigen::MatrixXf base, Eigen::MatrixXf kernel,int padding = 0, int stride = 1){
    int base_rows = base.rows();
    int base_cols = base.cols();
    int kernel_row = kernel.rows();
    int kernel_col = kernel.cols();

    /*
        image[i][j] * kernel[i][j]= 

    */

} 