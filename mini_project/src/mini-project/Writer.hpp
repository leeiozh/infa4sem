//
// Created by leeiozh on 23.03.2022.
//

#ifndef MINI_PROJECT_WRITER_HPP
#define MINI_PROJECT_WRITER_HPP

#include "Mesh.hpp"
#include "Ray.hpp"
#include <string>
#include <utility>

template <int DIM>
class Writer {
    /** класс писателя всего в файлы */
private:
    std::string path_; // путь записи

public:
    /**
     * базовый конструктор от пути
     * @param path путь записи
     */
    inline explicit Writer(std::string path) : path_(std::move(path)) {}

    /**
     * запись сетки в файл
     * @param mesh сетка
     */
    void snapshot(std::shared_ptr<Mesh<DIM>> mesh) const;

    /**
     * запись пути луча с номером итерации в файл
     * @param counter номер итерации (указывается в имени файла)
     * @param ray луч
     */
    void snapshot(int counter, const Ray<DIM> &ray) const;
};

#endif //MINI_PROJECT_WRITER_HPP
