//
// Created by leeiozh on 22.03.2022.
//

#include "gtest/gtest.h"
#include <vector>
#include "mini-project/Mesh.hpp"
#include "mini-project/Writer.hpp"
#include "mini-project/search_methods/Bisection.hpp"
#include "mini-project/func_refraction/LinearFunction.hpp"

TEST(SIMPLE_2D, SIZE_20) {

    const int DIM = 2; // размерность пространства
    int size = 20; // размер квадратной сетки
    double h = 1.; // шаг

    auto n_coeff = std::make_shared<LinearFunction<DIM>>(LinearFunction<DIM>(size * h, size * h, size * h, 1, 2));

    auto mesh = std::make_shared<Mesh<DIM>>(
            Mesh<DIM>(size, h, n_coeff)); // сетка с заданным шагом и распределением коэффициента преломления на ней

    auto writer = std::make_shared<Writer<DIM>>(Writer<DIM>(std::string(
            "/home/leeiozh/miptbot/proga/infa4sem/mini_project/out/res_quadr_"))); // писатель и путь, куда ему писать

    Bisection<DIM> bisection(n_coeff, mesh, writer); // метод, который будет все считать и заодно отрисовывать

    double res = bisection.search(0, 90, h * (size - 1), h); // запуск метода
    ASSERT_NEAR(res, 48.0981, TOLERANCE);
}

TEST(SIMPLE_2D, SIZE_200) {

    const int DIM = 2; // размерность пространства
    int size = 200; // размер квадратной сетки
    double h = 1.; // шаг

    auto n_coeff = std::make_shared<LinearFunction<DIM>>(LinearFunction<DIM>(size * h, size * h, size * h, 1, 1.5));

    auto mesh = std::make_shared<Mesh<DIM>>(
            Mesh<DIM>(size, h, n_coeff)); // сетка с заданным шагом и распределением коэффициента преломления на ней

    auto writer = std::make_shared<Writer<DIM>>(Writer<DIM>(std::string(
            "/home/leeiozh/miptbot/proga/infa4sem/mini_project/out/res_200_quadr_"))); // писатель и путь, куда ему писать

    Bisection<DIM> bisection(n_coeff, mesh, writer); // метод, который будет все считать и заодно отрисовывать

    double res = bisection.search(0, 90, h * (size - 1), h); // запуск метода
    ASSERT_NEAR(res, 57.81005859375, TOLERANCE);
}

TEST(SIMPLE_2D, SIZE_2000) {

    const int DIM = 2; // размерность пространства
    int size = 2000; // размер квадратной сетки
    double h = 1.; // шаг

    auto n_coeff = std::make_shared<LinearFunction<DIM>>(LinearFunction<DIM>(size * h, size * h, size * h, 1, 3));

    auto mesh = std::make_shared<Mesh<DIM>>(
            Mesh<DIM>(size, h, n_coeff)); // сетка с заданным шагом и распределением коэффициента преломления на ней

    auto writer = std::make_shared<Writer<DIM>>(Writer<DIM>(std::string(
            "/home/leeiozh/miptbot/proga/infa4sem/mini_project/out/res_2000_quadr_"))); // писатель и путь, куда ему писать

    Bisection<DIM> bisection(n_coeff, mesh, writer); // метод, который будет все считать и заодно отрисовывать

    double res = bisection.search(0, 90, h * (size - 1), h); // запуск метода
    ASSERT_NEAR(res, 66.64306640625, TOLERANCE);
}