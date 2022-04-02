//
// Created by leeiozh on 29.03.2022.
//

#ifndef MINI_PROJECT_BISECTION_HPP
#define MINI_PROJECT_BISECTION_HPP

#include "BaseSearchMethod.hpp"
#include "mini-project/Consts.hpp"

template <int DIM>

class Bisection : public BaseSearchMethod<DIM> {
    /** класс поиска оптимального угла запуска луча методом бисекции */
protected:
    std::shared_ptr<BaseFunction<DIM>> func_; // функция распределения коэффициента преломления в пространстве
    std::shared_ptr<Mesh<DIM>> mesh_; // сетка
    std::shared_ptr<Writer<DIM>> writer_; // писатель

public:

    /**
    * конструктор класса поиска методом бисекции
    * @param func функция распределения коэффициента преломления в пространстве
    * @param mesh сетка
    * @param writer писатель
    */
    inline Bisection(std::shared_ptr<BaseFunction<DIM>> func, std::shared_ptr<Mesh<DIM>> mesh,
                     std::shared_ptr<Writer<DIM>> writer)
            : func_(std::move(func)), mesh_(std::move(mesh)), writer_(std::move(writer)) {
    }

    /**
    * одна итерация поиска
    * @param count номер итерации (запишется в имя файла)
    * @param ang угол стрельбы (градусы)
    * @param step шаг
    * @return координата y в момент, когда x == x_bound
    */
    [[nodiscard]] double run(int count, double ang, double step) const {

        writer_->snapshot(mesh_);

        double angle = ang / 180. * M_PI;
        Ray<DIM> ray(angle, 0, 0, step);

        while (ray.get_x() < (func_->get_bound_x() - 1) * step) {
            ray.step(step, func_->calcRefrInd(ray.get_x(), ray.get_y()),
                     func_->calcRefrInd(ray.get_x() + step, ray.get_y()));
        }
        writer_->snapshot(count, ray);

        return ray.get_y();
    }

    /**
    * запуск поиска оптимального угла запуска луча
    * @param left левая граница поиска (градусы)
    * @param right правая граница поиска (градусы)
    * @param goal цель
    * @return оптимлаьный угол стрельбы
    */
    [[nodiscard]] double search(double left, double right, double goal, double step) const {

        double res = 0.5 * (left + right);
        int count = 0;
        while ((right - left) > TOLERANCE) {
            count++;
            if ((run(count, res, step) - goal) *
                (run(count, left, step) - goal) < 0.) {
                right = res;
            } else {
                left = res;
            }
            res = 0.5 * (right + left);
        }
        return res;
    }
};

#endif //MINI_PROJECT_BISECTION_HPP
