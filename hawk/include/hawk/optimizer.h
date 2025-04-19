/// @file: hawk/optimizer.h
/// @brief: Optimizers for HawkNet
#pragma once

#include <vector>
#include <hawk/matrix.h>

/*!
    @brief Optimizers
      - SGD
      - SGD with Momentum
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
        Scalar                          lr;
                                        SGD(std::vector<Tensor<Scalar>>& params, Scalar lr);
        void                            step() override;
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
        Scalar                          lr;
        Scalar                          momentum;
        std::vector<matrix>             velocities;
                                        SGDMomentum(std::vector<Tensor<Scalar>>& params, Scalar lr, Scalar momentum);
        void                            step() override;
};

/*!
    @class AdaGrad
    @ingroup Optimizers
    @brief Adaptive Gradient
    @tparam Scalar Type of the Optimizer
    @param lr Learning rate
    @param epsilon Small value to prevent division by zero
    @details Adaptive Gradient
    @note AdaGrad is an adaptive learning rate optimization algorithm that adjusts the learning rate
          for each parameter based on the historical gradients.
          w[t+1] = w[t] - lr * grad / (sqrt(G) + epsilon)
          where w is the parameter, lr is the learning rate, grad is the gradient of the loss function
          with respect to the parameter, G is the sum of the squares of the gradients, and epsilon is a small value
          to prevent division by zero.
*/
template<typename Scalar = double>
class AdaGrad : public Optimizer<Scalar>{
    public:
        Scalar                          lr, eps;
        std::vector<matrix>             cache;
                                        AdaGrad(std::vector<Tensor<Scalar>>& params, Scalar lr = 0.01, Scalar eps = 1e-8);
        void                            step() override;
};

/*!
    @class RMSProp
    @ingroup Optimizers
    @brief Root Mean Square Propagation
    @tparam Scalar Type of the optimizer
    @param lr Learning rate
    @param decay_rate Decay rate
    @param epsilon Small value to prevent division by zero
    @details Root Mean Square Propagation
    @note RMSProp is an adaptive learning rate optimization algorithm that adjusts the learning rate
          for each parameter based on the historical gradients.
          w[t+1] = w[t] - lr * grad / (sqrt(E) + epsilon)
          where w is the parameter, lr is the learning rate, grad is the gradient of the loss function
          with respect to the parameter, E is the exponential moving average of the squared gradients,
          and epsilon is a small value to prevent division by zero.
*/
template<typename Scalar = double>
class RMSProp : public Optimizer<Scalar>{
    public:
        Scalar                          lr, decay_rate, eps;
        std::vector<matrix>             cache;
                                        RMSProp(std::vector<Tensor<Scalar>>& params, Scalar lr = 0.01, Scalar decay_rate = 0.9, Scalar eps = 1e-8);
        void                            step() override;
};

/*!
    @class Adam
    @ingroup Optimizers
    @brief Adaptive Moment Estimation
    @tparam Scalar Type of the optimizer
    @param lr Learning rate
    @param beta1 Exponential decay rate for the first moment estimates
    @param beta2 Exponential decay rate for the second moment estimates
    @param epsilon Small value to prevent division by zero
    @details Adaptive Moment Estimation
    @note Adam is an adaptive learning rate optimization algorithm that combines the advantages of AdaGrad and RMSProp.
          w[t+1] = w[t] - lr * m / (sqrt(v) + epsilon)
          where w is the parameter, lr is the learning rate, m is the first moment estimate,
          v is the second moment estimate, and epsilon is a small value to prevent division by zero.
*/
template<typename Scalar = double>
class Adam : public Optimizer<Scalar>{
    public:
        Scalar                          lr, beta1, beta2, eps;
        std::vector<matrix>             m, v;
        int                             t;
                                        Adam(std::vector<Tensor<Scalar>>& params, Scalar lr = 0.001, Scalar beta1 = 0.9, Scalar beta2 = 0.999, Scalar eps = 1e-8);
        void                            step() override;
};

    }// namespace Optimizers
}// namespace HAWK


/*usage

int main() {
    // Example: Linear regression parameters (weight and bias)
    Tensor<float> weight(MatrixXf::Random(2, 1));
    Tensor<float> bias(MatrixXf::Zero(1, 1));
    
    std::vector<Tensor<float>> params = {weight, bias};
    Adam<float> optimizer(params, 0.001); // Adam optimizer
    
    // Simulate a training step
    weight.grad = MatrixXf::Random(2, 1);
    bias.grad = MatrixXf::Random(1, 1);
    
    optimizer.step(); // Update parameters
    optimizer.zero_grad(); // Reset gradients
    
    return 0;
}

*/