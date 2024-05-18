#include "permutation.hpp"
#include "tower-of-honai.hpp"
#include "magic-square.hpp"
#include "knights-tour.hpp"
#include "singly-circular-linked-list.hpp"
#include "doubly-circular-linked-list.hpp"
#include "linked-stack.hpp"
#include "binary-search-tree.hpp"
#include "heap.hpp"
#include "shortest-path.hpp"
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

    py::class_<BinarySearchTree<int>>(m, "BinarySearchTreeInt")
        .def(py::init<>())
        .def("search", &BinarySearchTree<int>::search)
        .def("search_iter", &BinarySearchTree<int>::search_iter)
        .def("insert", &BinarySearchTree<int>::insert)
        .def("insert_iter", &BinarySearchTree<int>::insert_iter)
        .def("delete", &BinarySearchTree<int>::dewete)
        .def("delete_iter", &BinarySearchTree<int>::dewete_iter)
        .def("empty", &BinarySearchTree<int>::empty)
        .def("print", &BinarySearchTree<int>::print, py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>())
        .def("construct_infix_prefix", &BinarySearchTree<int>::construct_infix_prefix)
        .def("construct_infix_postfix", &BinarySearchTree<int>::construct_infix_postfix);

    py::class_<BinarySearchTree<char>>(m, "BinarySearchTreeChar")
        .def(py::init<>())
        .def("search", &BinarySearchTree<char>::search)
        .def("search_iter", &BinarySearchTree<char>::search_iter)
        .def("insert", &BinarySearchTree<char>::insert)
        .def("insert_iter", &BinarySearchTree<char>::insert_iter)
        .def("delete", &BinarySearchTree<char>::dewete)
        .def("delete_iter", &BinarySearchTree<char>::dewete_iter)
        .def("empty", &BinarySearchTree<char>::empty)
        .def("print", &BinarySearchTree<char>::print, py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>())
        .def("construct_infix_prefix", &BinarySearchTree<char>::construct_infix_prefix)
        .def("construct_infix_postfix", &BinarySearchTree<char>::construct_infix_postfix);

    py::class_<Heap>(m, "Heap")
        .def(py::init<int>())
        .def("insert_heap", &Heap::insert_heap)
        .def("delete_heap", &Heap::delete_heap)
        .def("get_n", &Heap::get_n)
        .def("print", &Heap::print, py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>());

    py::class_<ShortestPath>(m, "ShortestPath")
        .def(py::init<int, int, int, int>(), py::arg("size") = 6, py::arg("range") = 1000, py::arg("threshold") = 1000, py::arg("wall") = 99999)
        .def("set_wall", &ShortestPath::set_wall)
        .def("set_range", &ShortestPath::set_range)
        .def("set_threshold", &ShortestPath::set_threshold)
        .def("toggle_directed", &ShortestPath::toggle_directed)
        .def("get_directed", &ShortestPath::get_directed)
        .def("random_weight_matrix", &ShortestPath::random_weight_matrix)
        .def("dynamic_programming", &ShortestPath::dynamic_programming)
        .def("trace_all_paths", &ShortestPath::trace_all_paths, py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>())
        .def("get_matrix", &ShortestPath::get_matrix)
        .def("print", &ShortestPath::print, py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>());
}