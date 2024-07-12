#ifndef A014
#define A014
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
// template<typename t>
class mvector{
private:
    int data;
public:
    mvector(int dat);
};

class NeuralNetwork {
public:
    NeuralNetwork(int inputSize, int hiddenSize, int outputSize);
    void train(std::vector<std::vector<double>>& inputs, std::vector<std::vector<double>>& outputs, int epochs, double learningRate);
    std::vector<double> predict(std::vector<double>& input);

private:
    int inputSize, hiddenSize, outputSize;
    std::vector<std::vector<double>> weightsInputHidden;
    std::vector<std::vector<double>> weightsHiddenOutput;
    std::vector<double> hiddenLayer;
    std::vector<double> outputLayer;

    void initializeWeights();
    std::vector<double> feedforward(std::vector<double>& input);
    void backpropagate(std::vector<double>& input, std::vector<double>& target, double learningRate);
};

#endif