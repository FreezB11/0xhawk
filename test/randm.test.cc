#include <iostream>
#include <eigen3/Eigen/Dense>
 
using Eigen::MatrixXd;
using Eigen::VectorXd;
 
int main()
{
  MatrixXd m = MatrixXd::Random(3,3);
  std::cout << "m =" << std::endl << m << std::endl;
}