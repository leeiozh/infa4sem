cmake_minimum_required(VERSION 3.17)
project(mini_project)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE MINI_PROJECT_SOURCES *.h *.cpp *.hpp)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_library(mini_project ${MINI_PROJECT_SOURCES})
target_link_libraries(mini_project PUBLIC ${VTK_LIBRARIES})

target_include_directories(mini_project PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#set(SRC_LIST Geometry.cpp GradientDescent.cpp)
#add_executable(MINI_PROJECT ${SRC_LIST})
#find_package(VTK REQUIRED)
#include(${VTK_USE_FILE})
#
#add_library(mini_project ${MINI_PROJECT_SOURCES})
#target_link_libraries(mini_project PUBLIC)

#target_include_directories(mini_project PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})










