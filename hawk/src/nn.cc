/*
    @file nn.cc
    @author yash
    @date 2021-09-30
*/
#include <hawk/nn.hh>
#include <fstream>
#include <iostream>
#include <hawk/matrix.h>
#include <hawk/simd.h>

namespace HAWK {
namespace NN {

NeuralNetwork::NeuralNetwork(const std::vector<int>& layers) {
    this->layers = layers;
    for (int i = 0; i < layers.size() - 1; i++) {
        weights.push_back(Eigen::MatrixXd::Random(layers[i + 1], layers[i]));
        biases.push_back(Eigen::MatrixXd::Random(layers[i + 1], 1));
    }
}

Eigen::MatrixXd NeuralNetwork::feedforward(const Eigen::MatrixXd& input) {
    Eigen::MatrixXd a = input;
    for (int i = 0; i < layers.size() - 1; i++) {
        a = sigmoid(weights[i] * a + biases[i]);
    }
    return a;
}

void NeuralNetwork::train(const Eigen::MatrixXd& input, const Eigen::MatrixXd& target, double learning_rate, int epochs) {
    for (int i = 0; i < epochs; i++) {
        backpropagate(input, target, learning_rate);
    }
}

Eigen::MatrixXd NeuralNetwork::sigmoid(const Eigen::MatrixXd& z) {
    return 1 / (1 + (-z.array()).exp());
}

Eigen::MatrixXd NeuralNetwork::sigmoid_derivative(const Eigen::MatrixXd& z) {
    return sigmoid(z).array() * (1 - sigmoid(z).array());
}

void NeuralNetwork::backpropagate(const Eigen::MatrixXd& input, const Eigen::MatrixXd& target, double learning_rate) {
    std::vector<Eigen::MatrixXd> activations;
    std::vector<Eigen::MatrixXd> zs;
    Eigen::MatrixXd a = input;
    activations.push_back(a);
    for (int i = 0; i < layers.size() - 1; i++) {
        Eigen::MatrixXd z = weights[i] * a + biases[i];
        zs.push_back(z);
        a = sigmoid(z);
        activations.push_back(a);
    }

    Eigen::MatrixXd delta = (activations.back() - target).array() * sigmoid_derivative(zs.back()).array();
    Eigen::MatrixXd nabla_b = delta;
    Eigen::MatrixXd nabla_w = delta * activations[activations.size() - 2].transpose();

    for (int i = layers.size() - 2; i > 0; i--) {
        delta = (weights[i].transpose() * delta).array() * sigmoid_derivative(zs[i - 1]).array();
        nabla_b = delta;
        nabla_w = delta * activations[i - 1].transpose();
    }

    weights[0] -= learning_rate * nabla_w;
    biases[0] -= learning_rate * nabla_b;
}

ncsv::ncsv(const char* filename, int idim){
    this->idim = idim;
    std::ifstream file(filename);
    char c;
    while (file.get(c)){
        if(c == '\n'){
            rows++;
        }
    }
    file.close();
}
ncsv::~ncsv(){
}

n_trainset ncsv::read_data(const char* filename, int n){
    n_trainset res;
    std::ifstream file(filename);
    if(!file.is_open()){
        throw std::runtime_error("Failed to open file");
    }
    std::string line;
    int currentline = 0;
    // skipping the first line as it is just the columen name
    std::getline(file,line);
    // we shall read now
    while (std::getline(file,line)){
        currentline++;
        if(currentline == n){
            std::istringstream linestream(line);
            std::string token;
            std::getline(linestream, token, ',');


            Eigen::VectorXd enc = Eigen::VectorXd::Zero(10);
            int p = std::stoi(token);
            // log(
            //     "the id"
            // )
            // std::cout << p << std::endl;
            enc[p] =1;

            res.id = enc;
            // log("one hot encoding")
            // std:: cout << enc << std::endl;

            std::vector<double> px;
            while(std::getline(linestream, token, ',')){
                px.push_back((std::stoi(token) / 255.0f));///255.0f));
            }
            if(px.size() != idim*idim){
                std::cerr << "expected " << idim*idim << " pixels, but got " << px.size() << std::endl;
                throw std::runtime_error("Invalid number of pixels");
            }
            Eigen::VectorXd img = Eigen::Map<Eigen::VectorXd>(px.data(), px.size());
            res.data = img;
            return res;
        }
    }
    throw std::out_of_range("requestd line number is out of bound");
}

int ncsv::getrow(){
    return rows;
}

} // namespace NN
} // namespace HAWK