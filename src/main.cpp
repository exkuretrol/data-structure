#include "permutation.hpp"
#include "tower-of-honai.hpp"
#include "magic-square.hpp"
#include "knights-tour.hpp"
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
        .def(py::init<>())
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

    py::class_<KnightsTour>(m, "KnightsTour")
        .def(py::init<int>(), py::arg("size") = 10)
        .def(py::init<int, int, int>(), py::arg("size"), py::arg("x"), py::arg("y"))
        .def("toggle_random", &KnightsTour::toggle_random)
        .def("run", &KnightsTour::run)
        .def("print", &KnightsTour::print)
        .def("get_data", &KnightsTour::get_data);
}