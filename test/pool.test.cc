#include <iostream>

#include <eigen3/Eigen/Dense>
#include "../lib/mmath.hh"


int main() {
    Eigen::MatrixXd input(4, 4);
    input << 1, 2, 3, 4,
             5, 6, 7, 8,
             9, 10, 11, 12,
             13, 14, 15, 16;

    Eigen::MatrixXd output = max_pool(input);

    std::cout << "Input Matrix:\n" << input << std::endl;
    std::cout << "Pooled Output:\n" << output << std::endl;

    return 0;
}
