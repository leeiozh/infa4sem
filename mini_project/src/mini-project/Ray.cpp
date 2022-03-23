//
// Created by leeiozh on 23.03.2022.
//

#include "Ray.hpp"
#include "iostream"

template <>
Ray<2>::Ray(double angle, double start_x, double start_y, double step) {

    trajectory_.push_back(std::array<double, 2>({start_x, start_y}));
    trajectory_.push_back(std::array<double, 2>({start_x + step, start_y + step * std::tan(angle)}));
}

template <>
Ray<3>::Ray(double angle1, double angle2, double start_x, double start_y, double start_z, double step) {

    trajectory_.push_back(std::array<double, 3>({start_x, start_y, start_z}));
    trajectory_.push_back(std::array<double, 3>({start_x * std::cos(angle1) - start_y * std::sin(angle1),
                                                 start_x * std::sin(angle1) + start_y * std::cos(angle1), 0.}));

}

template <>
void Ray<2>::step(double step, double n_prev, double n_next) {
    trajectory_.push_back(
            std::array<double, 2>({trajectory_.back()[0] + step, trajectory_.back()[1] + (trajectory_.back()[1] -
                                  trajectory_[trajectory_.size() - 2][1]) * n_prev / n_next}));

//    std::cout <<  trajectory_.back()[1] << std::endl;

}

template <>
void Ray<3>::step(double step, double n_prev, double n_next) {
    trajectory_.push_back(std::array<double, 3>(
            {trajectory_.back()[0] + step,
             trajectory_.back()[1] + (trajectory_.back()[1] - trajectory_[trajectory_.size() - 2][1]) *
                                     n_prev / n_next, trajectory_.back()[2] + (trajectory_.back()[2] -
                                                                               trajectory_[trajectory_.size() -
                                                                                           2][2]) * n_prev /
                                                                              n_next}));
}

template
class Ray<2>;

template
class Ray<3>;