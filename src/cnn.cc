/*
    @file: cnn.cc
    @author: yash
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "cnn.hh"
#include "lib/utils.hh"

void cnn::frwd_p(trainset & curr){
}

void cnn::_train(trainset &curr){
    int layer_id =0;
    int fid = 1;
    log("current image " << curr.id)

    buff_data.resize(net.layers.size());
    filters.resize(net.layers.size());

    for(auto f: net.layers){
        int i =0;
        //f.filters
        buff_data[i].resize(f.filters);
        filters[i].resize(f.filters);
        i++;
    }
    // buff_data[layer_id].resize(fid++);
    log(fid)
    dlog()
    // the error is below
    buff_data[layer_id][fid] = curr.image;

    for(auto layer: net.layers){
        if(layer._type == "conv"){
            int m = layer.kernel_s;
            dlog()
            for(int i = 0; i<layer.filters; i++){
                filters[layer_id][i] = Eigen::MatrixXd::Random(m,m);
            }
            dlog()
            for(int i = 0; i < layer.filters; i++){
                dlog()
                buff_data[layer_id+1][i] = convolve(buff_data[layer_id][i],filters[layer_id][i],layer.stride, layer.padding);
            }
            fid++;
        }else{

        }
        layer_id++;
        // buff_data[layer_id].resize(fid++);
    }

    // and here the flatten func
    log(fid)

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