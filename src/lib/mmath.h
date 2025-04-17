#pragma once

#include <math.h>
#include "../matrix.h"

Eigen::MatrixXd min_pool(Eigen::MatrixXd& input);

Eigen::MatrixXd avg_pool(Eigen::MatrixXd& input);

// Activation functions

matrix sigmoid(matrix& x);
matrix dsigmoid(matrix& x);
double binary_step(double c);
double tanh(double x);
double relu(double x);
Eigen::VectorXd softmax(Eigen::VectorXd inp);