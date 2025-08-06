#include "move_tank_forward.hpp"

MoveTankForward::MoveTankForward(std::shared_ptr<Tank> tank) : tank_(tank) {}

void MoveTankForward::Execute() { Tank::MoveForward(); }

void MoveTankForward::Undo() { Tank::MoveBackward(); }

std::string MoveTankForward::name() const { return "MoveTankForward"; }
