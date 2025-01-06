#pragma once

#include <eigen3/Eigen/Dense>
#include <math.h>

Eigen::MatrixXd convolve(Eigen::MatrixXd& base, Eigen::MatrixXd& kernel, int stride,int padding);

Eigen::MatrixXd max_pool(Eigen::MatrixXd& input);

Eigen::MatrixXd min_pool(Eigen::MatrixXd& input);

Eigen::MatrixXd avg_pool(Eigen::MatrixXd& input);

// Activation functions

double sigmoid(double x);

double binary_step(double c);

double tanh(double x);

double relu(double x);