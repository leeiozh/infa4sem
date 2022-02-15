cmake_minimum_required(VERSION 3.21)
project(lab1)

add_executable(demo demo_gmsh.cpp)

set(CMAKE_CXX_STANDARD 14)

add_library(gmsh SHARED IMPORTED)
set_target_properties(gmsh PROPERTIES
        IMPORTED_LOCATION "/home/leeiozh/miptbot/proga/gmsh-4.9.4-Linux64-sdk/lib/libgmsh.so"
        INTERFACE_INCLUDE_DIRECTORIES "/home/leeiozh/miptbot/proga/gmsh-4.9.4-Linux64-sdk/include"
        )
set(GMSH_LIBRARY gmsh)

target_link_libraries(demo ${GMSH_LIBRARY})
