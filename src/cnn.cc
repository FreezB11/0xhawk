/*
    @file: cnn.cc
    @author: yash
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "nn.hh"
#include "cnn.hh"
#include "lib/utils.hh"

void cnn::frwd_p(trainset & curr){
}

// void CNN::train(const std::vector<trainset>& dataset, int epochs, double learning_rate) {
//     for (int epoch = 0; epoch < epochs; ++epoch) {
//         double total_loss = 0.0;
//         for (const auto& data : dataset) {
//             Eigen::MatrixXd input = data.image;
//             Eigen::MatrixXd target = data.label;
            
//             // Forward pass
//             Eigen::MatrixXd output = forward(input);
            
//             // Compute loss
//             total_loss += (output - target).array().square().sum();
            
//             // Backpropagation
//             backpropagate(input, target, learning_rate);
//         }
//         std::cout << "Epoch " << epoch + 1 << "/" << epochs << " - Loss: " << total_loss / dataset.size() << std::endl;
//     }
// }


void cnn::_train(trainset &curr){
    Eigen::MatrixXd img = curr.image;
    log("image size " << img.rows() << "x" << img.cols());
    int i = 0; 
    buff_data[0][0] = img;
    buff_data[0][1] = img;
    int prvlyrfc = 0;
    for(auto layer: net.layers){
        if(layer._type == "conv"){
            // log("convolution layer");
            for(int j = 0; j< layer.filters; j++){
                buff_data[i+1][j] = convolve(buff_data[i][j], filters[i][j], layer.stride, layer.padding);
                log("convolution size " << buff_data[i+1][j].rows() << "x" << buff_data[i+1][j].cols());
                prvlyrfc++;
            }
            i++;
        }else{
            // log("layer.filer no " << prvlyrfc);
            for(int j = 0; j< prvlyrfc; j++){
                // log("size " << buff_data[i][j].rows() << "x" << buff_data[i][j].cols());

                buff_data[i+1][j] = layer.pool(buff_data[i][j]);
                log("pooling size " << buff_data[i+1][j].rows() << "x" << buff_data[i+1][j].cols());
            }
            prvlyrfc = 0;
            i++;
        }
    }
    std::vector<double> out;// = flatten(buff_data[i][0]);
    for(int j = 0; j< buff_data[i].size(); j++){
        std::vector<double> temp = flatten(buff_data[i][j]);
        out.insert(out.end(), temp.begin(), temp.end());
    }

    std::vector<int> lyrs;
    lyrs.push_back(out.size());
    lyrs.insert(lyrs.end(), net.hidden_lyrs.begin(), net.hidden_lyrs.end());
    lyrs.push_back(net.out_param_size);
    NeuralNetwork nn(lyrs);
    Eigen::VectorXd input = Eigen::Map<Eigen::VectorXd>(out.data(), out.size());
    Eigen::VectorXd enc = Eigen::VectorXd::Zero(10);
    enc[curr.id] =1;
    Eigen::VectorXd target = enc;
    nn.train(input, target, 0.1, 10);
    Eigen::MatrixXd outpp = nn.feedforward(input);
    log(outpp)

    // log("the out size is " << out.size());
    // for(auto i: out){
    //     std::cout << i << " ";
    // }
    // std::cout << std::endl;


}

std::vector<double> cnn::flatten(Eigen::MatrixXd& inp){
    std::vector<double> out;
    out.resize(inp.rows() * inp.cols());
    int idx =0;
    for(int i = 0; i< inp.rows(); i++){
        for(int j =0; j< inp.cols(); j++){
            out[idx++] = inp(i,j);
        }
    }
    return out;
}

cnn::cnn(_arch& cnn_arch){
    this->net = cnn_arch; 


    filters.resize(net.layers.size());
    buff_data.resize(net.layers.size()+2);
    buff_data[0].resize(2);
    int i = 0;
    for(auto layer: net.layers){
        if(layer._type == "conv"){
            filters[i].resize(layer.filters);
            buff_data[i+1].resize(layer.filters);
            for(int j = 0 ; j< layer.filters; j++){
                filters[i][j] = Eigen::MatrixXd::Random(layer.kernel_s, layer.kernel_s);
            }
            i++;
        }else{
            // filters[i].resize(2);
            buff_data[i+1].resize(2);
            i++;
        }
    }
}   
cnn::~cnn(){
}

void cnn::train(){
    csv train(this->net._trainset);
    // rows = train.getrow();
    rows = 1;
    for(int i = 1; i<= rows;++i){
        trainset curr = train.read_data(this->net._trainset, i);
        _train(curr);
        for(int i =0 ; i<max_fc;i++){
        std::cout << "Rows: " << this->buff_data[max_fc][i].rows() << std::endl;
        std::cout << "Cols: " << this->buff_data[max_fc][i].cols() << std::endl;
        }
    }
}   

//train

int main(){
    // std::cout << IMAGED << std::endl;
    // csv train("./dataset/train.csv");
    // std::cout << train.getrow() << std::endl;

    // //test for line data
    // csv test("./dataset/train.csv");
    // try{
    //     trainset t = test.read_data("./dataset/train.csv",1);

    //     std::cout << "img \n" << t.image << std::endl;

    // }catch (const std::exception& ex){
    //     std::cerr << "Error: " << ex.what() << std::endl;
    // }

    // cnn nn;
    // nn.train("./dataset/train.csv");

    // Eigen::MatrixXf input(5, 5);
    // input << 1, 2, 3, 4, 5,
    //          6, 7, 8, 9, 10,
    //          11, 12, 13, 14, 15,
    //          16, 17, 18, 19, 20,
    //          21, 22, 23, 24, 25;

    // Eigen::MatrixXf kernel(3, 3);
    // kernel << 1, 0, -1,
    //           1, 0, -1,
    //           1, 0, -1;

    // int padding = 0; // Example padding
    // int stride = 2;  // Example stride

    // Eigen::MatrixXf result = convolve(input, kernel, padding, stride);
    // std::cout << "Result of convolution:\n" << result << std::endl;

    _arch my = {
        .out_param_size = 10,
        .hidden_lyrs = {50,90},
        .activation = relu,
        ._testset = "./dataset/test.csv",
        ._trainset = "./dataset/train.csv",
        .layers = {
                    _layer{._type = "conv",.filters = 2,.kernel_s = 5},
                    _layer{._type = "pool",.pool = max_pool},
                    _layer{._type = "conv",.filters = 2,.kernel_s = 3},
                    _layer{._type = "pool",.pool = avg_pool},
                    _layer{._type = "conv",.filters = 2,.kernel_s = 2}
        },
    };

    cnn mynet(my);
    mynet.train();

    return 0;
}