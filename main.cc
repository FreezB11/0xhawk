#include <iostream>
#include "src/0x.hh"
int main(){

    //mvector c(8);
    NeuralNetwork nn(2, 4, 1);

    std::vector<std::vector<double>> inputs = { {0,0}, {1,0}, {2,0}, {3,0} };
    std::vector<std::vector<double>> outputs = { {0}, {2}, {4}, {6} };

    nn.train(inputs, outputs, 10000, 0.1);

    for (auto& input : inputs) {
        std::vector<double> output = nn.predict(input);
        std::cout << "Input: " << input[0] << ", " << input[1] << " - Predicted Output: " << output[0] << std::endl;
    }
    return 0;
}