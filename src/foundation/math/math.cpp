#include "Eigen/Core"

#include <iostream>

void test()
{
    Eigen::Matrix3f covariance_matrix;
    covariance_matrix.setZero();
    std::cout << covariance_matrix << std::endl;
}
