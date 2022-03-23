//
// Created by leeiozh on 22.03.2022.
//

#ifndef MINI_PROJECT_MESH_HPP
#define MINI_PROJECT_MESH_HPP

#include <string>
#include <vector>
#include "Utility.hpp"

template <int DIM>

class Mesh {
protected:
    std::vector<std::vector<std::vector<Node>>> points;

public:
    Mesh<DIM>(int size, double h, std::vector<double> &n_coeff);

    [[nodiscard]] std::vector<std::vector<std::vector<Node>>> get_points() const {
        return points;
    }
};


#endif //MINI_PROJECT_MESH_HPP
