// @file:"conv.h"
// @brief: Convolutional layer header file
#pragma once
#include "matrix.h"

namespace CNN{

matrix convolve(matrix& , matrix& , int stride = 1, int padding = 0);
matrix maxpool(matrix& , int pool_size = 2, int stride = 2, int padding = 0);
matrix avgpool(matrix& , int pool_size = 2, int stride = 2, int padding = 0);

void backprop(matrix& input , matrix& kernel, matrix& output_grad, matrix& input_grad, matrix& kernel_grad, int stride = 1, int padding = 0);
matrix backprop_maxpool(matrix& , matrix& , int pool_size = 2, int stride = 2, int padding = 0);
matrix backprop_avgpool(matrix& , matrix& , int pool_size = 2, int stride = 2, int padding = 0);

}