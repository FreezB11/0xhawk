#include "../src/nn.hh"
#include <iostream>

int main() {
    std::vector<int> layers = {784, 30, 10};
    NeuralNetwork nn(layers);

    Eigen::MatrixXd input(784, 1);
    input.setRandom();

    Eigen::MatrixXd target(10, 1);
    target.setRandom();

    nn.train(input, target, 0.1, 1000);

    Eigen::MatrixXd output = nn.feedforward(input);
    std::cout << output << std::endl;

    return 0;
}