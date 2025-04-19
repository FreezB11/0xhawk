#pragma once

#include <eigen3/Eigen/Dense>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>

namespace HAWK {
    namespace KNN{

class KNN {
public:
    KNN(int k = 5);
    void fit(const Eigen::MatrixXd& X, const Eigen::VectorXi& y);
    Eigen::VectorXi predict(const Eigen::MatrixXd& X);
    void setK(int k);

private:
    int k;
    Eigen::MatrixXd X_train;
    Eigen::VectorXi y_train;
    
    double euclideanDistance(const Eigen::VectorXd& a, const Eigen::VectorXd& b) const;
    std::vector<std::pair<double, int>> getNeighbors(const Eigen::VectorXd& test_point) const;
    int predictSingle(const Eigen::VectorXd& test_point) const;
};

    } // namespace KNN
} // namespace HAWK