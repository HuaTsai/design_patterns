#include "move_tank_backward.hpp"

MoveTankBackward::MoveTankBackward(std::shared_ptr<Tank> tank) : tank_(tank) {}

void MoveTankBackward::Execute() { tank_->MoveBackward(); }  // NOLINT

void MoveTankBackward::Undo() { tank_->MoveForward(); }  // NOLINT

std::string MoveTankBackward::name() const { return "MoveTankBackward"; }
