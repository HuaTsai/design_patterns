#include "move_tank_backward.hpp"

MoveTankBackward::MoveTankBackward(std::shared_ptr<Tank> tank) : tank_(tank) {}

void MoveTankBackward::Execute() { tank_->MoveBackward(); }

void MoveTankBackward::Undo() { tank_->MoveForward(); }

std::string MoveTankBackward::name() const { return "MoveTankBackward"; }
