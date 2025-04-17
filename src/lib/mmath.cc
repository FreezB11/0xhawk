#include "mmath.h"
#include "../matrix.h"
#include "../simd.h"
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

// double sigmoid(double x){
//     return (1/( 1 + exp(-x)));
// }

// AVX2 approximation of exp function
simde__m256d exp_approx_avx2(simde__m256d x) {
    // Implementation of exp approximation using AVX2
    // This is a simplified Taylor series approximation
    
    const simde__m256d one = simde_mm256_set1_pd(1.0);
    const simde__m256d half = simde_mm256_set1_pd(0.5);
    const simde__m256d sixth = simde_mm256_set1_pd(1.0/6.0);
    
    // exp(x) ≈ 1 + x + x²/2 + x³/6
    simde__m256d x2 = simde_mm256_mul_pd(x, x);
    simde__m256d x3 = simde_mm256_mul_pd(x2, x);
    
    simde__m256d result = simde_mm256_add_pd(
        one,
        simde_mm256_add_pd(
            x,
            simde_mm256_add_pd(
                simde_mm256_mul_pd(x2, half),
                simde_mm256_mul_pd(x3, sixth)
        )
    ));
    
    return result;
}

matrix sigmoid(matrix& x){
    matrix res(x.rows(), x.cols());
    const double* x_data = x.data();
    double* res_data = res.data();
    size_t size = x.size();
    // process 4 doubles at a time(avx2 can do 8 floats but matrix is double)
    for (size_t i = 0; i < size; i += 4){
        simde__m256d x_vec   = simde_mm256_loadu_pd(x_data + i);
        simde__m256d negx    = simde_mm256_mul_pd(x_vec, simde_mm256_set1_pd(-1.0));
        simde__m256d exp_vec = exp_approx_avx2(negx);
        simde__m256d denom   = simde_mm256_add_pd(exp_vec, _mm256_set1_pd(1.0));
        simde__m256d sigmoid_vec = simde_mm256_div_pd(_mm256_set1_pd(1.0), denom);
        _mm256_storeu_pd(res_data + i, sigmoid_vec);
    }
    // Handle remaining elements (if size is not a multiple of 4)
    for (size_t i = size - (size % 4); i < size; ++i){
        res_data[i] = 1.0 / (1.0 + exp(-x_data[i]));
    }
    return res;
}

// double dsigmoid(double x){
//     double t = sigmoid(x);
//     return t*(1-t);
// }

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