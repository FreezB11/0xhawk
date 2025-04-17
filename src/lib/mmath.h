#pragma once

#include <eigen3/Eigen/Dense>
#include <math.h>

Eigen::MatrixXd min_pool(Eigen::MatrixXd& input);

Eigen::MatrixXd avg_pool(Eigen::MatrixXd& input);

// Activation functions

double sigmoid(double x);
double dsigmoid(double x);
double binary_step(double c);
double tanh(double x);
double relu(double x);
Eigen::VectorXd softmax(Eigen::VectorXd inp);