#include <iostream>
#include "src/A014.hh"
int main(){

    //mvector c(8);
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