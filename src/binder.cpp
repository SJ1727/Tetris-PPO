#include <pybind11/pybind11.h>
#include "engine/TetrisEngine.hpp"

namespace py = pybind11;

PYBIND11_MODULE(tetris_engine, m) {
  m.doc() = "Test";

  py::enum_<Move>(m, "Move")
    .value("RIGHT", Move::RIGHT)
    .value("LEFT", Move::LEFT)
    .value("DOWN", Move::DOWN)
    .value("ROTATE_RIGHT", Move::ROTATE_RIGHT)
    .value("ROTATE_LEFT", Move::ROTATE_LEFT)
    .value("DROP", Move::DROP)
    .value("HOLD", Move::HOLD)
    .value("NO_MOVE", Move::NO_MOVE)
    .export_values();

  py::class_<TetrisEngine>(m, "TetrisEngine")
    .def(py::init<>())
    .def("init", &TetrisEngine::Init)
    .def("update", &TetrisEngine::Update)
    .def("set_next_move", &TetrisEngine::SetNextMove)
    .def("get_board_as_string", &TetrisEngine::GetBoardAsString);
}