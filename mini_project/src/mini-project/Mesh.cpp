//
// Created by leeiozh on 22.03.2022.
//

#include "Mesh.hpp"

template <int DIM>

Mesh<DIM>::Mesh(int size, double h, std::vector<double> &n_coeff) {

    points.resize(size);
    for (int i = 0; i < size; i++) {
        points[i].resize(size);
        for (int j = 0; j < size; j++) {
            if (DIM == 2) {
                points[i][j].resize(1);
                points[i][j][0] = Node({i * h, j * h, 0, n_coeff[i]});
            } else {
                points[i][j].resize(size);
                for (int k = 0; k < size; ++k) {
                    points[i][j][k] = Node({i * h, j * h, k * h, n_coeff[i]});
                }
            }
        }
    }
}

template
class Mesh<2>;

template
class Mesh<3>;