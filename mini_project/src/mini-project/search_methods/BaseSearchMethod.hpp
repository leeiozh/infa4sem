//
// Created by leeiozh on 29.03.2022.
//

#ifndef MINI_PROJECT_BASESEARCHMETHOD_HPP
#define MINI_PROJECT_BASESEARCHMETHOD_HPP

#include "mini-project/Ray.hpp"
#include "mini-project/Writer.hpp"
#include "mini-project/func_refraction/BaseFunction.hpp"

template <int DIM>

class BaseSearchMethod {
    /** базовый класс поиска оптимального угла запуска луча*/
protected:
    std::shared_ptr<BaseFunction<DIM>> func_; // функция распределения коэффициента преломления в пространстве
    std::shared_ptr<Mesh<DIM>> mesh_; // сетка
    std::shared_ptr<Writer<DIM>> writer_; // писатель

public:

    /**
     * одна итерация поиска
     * @param count номер итерации (запишется в имя файла)
     * @param ang угол стрельбы (градусы)
     * @param step шаг
     * @return координата y в момент, когда x == x_bound
     */
    [[nodiscard]] virtual double run(int count, double ang, double step) const = 0;

    /**
     * запуск поиска оптимального угла запуска луча
     * @param left левая граница поиска (градусы)
     * @param right правая граница поиска (градусы)
     * @param goal цель
     * @return оптимлаьный угол стрельбы
     */
    [[nodiscard]] virtual double search(double left, double right, double goal, double step) const = 0;
};

#endif //MINI_PROJECT_BASESEARCHMETHOD_HPP
