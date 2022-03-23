//
// Created by leeiozh on 22.03.2022.
//

#include "gtest/gtest.h"
#include <vector>
#include <cmath>

#include "mini-project/Mesh.hpp"
#include "mini-project/GradientDescent.hpp"
#include "mini-project/Ray.hpp"
#include "mini-project/Writer.hpp"

TEST(SIMPLE_2D, INIT) {

    // Размер расчётной сетки, точек на сторону
    int size = 20;
    // Шаг точек по пространству
    double h = 1;
    // Шаг по времени
    double tau = 0.01;

    // распределение коэффициента преломления
    std::vector<double> n_coeff(static_cast<int>(size / h));
    double n_min = 1.;
    double n_max = 1.5;
    for (int i = 0; i < n_coeff.size(); ++i) {
        n_coeff[i] = n_min + static_cast<double>(i) / static_cast<double>(n_coeff.size()) * (n_max - n_min);
    }

    const int DIM = 2;

    // Создаём сетку заданного размера
    Mesh<DIM> mesh(size, h, n_coeff);

    Writer<DIM> writer(std::string("/home/leeiozh/miptbot/proga/infa4sem/mini_project/out/2203"));

    double angle = 45. / 180. * M_PI;

    Ray<DIM> ray(angle, 0, 0, h);

    // Пишем её начальное состояние в VTK

    while (ray.get_x() < size * h) {
        ray.step(h, n_min + ray.get_x() / size / h * (n_max - n_min), n_min + (ray.get_x() + h) / size / h * (n_max - n_min));
        std::cout << ray.get_x() << " " << ray.get_y() << std::endl;
    }

    writer.snapshot(1, mesh, ray);

}
