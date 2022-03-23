//
// Created by leeiozh on 22.03.2022.
//

#ifndef MINI_PROJECT_RAY_HPP
#define MINI_PROJECT_RAY_HPP

#include <vector>
#include <cmath>
#include <array>
#include "Exception.hpp"

template <int DIM>
class Ray {
private:
    std::vector<std::array<double, DIM>> trajectory_;

public:
    Ray<DIM>(double angle1, double start_x, double start_y, double step);

    Ray<DIM>(double angle1, double angle2, double start_x, double start_y, double start_z, double step);

    void step(double step, double n_prev, double n_next);

    [[nodiscard]] double get_x() const {
        return trajectory_.back()[0];
    }

    [[nodiscard]] double get_y() const {
        return trajectory_.back()[1];
    }

    [[nodiscard]] std::vector<std::array<double, DIM>> get_tract() const {
        return trajectory_;
    }
};


#endif //MINI_PROJECT_RAY_HPP
