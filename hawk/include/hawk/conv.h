// @file:"conv.h"
// @brief: Convolutional layer header file
#pragma once
#include "matrix.h"

namespace HAWK{
namespace CNN{

matrix convolve(matrix& base, matrix& , int stride, int padding);
matrix maxpool(matrix& , int pool_size, int stride, int padding);
matrix avgpool(matrix& , int pool_size = 2, int stride = 2, int padding = 0);

void backprop(matrix& input , matrix& kernel, matrix& output_grad, matrix& input_grad, matrix& kernel_grad, int stride, int padding);
matrix backprop_maxpool(matrix& , matrix& , int pool_size, int stride, int padding);
matrix backprop_avgpool(matrix& , matrix& , int pool_size = 2, int stride = 2, int padding = 0);

}
}