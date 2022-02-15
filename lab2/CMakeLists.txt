cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_FLAGS "-std=c++11 -g")

project(vtkdemo)
add_executable(tor tor.cpp)

# Найдём VTK
find_package(VTK REQUIRED)
# ... и подключим её со всеми её компонентами её нативными средствами
include(${VTK_USE_FILE})

# gmsh укажем явно по кусочкам (потому что он был просто распакован руками)
add_library(gmsh SHARED IMPORTED)
set_target_properties(gmsh PROPERTIES
        IMPORTED_LOCATION "/home/leeiozh/miptbot/proga/gmsh-4.9.4-Linux64-sdk/lib/libgmsh.so"
        INTERFACE_INCLUDE_DIRECTORIES "/home/leeiozh/miptbot/proga/gmsh-4.9.4-Linux64-sdk/include"
        )
set(GMSH_LIBRARY gmsh)

# если бы gmsh был поставлен прилично, то можно было бы примерно вот так
#find_package(gmsh REQUIRED)
#include_directories(${GMSH_INCLUDE_DIR})
#target_link_libraries(tor ${GMSH_LIBRARY})

# Укажем библиотеки для линковки
# ... тут только VTK

# ... а тут ещё и gmsh
target_link_libraries(tor ${VTK_LIBRARIES})
target_link_libraries(tor ${GMSH_LIBRARY})