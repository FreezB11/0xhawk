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

template<typename Scalar>
AdaGrad<Scalar>::AdaGrad(std::vector<Tensor<Scalar>>& params, Scalar lr, Scalar epsilon){
    this->params = params;
    this->lr = lr;
    this->eps = epsilon;
    for(const auto& param: params){
        this->cache.push_back(matrix::Zero(param.data.rows(), param.data.cols()));
    }

}

template<typename Scalar>
void AdaGrad<Scalar>::step(){
    for(size_t i = 0; i < this->params.size(); ++i){
        this->cache[i] += this->params[i].grad.array().square().matrix();
        this->params[i].data -= (this->lr / (this->cache[i].array().sqrt() + this->eps)) * this->params[i].grad.array();
    }
}

template<typename Scalar>
RMSProp<Scalar>::RMSProp(std::vector<Tensor<Scalar>>& params, Scalar lr, Scalar decay_rate, Scalar epsilon){
    this->params = params;
    this->lr = lr;
    this->decay_rate = decay_rate;
    this->eps = epsilon;
    for(const auto& param: params){
        this->cache.push_back(matrix::Zero(param.data.rows(), param.data.cols()));
    }
}

template<typename Scalar>
void RMSProp<Scalar>::step(){
    for(size_t i = 0; i < this->params.size(); ++i){
        this->cache[i] = this->decay_rate * this->cache[i] + (1 - this->decay_rate) * this->params[i].grad.array().square().matrix();
        this->params[i].data -= (this->lr / (this->cache[i].array().sqrt() + this->eps)) * this->params[i].grad.array();
    }
}

template<typename Scalar>
Adam<Scalar>::Adam(std::vector<Tensor<Scalar>>& params, Scalar lr, Scalar beta1, Scalar beta2, Scalar epsilon){
    this->params = params;
    this->lr = lr;
    this->beta1 = beta1;
    this->beta2 = beta2;
    this->eps = epsilon;
    for(const auto& param: params){
        this->m.push_back(matrix::Zero(param.data.rows(), param.data.cols()));
        this->v.push_back(matrix::Zero(param.data.rows(), param.data.cols()));
    }
}

template<typename Scalar>
void Adam<Scalar>::step(){
    t++;
    for(size_t i = 0; i < this->params.size(); ++i){
        this->m[i] = this->beta1 * this->m[i] + (1 - this->beta1) * this->params[i].grad;
        this->v[i] = this->beta2 * this->v[i] + (1 - this->beta2) * this->params[i].grad.array().square().matrix();

        matrix m_hat = this->m[i] / (1 - std::pow(this->beta1, t));
        matrix v_hat = this->v[i] / (1 - std::pow(this->beta2, t));

        this->params[i].data -= (this->lr / (v_hat.array().sqrt() + this->eps)) * m_hat.array();
    }
}


    } // namespace Optimizers
}// namespace HAWK