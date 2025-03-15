/*
    * NeuralNetwork class
    * 
    * This class is a simple feedforward neural network with one hidden layer.
    * It is designed to be used with the MNIST dataset.
    *
    * The constructor takes a vector of integers as an argument. The first element
    * of the vector is the number of input neurons, the last element is the number
    * of output neurons, and the elements in between are the number of neurons in
    * each hidden layer.
    * 
    * @file nn.hh
    * @author yash
    * @version 1.0
    * @date 2021-09-30
*/

#pragma once
#include <vector>
#include <eigen3/Eigen/Dense>

typedef struct n_trainset{
    Eigen::VectorXd id;
    Eigen::VectorXd data;
}n_trainset;

class ncsv{
private:
    int idim;
    int rows = 0;
public:
    ncsv(const char* filename, int idim);
    ~ncsv();
    n_trainset                        read_data(const char* filename, int n);
    int                             getrow();
};

class NeuralNetwork {
public:
                                    NeuralNetwork(const std::vector<int>& layers);
    Eigen::MatrixXd                 feedforward(const Eigen::MatrixXd& input);
    void                            train(const Eigen::MatrixXd& input, const Eigen::MatrixXd& target, double learning_rate, int epochs);

private:
    std::vector<int>                layers;
    std::vector<Eigen::MatrixXd>    weights;
    std::vector<Eigen::MatrixXd>    biases;

    Eigen::MatrixXd                 sigmoid(const Eigen::MatrixXd& z);
    Eigen::MatrixXd                 sigmoid_derivative(const Eigen::MatrixXd& z);
    void                            backpropagate(const Eigen::MatrixXd& input, const Eigen::MatrixXd& target, double learning_rate);
};