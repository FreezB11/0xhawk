/// @file: hawk/optimizer.cc
/// @brief: Optimizers Implementation for HawkNet
#include <hawk/optimizer.h>
#include <hawk/matrix.h>

namespace HAWK{
    namespace Optimizers{

template<typename Scalar>
SGD<Scalar>::SGD(std::vector<Tensor<Scalar>>& params, Scalar lr){
    this->params = params;
    this->lr = lr;
}

template<typename Scalar>
void SGD<Scalar>::step(){
    for(auto& param : this->params){
        param.data -= lr * param.grad;
    }
}

template<typename Scalar>
SGDMomentum<Scalar>::SGDMomentum(std::vector<Tensor<Scalar>>& params, Scalar lr, Scalar momentum){
    this->params  = params;
    this->lr = lr;
    this->momentum = momentum;
    for(const auto& param: params){
        this->velocities.push_back(matrix::Zero(param.data.rows(), param.data.cols()));
    }
}

template<typename Scalar>
void SGDMomentum<Scalar>::step(){
    for(size_t i = 0; i < this->params.size(); ++i){
        this->velocities[i] = momentum * this->velocities[i] - lr * this->params[i].grad;
        this->params[i].data += this->velocities[i];
    }
}

    } // namespace Optimizers
}// namespace HAWK