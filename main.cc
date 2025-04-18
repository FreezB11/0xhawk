/// @file main.cc
#include <hawk/cnn.hh>
#include <hawk/conv.h>

int main(){
    /// @todo implement global namsepace "hawk"
    /// @brief This is a simple example of how to use the CNN class
    _arch my = {
        .out_param_size = 10,
        .hidden_lyrs = {50, 90},
        .activation = relu,
        ._testset = "./dataset/test.csv",
        ._trainset = "./dataset/train.csv",
        .layers = {
                    _layer{._type = "conv",.filters = 2,.kernel_s = 5},
                    _layer{._type = "pool",.pool = CNN::maxpool},
                    _layer{._type = "conv",.filters = 2,.kernel_s = 3},
                    _layer{._type = "pool",.pool = CNN::maxpool},
                    _layer{._type = "conv",.filters = 2,.kernel_s = 2}
        },
    };

    cnn mynet(my);
    mynet.train();
}