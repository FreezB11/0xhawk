/// @file: hawk/optimizer.cc
/// @brief: Optimizers Implementation for HawkNet
#include <hawk/optimizer.h>
#include <hawk/matrix.h>

namespace HAWK{
    namespace Optimizers{

SGD::SGD(std::vector<Tensor<Scalar>>& params, Scalar lr) : lr(lr){
    this->params = params;
}

void SGD::step() override {
    for(auto& param : this->params){
        param.data -= lr * param.grad;
    }
}

SGDMomentum::SGDMomentum(std::vector<Tensor<Scalar>>& params, Scalar lr, Scalar momentum) : SGD(params, lr), momentum(momentum){
    this->params  = params;
    for(const auto& param: params){
        velocity.push_back(matrix::Zero(param.data.rows(), param.data.cols()));
    }
}

void SGDMomentum::step() override {
    for(size_t i = 0; i < this->params.size(); ++i){
        velocity[i] = momentum * velocity[i] - lr * this->params[i].grad;
        this->params[i].data += velocity[i];
    }
}

    } // namespace Optimizers
}// namespace HAWK