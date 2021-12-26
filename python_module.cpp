#include <SO3.h>
#include <SE3.h>
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <sstream>

using namespace Eigen;
namespace py = pybind11;

PYBIND11_MODULE(geometry, m)
{
  m.doc() = "Python binding module for SO3/SE3.";
  
  py::class_<SO3d>(m, "SO3")
    .def_static("random", &SO3d::random)
    .def_static("identity", &SO3d::identity)
    .def_static("fromAxisAngle", &SO3d::fromAxisAngle)
    .def_static("fromEuler", &SO3d::fromEuler)
    .def_static("fromR", &SO3d::fromR)
    .def_static("fromTwoUnitVectors", &SO3d::fromTwoUnitVectors)
    .def_static("fromQuat", static_cast<SO3d (*)(const double, const double, const double, const double)>(&SO3d::fromQuat), "Instantiate SO3 from quaternion fields")
    .def_static("fromQuat", static_cast<SO3d (*)(const Matrix<double,4,1> &)>(&SO3d::fromQuat), "Instantiate SO3 from a vector of quaternion fields")
    .def(py::init())
    .def(py::init<const Ref<const Matrix<double,4,1>>>())
    .def(py::init<const SO3d &>())
    .def("w", &SO3d::w)
    .def("x", &SO3d::x)
    .def("y", &SO3d::y)
    .def("z", &SO3d::z)
    .def("setW", &SO3d::setW)
    .def("setX", &SO3d::setX)
    .def("setY", &SO3d::setY)
    .def("setZ", &SO3d::setZ)
    .def("array", &SO3d::array)
    .def("normalize", &SO3d::normalize)
    .def("R", &SO3d::R)
    .def("inverse", &SO3d::inverse)
    .def("invert", &SO3d::invert)
    .def("roll", &SO3d::roll)
    .def("pitch", &SO3d::pitch)
    .def("yaw", &SO3d::yaw)
    .def("toEuler", &SO3d::toEuler)
    .def("qMatLeft", &SO3d::qMatLeft)
    .def(py::self * py::self)
    .def(py::self * Matrix<double,3,1>())
    .def(py::self + Matrix<double,3,1>())
    .def(py::self - py::self)
    .def_static("hat", &SO3d::hat)
    .def_static("vee", &SO3d::vee)
    .def_static("log", &SO3d::log)
    .def_static("Log", &SO3d::Log)
    .def_static("exp", &SO3d::exp)
    .def_static("Exp", &SO3d::Exp)
    .def("__repr__",
      [](const SO3d &q) {
        std::stringstream ss;
        ss << q;
        return ss.str();
      }
    );
    
  py::class_<SE3d>(m, "SE3")
    .def_static("random", &SE3d::random)
    .def_static("identity", &SE3d::identity)
    .def_static("fromH", &SE3d::fromH)
    .def_static("fromVecAndQuat", static_cast<SE3d (*)(const double, const double, const double, const double, const double, const double, const double)>(&SE3d::fromVecAndQuat), "Instantiate SE3 from translation and quaternion fields")
    .def_static("fromVecAndQuat", static_cast<SE3d (*)(const Matrix<double,3,1> &, const Matrix<double,4,1> &)>(&SE3d::fromVecAndQuat), "Instantiate SE3 from a translation vector and vector of quaternion fields")
    .def_static("fromVecAndQuat", static_cast<SE3d (*)(const Matrix<double,3,1> &, const SO3d &)>(&SE3d::fromVecAndQuat), "Instantiate SE3 from a translation vector and SO3 rotation")
    .def(py::init())
    .def(py::init<const Ref<const Matrix<double,7,1>>>())
    .def(py::init<const SE3d &>())
    .def("t", &SE3d::t)
    .def("q", &SE3d::q)
    .def("array", &SE3d::array)
    .def("H", &SE3d::H)
    .def("inverse", &SE3d::inverse)
    .def("invert", &SE3d::invert)
    .def(py::self * py::self)
    .def(py::self * Matrix<double,3,1>())
    .def(py::self + Matrix<double,6,1>())
    .def(py::self - py::self)
    .def_static("hat", &SE3d::hat)
    .def_static("vee", &SE3d::vee)
    .def_static("log", &SE3d::log)
    .def_static("Log", &SE3d::Log)
    .def_static("exp", &SE3d::exp)
    .def_static("Exp", &SE3d::Exp)
    .def("__repr__",
      [](const SE3d &q) {
        std::stringstream ss;
        ss << q;
        return ss.str();
      }
    );
}
