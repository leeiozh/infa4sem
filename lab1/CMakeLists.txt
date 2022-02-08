cmake_minimum_required(VERSION 3.21)
project(lab1)

add_executable(tor1 demo_gmsh.cpp)

set(CMAKE_CXX_STANDARD 14)

# gmsh укажем явно (потому что он был просто распакован руками)
add_library(gmsh SHARED IMPORTED)
set_target_properties(gmsh PROPERTIES
        IMPORTED_LOCATION "/home/leeiozh/miptbot/proga/gmsh-4.9.4-Linux64-sdk/lib/libgmsh.so"
        INTERFACE_INCLUDE_DIRECTORIES "/home/leeiozh/miptbot/proga/gmsh-4.9.4-Linux64-sdk/include"
        )
set(GMSH_LIBRARY gmsh)

# Укажем библиотеки для линковки
target_link_libraries(tor1 ${GMSH_LIBRARY})
