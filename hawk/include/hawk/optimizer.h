/// @file: hawk/optimizer.h
/// @brief: Optimizers for HawkNet
#pragma once

#include <vector>
#include <hawk/matrix.h>

/*!
    @brief Optimizers
      - SGD
      - Adam
      - AdaGrad
      - RMSProp
*/
/// @namespace hawk
namespace HAWK{
    namespace Optimizers{
/*!
    @brief Optimizer class ( base class)
    @tparam Scalar Type of the optimizer
*/
template<typename Scalar = double>
class Optimizer{
    public:
        virtual void step() = 0; ///< Step function
        std::vector<Tensor<Scalar>> params; ///< Parameters
        virtual void zero_grad(){
            for(auto& param : this->params){
                param.grad.setZero();
            }
        }
};
/*!
    @class SGD
    @ingroup Optimizers
    @brief SGD Optimizer
    @tparam Scalar Type of the optimizer
    @param lr Learning rate
    @details Stochastic Gradient Descent
    @note SGD is a simple and efficient optimization algorithm that updates the parameters
          using the gradient of the loss function with respect to the parameters.
          w[t+1] = w[t] - lr * grad
          where w is the parameter, lr is the learning rate, and grad is the gradient of the loss function
          with respect to the parameter.
*/
template<typename Scalar = double>
class SGD : public Optimizer<Scalar>{
    public:
        Scalar lr;
        SGD(std::vector<Tensor<Scalar>>& params, Scalar lr);
        void step() override;
};

/*!
    @class SGDMomentum
    @ingroup Optimizers
    @brief SGD with Momentum Optimizer
    @tparam Scalar Type of the optimizer
    @param lr Learning rate
    @param momentum Momentum
    @details Stochastic Gradient Descent with Momentum
    @note SGD with Momentum is an extension of SGD that adds a momentum term to the update rule.
          w[t+1] = w[t] - lr * grad + momentum * (w[t] - w[t-1])
          where w is the parameter, lr is the learning rate, grad is the gradient of the loss function
          with respect to the parameter, and momentum is the momentum term.
          The momentum term helps to accelerate the convergence of the optimization algorithm
          by adding a fraction of the previous update to the current update.
*/
template<typename Scalar = double>
class SGDMomentum : public Optimizer<Scalar>{
    public:
        Scalar lr;
        Scalar momentum;
        std::vector<matrix> velocities;
        SGDMomentum(std::vector<Tensor<Scalar>>& params, Scalar lr, Scalar momentum);
        void step() override;
};


    }// namespace Optimizers
}// namespace HAWK