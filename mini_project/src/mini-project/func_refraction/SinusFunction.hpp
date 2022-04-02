//
// Created by leeiozh on 02.04.2022.
//

#ifndef MINI_PROJECT_SINUSFUNCTION_HPP
#define MINI_PROJECT_SINUSFUNCTION_HPP

#include "BaseFunction.hpp"
#include <cmath>

template <int DIM>

class SinusFunction : public BaseFunction<DIM> {
    /** класс функции линейного распределения коэффициента преломления в пространстве (х, y, z) */
protected:
    double n_min_ = 1.; // минимальный коэффициент преломления
    double n_max_ = 3.; // максимальный коэффициент преломления
    double bound_x_ = 100.; // правая граница по х (левая - 0)
    double bound_y_ = 100.; // правая граница по у (левая - 0)
    double bound_z_ = 100.; // правая граница по z (левая - 0)
public:
    /**
     * конструктор класса функции линейного распределения коэффициента преломления на сетке
     * @param bound_x правая граница по х (левая - 0)
     * @param bound_y правая граница по у (левая - 0)
     * @param bound_z правая граница по z (левая - 0)
     * @param n_min минимальный коэффициент преломления
     * @param n_max максимальный коэффициент преломления
     */
    inline explicit SinusFunction(double bound_x, double bound_y = 100., double bound_z = 100., double n_min = 1.,
                                   double n_max = 3.)
            : BaseFunction<DIM>(bound_x, bound_y, bound_z, n_min, n_max) {}

    /**
     * вычисление коэффициента преломления в точке (x, y, 0) для двухмерья
     * @param x координата вызываемой точки
     * @param y координата вызываемой точки
     * @return коэффициент преломления в точке (x, y, 0)
     */
    [[nodiscard]] inline double calcRefrInd(double x, double y) const {
        return n_min_ + (n_max_ - n_min_) * std::sin(4 * M_PI * (x / bound_x_ + y / bound_y_));
    }

    /**
     * вычисление коэффициента преломления в точке (x, y, z) для трехмерья
     * @param x координата вызываемой точки
     * @param y координата вызываемой точки
     * @param z координата вызываемой точки
     * @return коэффициент преломления в точке (x, y, z)
     */
    [[nodiscard]] inline double calcRefrInd(double x, double y, double z) const {
        return n_min_ + (n_max_ - n_min_) * std::sin(4 * M_PI * (x / bound_x_ + y / bound_y_ + z / bound_z_));
    }
};

#endif //MINI_PROJECT_SINUSFUNCTION_HPP
