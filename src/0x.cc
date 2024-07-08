#include <iostream>
#include <math.h>
#define log(x) std::cout << x << std::endl;
int count_digits(int n) { return int(log10(n) + 1); }
template<typename T> T max(T &a, T &b) { return a > b ? a : b; }
#include "0x.hh"

mvector::mvector(int dat){
    data = dat;
    log(data)
}
// Activation function and its derivative
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double sigmoid_derivative(double x) {
    return x * (1.0 - x);
}

NeuralNetwork::NeuralNetwork(int inputSize, int hiddenSize, int outputSize)
    : inputSize(inputSize), hiddenSize(hiddenSize), outputSize(outputSize) {
    initializeWeights();
    hiddenLayer.resize(hiddenSize);
    outputLayer.resize(outputSize);
}

void NeuralNetwork::initializeWeights() {
    srand(static_cast<unsigned int>(time(0)));
    weightsInputHidden.resize(inputSize, std::vector<double>(hiddenSize));
    weightsHiddenOutput.resize(hiddenSize, std::vector<double>(outputSize));

    for (int i = 0; i < inputSize; ++i) {
        for (int j = 0; j < hiddenSize; ++j) {
            weightsInputHidden[i][j] = ((double) rand() / (RAND_MAX));
        }
    }

    for (int i = 0; i < hiddenSize; ++i) {
        for (int j = 0; j < outputSize; ++j) {
            weightsHiddenOutput[i][j] = ((double) rand() / (RAND_MAX));
        }
    }
}

std::vector<double> NeuralNetwork::feedforward(std::vector<double>& input) {
    for (int i = 0; i < hiddenSize; ++i) {
        hiddenLayer[i] = 0.0;
        for (int j = 0; j < inputSize; ++j) {
            hiddenLayer[i] += input[j] * weightsInputHidden[j][i];
        }
        hiddenLayer[i] = sigmoid(hiddenLayer[i]);
    }

    for (int i = 0; i < outputSize; ++i) {
        outputLayer[i] = 0.0;
        for (int j = 0; j < hiddenSize; ++j) {
            outputLayer[i] += hiddenLayer[j] * weightsHiddenOutput[j][i];
        }
        outputLayer[i] = sigmoid(outputLayer[i]);
    }

    return outputLayer;
}

void NeuralNetwork::backpropagate(std::vector<double>& input, std::vector<double>& target, double learningRate) {
    std::vector<double> outputErrors(outputSize);
    for (int i = 0; i < outputSize; ++i) {
        outputErrors[i] = target[i] - outputLayer[i];
    }

    std::vector<double> hiddenErrors(hiddenSize);
    for (int i = 0; i < hiddenSize; ++i) {
        hiddenErrors[i] = 0.0;
        for (int j = 0; j < outputSize; ++j) {
            hiddenErrors[i] += outputErrors[j] * weightsHiddenOutput[i][j];
        }
        hiddenErrors[i] *= sigmoid_derivative(hiddenLayer[i]);
    }

    for (int i = 0; i < hiddenSize; ++i) {
        for (int j = 0; j < outputSize; ++j) {
            weightsHiddenOutput[i][j] += learningRate * outputErrors[j] * hiddenLayer[i];
        }
    }

    for (int i = 0; i < inputSize; ++i) {
        for (int j = 0; j < hiddenSize; ++j) {
            weightsInputHidden[i][j] += learningRate * hiddenErrors[j] * input[i];
        }
    }
}

void NeuralNetwork::train(std::vector<std::vector<double>>& inputs, std::vector<std::vector<double>>& outputs, int epochs, double learningRate) {
    for (int epoch = 0; epoch < epochs; ++epoch) {
        for (size_t i = 0; i < inputs.size(); ++i) {
            feedforward(inputs[i]);
            backpropagate(inputs[i], outputs[i], learningRate);
        }
    }
}

std::vector<double> NeuralNetwork::predict(std::vector<double>& input) {
    return feedforward(input);
}