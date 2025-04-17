#pragma once
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Core>
#include <vector>

using namespace Eigen;

using matrix = Matrix<double, Dynamic, Dynamic>;
using vector = Matrix<double, Dynamic, 1>;

using tensor = vector<Matrix<double, Dynamic, Dynamic>>;