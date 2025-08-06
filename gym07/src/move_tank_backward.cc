#include "move_tank_backward.hpp"

MoveTankBackward::MoveTankBackward(std::shared_ptr<Tank> tank) : tank_(tank) {}

void MoveTankBackward::Execute() { Tank::MoveBackward(); }

void MoveTankBackward::Undo() { Tank::MoveForward(); }

std::string MoveTankBackward::name() const { return "MoveTankBackward"; }
