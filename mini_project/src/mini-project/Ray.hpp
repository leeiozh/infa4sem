//
// Created by leeiozh on 22.03.2022.
//

#ifndef MINI_PROJECT_RAY_HPP
#define MINI_PROJECT_RAY_HPP

#include <vector>
#include <cmath>
#include <array>
#include <string>
#include "Exception.hpp"

template <int DIM>
class Ray {
    /** класс луча  */
private:
    std::vector<std::array<double, DIM>> trajectory_; // траектория луча

public:
    /**
     * базовый конструктор в двухмерье
     * @param angle1 угол выстрела
     * @param start_x координата х точки старта
     * @param start_y координата у точки старта
     * @param step шаг
     */
    Ray<DIM>(double angle1, double start_x, double start_y, double step);

    /**
     * базовый конструктор в трехмерье
     * @param angle1 угол выстрела по тангажу
     * @param angle2 угол выстрела по рысканью
     * @param start_x координата х точки старта
     * @param start_y координата у точки старта
     * @param start_z координата z точки старта
     * @param step шаг
     */
    Ray<DIM>(double angle1, double angle2, double start_x, double start_y, double start_z, double step);

    /**
     * сделать один шаг
     * @param step размер шага
     * @param n_prev коэффициент преломления на текущем шаге
     * @param n_next коэффициент преломления на следующем шаге
     */
    void step(double step, double n_prev, double n_next);

    /* геттер текущего положения по координате х*/
    [[nodiscard]] double get_x() const {
        return trajectory_.back()[0];
    }

    /* геттер текущего положения по координате у*/
    [[nodiscard]] double get_y() const {
        return trajectory_.back()[1];
    }

    /* геттер текущего положения по координате z*/
    [[nodiscard]] double get_z() const {
        if (DIM == 3) {
            return trajectory_.back()[2];
        } else {
            std::stringstream buff;
            buff << "can't use get_z() when DIM == 2!";
            throw BaseException(buff.str().c_str());
        }
    }

    /* геттер всей насчитанной траектории */
    [[nodiscard]] std::vector<std::array<double, DIM>> get_tract() const {
        return trajectory_;
    }
};


#endif //MINI_PROJECT_RAY_HPP
