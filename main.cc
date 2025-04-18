/// @file main.cc
#include <hawk/cnn.hh>
#include <hawk/conv.h>

int main(){
    /// @todo implement global namsepace "hawk"
    /// @brief This is a simple example of how to use the CNN class
    HAWK::CNN::model my = {
        .out_param_size = 10,
        .hidden_lyrs = {50, 90},
        .activation = relu,
        ._testset = "./dataset/test.csv",
        ._trainset = "./dataset/train.csv",
        .layers = {
                    HAWK::CNN::_layer{._type = "conv",.filters = 2,.kernel_s = 5},
                    HAWK::CNN::_layer{._type = "pool",.pool = HAWK::CNN::maxpool},
                    HAWK::CNN::_layer{._type = "conv",.filters = 2,.kernel_s = 3},
                    HAWK::CNN::_layer{._type = "pool",.pool = HAWK::CNN::maxpool},
                    HAWK::CNN::_layer{._type = "conv",.filters = 2,.kernel_s = 2}
        },
    };

    HAWK::CNN::cnn mynet(my);
    mynet.train();
}