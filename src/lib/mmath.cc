#include "mmath.h"
#include <eigen3/Eigen/Dense>
#include <iostream>

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
    Eigen::MatrixXd curr_base = input;

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
    return (1/( 1 + exp(-x)));
}

double dsigmoid(double x){
    double t = sigmoid(x);
    return t*(1-t);
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

Eigen::VectorXd softmax(Eigen::VectorXd inp){
    int s = inp.size();
    double t = 0.0f;
    for(int i = 0; i< s; i++){
        t += inp[i];
    }
    // std::cout << "the sum = " << t << std::endl;
    Eigen::VectorXd res = Eigen::VectorXd::Zero(10);
    for (int i = 0; i < s; i++){
        res[i] = inp[i]/t;
    }
    return res;
}   