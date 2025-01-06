#include "mmath.h"
#include <eigen3/Eigen/Dense>

Eigen::MatrixXd convolve(Eigen::MatrixXd& base, Eigen::MatrixXd& kernel, int stride = 1,int padding = 0){
    int base_rows = base.rows();
    int base_cols = base.cols();
    int kernel_row = kernel.rows();
    int kernel_col = kernel.cols();

    Eigen::MatrixXd curr_base;

    if(padding != 0){
        base_rows += 2*padding;
        base_cols += 2*padding;
        
        Eigen::MatrixXd padded(base_rows,base_cols);
        padded.setZero();
        padded.block(padding, padding, base_rows-2*padding, base_cols-2*padding) = base;
        curr_base = padded;
        
    }else{
        curr_base = base;
    }

    int opr = (curr_base.rows() - kernel_row)/ stride + 1;
    int opc = (curr_base.cols() - kernel_col)/ stride + 1;

    Eigen::MatrixXd out(opr,opc);

   for(int i = 0; i < opr; i++){
        for (int j = 0; j < opc; j++){
            int rowS = i* stride;
            int colS = j* stride;

            Eigen::MatrixXd sub_matix = curr_base.block(rowS,colS, kernel_row, kernel_col);
            
            out(i,j) = (sub_matix.array() * kernel.array()).sum();
        }
        
   }

    return out;
}

Eigen::MatrixXd max_pool(Eigen::MatrixXd& input){
    int base_rows = input.rows();
    int base_cols = input.cols();
    int stride =2;
    Eigen::MatrixXd curr_base = input; // << there was stupid bug here

    int opr = base_rows / 2;
    int opc = base_cols / 2;

    Eigen::MatrixXd out(opr,opc);

   for(int i = 0; i < opr; i++){
        for (int j = 0; j < opc; j++){
            int rowS = i* stride;
            int colS = j* stride;
            // std::cout << "the error is here" << std::endl;
            Eigen::MatrixXd sub_matix = curr_base.block(rowS,colS, 2, 2);
            // std::cout << "maybe here" << std::endl;
            out(i,j) = sub_matix.maxCoeff();
        }
   }
    return out;
}

Eigen::MatrixXd min_pool(Eigen::MatrixXd& input){
    int base_rows = input.rows();
    int base_cols = input.cols();
    int stride =2;
    Eigen::MatrixXd curr_base;

    int opr = base_rows / 2;
    int opc = base_cols / 2;

    Eigen::MatrixXd out(opr,opc);

   for(int i = 0; i < opr; i++){
        for (int j = 0; j < opc; j++){
            int rowS = i* stride;
            int colS = j* stride;

            Eigen::MatrixXd sub_matix = curr_base.block(rowS,colS, 2, 2);
            
            out(i,j) = sub_matix.minCoeff();
        }
   }
    return out;
}

Eigen::MatrixXd avg_pool(Eigen::MatrixXd& input){
    int base_rows = input.rows();
    int base_cols = input.cols();
    int stride =2;
    Eigen::MatrixXd curr_base;

    int opr = base_rows / 2;
    int opc = base_cols / 2;

    Eigen::MatrixXd out(opr,opc);

   for(int i = 0; i < opr; i++){
        for (int j = 0; j < opc; j++){
            int rowS = i* stride;
            int colS = j* stride;

            Eigen::MatrixXd sub_matix = curr_base.block(rowS,colS, 2, 2);
            
            out(i,j) = sub_matix.sum()/4;
        }
   }
    return out;
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