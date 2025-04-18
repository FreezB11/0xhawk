/*
    @file: cnn.cc
    @author: yash
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <hawk/nn.hh>
#include <hawk/cnn.hh>
#include <hawk/conv.h>

#define log(x) std::cout << x << std::endl;

namespace HAWK{
    namespace CNN{
void cnn::frwd_p(trainset & curr){
}

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
                buff_data[i+1][j] = CNN::convolve(buff_data[i][j], filters[i][j], layer.stride, layer.padding);
                log("convolution size " << buff_data[i+1][j].rows() << "x" << buff_data[i+1][j].cols());
                prvlyrfc++;
            }
            i++;
        }else{
            // log("layer.filer no " << prvlyrfc);
            for(int j = 0; j< prvlyrfc; j++){
                log("size " << buff_data[i][j].rows() << "x" << buff_data[i][j].cols());

                buff_data[i+1][j] = layer.pool(buff_data[i][j],2,2,0);
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

cnn::cnn(model& cnnmodel){
    this->net = cnnmodel; 


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

    }// namespace CNN
}// namespace HAWK