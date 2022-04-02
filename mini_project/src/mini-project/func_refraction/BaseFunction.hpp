//
// Created by leeiozh on 29.03.2022.
//

#ifndef MINI_PROJECT_BASEFUNCTION_HPP
#define MINI_PROJECT_BASEFUNCTION_HPP

template <int DIM>

class BaseFunction {
    /** базовый класс функции распределения коэффициента преломления в пространстве (х, y, z) */
protected:
    double n_min_ = 1.; // минимальный коэффициент преломления
    double n_max_ = 3.; // максимальный коэффициент преломления
    double bound_x_ = 100.; // правая граница по х (левая - 0)
    double bound_y_ = 100.; // правая граница по у (левая - 0)
    double bound_z_ = 100.; // правая граница по z (левая - 0)
public:
    /**
     * конструктор базового класса функции распределения коэффициента преломления на сетке
     * @param bound_x правая граница по х (левая - 0)
     * @param bound_y правая граница по у (левая - 0)
     * @param bound_z правая граница по z (левая - 0)
     * @param n_min минимальный коэффициент преломления
     * @param n_max максимальный коэффициент преломления
     */
    inline explicit BaseFunction(double bound_x, double bound_y = 100., double bound_z = 100., double n_min = 1.,
                                 double n_max = 3.) : bound_x_(bound_x), bound_y_(bound_y), bound_z_(bound_z),
                                                      n_min_(n_min), n_max_(n_max) {}

     /**
    * вычисление коэффициента преломления в точке (x, y, 0) для двухмерья
    * @param x координата вызываемой точки
    * @param y координата вызываемой точки
    * @return коэффициент преломления в точке (x, y, 0)
    */
    [[nodiscard]] virtual inline double calcRefrInd(double x, double y) const = 0;

    /**
     * вычисление коэффициента преломления в точке (x, y, z) для трехмерья
     * @param x координата вызываемой точки
     * @param y координата вызываемой точки
     * @param z координата вызываемой точки
     * @return коэффициент преломления в точке (x, y, z)
     */
    [[nodiscard]] virtual inline double calcRefrInd(double x, double y, double z) const = 0;

    // геттер минимального коэффициента преломления
    inline double get_n_min() { return n_min_; }

    // геттер максимального коэффициента преломления
    inline double get_n_max() { return n_max_; }

    // геттер границы по x
    inline double get_bound_x() { return bound_x_; }

    // геттер границы по у
    inline double get_bound_y() { return bound_y_; }

    // геттер границы по z
    inline double get_bound_z() { return bound_z_; }
};

#endif //MINI_PROJECT_BASEFUNCTION_HPP
