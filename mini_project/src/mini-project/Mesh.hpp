//
// Created by leeiozh on 22.03.2022.
//

#ifndef MINI_PROJECT_MESH_HPP
#define MINI_PROJECT_MESH_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Utility.hpp"
#include "func_refraction/BaseFunction.hpp"

template <int DIM>

class Mesh {
    /** класс сетки */
protected:
    std::vector<std::vector<std::vector<Node>>> points_; // точки сетки в формате структуры нода

public:
    /**
     * конструктор класса сетки
     * @param size размер сетки (кубической)
     * @param h шаг сетки
     * @param n_coeff функция распределения коэффициента преломления
     */
    Mesh<DIM>(int size, double h, std::shared_ptr<BaseFunction<DIM>> n_coeff) {
        points_.resize(size);
        for (int i = 0; i < size; i++) {
            points_[i].resize(size);
            for (int j = 0; j < size; j++) {
                if (DIM == 2) {
                    points_[i][j].resize(1);
                    points_[i][j][0] = Node({i * h, j * h, 0, n_coeff->calcRefrInd(i * h, j * h)});
                } else {
                    points_[i][j].resize(size);
                    for (int k = 0; k < size; ++k) {
                        points_[i][j][k] = Node({i * h, j * h, k * h, n_coeff->calcRefrInd(i * h, j * h, k * h)});
                    }
                }
            }
        }
    }

    // геттер одного нода сетки
    [[nodiscard]] Node get_point(int i, int j, int k) const {
        return points_[i][j][k];
    }

    // геттер размера сетки
    [[nodiscard]] int get_size() {
        return points_.size();
    }
};


#endif //MINI_PROJECT_MESH_HPP
