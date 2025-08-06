#include "move_tank_backward.hpp"

MoveTankBackward::MoveTankBackward(std::shared_ptr<Tank> tank) : tank_(tank) {}

void MoveTankBackward::Execute() { tank_->MoveBackward(); }  // NOLINT(readability-static-accessed-through-instance)

void MoveTankBackward::Undo() { tank_->MoveForward(); }  // NOLINT(readability-static-accessed-through-instance)

std::string MoveTankBackward::name() const { return "MoveTankBackward"; }
