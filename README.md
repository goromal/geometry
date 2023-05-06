# Geometry

![example workflow](https://github.com/goromal/geometry/actions/workflows/test.yml/badge.svg)

Python bindings for the [manif-geom-cpp](https://github.com/goromal/manif-geom-cpp) library.

## Building / Installing

This library is built with CMake. Most recently tested with the following dependencies:

- Pybind11
- Eigen 3.4.0
- [manif-geom-cpp](https://github.com/goromal/manif-geom-cpp)

```bash
mkdir build
cd build
cmake ..
make # or make install
```

Pytest unit tests are present in the `tests/` folder.
