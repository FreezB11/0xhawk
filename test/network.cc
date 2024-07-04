#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

// Activation function and its derivative
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double sigmoid_derivative(double x) {
    return x * (1.0 - x);
}

// Neural Network Class
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

int main() {
    NeuralNetwork nn(2, 2, 1);

    std::vector<std::vector<double>> inputs = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
    std::vector<std::vector<double>> outputs = { {0}, {0}, {0}, {1} };

    nn.train(inputs, outputs, 10000, 0.1);

    for (auto& input : inputs) {
        std::vector<double> output = nn.predict(input);
        std::cout << "Input: " << input[0] << ", " << input[1] << " - Predicted Output: " << output[0] << std::endl;
    }

    return 0;
}
