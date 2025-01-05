/*
    @file: cnn.cc
    @author: yash
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "cnn.hh"

#define KERNEL_SIZE 3
#define STRIDE 1
#define IMAGED 28 // taking the image to be square



csv::csv(const char* filename){
    std::ifstream file(filename);
    char c;
    while (file.get(c)){
        if(c == '\n'){
            rows++;
        }
    }
    file.close();
}
csv::~csv(){
}

trainset csv::read_data(const char* filename, int n){
    trainset res;
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
            res.id = std::stoi(token);
            std::vector<float> px;
            while(std::getline(linestream, token, ',')){
                px.push_back((std::stoi(token)/255.0f));
            }
            if(px.size() != IMAGED*IMAGED){
                throw std::runtime_error("Invalid number of pixels");
            }
            Eigen::Matrix<double, IMAGED, IMAGED> img;
            for(int i = 0;  i< IMAGED;++i){
                for(int j = 0; j < IMAGED; ++j){
                    img(i,j) = px[i*28 + j];
                }
            }
            res.image = img;
            return res;
        }
    }
    throw std::out_of_range("requestd line number is out of bound");
}

int csv::getrow(){
    return rows;
}



void cnn::frwd_p(trainset & curr){
}

void cnn::_train(trainset &curr){

    int layer_id = 0;
    std::cout << curr.id << std::endl;
    // std::cout << "image: \n" << curr.image << std::endl;
    this->buff_data = curr.image;
    for(auto layer: net.layers){
        if(layer._type == "conv"){
            kernels.resize(layer_id+1);
            std::cout << "checksum" << std::endl;
            int m = layer.kernel_s;

            if (layer_id >= kernels.size()) {
                throw std::runtime_error("Kernel storage not initialized for layer_id");
            }

            kernels[layer_id] = Eigen::MatrixXd::Random(m,m);

            this->buff_data = convolve(this->buff_data,kernels[layer_id],layer.stride,layer.padding);


        }else{
            std::cout << "i will pool " << std::endl;
            this->buff_data = max_pool(this->buff_data);
        }
    }

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
        .activation = relu,
        ._testset = "./dataset/test.csv",
        ._trainset = "./dataset/train.csv",
        .layers = {
                    _layer{._type = "conv",.filters = 2,.kernel_s = 3,.stride =1},
                    _layer{._type = "pool",.pool = max_pool},
                },
    };

    cnn mynet(my);
    mynet.train();

    return 0;
}