#include "src/cnn.hh"

int main(){

    _arch my = {
        .out_param_size = 10,
        .activation = relu,
        ._testset = "./dataset/test.csv",
        ._trainset = "./dataset/train.csv",
    };

    cnn mynet(my);
    mynet.train();
}