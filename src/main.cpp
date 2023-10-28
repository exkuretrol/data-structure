#include "permutation.hpp"
#include "tower-of-honai.hpp"
#include "magic-square.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(homework, m)
{
    py::class_<Permutation>(m, "Permutation")
        .def(py::init<std::string>(), py::arg("input"))
        .def(py::init<int>(), py::arg("length"))
        .def(py::init<>())
        .def("run", &Permutation::run, py::arg("k"))
        .def("toggleTrace", &Permutation::toggleTrace)
        .def("print", &Permutation::print)
        .def("getData", &Permutation::getData);

    py::class_<Honai>(m, "Honai")
        .def(py::init<int>(), py::arg("layer"))
        .def("run", &Honai::run, "Execute Hanoi Tower algorithm",
             py::arg("n"), py::arg("A") = 'A', py::arg("B") = 'B', py::arg("C") = 'C')
        .def("print", &Honai::print, "Print the records")
        .def("getData", &Honai::getData, "Get the records as a list");

    py::class_<MagicSquare>(m, "MagicSquare")
        .def(py::init<int>())
        .def(py::init<int, std::string>())
        .def("run", &MagicSquare::run)
        .def("print", &MagicSquare::print)
        .def("getData", &MagicSquare::getData);
}