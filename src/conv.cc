// @file: conv.cc
#include "conv.h"
#include "matrix.h"

namespace CNN{

matrix convolve(matrix& base, matrix& kernel, int stride =1, int padding =0){
    // apply padding
    int pr = base.rows() + 2*padding;
    int pc = base.cols() + 2*padding;

    matrix padded = matrix::Zero(pr, pc);
    if(padding > 0){
        padded.block(padding, padding, base.rows(), base.cols()) = base;
    }else{
        padded = base;
    }

    int kr = kernel.rows();
    int kc = kernel.cols();

    int opr = (padded.rows() - kr)/ stride + 1;
    int opc = (padded.cols() - kc)/ stride + 1;

    matrix out(opr, opc);

    for(int i = 0; i < opr; i++){
        for (int j = 0; j < opc; j++){
            int rowS = i* stride;
            int colS = j* stride;

            matrix sub_matix = padded.block(rowS, colS, kr, kc);
            
            out(i,j) = (sub_matix.array() * kernel.array()).sum();
        }
    }
    return out;
}

void backprop(matrix& input , matrix& kernel, matrix& output_grad, matrix& input_grad, matrix& kernel_grad, int stride = 1, int padding = 0){
    int ir = input.rows();
    int ic = input.cols();
    int kr = kernel.rows();
    int kc = kernel.cols();

    input_grad = matrix::Zero(ir, ic);
    kernel_grad = matrix::Zero(kr, kc);

    matrix padded = matrix::Zero(ir + 2*padding, ic + 2*padding);

    matrix kernel_rotated = kernel.reverse();

    int dr = (output_grad.rows() - 1) * stride + 1;
    int dc = (output_grad.cols() - 1) * stride + 1;

    matrix d_out_grad = matrix::Zero(dr, dc);

    for(int i = 0; i < output_grad.rows(); i++){
        for (int j = 0; j < output_grad.cols(); j++){
            d_out_grad(i*stride, j*stride) = output_grad(i,j);
        }
    }
    int pr = kr -1;
    int pc = kc -1;

    matrix padded_out_grad = matrix::Zero(dr + 2*pr, dc + 2*pc);
    padded_out_grad.block(pr, pc, dr, dc) = d_out_grad;

    for(int i = 0; i < padded.rows(); i++){
        for (int j = 0; j < padded.cols(); j++){
            double sum = 0.0;
            for(int ki = 0; ki < kr; ki++){
                for (int kj = 0; kj < kc; kj++){
                    if(i - ki >= 0 &&  i - ki < padded_out_grad.rows() && 
                       j - kj >= 0 &&  j - kj < padded_out_grad.cols()){
                        sum += kernel_rotated(ki, kj) * padded_out_grad(i - ki, j - kj);
                    }
                }
                padded(i, j) = sum;
            }
        }
    }
    if(padding > 0){
        input_grad = padded.block(padding, padding, ir, ic);
    }else{
        input_grad = padded;
    }

    /// compute kernel gradient
    matrix pi = matrix::Zero(ir + 2*padding, ic + 2*padding);
    if(padding > 0){
        pi.block(padding, padding, ir, ic) = input;
    }else{
        pi = input;
    }

    for(int ki = 0; ki < kr; ki++){
        for(int kj = 0; kj < kc; kj++){
            double sum = 0.0;
            for(int i = 0; i < output_grad.rows(); i++){
                for (int j = 0; j < output_grad.cols(); j++){
                   int ii = i * stride + ki;
                   int ij = j * stride + kj;
                   sum += pi(ii, ij) * output_grad(i, j);
                }
            }
            kernel_grad(ki, kj) = sum;
        }
    }

}

matrix maxpool(matrix& input, int pool_size = 2, int stride = 2, int padding = 0){
    int padded_rows = input.rows() + 2*padding;
    int padded_cols = input.cols() + 2*padding;

    matrix padded_input = matrix::Zero(padded_rows, padded_cols);

    if(padding > 0){
        padded_input.block(padding, padding, input.rows(), input.cols()) = input;
    }else{
        padded_input = input;
    }

    int opr = (padded_input.rows() - pool_size)/ stride + 1;
    int opc = (padded_input.cols() - pool_size)/ stride + 1;

    matrix output(opr, opc);

    for(int i = 0; i < opr; i++){
        for (int j = 0; j < opc; j++){
            int rowS = i* stride;
            int colS = j* stride;

            double max_val = padded_input(rowS, colS);
            for(int ki = 0; ki < pool_size; ki++){
                for (int kj = 0; kj < pool_size; kj++){
                     if(rowS + ki < opr && colS + kj < opc){
                        max_val = std::max(max_val, padded_input(rowS + ki, colS + kj));
                    }
                }
            }
            output(i,j) = max_val;
        }
    }
    return output;
}

matrix backprop_maxpool(matrix& input, matrix& output_grad, int pool_size = 2, int stride = 2, int padding = 0){
    // Apply padding to input
    int padded_rows = input.rows() + 2 * padding;
    int padded_cols = input.cols() + 2 * padding;
    MatrixXd padded_input = MatrixXd::Zero(padded_rows, padded_cols);
    
    if (padding > 0) {
        padded_input.block(padding, padding, input.rows(), input.cols()) = input;
    } else {
        padded_input = input;
    }
    
    // Initialize gradient with zeros
    MatrixXd input_grad = MatrixXd::Zero(padded_rows, padded_cols);
    
    int output_rows = output_grad.rows();
    int output_cols = output_grad.cols();
    
    // Backpropagate the gradients
    for (int i = 0; i < output_rows; ++i) {
        for (int j = 0; j < output_cols; ++j) {
            int start_i = i * stride;
            int start_j = j * stride;
            
            // Find the position of the max value in this pooling region
            double max_val = padded_input(start_i, start_j);
            int max_i = start_i;
            int max_j = start_j;
            
            for (int pi = 0; pi < pool_size; ++pi) {
                for (int pj = 0; pj < pool_size; ++pj) {
                    if (start_i + pi < padded_rows && start_j + pj < padded_cols) {
                        if (padded_input(start_i + pi, start_j + pj) > max_val) {
                            max_val = padded_input(start_i + pi, start_j + pj);
                            max_i = start_i + pi;
                            max_j = start_j + pj;
                        }
                    }
                }
            }
            
            // Only the max position gets the gradient
            input_grad(max_i, max_j) += output_grad(i, j);
        }
    }
    
    // Remove padding if needed
    if (padding > 0) {
        return input_grad.block(padding, padding, input.rows(), input.cols());
    }
    return input_grad;
}


} // namespace CNN