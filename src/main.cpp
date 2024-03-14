#include "permutation.hpp"
#include "tower-of-honai.hpp"
#include "magic-square.hpp"
#include "knights-tour.hpp"
#include "singly-circular-linked-list.hpp"
#include "doubly-circular-linked-list.hpp"
#include "linked-stack.hpp"
#include "binary-search-tree.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>

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

    py::add_ostream_redirect(m, "ostream_redirect");

    py::class_<SinglyCircularLinkedList>(m, "SinglyCircularLinkedList")
        .def(py::init<>())
        .def("insert_front", &SinglyCircularLinkedList::insert_front)
        .def("insert_rear", &SinglyCircularLinkedList::insert_rear)
        .def("insert_after", &SinglyCircularLinkedList::insert_after)
        .def("insert_before", &SinglyCircularLinkedList::insert_before)
        .def("delete_node", &SinglyCircularLinkedList::delete_node)
        .def("delete_front", &SinglyCircularLinkedList::delete_front)
        .def("delete_rear", &SinglyCircularLinkedList::delete_rear)
        .def("delete_after", &SinglyCircularLinkedList::delete_after)
        .def("delete_before", &SinglyCircularLinkedList::delete_before)
        .def("invert", &SinglyCircularLinkedList::invert)
        .def("search_node", &SinglyCircularLinkedList::search_node)
        .def("print_nodes", &SinglyCircularLinkedList::print_nodes, py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>())
        .def("print_detailed_nodes", &SinglyCircularLinkedList::print_detailed_nodes, py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>())
        .def("delete_all_nodes", &SinglyCircularLinkedList::delete_all_nodes);

    py::class_<DoublyCircularLinkedList>(m, "DoublyCircularLinkedList")
        .def(py::init<>())
        .def("insert_front", &DoublyCircularLinkedList::insert_front)
        .def("insert_rear", &DoublyCircularLinkedList::insert_rear)
        .def("insert_after", &DoublyCircularLinkedList::insert_after)
        .def("insert_before", &DoublyCircularLinkedList::insert_before)
        .def("delete_node", &DoublyCircularLinkedList::delete_node)
        .def("delete_front", &DoublyCircularLinkedList::delete_front)
        .def("delete_rear", &DoublyCircularLinkedList::delete_rear)
        .def("delete_after", &DoublyCircularLinkedList::delete_after)
        .def("delete_before", &DoublyCircularLinkedList::delete_before)
        .def("invert", &DoublyCircularLinkedList::invert)
        .def("search_node", &DoublyCircularLinkedList::search_node)
        .def("print_nodes", &DoublyCircularLinkedList::print_nodes, py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>())
        .def("print_detailed_nodes", &DoublyCircularLinkedList::print_detailed_nodes, py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>())
        .def("delete_all_nodes", &DoublyCircularLinkedList::delete_all_nodes);

    py::class_<LinkedStack>(m, "LinkedStack")
        .def(py::init<>())
        .def("push", &LinkedStack::push)
        .def("pop", &LinkedStack::pop)
        .def("print_nodes", &LinkedStack::print_nodes, py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>())
        .def("print_detailed_nodes", &LinkedStack::print_detailed_nodes, py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>());

    py::class_<BinarySearchTree>(m, "BinarySearchTree")
        .def(py::init<>())
        .def("search", &BinarySearchTree::search)
        .def("insert", &BinarySearchTree::insert)
        .def("empty", &BinarySearchTree::empty)
        .def("print", &BinarySearchTree::print, py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>());
}