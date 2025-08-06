#include "move_tank_forward.hpp"

MoveTankForward::MoveTankForward(std::shared_ptr<Tank> tank) : tank_(tank) {}

void MoveTankForward::Execute() { tank_->MoveForward(); }  // NOLINT(readability-static-accessed-through-instance)

void MoveTankForward::Undo() { tank_->MoveBackward(); }  // NOLINT(readability-static-accessed-through-instance)

std::string MoveTankForward::name() const { return "MoveTankForward"; }
