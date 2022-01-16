cmake_minimum_required(VERSION 2.8.12)
project(geometry)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

find_package(Eigen3 REQUIRED)
find_package(pybind11 REQUIRED)
find_package(manif-geom-cpp REQUIRED)

include_directories(
  ${EIGEN3_INCLUDE_DIRS}
)

pybind11_add_module(geometry python_module.cpp)
target_link_libraries(geometry INTERFACE manif-geom-cpp)
