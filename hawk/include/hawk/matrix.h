#pragma once
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Core>
#include <vector>

using namespace Eigen;

using matrix = Matrix<double, Dynamic, Dynamic>;
using vector = Matrix<double, Dynamic, 1>;

// using tensor = std::vector<Matrix<double, Dynamic, Dynamic>>;
/*!
    @brief Tensor class
    @tparam Scalar Type of the tensor elements
*/
template<typename Scalar = double>
class Tensor{
public:
    matrix data; ///< Data of the tensor
    matrix grad;

    std::function<void()> backward; ///< Backward function

    Tensor() = default;
    Tensor(const matrix& data) : data(data){}

    Tensor<Scalar> relu(){
        Tensor<Scalar> out(data.cwiseMax(0));
        out.backward = [this, out](){
            if(this->grad.size() > 0){
                this->grad = (this->data.array() > 0).cast<Scalar>() * out.grad;
            }
        };
        return out;
    }
}