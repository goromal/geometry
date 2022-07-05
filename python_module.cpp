#include <SO2.h>
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
  m.doc() = "Python binding module for SO2/SO3/SE3.";
  
  py::class_<SO2d>(m, "SO2")
    .def_static("random", &SO2d::random)
    .def_static("identity", &SO2d::identity)
    .def_static("fromAngle", &SO2d::fromAngle)
    .def_static("fromR", &SO2d::fromR)
    .def_static("fromTwoUnitVectors", &SO2d::fromTwoUnitVectors)
    .def_static("fromComplex", static_cast<SO2d (*)(const double, const double)>(&SO2d::fromComplex), "Instantiate SO2 from complex number fields")
    .def_static("fromComplex", static_cast<SO2d (*)(const Matrix<double,2,1> &)>(&SO2d::fromComplex), "Instantiate SO2 from a vector of complex number fields")
    .def(py::init())
    .def(py::init<const Ref<const Matrix<double,2,1>>>())
    .def(py::init<const SO2d &>())
    .def("w", static_cast<double& (SO2d::*)(void)>(&SO2d::w), "Write access to w.")
    .def("x", static_cast<double& (SO2d::*)(void)>(&SO2d::x), "Write access to x.")
    .def("array", &SO2d::array)
    .def("normalize", &SO2d::normalize)
    .def("normalized", &SO2d::normalized)
    .def("R", &SO2d::R)
    .def("inverse", &SO2d::inverse)
    .def("invert", &SO2d::invert)
    .def("angle", &SO2d::angle)
    .def(py::self * py::self)
    .def(py::self * Matrix<double,2,1>())
    .def(py::self + Matrix<double,1,1>())
    .def(py::self - py::self)
    .def(py::self * float())
    .def(float() * py::self)
    .def(py::self / float())
    .def_static("hat", &SO2d::hat)
    .def_static("vee", &SO2d::vee)
    .def_static("log", &SO2d::log)
    .def_static("Log", &SO2d::Log)
    .def_static("exp", &SO2d::exp)
    .def_static("Exp", &SO2d::Exp)
    .def("__repr__",
      [](const SO2d &q) {
        return "SO(2): [ " + std::to_string(q.w()) + ", " + std::to_string(q.x()) +
          "i ]";
      }
    );
  
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
    .def("w", static_cast<double& (SO3d::*)(void)>(&SO3d::w), "Write access to w.")
    .def("x", static_cast<double& (SO3d::*)(void)>(&SO3d::x), "Write access to x.")
    .def("y", static_cast<double& (SO3d::*)(void)>(&SO3d::y), "Write access to y.")
    .def("z", static_cast<double& (SO3d::*)(void)>(&SO3d::z), "Write access to z.")
    .def("array", &SO3d::array)
    .def("normalize", &SO3d::normalize)
    .def("normalized", &SO3d::normalized)
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
    .def(py::self * float())
    .def(float() * py::self)
    .def(py::self / float())
    .def_static("hat", &SO3d::hat)
    .def_static("vee", &SO3d::vee)
    .def_static("log", &SO3d::log)
    .def_static("Log", &SO3d::Log)
    .def_static("exp", &SO3d::exp)
    .def_static("Exp", &SO3d::Exp)
    .def("__repr__",
      [](const SO3d &q) {
        return "SO(3): [ " + std::to_string(q.w()) + ", " + std::to_string(q.x()) +
          "i, " + std::to_string(q.y()) + "j, " + std::to_string(q.z()) + "k ]";
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
    .def("t", static_cast<Map<Vector3d>& (SE3d::*)(void)>(&SE3d::t), "Write access to t.")
    .def("q", static_cast<SO3d& (SE3d::*)(void)>(&SE3d::q), "Write access to q.")
    .def("array", &SE3d::array)
    .def("H", &SE3d::H)
    .def("inverse", &SE3d::inverse)
    .def("invert", &SE3d::invert)
    .def(py::self * py::self)
    .def(py::self * Matrix<double,3,1>())
    .def(py::self + Matrix<double,6,1>())
    .def(py::self - py::self)
    .def(py::self * float())
    .def(float() * py::self)
    .def(py::self / float())
    .def_static("hat", &SE3d::hat)
    .def_static("vee", &SE3d::vee)
    .def_static("log", &SE3d::log)
    .def_static("Log", &SE3d::Log)
    .def_static("exp", &SE3d::exp)
    .def_static("Exp", &SE3d::Exp)
    .def("__repr__",
      [](const SE3d &x) {
        return "SE(3): [ " + std::to_string(x.t().x()) + "i, " + std::to_string(x.t().y()) + "j, " +
          std::to_string(x.t().z()) + "k ] [ " + std::to_string(x.q().w()) + ", " + std::to_string(x.q().x()) +
          "i, " + std::to_string(x.q().y()) + "j, " + std::to_string(x.q().z()) + "k ]";
      }
    );
}
