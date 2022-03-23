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
private:
    std::string path_;

public:
    inline explicit Writer(std::string path) : path_(std::move(path)) {}

    void snapshot(const Mesh<DIM> &mesh) const;
    void snapshot(int counter, const Mesh<DIM> &mesh, const Ray<DIM> &ray) const;
};

#endif //MINI_PROJECT_WRITER_HPP
